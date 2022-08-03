cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)	


set(DIRSYNC_PROJECT_NAME dirsync)
set(DIRSYNC_SOURCE_DIR src)
set(DIRSYNC_SOURCE ${DIRSYNC_SOURCE_DIR}/main.cpp)
set(DIRSYNC_LIBRARIES_DIR libs)
set(DIRSYNC_LIBRARIES
	yaml-cpp
	)

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
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
include_directories(${GTKMM3_INCLUDE_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTKMM3_CFLAGS_OTHER})

# pkg_search_module(YAML_CPP REQUIRED yaml-cpp)

# if (YAML_CPP_FOUND)
# 	# Print some message showing some of them
# else ()
# 	message(FATAL_ERROR "Could not locate yaml-cpp" \n)
# endif()


# include_directories(dirsync ${YAML_CPP_INCLUDEDIR} ${YAML_CPP_INCLUDE_DIRS})
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/build)

# add_library(yaml_worker SHARED ${CMAKE_CURRENT_SOURCE_DIR}/defines/yaml_worker.cpp)

# target_include_directories(yaml_worker
# 	PUBLIC
# 		${CMAKE_CURRENT_SOURCE_DIR}/defines
# 		${YAML_CPP_INCLUDEDIR} 
# 		${YAML_CPP_INCLUDE_DIRS}
# )

# include(${CMAKE_CURRENT_SOURCE_DIR}/libs/argumentum/CMakeLists.txt)

# add_library(log_maintain SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/log_maintainer/log_maintain.cpp
# 							${CMAKE_CURRENT_SOURCE_DIR}/utils/log_maintainer/log_maintain.hpp)
							
# add_library(path_wrapper	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/utils/logic/path_wrapper.cpp)


# include(${CMAKE_CURRENT_SOURCE_DIR}/hardware_interfaces/hardware_interfaces.txt)

# target_link_libraries(obsolete variables coordinates)


#~ target_link_libraries(serial -lCppLinuxSerial)
# target_link_libraries(yaml_worker variables ${YAML_CPP_LIBRARIES})

add_library(yaml_worker 	SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/yaml_worker/yaml_worker.cpp)
add_library(variables 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/variables/variables.cpp)
add_library(found_file 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/found_file/found_file.cpp)
add_library(file_list 		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/file_list/file_list.cpp)
add_library(double_text		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/double_text.cpp)
add_library(list_folder		SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/gui/elements/list_folder.cpp)

# Current building machine requires -lstdc++fs to be linked to any library that operates with filesystem
target_link_libraries(yaml_worker variables ${YAML_CPP_LIBRARIES} ${DIRSYNC_LIBRARIES} stdc++fs)
target_link_libraries(file_list found_file)
target_link_libraries(double_text ${GTKMM3_LIBRARIES})

target_compile_features(dirsync PRIVATE cxx_std_17)
# link_directories(${OpenCV_LIB_DIR})
# Link the target to the GTK+ libraries
# target_link_libraries(hello ${GTKMM3_LIBRARIES})

target_link_libraries(dirsync 
			Threads::Threads ${YAML_CPP_LIBRARIES} ${ARGUMENTUM_INTERNAL_NAME}
			yaml_worker variables found_file file_list list_folder ${GTKMM3_LIBRARIES})
