cmake_minimum_required(VERSION 3.16)
project(JsonParser LANGUAGES CXX) # specify the project name and the language used

if (APPLE)
    cmake_policy(SET CMP0135 NEW)
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS "-g3 -O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "-O2 /EHsc")
endif() # set extra flags

include(FetchContent)

# Fetch jsoncpp using FetchContent
FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG 1.9.4
)
FetchContent_MakeAvailable(jsoncpp)

file(GLOB SOURCES "*.cpp") # specify the source files
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC jsoncpp_lib)

target_include_directories(JsonParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET JsonParser PROPERTY POSITION_INDEPENDENT_CODE ON)

if (WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/bin/Debug/ ${CMAKE_BINARY_DIR}/
    )
endif()
