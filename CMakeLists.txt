cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")


set(DIRSYNC_PROJECT_NAME dirsync)
set(DIRSYNC_SOURCE_DIR src)
set(DIRSYNC_SOURCE ${DIRSYNC_SOURCE_DIR}/main.cpp)
set(DIRSYNC_LIBRARIES_DIR libs)
set(DIRSYNC_LIBRARIES
	yaml-cpp
	)

# set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/toolchains/windows_gcc.txt)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)	

project(${DIRSYNC_PROJECT_NAME} VERSION 0.0.0)
set(CMAKE_CXX_FLAGS "-std=c++17 -g ${CMAKE_CXX_FLAGS}")

# #########
# # GTest #
# #########
# enable_testing()
# add_subdirectory(libs/gtest-1.7.0)
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

###########
# Project #
###########
add_executable(${DIRSYNC_PROJECT_NAME} ${DIRSYNC_SOURCE})

foreach(LIBRARY ${DIRSYNC_LIBRARIES})
	add_subdirectory("${DIRSYNC_LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)

include(${CMAKE_CURRENT_SOURCE_DIR}/libs/argumentum/CMakeLists.txt)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/argumentum/include)
set(PARSER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/libs/argumentum/src/argparser.cpp)

target_link_libraries(${DIRSYNC_PROJECT_NAME} ${DIRSYNC_LIBRARIES} ${ARGUMENTUM_STATIC_NAME})

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)


# include(ExternalProject)
# ExternalProject_Add(GTKMM3
# 	SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/gtkmm
# 	CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/libs/gtkmm/autogen.sh --prefix=${CMAKE_CURRENT_SOURCE_DIR}/libs/gtkmm/gtkmm_build
# 	BUILD_COMMAND "${MAKE} -j4")

pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
include_directories(${GTKMM3_INCLUDE_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTKMM3_CFLAGS_OTHER})

add_library(yaml_worker 	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/yaml_worker/yaml_worker.cpp)
add_library(variables 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/variables/variables.cpp)
add_library(found_file 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/found_file/found_file.cpp)
add_library(file_list 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/file_list/file_list.cpp)

add_library(double_text		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/double_text.cpp)
add_library(list_folder		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/list_folder.cpp)

add_library(blacklist_mc	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/blacklist_model_column.cpp)
add_library(view_mc			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/view_model_column.cpp)
add_library(file_mc			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/file_model_column.cpp)
add_library(folder_mc		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/folder_model_column.cpp)

add_library(list_operator	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/list_operator.cpp)

add_library(list_blacklist	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/list_blacklist.cpp)
add_library(list_file		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/list_file.cpp)

add_library(presets			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/presets.cpp)
add_library(window			SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/window/window.cpp)

# Current building machine requires -lstdc++fs to be linked to any library that operates with filesystem
target_link_libraries(yaml_worker variables ${YAML_CPP_LIBRARIES} ${DIRSYNC_LIBRARIES} stdc++fs)
target_link_libraries(file_list found_file)

# GTK-dependant libs
target_link_libraries(double_text 		${GTK3_LIBRARIES})
target_link_libraries(presets	 		list_blacklist list_folder ${GTK3_LIBRARIES})

target_link_libraries(blacklist_mc		${GTK3_LIBRARIES})
target_link_libraries(view_mc			${GTK3_LIBRARIES})
target_link_libraries(file_mc			${GTK3_LIBRARIES})
target_link_libraries(folder_mc			${GTK3_LIBRARIES})

target_link_libraries(list_operator		${GTK3_LIBRARIES})
target_link_libraries(list_file 		list_operator ${GTK3_LIBRARIES})
target_link_libraries(list_folder 		list_operator -lstdc++fs ${GTK3_LIBRARIES})
target_link_libraries(list_blacklist	${GTK3_LIBRARIES})
target_link_libraries(found_file 		-lstdc++fs)
target_link_libraries(file_list 		found_file -lstdc++fs)
target_link_libraries(window 			list_file list_folder yaml_worker presets double_text found_file -lstdc++fs)

target_compile_features(dirsync PRIVATE cxx_std_17)
# link_directories(${OpenCV_LIB_DIR})
# Link the target to the GTK+ libraries
# target_link_libraries(hello ${GTKMM3_LIBRARIES})

target_link_libraries(dirsync 
			Threads::Threads ${YAML_CPP_LIBRARIES} ${ARGUMENTUM_INTERNAL_NAME}
			yaml_worker variables found_file file_list list_folder 
			blacklist_mc view_mc file_mc folder_mc list_operator list_file
			list_folder list_blacklist found_file file_list window presets
			${GTKMM3_LIBRARIES})
