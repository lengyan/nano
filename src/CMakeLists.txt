# include 目录
include_directories(${NANO_SOURCE_DIR}/dep/include)

# 链接目录
link_directories(${NANO_SOURCE_DIR}/dep/lib/ubuntu)

# 增加可运行文件
add_executable(nano Main.cpp World.cpp utils/Config.cpp utils/Logger.cpp WorldSocket.cpp WorldSession.cpp WorldTask.cpp)

# 链接库
target_link_libraries(nano ACE)
