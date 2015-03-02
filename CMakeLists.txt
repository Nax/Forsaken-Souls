cmake_minimum_required(VERSION 3.0)
project(ForsakenSouls)
set(CMAKE_CXX_FLAGS --std=c++11 ${CMAKE_CXX_FLAGS})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(Lums)
file(GLOB SRC "src/*.cpp")
file(GLOB ASSETS "assets/*")
include_directories(include)
include_directories(${LUMS_INCLUDE_DIRS} SYSTEM)
add_custom_command(
	OUTPUT "${CMAKE_SOURCE_DIR}/assets/level_links.bin"
	COMMAND "ruby" "${CMAKE_SOURCE_DIR}/utils/build_level_links.rb" "${CMAKE_SOURCE_DIR}/map/links.json" "${CMAKE_SOURCE_DIR}/assets/level_links.bin"
	DEPENDS "${CMAKE_SOURCE_DIR}/map/links.json"
)
add_executable(forsaken MACOSX_BUNDLE ${SRC} ${ASSETS})
set_target_properties(forsaken PROPERTIES OUTPUT_NAME "Forsaken Souls")
foreach(ASSET ${ASSETS})
    SET_SOURCE_FILES_PROPERTIES(${ASSET} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endforeach()
target_link_libraries(forsaken ${LUMS_LIBRARIES})