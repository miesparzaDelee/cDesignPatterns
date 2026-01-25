# C Design Patterns: A Literate Programming Project

This repository contains the source code and manuscript for the book **"C Design Patterns"**.

It uses a custom **Literate Programming** build system where the C source code (`src/`) is automatically injected into the Markdown chapters (`book/`) during the build process. This ensures that every code snippet in the book is compilable, testable, and always up-to-date.

## 📂 Repository Structure

* **`book/`**: The manuscript content.
    * `*.md`: Chapters written in Markdown. Use `{{ file "path/to/code.c" }}` to inject code.
    * `structure.txt`: Defines the order and hierarchy of chapters.
    * `template.typ`: The Typst styling template for the PDF.
* **`src/`**: The actual C source code.
    * Standard C project structure (`.c`, `.h`).
* **`scripts/`**: The build tools and automation logic.
    * See [`scripts/README.md`](scripts/README.md) for technical details on the builder.
* **`build/`**: (Git-ignored) The output directory.
    * Contains hydrated Markdown files (for EPUB/Web) and `main.typ` (for PDF).
* **`vscode_templates/`**: Configuration files to standardize the VS Code environment.

---

## 🚀 Quick Start

### 1. Prerequisites
* **Python 3.x** (No external dependencies required).
* **VS Code** (Recommended editor).
* **Typst** (Required for PDF generation).

### 2. Environment Setup
If you have just cloned this repo, run the initialization script to configure your editor:

```bash
python scripts/init_env.py
```

* This installs recommended VS Code tasks, snippets, and settings.
* **Action:** When VS Code asks *"Do you want to install the recommended extensions?"*, click **Install**.

### 3. The Workflow

**A. Editing Content**
* Write your chapters in `book/`.
* Write your code in `src/`.
* To include code in a chapter, use the snippet: `{{ file "src/driver/spi.c" }}`.

**B. Building the Book**
You have two options:
1.  **Manual:** Run the build script in the terminal:
    ```bash
    python scripts/build_book.py
    ```
2.  **Automatic (VS Code):** Just save any `.md`, `.c`, or `.typ` file. The "Trigger Task on Save" extension will rebuild the book in the background.

**C. Previewing**
* Open `build/main.typ` in VS Code.
* Click the **Typst Preview** button (Eye icon).
* Keep this window open; it updates live as you save.

**D. Rendering the PDF**
Use the VS Code "Build Book PDF" task or run manually:

```bash
typst compile --root . build/main.typ build/main.pdf
```

---

## 🧪 Running Unit Tests

The companion code includes unit tests for the design patterns implemented in `companion_code/ch3_patterns/`. Tests use the CppUTest framework.

### Prerequisites
- WSL (Windows Subsystem for Linux) or a Linux environment
- CppUTest installed (auto-detected in WSL)

### Running Tests
Use the VS Code "Test Patterns" task, or run manually:

```bash
# Run all tests
powershell -ExecutionPolicy Bypass -File companion_code/ch3_patterns/scripts/invoke_wsl_tests.ps1
```

## ⚙️ Configuration

### Changing Book Metadata
To change the Title or Author, edit the configuration block at the top of:
* `scripts/build_book.py`

### Changing Chapter Order
To add, remove, or reorder chapters, edit:
* `book/structure.txt`

**Format:**
```text
chapter1.md       # New Page (Chapter)
chapter2.md
  section2_1.md   # Indented = Continuous flow (Section)
# draft.md        # Commented out = Ignored
```

### Changing Visual Style
To modify fonts, margins, or colors, edit:
* `book/template.typ`

### Markdown Extensions
We support custom HTML tags in Markdown (e.g., `<convention>` and `<draft>`) so
contributors can keep prose readable while Typst applies styling. See
`docs/markdown_tags.md` for the supported tags and how to add new ones.

---

## 🛠 Extension Recommendations

This project relies on specific VS Code extensions for the best experience. The `extensions.json` file recommends:
1.  **Tinymist** (Typst preview and language support).
2.  **Trigger Task on Save** (Automates the build loop).
3.  **Path Autocomplete** (Helps find C files when writing injection tags).

---

## 📄 Output Formats

The build process generates two distinct artifacts in the `build/` folder:
1.  **Universal Markdown (`build/*.md`):** Standard Markdown files with all C code fully expanded. Ideal for converting to EPUB, HTML, or importing into Obsidian.
2.  **PDF Document (`build/main.typ`):** A Typst wrapper that renders the professional PDF.
