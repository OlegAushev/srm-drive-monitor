add_subdirectory(models)
add_subdirectory(mcoclient)
add_subdirectory(drive)

qtquick_compiler_add_resources(RESOURCES ./../resources.qrc)

add_executable(${CMAKE_PROJECT_NAME}
		main.cpp	
		${SOURCES}
		${RESOURCES})

target_sources(${CMAKE_PROJECT_NAME} PRIVATE canbusdevice/canbusdevice.cpp)

#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE		
#		canbusdevice)

target_link_libraries(${CMAKE_PROJECT_NAME} 
		Qt5::Quick 
		Qt5::Widgets 
		Qt5::SerialBus 
		Qt5::Charts)



