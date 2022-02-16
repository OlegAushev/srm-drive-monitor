### -- Sources
add_subdirectory(models)
add_subdirectory(mcoclient)
add_subdirectory(drive)


### -- Sources
if (NOT EDGE_BUILD)
	qtquick_compiler_add_resources(RESOURCES ./../resources.qrc)
else()
	set(RESOURCES ./../resources.qrc)
endif()

add_executable(${CMAKE_PROJECT_NAME}
		main.cpp	
		${SOURCES}
		${RESOURCES})

target_sources(${CMAKE_PROJECT_NAME} PRIVATE cansocketdevice/cansocketdevice.cpp)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE chartplotter/chartplotter.cpp)
#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE canbusdevice)


### -- Libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
		PRIVATE
		Qt5::Quick  
		Qt5::Charts)


### -- Compile options and features
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)


### -- Print compile options at cmake run and after build
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(cxx_flags ${CMAKE_CXX_FLAGS_DEBUG})
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(cxx_flags ${CMAKE_CXX_FLAGS_RELEASE})
elseif (CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	set(cxx_flags ${CMAKE_CXX_FLAGS_MINSIZEREL})
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	set(cxx_flags ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
endif()
message(STATUS "CMake CXX flags: ${cxx_flags}")

get_target_property(target_options ${CMAKE_PROJECT_NAME} COMPILE_OPTIONS)
message(STATUS "Target compiler options: ${target_options}")

get_target_property(target_features ${CMAKE_PROJECT_NAME} COMPILE_FEATURES)
message(STATUS "Target compiler features: ${target_features}")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
COMMAND echo Built with flags: ${cxx_flags})
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
COMMAND echo Built with options: ${target_options})
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
COMMAND echo Built with features: ${target_features})

