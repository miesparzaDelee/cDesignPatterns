<#
.SYNOPSIS
    WSL Bridge for Library Template.
    Wrapper that executes the Linux test runner (run_tests.sh) inside WSL.

.DESCRIPTION
    1. Teleports execution into WSL.
    2. Automatically fixes Windows Line Endings (CRLF) in the .sh script.
    3. Preserves the "Exit 0 on Failure" logic for VS Code Task compatibility.

.EXAMPLE
    .\build\run_tests.ps1 -t clean
#>

param(
    [string]$Distro = "",
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$PassthroughArgs
)

$ErrorActionPreference = "Stop"

# --- 1. Locate Project Root ---
$ScriptDir = Split-Path $MyInvocation.MyCommand.Path
$PotentialRoot = Split-Path $ScriptDir

if (Test-Path "$PotentialRoot\src") {
    Set-Location $PotentialRoot
    $CurrentPath = (Get-Location).Path
    $wslPath = $CurrentPath -replace '\\', '/' -replace 'C:', '/mnt/c'

    $PassthroughArgs += "-w", "$wslPath"
    Write-Verbose "Root detected at: $CurrentPath"
} else {
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

# --- 4. Auto-Detect CPPUTEST_HOME ---
$HasCArg = $PassthroughArgs -match "^-c$"

if (-not $HasCArg -and -not $env:CPPUTEST_HOME) {
    $LinuxUser = (& wsl whoami).Trim()
    $DefaultPath = "/home/$LinuxUser/cpputest"

    $PathExists = & wsl bash -c "test -d '$DefaultPath' && echo 'yes'"

    if ($PathExists -eq "yes") {
        Write-Verbose "Auto-detecting CPPUTEST_HOME as $DefaultPath"
        $PassthroughArgs += "-c", "$DefaultPath"
    }
}

# --- 5. Execution ---
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

$WslExecArgs += "--", "bash", "-l", "-c", $BashCommand

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
