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
# find_package(PkgConfig REQUIRED)
# pkg_search_module(YAML_CPP REQUIRED yaml-cpp)

# if (YAML_CPP_FOUND)
# 	# Print some message showing some of them
message(STATUS "Toto: ${ARGUMENTUM_STATIC_NAME}")
# 	message(STATUS "    version: ${YAML_CPP_VERSION}")
# 	message(STATUS "    include path: ${YAML_CPP_INCLUDEDIR}" )
# 	message(STATUS "    cpp flags: ${YAML_CPP_LIBRARIES}")
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





# link_directories(${OpenCV_LIB_DIR})
target_compile_features(dirsync PRIVATE cxx_std_17)

target_link_libraries(dirsync Threads::Threads ${YAML_CPP_LIBRARIES} ${ARGUMENTUM_INTERNAL_NAME})
