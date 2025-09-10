add_library(libcompressor STATIC
    src/libcompressor.cpp
)

target_include_directories(libcompressor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(libcompressor
    CONAN_PKG::zlib
    CONAN_PKG::bzip2


install(TARGETS libcompressor
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/libcompressor
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
