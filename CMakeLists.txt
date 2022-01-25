cmake_minimum_required(VERSION 3.0.0)
project(srm-drive-monitor VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")


set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
cmake_policy(SET CMP0071 NEW)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


message("Looking for Qt...")
find_package(Qt5 COMPONENTS Quick Core Widgets SerialBus Charts REQUIRED)
find_package(Qt5QuickCompiler REQUIRED)
if (${Qt5_FOUND})
    message("Found Qt " ${Qt5_VERSION})
else()
    message("Couldn't find Qt")
endif()


qtquick_compiler_add_resources(RESOURCES resources.qrc)
add_executable(${CMAKE_PROJECT_NAME} 
	src/main.cpp
	src/canbusdevice/canbusdevice.cpp
	${RESOURCES}
)

include_directories(src/)

target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Quick Qt5::Widgets Qt5::SerialBus Qt5::Charts)


#set(CMAKE_AUTOUIC_SEARCH_PATHS /ui/)

#include(CTest)
#enable_testing()

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)