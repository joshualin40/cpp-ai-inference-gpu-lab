cmake_minimum_required(VERSION 3.16)

project(CppAIInferenceGpuLab VERSION 0.1.0 LANGUAGES CXX)

add_executable(cpp_local_llm_inference_workbench
    src/main.cpp
)

target_include_directories(cpp_local_llm_inference_workbench PRIVATE include)

set_target_properties(cpp_local_llm_inference_workbench PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(cpp_local_llm_inference_workbench PRIVATE
        /W4
        /permissive-
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(cpp_local_llm_inference_workbench PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
