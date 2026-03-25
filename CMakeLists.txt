cmake_minimum_required(VERSION 3.10)
project(GenAI_SDV_SoA)

set(CMAKE_CXX_STANDARD 17)

add_executable(genai_tool
    src/main.cpp
    src/PromptBuilder.cpp
    src/ServiceGenerator.cpp
    src/GenAIClient.cpp
)
