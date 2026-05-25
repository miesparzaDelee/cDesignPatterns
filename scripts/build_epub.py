import os
import subprocess
import sys

sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import build_book


OUTPUT_FILE = os.path.join(build_book.BUILD_DIR, "EmbeddedModularDevelopment.epub")
EPUB_CSS = os.path.join(build_book.SOURCE_DIR, "epub.css")
CALLOUT_FILTER = os.path.join(os.path.dirname(os.path.abspath(__file__)), "epub_callouts.lua")


def build_epub():
    structure_items = build_book.get_structure()
    chapter_paths = [
        os.path.join(build_book.BUILD_DIR, item["file"])
        for item in structure_items
    ]

    missing = [path for path in chapter_paths if not os.path.exists(path)]
    if missing:
        missing_list = "\n".join(missing)
        raise FileNotFoundError(
            "Hydrated Markdown is missing. Run scripts/build_book.py first.\n"
            f"Missing files:\n{missing_list}"
        )

    command = [
        "pandoc",
        *chapter_paths,
        "--from",
        "markdown+raw_html",
        "--to",
        "epub3",
        "--toc",
        "--metadata",
        f"title={build_book.BOOK_TITLE}",
        "--metadata",
        f"author={build_book.BOOK_AUTHOR}",
        "--css",
        EPUB_CSS,
        "--lua-filter",
        CALLOUT_FILTER,
        "--highlight-style",
        "tango",
        "--output",
        OUTPUT_FILE,
    ]

    subprocess.run(command, check=True)
    return OUTPUT_FILE


def main():
    print("--- C Book EPUB Builder ---")
    try:
        output_file = build_epub()
        print(f"EPUB written to {output_file}")
    except subprocess.CalledProcessError as exc:
        print(f"[ERROR] Pandoc failed with exit code {exc.returncode}")
        sys.exit(exc.returncode)
    except Exception as exc:
        print(f"[ERROR] {exc}")
        sys.exit(1)


if __name__ == "__main__":
    main()
