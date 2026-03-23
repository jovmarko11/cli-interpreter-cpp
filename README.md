This project simulates core concepts of operating system shells, including stream-based execution, piping, and command orchestration.

# CLI Interpreter (C++)

A modular command-line interpreter implemented in C++ as part of the OOP1 course at ETF Belgrade.

## Features

- Command parsing (tokenizer + multi-stage parser)
- Input/output redirection (`<`, `>`, `>>`)
- Pipelines (`|`)
- Modular command system (Command pattern + registry)
- Batch execution from file
- Structured error handling (lexical, syntax, semantic, system)

## Supported Commands

echo, wc, tr, head, tail, batch, help, history, last, prompt, touch, truncate, rm, copy, exec, date, time

## Architecture

The system is organized into clearly separated components:

- **Parser**  
  Transforms raw input into structured commands (`ParsedCommand`, `ParsedPipeline`), handling tokenization, pipes, and redirections.

- **CommandRegistry**  
  Central registry that maps command names to their implementations using factory functions. Enables easy extension without modifying core logic.

- **ExecContext**  
  Shared execution state (streams, history, registry, prompt). Eliminates global state and simplifies communication between components.

- **Engine / LineExecutor**  
  Core execution layer. Determines whether to run a single command or a pipeline and coordinates execution.

- **StreamResolver**  
  Resolves input/output sources (console, file, pipe) and enforces constraints (e.g. no mixing pipe and file input).

## Example

```bash
   time | tr -":" "." | wc -c > out.txt
