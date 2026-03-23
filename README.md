# CLI Interpreter (C++)

This project simulates core concepts of operating system shells, including stream-based execution, piping, and command orchestration.

A modular command-line interpreter implemented in C++ as part of the OOP1 course at ETF Belgrade.

---

## Features

- Multi-stage command parsing (tokenizer + structured parser)
- Input/output redirection (`<`, `>`, `>>`)
- Pipeline execution (`|`)
- Modular command system (Command pattern + registry)
- Batch execution from file
- Structured error handling (lexical, syntax, semantic, system)

---

## Supported Commands

echo, wc, tr, head, tail, batch, help, history, last, prompt, touch, truncate, rm, copy, exec, date, time

---

## Architecture

The system is designed with a clear separation of concerns and modular components:

- **Parser**  
  Converts raw input into structured representations (`ParsedCommand`, `ParsedPipeline`), handling tokenization, pipes, and redirections.

- **CommandRegistry**  
  Maps command names to their implementations using factory functions, enabling extensibility without modifying core logic.

- **ExecContext**  
  Shared execution state (streams, history, registry, prompt), avoiding global state and simplifying communication between components.

- **Engine / LineExecutor**  
  Core execution layer responsible for coordinating single command execution and pipelines.

- **StreamResolver**  
  Determines input/output sources (console, file, pipe) and enforces semantic constraints.

---

## Example

```bash
$ time | tr -":" "." | wc -c > out.txt
