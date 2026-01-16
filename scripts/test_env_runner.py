# scripts/test_env_runner.py
import os
import sys

# Import builder from the same directory
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import builder

# --- CONFIGURATION ---
ROOT_DIR = os.getcwd()
INPUT_FILE = os.path.join(ROOT_DIR, "test_env/book/test_chapter.md")
OUTPUT_FILE = os.path.join(ROOT_DIR, "test_env/book/test_chapter_rendered.md")

def main():
    print("--- Test Environment Runner ---")
    
    if not os.path.exists(INPUT_FILE):
        print(f"Error: {INPUT_FILE} missing.")
        return

    with open(INPUT_FILE, 'r', encoding='utf-8') as f:
        md = f.read()
    
    # Use the logic from builder.py
    new_md = builder.process_markdown_content(md, ROOT_DIR)
    
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        f.write(new_md)
        
    print(f"Success! Output saved to: {OUTPUT_FILE}")

if __name__ == "__main__":
    main()