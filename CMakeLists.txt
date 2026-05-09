cmake_minimum_required (VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(PROJECT_NAME "Mahjong")
project (${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_Declare(lunasvg
    GIT_REPOSITORY https://github.com/sammycage/lunasvg.git
    GIT_TAG master
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(lunasvg)

set (SOURCES 
"code/main.cpp"
"code/card.cpp"
"code/button.cpp"
"code/assetManager.cpp"
"code/gameField.cpp"
"code/gamemode.cpp")
set (HEADERS 
"code/card.h"
"code/button.h"
"code/assetManager.h"
"code/gameField.h"
"code/gamemode.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    lunasvg
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)

target_include_directories(${PROJECT_NAME} PUBLIC
    code
    data
)