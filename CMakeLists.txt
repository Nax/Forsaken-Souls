cmake_minimum_required(VERSION 3.0)
project(ForsakenSouls)
set(CMAKE_CXX_FLAGS "-std=c++11 -fcolor-diagnostics -Wall -fno-exceptions -fno-rtti ${CMAKE_CXX_FLAGS}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
find_package(Lums)
include_directories(${LUMS_INCLUDE_DIRS} SYSTEM)
include_directories(include)

# Build game

file(GLOB_RECURSE SRC "src/*.cpp")
add_executable(forsaken_souls MACOSX_BUNDLE ${SRC})
set_target_properties(forsaken_souls PROPERTIES OUTPUT_NAME "Forsaken Souls")
set_target_properties(forsaken_souls PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.plist")
target_link_libraries(forsaken_souls ${LUMS_LIBRARIES})

# Build assets

add_custom_target(
	assets ALL
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
	COMMAND "rm" "-rf" "${CMAKE_BINARY_DIR}/Forsaken Souls.app/Contents/Resources"
	COMMAND "ruby" "${CMAKE_SOURCE_DIR}/utils/build.rb"
	COMMAND "cp" "-r" "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/Forsaken Souls.app/Contents/Resources"
)

# check bundle

install(CODE "
    include(BundleUtilities)
    file(COPY \"/usr/local/lib/libLums.dylib\" DESTINATION \"${CMAKE_BINARY_DIR}/Forsaken Souls.app/Contents/MacOS/\")
    fixup_bundle(\"${CMAKE_BINARY_DIR}/Forsaken Souls.app/Contents/MacOS/Forsaken Souls\" \"${CMAKE_BINARY_DIR}/Forsaken Souls.app/Contents/MacOS/libLums.dylib\" \"/usr/local/lib\")
")
#verify_app("${CMAKE_BINARY_DIR}/Forsaken Souls.app")
