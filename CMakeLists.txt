cmake_minimum_required(VERSION 3.0)
project(GLBase VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDES
"deps/glew/include"
"deps/glfw/include"
"deps/imgui/include"
"include"
)


add_subdirectory(deps)
    
file(GLOB_RECURSE GLBase_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)
    
add_library(GLBase STATIC ${GLBase_SOURCES})
    
target_link_libraries(GLBase
    glew_s
    glfw
    imgui
)
target_include_directories(GLBase PUBLIC ${INCLUDES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    
option(BUILD_TESTS "Build test executables" ON)
option(BUILD_EXAMPLES "Build example executable" ON)

if(${BUILD_TESTS})
    include(CTest)
    enable_testing()
    add_executable(math_tests tests/math.cpp)
    add_test(NAME MathTests COMMAND math_tests)
    target_link_libraries(math_tests GLBase)    
endif(${BUILD_TESTS})

if(${BUILD_EXAMPLES})
    add_executable(sandbox examples/sandbox.cpp)
    target_link_libraries(sandbox GLBase)
endif(${BUILD_EXAMPLES})

