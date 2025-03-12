cmake_minimum_required(VERSION 3.10)
project(DeepSeekClient)

set(CMAKE_CXX_STANDARD 11)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加源文件
set(SOURCES
    src/main.cpp
    src/config.cpp
    src/curl_wrapper.cpp
    src/deepseek_client.cpp
)

# 生成可执行文件
add_executable(DeepSeekClient ${SOURCES})

# 链接 curl 库（确保系统已安装 libcurl）
find_package(CURL REQUIRED)
target_link_libraries(DeepSeekClient CURL::libcurl)
