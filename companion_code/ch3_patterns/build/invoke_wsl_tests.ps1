<#
.SYNOPSIS
    WSL Bridge for Embedded Pattern Library.
    Wrapper that executes the Linux test runner (run_tests.sh) inside WSL.

.DESCRIPTION
    1. Teleports execution into WSL.
    2. Automatically fixes Windows Line Endings (CRLF) in the .sh script.
    3. Preserves the "Exit 0 on Failure" logic for VS Code Task compatibility.
    
.EXAMPLE
    .\build\invoke_wsl_tests.ps1 -t clean
#>

param(
    [string]$Distro = "",            # Optional: Select specific WSL distro (e.g., Ubuntu-20.04)
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$PassthroughArgs       # Catches -t, -b, -c, etc. and sends them to Linux
)

$ErrorActionPreference = "Stop"

# --- 1. Locate Project Root (Hybrid Logic) ---
# We look for the 'src' folder relative to this script to confirm the root.
$ScriptDir = Split-Path $MyInvocation.MyCommand.Path
$PotentialRoot = Split-Path $ScriptDir

if (Test-Path "$PotentialRoot\src") {
    # HAPPY PATH: We found 'src', so we know exactly where we are.
    # We will explicitly tell the Linux script where the workspace is (-w).
    Set-Location $PotentialRoot
    $CurrentPath = (Get-Location).Path
    $wslPath = $CurrentPath -replace '\\', '/' -replace 'C:', '/mnt/c'
    
    # Inject the -w argument into the list
    $PassthroughArgs += "-w", "$wslPath"
    Write-Verbose "Root detected at: $CurrentPath"
} else {
    # FALLBACK: We couldn't find 'src'. 
    # We won't pass -w. We let the .sh script use its own auto-detection.
    Write-Warning "Could not verify 'src' folder. Relying on Linux script auto-detection."
    Set-Location $PotentialRoot
}

# --- 2. Check WSL Availability ---
if (-not (Get-Command wsl -ErrorAction SilentlyContinue)) {
    Write-Error "WSL is not installed or not in your PATH."
    exit 1
}

# --- 3. Sanitize the Linux Script (CRLF Fix) ---
$LinuxScriptRelPath = "./build/run_tests.sh"
$SedArgs = @()
if ($Distro) { $SedArgs += "-d", $Distro }
$SedArgs += "sed", "-i", "'s/\r$//'", $LinuxScriptRelPath

& wsl @SedArgs

# --- 4. Auto-Detect CPPUTEST_HOME (Optional Convenience) ---
# Check if user already passed -c
$HasCArg = $PassthroughArgs -match "^-c$"

# If not passed and not in Env, try to guess it inside Linux
if (-not $HasCArg -and -not $env:CPPUTEST_HOME) {
    # Use 'wsl whoami' to get the real Linux username (handles case sensitivity/differences)
    $LinuxUser = (& wsl whoami).Trim()
    $DefaultPath = "/home/$LinuxUser/cpputest"
    
    # FIX: Send the check logic entirely to Bash so PowerShell doesn't get confused by &&
    $PathExists = & wsl bash -c "test -d '$DefaultPath' && echo 'yes'"
    
    if ($PathExists -eq "yes") {
        Write-Verbose "Auto-detecting CPPUTEST_HOME as $DefaultPath"
        $PassthroughArgs += "-c", "$DefaultPath"
    }
}

# --- 5. Execution ---
# Join arguments but ensure multi-word arguments are quoted for Bash
$LinuxArgsArray = @()
foreach ($arg in $PassthroughArgs) {
    if ($arg -match '\s') {
        $LinuxArgsArray += "'$arg'"
    } else {
        $LinuxArgsArray += $arg
    }
}
$LinuxArgsString = $LinuxArgsArray -join " "
$BashCommand = "$LinuxScriptRelPath $LinuxArgsString"

$WslExecArgs = @()
if ($Distro) { $WslExecArgs += "-d", $Distro }

# CRITICAL: Use Login Shell (-l) to ensure .bashrc is loaded
$WslExecArgs += "--", "bash", "-l", "-c", $BashCommand

# Run the command.
& wsl @WslExecArgs

# --- 6. Exit Code Handling ---
$ExitCode = $LASTEXITCODE

if ($ExitCode -eq 0) {
    exit 0
} elseif ($ExitCode -eq 1) {
    Write-Warning "Unit Tests Failed (Exit Code 1). Returning 0 for IDE compatibility."
    exit 0
} else {
    Write-Error "Script failed with error code $ExitCode"
    exit $ExitCode
}
