# Phase 02 — Building a CLI Application

## Scope

This Phase extends the existing **C++ Local LLM Inference Workbench** executable with an interactive command-line interface. The application accepts `help`, `status`, and `exit` commands. It continues running until the user exits or standard input reaches end-of-file (EOF). The project remains on C++17, retains its existing CMake target, and has no external dependencies or inference backend.

## Application functions and separation of responsibilities

The implementation keeps its functions in `src/main.cpp`, but gives each function one clear responsibility:

- `main()` is the program entry point. It delegates the interactive work to `runApplication()` and returns a successful exit code.
- `printWelcomeMessage()` prints the initial greeting and short command list.
- `printHelp()` prints command names and descriptions.
- `printStatus()` reports the application identity, project, current development stage, and inference-backend status.
- `handleCommand()` normalizes and processes one input line. Its boolean result indicates whether the application should continue.
- `runApplication()` owns the input loop, displays the prompt, reads input, and stops when the command handler requests exit or input reaches EOF.
- `trim()` removes leading and trailing whitespace, while `normalizeCommand()` also converts the command to lowercase.

Dividing the work into functions makes each behavior easier to read, test, and change independently. It also keeps `main()` small. The trade-off is a few additional function definitions, which is worthwhile even for this small interface because command behavior is already distinct from the application loop and output formatting.

## Reading complete input lines with `std::getline()`

The application uses `std::getline(std::cin, input)` to read one complete line into a `std::string`.

This is preferable to `std::cin >> input` here because formatted extraction stops at the first whitespace character. `std::getline()` captures the whole line, allowing the program to handle leading and trailing spaces consistently and making it straightforward to treat a blank line as empty input. This interface currently accepts single-word commands, but line-based input provides a clean foundation for future commands that may accept arguments.

When `std::getline()` returns false, the loop recognizes that input is no longer available. It prints a shutdown message and leaves the loop instead of repeatedly attempting to read from a failed stream.

## Command-processing flow

For each iteration, `runApplication()` displays `> ` and reads a line. `handleCommand()` then:

1. Trims whitespace from both ends of the input.
2. Converts the remaining command to lowercase using character-safe calls to `std::tolower()`.
3. Treats an empty result as a no-op and continues the application.
4. Calls the corresponding output function for `help` or `status`.
5. Prints a shutdown message and returns `false` for `exit`.
6. Prints an informative error and help hint for any unsupported command.

For all commands other than `exit`, the handler returns `true`. The loop therefore continues until the user explicitly exits or EOF is detected. Normalizing case and whitespace gives users a more forgiving interface; validating the normalized command prevents unsupported input from being mistaken for a valid operation.

## Why a loop is necessary

A command-line workbench is interactive: one launch should support multiple commands rather than print information and immediately terminate. The application loop provides that repeated interaction. It has two explicit termination paths: the `exit` command and a failed line read caused by EOF or another input-stream failure.

## Why conditional command handling is sufficient

A small `if` / `else if` chain is clear and proportionate for three commands. It makes the command set and each behavior easy for a junior developer to follow, without introducing registration machinery or indirection. As the command set grows, the handler can be reorganized while preserving the input loop and individual command functions.

Possible alternatives include:

- **Command-pattern architecture:** each command could become an object with a shared interface. This can help when commands have substantial state, dependencies, or independently configurable behavior, but would be unnecessary overhead for three simple actions.
- **A command table or map:** command names could map to function handlers. This can be useful for a larger set of uniform commands, although it introduces lookup and function-pointer or callable-type concepts that are not currently needed.
- **A CLI parsing library:** libraries can provide structured options, flags, arguments, and generated help for applications with command-line arguments or complex syntax. This application currently reads a few interactive words and does not need an external dependency.

## Why no additional classes or dependencies are introduced

The current workflow has no persistent domain objects, complex ownership, or independent subsystems that require classes. Free functions and standard-library types express the requirements directly. Avoiding premature abstractions keeps the code easier to understand and reduces the maintenance burden. This is a current-scope decision, not a rule against classes: later Phases can introduce types when they model real responsibilities or improve ownership and interfaces.

## Extension path

Future Phases can add commands by extending `handleCommand()` and adding focused functions for the new behavior. When the implementation becomes larger or needs reusable components, the functions can be moved into dedicated source and header files without changing the CMake target or the user-facing command contract. More advanced argument parsing, command registration, application state, and inference operations should be introduced only when a concrete milestone requires them.

## Preserved project decisions

Phase 02 preserves the Phase 01 CMake minimum version, project name, executable target, C++17 requirement, disabled compiler extensions, and compiler warning configuration. The original [Phase 01 setup documentation](Phase-01-setup.md) remains intact. No Python, PyTorch, Transformers, CUDA, llama.cpp, model files, inference libraries, or third-party C++ dependencies are introduced.
