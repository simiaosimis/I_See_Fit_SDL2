message("*** Starting subdir 'src' cmake")

message(AUTHOR_WARNING "Getting source files by using glob")
file(GLOB_RECURSE MyCppSources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Create a list with all cpp sources except for main, so the library doesn't contain it
set(MySourcesNoMain ${MyCppSources})
list(REMOVE_ITEM MySourcesNoMain main.cpp)

set(ExecTarget ${MyProjectName}_exec)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library(${MyProjectLib} STATIC ${MySourcesNoMain})
# add_library(${MyProjectLib}Shared SHARED ${MySourcesNoMain})
add_executable(${ExecTarget} ${MyCppSources}) # '_exec' suffix to make gitignore's life easy

target_link_libraries(${ExecTarget}
	${MyProjectLib}
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_MIXER_LIBRARY}
	${SDL2_TTF_LIBRARY}
)

# Used to be '/include', but is now '/src' due to remodeling of the project structure
include_directories(
	${PROJECT_SOURCE_DIR}/src
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_MIXER_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIR}	
)

# Files that are packed with CPack
install(TARGETS ${ExecTarget} #${MyProjectLib}Shared
	RUNTIME DESTINATION bin
	COMPONENT executables
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets
	DESTINATION bin
	COMPONENT assets
)

message("*** Finish subdir 'src' cmake")
