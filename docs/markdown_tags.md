# Markdown HTML Tags

These tags are parsed by cmarker during `typst` rendering and can also be
styled directly by EPUB/CSS tooling because they use standard HTML elements.

## Supported Tags

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

## Adding New Tags

1. Add or extend an `aside` class handled by the `html:` mapping in `scripts/build_book.py`.
2. Implement a Typst function in `book/template.typ` that renders the class.
3. Document the new tag and attributes here.
