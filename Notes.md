Notes:
- "Ownership and Borrowing Systems (OBS) ensure memory safety and prevent data races 
at compile-time without relying on a garbage collector.""

Thinking about memory in terms of "owners" and "borrowers" was
popularized by Rust, and recently formalized by so-called
Ownership and Borrowing Systems. They are a concrete way to ensure that our
programs do not leak memory or access invalid memory, at the cost of
potentially copying data sometimes that it is not necessary to.

features
- support running concurrent processes.
- scheduling infrastructure + policys
- PCBs
- 'Backgroud mode'
    - approximates the behavior of a bash shell when the `&` modifier is placed after a command.
    - Execution in the background. add the # option to the exec