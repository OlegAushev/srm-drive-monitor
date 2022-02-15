cmake_minimum_required(VERSION 3.1.0)
project(srm-drive-monitor VERSION 0.1.0)


set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE ${default_build_type})
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -DDEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) 


set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
cmake_policy(SET CMP0071 NEW)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


message(STATUS "Looking for Qt...")
find_package(Qt5 COMPONENTS Quick Core Widgets Charts REQUIRED)
find_package(Qt5QuickCompiler REQUIRED)
if (${Qt5_FOUND})
    message(STATUS "Found Qt " ${Qt5_VERSION})
else()
    message(FATAL_ERROR "Couldn't find Qt")
endif()


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

