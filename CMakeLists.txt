cmake_minimum_required(VERSION 3.15)
project(numen
    VERSION 1.0.0
    DESCRIPTION "Numen - Linear Algebra and Calculus library written in C"
    LANGUAGES C CXX
)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_STATIC_LIBS "Build static libraries" ON)
option(BUILD_TESTING "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(INSTALL_SYSTEM_WIDE "Install system-wide" ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall -Wextra -pedantic -pipe -g
        -D_FORTIFY_SOURCE=2 -D_GNU_SOURCE -fstack-protector-all
    )
endif()

file(GLOB_RECURSE LIB_SOURCES
    "src/*.c"
    "utils/*.c"
)

add_library(numen_interface INTERFACE)
target_include_directories(numen_interface INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utils>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(BUILD_SHARED_LIBS)
    add_library(numen_shared SHARED ${LIB_SOURCES})
    target_link_libraries(numen_shared PUBLIC numen_interface m)
    set_target_properties(numen_shared PROPERTIES
        OUTPUT_NAME "numen"
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
    )
endif()

if(BUILD_STATIC_LIBS)
    add_library(numen_static STATIC ${LIB_SOURCES})
    target_link_libraries(numen_static PUBLIC numen_interface m)
    set_target_properties(numen_static PROPERTIES
        OUTPUT_NAME "numen"
    )
    if(WIN32)
        set_target_properties(numen_static PROPERTIES OUTPUT_NAME "numen_s")
    endif()
endif()

if(INSTALL_SYSTEM_WIDE)
    include(GNUInstallDirs)

    install(TARGETS numen_interface numen_shared numen_static
        EXPORT numen-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/numen)
    install(DIRECTORY utils/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/numen/utils)

    install(EXPORT numen-targets
        FILE numen-config.cmake
        NAMESPACE numen::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/numen
    )
endif()

if(BUILD_TESTING)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(gtest)

    file(GLOB TEST_SOURCES "tests/*.cpp")

    if(TEST_SOURCES)
        add_executable(numen_tests ${TEST_SOURCES})

        if(BUILD_SHARED_LIBS)
            target_link_libraries(numen_tests PRIVATE numen_shared)
        else()
            target_link_libraries(numne_tests PRIVATE numen_static)
        endif()

        target_link_libraries(numen_tests PRIVATE gtest)
        target_include_directories(numen_tests PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/utils
        )

        add_test(NAME numen_tests COMMAND numen_tests)
    else()
        message(WARNING "No test sources found in tests/ directory")
    endif()
endif()
