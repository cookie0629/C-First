cmake_minimum_required(VERSION 3.20)
project(compressor_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器警告
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# 设置编译命令导出
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 包含Conan生成的工具链
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# 添加子目录
add_subdirectory(libcompressor)
add_subdirectory(compressor)

# 启用测试
enable_testing()

# 添加单元测试
add_subdirectory(libcompressor/tests)

# 安装目标
include(GNUInstallDirs)
install(TARGETS libcompressor compressor
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Doxygen文档生成
find_package(Doxygen REQUIRED)
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
set(DOXYGEN_EXTRACT_ALL YES)
doxygen_add_docs(docs libcompressor/include)