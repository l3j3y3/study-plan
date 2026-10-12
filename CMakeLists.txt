cmake_minimum_required(VERSION 3.16)
project(study-plan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 正式程序:计时学习 + 任务记录/查询
add_executable(main
    src/main.cpp
    src/TaskWriter.cpp
    src/TaskReader.cpp
    src/TaskModify.cpp
)
target_include_directories(main PRIVATE src)

# 旧版:只做计时写入(仅用 TaskWriter)
add_executable(main1
    test/main1.cpp
    src/TaskWriter.cpp
)
target_include_directories(main1 PRIVATE src)

# 试验程序:查询/写入(用 TaskWriter + TaskReader)
add_executable(test
    test/test.cpp
    src/TaskWriter.cpp
    src/TaskReader.cpp
)
target_include_directories(test PRIVATE src)
