# Phase 01 — Project Setup & Development Environment

## Scope

This Phase creates the foundation for the **C++ AI Inference & GPU Acceleration Lab** and its main application, **C++ Local LLM Inference Workbench**. It intentionally contains one executable and no inference, model-loading, GPU, or external-library implementation.

## Initial decisions

### CMake as the build system

CMake describes the project and generates native build-system files for the developer's chosen toolchain. It supports common environments such as Visual Studio, Ninja, and Make-based generators, allowing the project definition to remain largely independent of one IDE or operating system.

Alternatives considered:

- **Direct compiler commands:** useful for a tiny experiment, but become harder to maintain as source files, configurations, and platform differences grow.
- **A hand-written Makefile:** a reasonable option on Make-oriented systems, but less convenient as the sole cross-platform project definition, especially for Visual Studio users.
- **Meson:** also a capable modern build system, but CMake was selected for its broad adoption in C++ libraries and tooling likely to be encountered later.

### C++17

C++17 is a widely supported modern C++ standard and is sufficient for the initial application. Requiring it explicitly gives the project a predictable language baseline without adopting a newer standard before a concrete feature needs it. Compiler-specific language extensions are disabled so the code is built as standard C++17.

C++20 was not selected because this Phase does not need its additional language features. The standard can be reconsidered later if a requirement justifies changing the project baseline.

### One executable

The application currently has one small entry point, so a single executable target is the simplest accurate representation. Separate libraries, interfaces, and architectural layers would add structure without solving a current problem. They can be introduced when the implementation grows.

### `main.cpp` responsibilities

`src/main.cpp` contains the program entry point. It prints the project name, current development stage, environment initialization status, and the fact that no inference runtime is integrated. It returns `EXIT_SUCCESS`. It does not own build configuration or future inference responsibilities.

## Build concepts

- **Source code:** human-readable program instructions, such as `src/main.cpp`.
- **Compilation:** the compiler translates source code into lower-level object code (often through preprocessing and compilation/assembly stages). Object files are not usually standalone applications.
- **Linking:** the linker combines object files and required libraries, resolves references between them, and produces the final executable or library.
- **Executable:** the program file the operating system can load and run.

For this project, CMake coordinates the configure and build process; the selected compiler toolchain performs compilation and invokes or works with the linker.

## IDE, compiler, and build system

- **IDE (Integrated Development Environment):** the application used to edit, navigate, and debug code, such as Visual Studio or VS Code. An IDE may integrate with the other tools, but it is not itself the C++ language compiler.
- **Compiler toolchain:** translates C++ source code and participates in producing machine code. Examples include MSVC, GCC, and Clang, normally paired with a platform linker and other toolchain utilities.
- **Build system:** describes dependencies and the steps needed to produce targets. CMake generates build files for a native build tool such as Ninja, Make, or the Visual Studio build system; that tool then runs the necessary compiler and linker commands.

These roles can be integrated into one user workflow, but they are separate responsibilities.

## Compiler warnings

The executable enables `/W4` and `/permissive-` for MSVC, and `-Wall`, `-Wextra`, and `-Wpedantic` for GCC and Clang-family compilers. Warnings are enabled without treating every warning as an error, avoiding an unnecessarily brittle initial build across compiler versions.

## Repository continuity

The initial target name, project identity, C++17 baseline, and CMake-based build are the starting conventions for subsequent Phases. Later work should modify and extend this repository rather than recreate it. Dependencies and new directories should be added only when a milestone requires them.
