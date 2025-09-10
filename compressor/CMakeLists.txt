add_executable(compressor src/compressor.cpp)
target_link_libraries(compressor
    libcompressor
    CONAN_PKG::spdlog
)

install(TARGETS compressor
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
