# 项目命名
# 其他cmake文件可通过${项目名称_SOURCE_DIR}引用到根源文件目录
# 通过${项目名称_BINARY_DIR}引用到跟二进制文件目录
cmake_minimum_required(VERSION 2.6)
project(NANO)

# 增加子目录
add_subdirectory(src)
