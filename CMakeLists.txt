cmake_minimum_required(VERSION 3.0)
project(ForsakenSouls)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
find_package(Lums)
include_directories(${LUMS_INCLUDE_DIRS} SYSTEM)
include_directories(include)

# Build game

file(GLOB SRC "src/*.cpp")
add_executable(forsaken_souls MACOSX_BUNDLE ${SRC})
set_target_properties(forsaken_souls PROPERTIES OUTPUT_NAME "Forsaken Souls")
set_target_properties(forsaken_souls PROPERTIES MACOSX_BUNDLE_ICON_FILE "Icon")
target_link_libraries(forsaken_souls ${LUMS_LIBRARIES})

# Build assets

add_custom_target(
	assets ALL
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	COMMAND "rm" "-rf" "${CMAKE_BINARY_DIR}/Forsaken Souls.app/Contents/Resources"
	COMMAND "ruby" "${CMAKE_SOURCE_DIR}/utils/build.rb"
	COMMAND "cp" "-r" "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/Forsaken Souls.app/Contents/Resources"
)
