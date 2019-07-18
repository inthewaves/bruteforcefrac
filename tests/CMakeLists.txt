project(catch2)
set(CMAKE_CXX_STANDARD 17)

add_library(Catch2 INTERFACE)
add_library(Catch2::Test ALIAS Catch2)
target_include_directories(Catch2 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(../include)

# CTest testing
enable_testing()

# Add testing executables
add_executable(unit_tests main.cpp test_rationalnum.cpp)

target_link_libraries(unit_tests bruteforcefrac Catch2::Test)

add_test(test_all unit_tests)
