cmake_minimum_required(VERSION 3.0)
project(ForsakenSouls)
set(CMAKE_CXX_FLAGS --std=c++11 ${CMAKE_CXX_FLAGS})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(Lums)
file(GLOB SRC "src/*.cpp")
file(GLOB_RECURSE ASSETS "assets/*")
file(GLOB TOP_ASSETS "assets/*")
include_directories(include)
include_directories(inc)
include_directories(${LUMS_INCLUDE_DIRS} SYSTEM)
add_custom_command(
	OUTPUT "${CMAKE_SOURCE_DIR}/assets/level_links.bin"
	COMMAND "ruby" "${CMAKE_SOURCE_DIR}/utils/build_level_links.rb" "${CMAKE_SOURCE_DIR}/map/links.json" "${CMAKE_SOURCE_DIR}/assets/level_links.bin"
	DEPENDS "${CMAKE_SOURCE_DIR}/map/links.json"
)
file(GLOB MAP "map/level*")
foreach(M ${MAP})
	get_filename_component(N ${M} NAME)
	file(GLOB MAP_SRC "${M}/*.json")
	message(STATUS "${N} ${M} ${MAP_SRC}")
	add_custom_command(
		OUTPUT "${CMAKE_SOURCE_DIR}/assets/levels/${N}.lvl"
		COMMAND "ruby" "${CMAKE_SOURCE_DIR}/utils/build_level.rb" "${M}" "${CMAKE_SOURCE_DIR}/assets/levels/${N}.lvl"
		DEPENDS ${M}
	)
endforeach()
add_executable(forsaken MACOSX_BUNDLE ${SRC} ${ASSETS})
set_target_properties(forsaken PROPERTIES OUTPUT_NAME "Forsaken Souls")
add_custom_command(
    OUTPUT "Forsaken Souls.app/Content/Resources"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/assets" "Forsaken Souls.app/Content/Resources"
    MAIN_DEPENDENCY "${CMAKE_SOURCE_DIR}/assets"
)
target_link_libraries(forsaken ${LUMS_LIBRARIES})
