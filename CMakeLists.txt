cmake_minimum_required(VERSION 3.14)

enable_language(CXX)

if (NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR NOT "${CMAKE_CXX_COMPILER_VERSION}" VERSION_GREATER_EQUAL 4)
    message(FATAL_ERROR "This project requires clang >= 4 to build.")
endif ()

find_program(CPP_FILT NAMES c++filt)

if ("${CPP_FILT}" STREQUAL "CPP_FILT-NOTFOUND")
    message(FATAL_ERROR "This project requires the c++filt binary in $PATH.")
endif ()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

project(cpp-llvm-coverage LANGUAGES CXX VERSION 0.1.0)

add_executable(cpp-llvm-coverage src/main.cpp src/util.cpp)

add_executable(cpp-llvm-coverage-tests src/util.cpp src/tests/test_util.cpp)

target_compile_options(cpp-llvm-coverage-tests PRIVATE "-fprofile-instr-generate=$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/cpp-llvm-coverage.profraw" "-fcoverage-mapping")
target_link_options(cpp-llvm-coverage-tests PRIVATE "-fprofile-instr-generate=$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/cpp-llvm-coverage.profraw")

if ("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Linux")
    set(LLVM_PROFDATA "${CMAKE_SOURCE_DIR}/tools/code_coverage/llvm_coverage_linux_x64/bin/llvm-profdata")
    set(LLVM_COV "${CMAKE_SOURCE_DIR}/tools/code_coverage/llvm_coverage_linux_x64/bin/llvm-cov")
elseif ("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Darwin")
    set(LLVM_PROFDATA "${CMAKE_SOURCE_DIR}/tools/code_coverage/llvm_coverage_macos_x64/bin/llvm-profdata")
    set(LLVM_COV "${CMAKE_SOURCE_DIR}/tools/code_coverage/llvm_coverage_macos_x64/bin/llvm-cov")
endif ()

add_custom_target(coverage-report
    COMMAND "${CMAKE_COMMAND}" -E remove "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/cpp-llvm-coverage.profraw"
    COMMAND "${CMAKE_COMMAND}" -E remove "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/cpp-llvm-coverage.profdata"
    COMMAND "${CMAKE_COMMAND}" -E remove "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/args.gn"
    COMMAND "${CMAKE_COMMAND}" -E echo "use_clang_coverage = true" > "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/args.gn"
    COMMAND "$<TARGET_FILE:cpp-llvm-coverage-tests>"
    COMMAND "${LLVM_PROFDATA}" merge -sparse "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/cpp-llvm-coverage.profraw" -o "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/cpp-llvm-coverage.profdata"
    COMMAND "${CMAKE_SOURCE_DIR}/tools/code_coverage/coverage.py" --no-component-view -p "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/cpp-llvm-coverage.profdata" -b "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>" "$<TARGET_FILE:cpp-llvm-coverage-tests>" -o "$<TARGET_FILE_DIR:cpp-llvm-coverage-tests>/coverage" -i "'.*src/tests/.*'"
    DEPENDS cpp-llvm-coverage-tests
    )
