# Recommended Practices and Conventions

The recommended practices and proposed coding and development conventions detailed in this book are purely pragmatic.
They were gathered and refined through years of professional experience, evolving through a process of natural selection.
Practices that provided clear value remained part of our workflow.
Conversely, those that demanded more effort than the benefit they ultimately provided naturally fell out of use.
During this exploratory period, numerous approaches were tested, adopted, or discarded.
Most derive from gold-standard literature and established conventions in the embedded software world.
Others have been adapted or evolved specifically to support the modular framework presented here.

Using the right tools and strict conventions is critical to the success of the modular approach presented.
We group these practices into four main categories, narrowing our focus to what matters most for embedded modularity.
First, coding standards and conventions—covering file organization, naming, code structure, and documentation—ensure consistency and prevent common pitfalls across the codebase.
Second, hardware emulation approaches allow us to develop and verify logic without constant access to physical boards.
This is often the most challenging aspect of embedded modularization, but special techniques make it manageable.
By leveraging these techniques, we aim to spend as much time as possible in the development environment.
Debugging and testing on the host significantly speeds up the development cycle compared to testing on real hardware.
Third, debug modules and testing strategies enable us to isolate components and verify them continuously.

It is important to note that these are recommendations, not immutable laws.
We try to follow them strictly throughout this book to demonstrate their effectiveness within the EMoD framework.
We encourage the reader to identify how these practices are applied in the chapters that follow.
However, in different contexts or legacy environments, strict adherence might not always be possible or beneficial.

<highlight title = Convention Format>

Throughout this chapter, standards are presented as distinct "Convention" blocks for easy reference. Each block contains:

* **ID**: A unique identifier (e.g., `FO-01`) for referencing in code reviews.
* **Standard**: The rule itself.
* **Rationale**: The "why" behind the rule. Understanding the reason is more important than memorizing the rule; if the rationale no longer applies, the rule should be revisited.

</highlight>
