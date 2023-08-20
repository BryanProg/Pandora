cmake_minimum_required(VERSION 3.20)
project(pandora VERSION 0.0.2 LANGUAGES CXX)

message("Build Type: ${CMAKE_BUILD_TYPE}")
message("Generator Type: ${CMAKE_GENERATOR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(pandr_dir ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "" FORCE)
set(pandr_headers_dir ${pandr_dir}/include CACHE STRING "" FORCE)
set(pandr_sources_dir ${pandr_dir}/src CACHE STRING "" FORCE)

set(pandr_headers
	${pandr_headers_dir}/pandora.hpp
	${pandr_headers_dir}/utils.hpp
	${pandr_headers_dir}/vec.hpp
	${pandr_headers_dir}/pandora.hpp
)

set(pandr_sources
	${pandr_sources_dir}/main.cpp
)

add_executable(pandora ${pandr_sources} ${pandr_headers})

target_include_directories(pandora PRIVATE ${pandr_headers_dir})

set_target_properties(pandora PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
