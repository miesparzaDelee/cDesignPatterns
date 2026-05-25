# Markdown HTML Tags

These tags are parsed by cmarker during `typst` rendering and can also be
styled directly by EPUB/CSS tooling because they use standard HTML elements.

## Supported Tags

Custom book sections should use standard HTML `aside` blocks with a class that
names the semantic role. This keeps the source Markdown usable by both renderers:

- PDF: `scripts/build_book.py` maps `aside` blocks to `book/template.typ`.
- EPUB: `scripts/build_epub.py` passes the same blocks to Pandoc, with styles in
  `book/epub.css` and generated headings in `scripts/epub_callouts.lua`.

### convention

Use this for Chapter 2 convention blocks.

```md
<aside class="convention" id="NC-01" data-title="Public Function/Type Naming">
**Standard**: ...

**Rationale**: ...
</aside>
```

Attributes:
- `id`: Convention identifier (e.g., `NC-01`)
- `data-title`: Convention title

### draft

Use this for draft notes in the book.

```md
<aside class="draft">
Write your ideas here.
</aside>
```

Attributes:
- `class`: Must be `draft`

### note

Use this for general explanatory callouts that are not formal conventions.

```md
<aside class="note" data-title="Convention Format">
Content goes here.
</aside>
```

Attributes:
- `class`: Must be `note`
- `data-title`: Note title

## Adding New Tags

Use `aside` classes for new cross-format sections. Avoid inventing new raw HTML
tags such as `<warning>` or `<highlight>` because EPUB readers expect valid XHTML
and may reject non-standard or malformed tags.

1. Choose the source Markdown shape, normally `<aside class="name" data-title="Title">`.
2. Document the class, purpose, and attributes in this file.
3. Add PDF rendering in `book/template.typ` by extending `callout(...)`.
4. Add EPUB styling in `book/epub.css`.
5. If the title or header must be real EPUB content, add it in `scripts/epub_callouts.lua` instead of relying only on CSS `::before`.
6. Verify with `py -3 scripts/build_book.py`, `typst compile --root . build/main.typ build/main.pdf`, and `py -3 scripts/build_epub.py`.
