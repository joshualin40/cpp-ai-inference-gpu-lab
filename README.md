# C++ AI Inference & GPU Acceleration Lab

**Main application:** C++ Local LLM Inference Workbench  
**Current milestone:** Phase 02 — Building a CLI Application

## Project objective

This repository is being developed incrementally into a C++ application for local large-language-model inference. Planned development includes inference-runtime integration, CPU and GPU execution, benchmarking, and CUDA experiments.

The current application provides a small interactive command-line interface (CLI). It supports `help`, `status`, and `exit`. **No model, inference runtime, CUDA code, or external library is included at this stage.** Future Phases should extend this repository while preserving its project identity and established engineering decisions.

## Prerequisites

- CMake 3.16 or newer.
- A C++ compiler with C++17 support, such as MSVC, GCC, or Clang.
- Git, if you want to initialize and maintain the repository history.

No third-party C++ dependencies are required.

Check the installed tools:

```sh
cmake --version
git --version
```

Check your compiler using the command appropriate to your toolchain:

```sh
# GCC
g++ --version

# Clang
clang++ --version

# MSVC (from a Visual Studio Developer Command Prompt)
cl
```

## Project structure

```text
cpp-ai-inference-gpu-lab/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── src/
│   └── main.cpp
└── docs/
    ├── Phase-01-setup.md
    └── Phase-02-cli.md
```

The repository contains only the files needed by the completed Phases. New directories and modules will be introduced when later features require them.

## Configure

Run this command from the project root:

```sh
cmake -S . -B build
```

CMake detects the available toolchain and generates build files for its selected generator. The command is intentionally portable and does not hardcode compiler paths.

## Build

```sh
cmake --build build --config Release
```

The `--config Release` option supports multi-configuration generators such as Visual Studio. It is harmless for common single-configuration generators; those generators can also select a build type during configuration with `-DCMAKE_BUILD_TYPE=Release`.

## Run

The executable target is named `cpp_local_llm_inference_workbench` (with `.exe` on Windows). Its exact output directory depends on the CMake generator and platform.

**Windows PowerShell — Visual Studio generator:**

```powershell
.\build\Release\cpp_local_llm_inference_workbench.exe
```

**Windows PowerShell — single-configuration generator (for example, Ninja or MinGW Makefiles):**

```powershell
.\build\cpp_local_llm_inference_workbench.exe
```

**Linux or macOS — common single-configuration generators:**

```sh
./build/cpp_local_llm_inference_workbench
```

For a different generator or a custom configuration, locate the executable under the generated `build` directory and run that file.

## Using the CLI

After launching the application, enter a command at the `>` prompt. Commands are case-insensitive, and leading or trailing whitespace is ignored.

| Command | Description |
| --- | --- |
| `help` | Show available commands and their descriptions. |
| `status` | Display the application name, project, development stage, and inference-backend status. |
| `exit` | Exit the application gracefully. |

Empty input is ignored. An unsupported command displays an error and suggests using `help`. If the input stream reaches EOF (for example, when standard input is closed), the application shuts down gracefully.

Example interaction:

```text
Welcome to C++ Local LLM Inference Workbench!

Available commands:
- help
- status
- exit

> help

Available commands:
- help    Show available commands
- status  Display application information
- exit    Exit the application

> status

Application: C++ Local LLM Inference Workbench
Project: C++ AI Inference & GPU Acceleration Lab
Development stage: Phase 02 - Building a CLI Application
Status: Initialized
Inference backend: Not integrated yet

> exit

Shutting down application...
```

## Initialize Git

Run the following from the project root if this repository has not already been initialized:

```sh
git init
git add CMakeLists.txt README.md .gitignore src/main.cpp docs/Phase-01-setup.md docs/Phase-02-cli.md
git commit -m "Build interactive CLI application"
```

Build output is ignored by `.gitignore`. The distributable project ZIP intentionally excludes the `.git` directory.

## Engineering decisions and Phase documentation

The initial tooling and architecture decisions are documented in [docs/Phase-01-setup.md](docs/Phase-01-setup.md). Phase 02's function responsibilities, input handling, command flow, and design trade-offs are documented in [docs/Phase-02-cli.md](docs/Phase-02-cli.md).

The project retains its CMake-based build, C++17 requirement, compiler warning settings, and single executable target. CLI functionality remains in `src/main.cpp` until later requirements justify splitting the implementation into additional source files or modules.
