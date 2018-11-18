
# Supports generating both linux makefiles and MSVC solution files
# For generating MSVC solutions set the SFML_DIR_R and TGUI_DIR_R to the SFML and TGUI directories respectively



cmake_minimum_required(VERSION 3.10.2)

project(Somber)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(EngineX)



# change these to the SFML and TGUI directories
set(SFML_DIR_R "C:/Program Files (x86)/SFML-2.5.0")
set(TGUI_DIR_R "C:/Program Files (x86)/TGUI-0.8")



# specifying the source files
set(MY_SOURCES
        pch.cpp
        pch.h
        EngineX/AniSprite.cpp
        EngineX/AniSprite.h
        EngineX/eClock.h
        EngineX/Engine.cpp
        EngineX/Engine.h
        EngineX/EngineX.h
        EngineX/Inventory.cpp
        EngineX/Inventory.h
        EngineX/Point.h
        EngineX/Polygon.cpp
        EngineX/Polygon.h
        EngineX/Scene.h
        EngineX/Utility.h
        EngineX/CompResolve.h
        Array2d.h
        Balcony.cpp
        Balcony.h
        Boss1.cpp
        Boss1.h
        Boss2.cpp
        Boss2.h
        Boss3.cpp
        Boss3.h
        Bullet.h
        Button.h
        Coin.cpp
        Coin.h
        DefaultInv.h
        Door.cpp
        Door.h
        Floor1.cpp
        Floor1.h
        Floor2.cpp
        Floor2.h
        FuseInfo.h
        Grid.cpp
        Grid.h
        GridPoint.h
        InvShow.cpp
        InvShow.h
        MainChar.cpp
        MainChar.h
        MainMenu.cpp
        MainMenu.h
        Maze.cpp
        Maze.h
        OptionMenu.cpp
        OptionMenu.h
        PauseMenu.cpp
        PauseMenu.h
        Player.h
        RestartMenu.cpp
        RestartMenu.h
        Snek.cpp
        Snek.h
        Spotlight.h
        TextBox.cpp
        TextBox.h
        TimeText.cpp
        TimeText.h
        Undead.cpp
        Undead.h
        Walls.cpp
        Walls.h
        main.cpp
)



# finding and setting directories of libraries (not required on linux)
if(MSVC)
	# SFML
	set(SFML_DIR "${SFML_DIR_R}/lib/cmake/SFML")
	# for building on windows, at least SFML 2.5 is required 
	find_package(SFML 2.5 COMPONENTS graphics window system network audio REQUIRED)
	
	# TGUI
	include_directories(${TGUI_DIR_R}/include)
	link_directories(${TGUI_DIR_R}/lib)
endif()



# adding sources to the build
add_executable(${PROJECT_NAME} ${MY_SOURCES})



# linking libraries
target_link_libraries(${PROJECT_NAME}
            sfml-graphics
            sfml-window
            sfml-system
            sfml-network
            sfml-audio
            tgui
)


# set compatibility mode if building on VS
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()



# set the macro _DUBUG to be defined only when build target is debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")



# force include precompiled header in all files
if(MSVC)
    add_definitions(/FI"pch.h")
else()
    # GCC or Clang
    add_definitions(-include pch.h)
endif()
