
include(CTest)
enable_testing()



add_executable(TestSieves test_sieves.cpp)
target_link_libraries(TestSieves gtest_main)
target_include_directories(TestSieves PRIVATE ../Sequential)
target_compile_options(TestSieves PRIVATE -Wall -Wextra -Wpedantic -Weffc++ -Wshadow -fsanitize=address)
target_link_options(TestSieves PRIVATE -fsanitize=address)
target_compile_features(TestSieves PRIVATE cxx_std_20)

add_test(TestEachSieve TestSieves)