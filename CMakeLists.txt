cmake_minimum_required(VERSION 2.8)

project(brl)

SET(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(
	include/
)

file(
	GLOB_RECURSE
	source_files
	src/*
)

file(
	GLOB_RECURSE
	header_files
	include/*
)

add_executable(brl
	${header_files}
	${source_files}
)