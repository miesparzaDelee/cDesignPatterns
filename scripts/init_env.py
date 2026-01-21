import os
import shutil

# Configuration
ROOT_DIR = os.getcwd() 
TEMPLATE_DIR = os.path.join(ROOT_DIR, "scripts/vscode_templates")
VSCODE_DIR = os.path.join(ROOT_DIR, ".vscode")

# Add extensions.json to this list
FILES_TO_INSTALL = [
    "tasks.json",
    "book.code-snippets",
    "extensions.json",        
    "settings.json"
]

def main():
    print("--- Initializing VS Code Environment ---")
    
    if not os.path.exists(VSCODE_DIR):
        os.makedirs(VSCODE_DIR)
        print(f"Created directory: {VSCODE_DIR}")
    
    for filename in FILES_TO_INSTALL:
        src = os.path.join(TEMPLATE_DIR, filename)
        dst = os.path.join(VSCODE_DIR, filename)
        
        if os.path.exists(src):
            shutil.copy(src, dst)
            print(f"Installed: {filename}")
        else:
            print(f"WARNING: Template not found: {src}")

    print("--- Done. Reload Window to see extension recommendations. ---")

if __name__ == "__main__":
    main()