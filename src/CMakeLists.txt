cmake_minimum_required(VERSION 3.20)

project(sketchacitor VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_EXTENSIONS OFF)

set(ARCH ${CMAKE_SYSTEM_PROCESSOR})
set(OUT "${CMAKE_CURRENT_SOURCE_DIR}/arch/${ARCH}/out")
set(LIB_D "${OUT}/framework")
set(TEST_D "${OUT}/tests")

set(SRC
	reader/read_file.c
	reader/smobo_interpret.c
)

option(BUILD_TESTS "Builds tests for sketchacitor for looking for bugs and making sure everything works. only for developers" OFF)
option(DEBUG_MODE "Adds debugging features to functions. Only for development testing" OFF)

add_library(sketchacitor_static STATIC ${SRC})
add_library(sketchacitor_shared SHARED ${SRC})

set_target_properties(sketchacitor_static PROPERTIES
	OUTPUT_NAME sketchacitor
	ARCHIVE_OUTPUT_DIRECTORY "${LIB_D}"
)

set_target_properties(sketchacitor_shared PROPERTIES
	OUTPUT_NAME sketchacitor
	LIBRARY_OUTPUT_DIRECTORY "${LIB_D}"
)

target_include_directories(sketchacitor_static PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(sketchacitor_shared PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(BUILD_TESTS)
	add_executable(smobo_interpreting_test tests/smobo_test.c reader/smobo_interpret.c)
	set_target_properties(smobo_interpreting_test PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${TEST_D}"
	)
	target_include_directories(smobo_interpreting_test PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
	)
	target_compile_definitions(smobo_interpreting_test PRIVATE DEBUG)
endif()

if(DEBUG_MODE)
	target_compile_definitions(sketchacitor_static PRIVATE DEBUG)
	target_compile_definitions(sketchacitor_shared PRIVATE DEBUG)
endif()
