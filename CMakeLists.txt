cmake_minimum_required(VERSION 2.8)

project(gsquares)

set(SOURCE_EXE src/main.cpp)
set(EXE_NAME "gsquares")
add_library(bot STATIC src/headers/bot.cpp)
add_library(field STATIC src/headers/field.cpp)

add_executable(gsquares src/main.cpp)

find_package(SFML 2.5 REQUIRED graphics window system)
if (NOT SFML_FOUND)
	messsage(SEND_ERROR "Failed to find SFML")
	return()
endif()

target_link_libraries(${EXE_NAME} bot field sfml-graphics sfml-window sfml-system)

install(TARGETS ${EXE_NME} DESTINATION bin)
