cmake_minimum_required(VERSION 3.0.0)
project(PrimeBench VERSION 0.1.0)

include(CTest)
enable_testing()


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


find_package(benchmark REQUIRED)

add_executable(PrimeBench main.cpp
        Concurrent/find_primesv4.hpp
        Concurrent/find_primesv5.hpp)
target_compile_options(PrimeBench PUBLIC -Wall -Wextra -Wpedantic -Weffc++ -Ofast -fno-exceptions -march=native -funroll-loops -fprofile-use)
target_compile_features(PrimeBench PUBLIC cxx_std_23)
target_link_libraries(PrimeBench benchmark::benchmark pthread)
target_link_options(PrimeBench PRIVATE -fprofile-use)


install(TARGETS PrimeBench DESTINATION bin)

add_executable(TestAlgo test.cpp)
target_compile_options(TestAlgo PRIVATE -Wall -Wextra -Wpedantic -Weffc++ )
target_compile_features(TestAlgo PUBLIC cxx_std_23)
target_link_options(TestAlgo PRIVATE )
target_link_libraries(TestAlgo pthread)

add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
