add_executable(libcompressortest libcompressortest.cpp)
target_link_libraries(libcompressortest
    libcompressor
    GTest::gtest_main
)

# ÉèÖÃ²âÊÔÊä³öÎªXML
add_test(NAME libcompressor_test COMMAND libcompressortest --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml)
