project(
    coreMx
    VERSION     0.0.1
    LANGUAGES   C ASM CXX
    DESCRIPTION "Cube MX project"
)
if(NOT (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm"))
    message(FATAL_ERROR "${PROJECT_NAME} can only compile with a suitable ARM cross compiler; no target build.")
endif()
if(NOT DEFINED STM32_DEVICE)
    message(FATAL_ERROR "${PROJECT_NAME} can only compile with a STM32 device definition")
endif()
set (ARMCMSIS_DEVICE "ARM$ENV{CORTEX_TYPE}")
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CMakePrintHelpers)

add_library(${PROJECT_NAME} STATIC)
add_library(${PROJECT_NAME}::framework ALIAS ${PROJECT_NAME})

# USE OF GLOB TO MAKE IT USEFUL FOR FUTURE
file(GLOB CUBEMX_CORE_SOURCES ${CMAKE_CURRENT_LIST_DIR}/Core/Src/*.c)
file(GLOB ${PROJECT_NAME}_PUBLIC_HEADERS ${CMAKE_CURRENT_LIST_DIR}/Core/Inc/*.h)

# exclude all templates from the library
list(FILTER CUBEMX_CORE_SOURCES EXCLUDE REGEX "template")
list(FILTER CUBEMX_CORE_SOURCES EXCLUDE REGEX "ll")
list(FILTER CUBEMX_CORE_SOURCES EXCLUDE REGEX "main")
list(FILTER ${PROJECT_NAME}_PUBLIC_HEADERS EXCLUDE REGEX "template")
list(FILTER ${PROJECT_NAME}_PUBLIC_HEADERS EXCLUDE REGEX "ll")

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CUBEMX_CORE_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${cmsis-v5_SOURCE_DIR}/include/cmsis-v5
        ${cubemx_SOURCE_DIR}/include/cubemx
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../cubemx/Core/Inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    USE_HAL_DRIVER
    USE_FULL_LL_DRIVER
    ${STM32_DEVICE}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        C_STANDARD          11
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS        OFF
        PUBLIC_HEADER       "${${PROJECT_NAME}_PUBLIC_HEADERS}"
        EXPORT_NAME         framework
)

write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake
    VERSION       ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
    cmsis-v5
    PUBLIC
        cubemx
)

setTargetCompileOptions(PROJECT_NAME)

# CPACK begins here
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
set(CPACK_BINARY_7Z ON)
set(CPACK_BINARY_NSIS OFF)
include(CPack)
