# Minimum version for cmake compatiblity
cmake_minimum_required(VERSION 3.22)
include(CMakePrintHelpers)
include(FetchContent)
set(CORTEX_TYPE "cm0")
# Set branch names for the sub modules dependencies
set(GITHUB_BRANCH_TOOLCHAIN "HEAD" CACHE STRING "git SHA for CMake Toolchain")
# set the location of all fetched repos
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/_deps")
# show limited messages while cloning git repos
set(FETCHCONTENT_QUIET ON)

cmake_print_variables(GITHUB_BRANCH_TOOLCHAIN)
FetchContent_Declare(
    cmake-toolchains                             # Recommendation: Stick close to the original name.
    GIT_REPOSITORY  git@github.com:kodezine/cmake-toolchains.git
    GIT_TAG         ${GITHUB_BRANCH_TOOLCHAIN}
)

# pre-fetch the toolchain repository as the first job before project configuration
FetchContent_GetProperties(cmake-toolchains)

if(NOT cmake-toolchains_POPULATED)
    FetchContent_Populate(cmake-toolchains)
endif()

project(
    nucleo-f031k6
    VERSION     0.0.1
    LANGUAGES   C ASM CXX
    DESCRIPTION "Hardware Abstraction Layer for STM32CubeXX based project"
)
set(STM32_TYPE "f0")
set(STM32_DEVICE "STM32F031x6")
set(JLINK_DEVICE "STM32F031K6")
set(STM32_HAL_CONFIGURATION "${CMAKE_CURRENT_SOURCE_DIR}/cubemx/Core/Inc/stm32f0xx_hal_conf.h" CACHE STRING "File for configuring the STM32Cube.cmake below" FORCE)

include(${cmake-toolchains_SOURCE_DIR}/frameworks/segger_rtt/segger_rtt.cmake)
include(${cmake-toolchains_SOURCE_DIR}/silicon/st/STM32Cube.cmake)
include(${cmake-toolchains_SOURCE_DIR}/frameworks/lib_QPC.cmake)
include(${cmake-toolchains_SOURCE_DIR}/frameworks/unity/unity.cmake)
include(${cmake-toolchains_SOURCE_DIR}/frameworks/cmock/cmock.cmake)
include(${cmake-toolchains_SOURCE_DIR}/frameworks/unity/target/cortex-m.cmake)
add_subdirectory(cubemx)

#include(cmake/qpc_app.cmake)
add_subdirectory(src/test)