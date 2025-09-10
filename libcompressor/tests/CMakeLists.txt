find_package(GTest REQUIRED)

add_executable(libcompressortest libcompressortest.cpp)
target_link_libraries(libcompressortest
    libcompressor
    GTest::gtest_main
)

add_test(NAME libcompressor_test COMMAND libcompressortest)
