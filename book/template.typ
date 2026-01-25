// book/template.typ

#let draft(body) = {
  block(
    fill: rgb("#f5feff"), // Light Red Background
    stroke: (left: 4pt + rgb("#31b2bb")), // Red Border
    inset: 16pt,
    radius: 4pt,
    width: 100%,
    [*PARAGRAPH:* #body], // Automatically adds bold "DRAFT" label
  )
}

#let convention(id: "", title: "", body) = {
  let primary-color = rgb("#0056b3") // Professional Blue
  let bg-color = rgb("#f0f7ff") // Very Light Blue
  let border-color = primary-color.lighten(30%)

  // The Container
  block(
    width: 100%,
    stroke: 1pt + border-color,
    radius: 4pt,
    clip: true, // Ensures the header background respects the border radius
    below: 2em,
    stack(
      dir: ttb,

      // Header Section
      block(
        width: 100%,
        fill: primary-color,
        inset: (x: 12pt, y: 8pt),
        stack(
          dir: ltr,
          spacing: 12pt,
          // ID Pill
          box(
            fill: white,
            radius: 3pt,
            inset: (x: 6pt, y: 3pt),
            text(fill: primary-color, weight: "bold", size: 0.9em, id),
          ),
          // Title
          align(horizon, text(fill: white, weight: "bold", size: 1em, title)),
        ),
      ),

      // Body Section
      block(
        width: 100%,
        fill: bg-color,
        inset: 16pt,
        body,
      ),
    ),
  )
}

#let project(title: "", authors: (), body) = {
  // --- 1. Page Setup ---
  set page(
    paper: "us-letter",
    margin: (x: 1in, y: 1in, top: 1in, bottom: 1in),
    // REMOVED: numbering: "1" (for pages is fine, but we kept it simple)
    numbering: "1",

    header: context {
      let page-num = counter(page).get().first()
      if page-num > 1 {
        set text(size: 9pt, style: "italic", fill: luma(100))
        stack(dir: ltr, spacing: 1fr, title, str(page-num))
        line(length: 100%, stroke: 0.5pt + luma(200))
      }
    },
  )

  set text(font: "Times New Roman", size: 11pt, lang: "en")
  set par(justify: true, leading: 0.65em)

  // --- 2. NO NUMBERING ---
  // We set this to none so Typst doesn't add "1.", "1.1", etc.
  set heading(numbering: none)

  // --- 3. Heading Styling ---
  show heading.where(level: 1): it => {
    pagebreak(weak: true)
    v(2em)
    set text(size: 18pt, weight: "bold", fill: rgb("#2c3e50"))
    block(it)
    v(1em)
    line(length: 100%, stroke: 1pt + rgb("#2c3e50"))
    v(1em)
  }

  show heading.where(level: 2): it => {
    v(1em)
    set text(size: 14pt, weight: "semibold", fill: rgb("#34495e"))
    block(it)
    v(0.5em)
  }

  // --- 4. Code Blocks ---
  show raw: it => {
    if it.block {
      block(
        fill: rgb("#f4f6f8"),
        inset: 12pt,
        radius: 5pt,
        width: 100%,
        stroke: 0.5pt + luma(200),
        text(font: "Consolas", size: 9pt, it),
      )
    } else {
      box(fill: luma(240), inset: (x: 3pt), radius: 2pt, text(font: "Consolas", size: 9pt, it))
    }
  }

  // --- 5. Title Page ---
  align(center + horizon)[
    #v(2em)
    #rect(inset: 2em, stroke: 2pt + rgb("#2c3e50"), radius: 1em)[
      #text(2.5em, weight: 800, fill: rgb("#2c3e50"), title)
    ]
    #v(3em)
    #text(1.4em, style: "italic", authors.join(", "))
    #v(2em)
    #line(length: 50%, stroke: 0.5pt)
    #v(1em)
    #text(1em, datetime.today().display("[month repr:long] [day], [year]"))
  ]
  pagebreak()

  body
}
