# Depths-of-CSEDU
CSE-1211 Lab Project (Fall 2018)

## Outline
This is an academic group project of the course CSE-1211 for 1st year 2nd semester in the Department of Computer Science and Engineering of the Univeristy of Dhaka.

## Members
1. Raheeb Hassan (Roll: AE-42)
2. Farhan Kabir (Roll: AE-12)

## Abstract/Summary
The project is an adventure based top view role playing game.
The game is a slightly different take on the classic adventure role playing games. The premise, the main character played as a university student gets trapped within the compounds of his university. While trying to escape, he soon discovers that his department isn’t the same at night. There are locked rooms and unknown stairways which lead to the depths of the building. Now, he must cross it all and escape. The player would have to wander and find "keys". Often, in order to unlock keys there will be puzzles and enemies to defeat. Each key unlocks a new region. Coins are scattered around the map which can be used to gain special abilities and discover hidden secrets. If all the keys are collected and the final level is completed, the player can leave the department premises. Or, he can replay all the levels again.

### Prerequisites
1. SFML 2.5.0 (for Visual Studio 2017, 32 bit) [link](https://www.sfml-dev.org/download/sfml/2.5.0/)
2. TGUI 0.8 (for Visual Studio 2017) [link](https://tgui.eu/download/)

### Installing
#### SFML
1. Download the precompiled library files of SFML 2.5.0 for Visual Studio 2017 (32 bit) and place in desired folder.
2. In Visual Studio open Project > Properties > C/C++ > Additional include libraries and add the path to the `/include` folder of the SFML library here.
3. Again in Project > Properties, goto Linker > General and add the path to the `/lib` folder of the SFML library to the Additional Library Directories option.
4. Finally in Linker > Input > Additional Dependencies add the following to the front of the line separated by a semi-colon
```
sfml-graphics.lib;sfml-window.lib;sfml-system.lib;sfml-network.lib;sfml-audio.lib;
```
5. Copy paste the .dll files from the /lib folder to the project folder or the system32 folder of the PC
#### TGUI
1. Download the precompiled library files of TGUI 0.8 for Visual Studio 2017 and place in desired folder.
2. In Visual Studio open Project > Properties > C/C++ > Additional include libraries and add the path to the `/include` folder of the TGUI library here.
3. Again in Project > Properties, goto Linker > General and add the path to the `/lib` folder of the TGUI library to the Additional Library Directories option.
4. Finally in Linker > Input > Additional Dependencies add the following ** after the SFML libraries ** `tgui.lib`. It should look something like this afterwards.
```
sfml-graphics.lib;sfml-window.lib;sfml-system.lib;sfml-network.lib;sfml-audio.lib;tgui.lib;....
```
5. Copy paste the .dll files from the /lib folder to the project folder or the system32 folder of the PC

### Modules
1.	Engine (game engine)
    -	Core (state manager)
    -	Animated sprite (animation class)
    -	Polygon (for SAT collision detection)
    -	Inventory (storing and saving inventory)
    -	Utility (miscellaneous functions)
2.	Floor 1
    -	Balcony
    -	Coin
    -	Door
3.	Levels
    -	Boss 1
        -	Spotlight
        -	Fuses
    -	Boss 2
        -	Bullet
        -	Player
        -	Undead
    -	Boss 3
        -	Grid
        -	Snake
        -	Walls
        -	Maze
4.	Menus
    -	Main menu
    -	Options menu
    -	Pause menu
5.	Side
    -	Text box
    -	Restart menu
    -	Inventory (interface)
    -	Mini-map
    
### Gameplay
Youtube video: [link] (https://youtu.be/coCe4rCoKEU)
