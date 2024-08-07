cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# Define variables
set(MY_PROJECT "Ray Tracing")
set(MY_EXECUTABLE "ray_tracing")

# 定義專案屬性
project(${MY_PROJECT})

# 建立二進位執行檔目標
add_executable(${MY_EXECUTABLE})

# 設定目標屬性: C++ 語言
set_target_properties(${MY_EXECUTABLE}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

# 顯示相關資訊
message(STATUS)
message(STATUS "========== Build Information ==========")
message(STATUS "\tHost System Name:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "\tHost System Version:      ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "\tHost System Processor:    ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS)
message(STATUS "\tC++ Compiler:             ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "\tC++ Compiler Path:        ${CMAKE_CXX_COMPILER}")
message(STATUS)

if (MSVC)
    message(STATUS "\tMSVC Version:             ${MSVC_VERSION}")
    message(STATUS "\tMSVC Toolset:             ${MSVC_TOOLSET_VERSION}")
endif ()
message(STATUS)

message(STATUS "========================================")

# 指定標頭檔資料夾、找尋所有原始檔、並將【原始碼】加入到【執行檔目標】中
target_include_directories(${MY_EXECUTABLE} PRIVATE "include")

file(GLOB MY_SOURCE CONFIGURE_DEPENDS
    "src/Entity/*.cpp"
    "src/Image/*.cpp"
    "src/Material/*.cpp"
    "src/Utility/*.cpp"
    "src/*.cpp"
)
target_sources(${MY_EXECUTABLE} PRIVATE ${MY_SOURCE})

# 針對不同的編譯器有不同的引入設定
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        target_link_libraries(${MY_EXECUTABLE} PRIVATE stdc++fs) # C++ filesystem
    endif ()
endif ()

# 建立 Symlink 到 assets 資料夾
add_custom_command(TARGET ${MY_EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${MY_EXECUTABLE}>/assets"
    DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    COMMENT
        "Creating symlinks to project resources..."
    VERBATIM
)