# Markdown HTML Tags

These tags are parsed by cmarker during `typst` rendering so Markdown stays
readable while Typst handles layout.

## Supported Tags

### convention

Use this for Chapter 2 convention blocks.

```md
<convention id="NC-01" title="Public Function/Type Naming">
**Standard**: ...

**Rationale**: ...
</convention>
```

Attributes:
- `id`: Convention identifier (e.g., `NC-01`)
- `title`: Convention title

### draft

Use this for draft notes in the book.

```md
<draft>
Write your ideas here.
</draft>
```

Attributes:
- none

## Adding New Tags

1. Add an entry in the `html:` mapping in `scripts/build_book.py`.
2. Implement a Typst function in `book/template.typ` that renders the block.
3. Document the new tag and attributes here.
