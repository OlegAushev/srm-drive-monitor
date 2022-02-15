cmake_minimum_required(VERSION 3.1.0)
project(srm-drive-monitor VERSION 0.2.0)


# -- Setting default build type
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified")
	set(CMAKE_BUILD_TYPE ${default_build_type})
endif()


# -- EDGE controler option definition
option(EDGE_BUILD "Build for EDGE-board" OFF)
if(EDGE_BUILD)
	message(STATUS "EDGE-board build configuration is ON")
endif()


#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -DDEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) 


# -- Searching for Qt libraries
message(STATUS "Searching for Qt...")
find_package(Qt5 COMPONENTS Quick Core Charts REQUIRED)
find_package(Qt5QuickCompiler REQUIRED)
if (${Qt5_FOUND})
    message(STATUS "Found Qt " ${Qt5_VERSION})
else()
    message(FATAL_ERROR "Couldn't find Qt")
endif()


set(CMAKE_AUTOMOC ON)
if(EDGE_BUILD)
	set(CMAKE_AUTORCC ON)
endif()
cmake_policy(SET CMP0071 NEW)


include_directories(src)
add_subdirectory(src)


#######################################################################
#set(CMAKE_AUTOUIC_SEARCH_PATHS /ui/)

#include(CTest)
#enable_testing()

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

#install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)

