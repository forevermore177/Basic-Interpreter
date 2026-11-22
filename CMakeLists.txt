cmake_minimum_required(VERSION 3.10)
project(BasicInterpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# AddressSanitizer 开关
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

include_directories(include)

set(SOURCES
src/Basic.cpp
src/Expression.cpp
src/Lexer.cpp
src/Parser.cpp
src/Program.cpp
src/Recorder.cpp
src/Statement.cpp
src/Token.cpp
src/VarState.cpp
src/utils/Error.cpp
)

add_executable(code ${SOURCES})

if(ENABLE_ASAN)
    target_compile_options(code PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
    )
    target_link_options(code PRIVATE
        -fsanitize=address
    )
endif()

add_executable(attached_test AttachedTest.cpp)
add_executable(scope_test ScopeTest.cpp)