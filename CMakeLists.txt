# cmake_minimum_required(VERSION 3.10)
# project(DeepSeekClient)

# set(CMAKE_CXX_STANDARD 11)

# # 添加头文件搜索路径
# include_directories(${PROJECT_SOURCE_DIR}/include)

# # 添加源文件
# set(SOURCES
#     src/main.cpp
#     src/config.cpp
#     src/curl_wrapper.cpp
#     src/deepseek_client.cpp
# )

# # 生成可执行文件
# add_executable(DeepSeekClient ${SOURCES})

# # 链接 curl 库（确保系统已安装 libcurl）
# find_package(CURL REQUIRED)
# target_link_libraries(DeepSeekClient CURL::libcurl)
cmake_minimum_required(VERSION 3.10)
project(LiteratureCreator)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/config.cpp
    src/curl_wrapper.cpp
    src/db_manager.cpp
    src/deepseek_client.cpp
)

add_executable(app ${SOURCES})

# 链接 sqlite3 库（确保系统中安装了 sqlite3 开发包）
find_library(SQLITE3_LIBRARY sqlite3)
if(SQLITE3_LIBRARY)
    target_link_libraries(app ${SQLITE3_LIBRARY})
else()
    message(FATAL_ERROR "未找到 sqlite3 库")
endif()

find_package(CURL REQUIRED)
target_link_libraries(app CURL::libcurl)