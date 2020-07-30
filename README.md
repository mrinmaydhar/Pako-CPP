# Pako-CPP
Game created using Borland Graphics Interface in Turbo C++ emulated in DOSBox

To be included in next build:
1. More walls
2. Timer
3. Mouse Integration
4. Triple Buffer video memory (simultaneous artifact render)
5. Procedurally generated mazes: depth based, recursive division etc.

## Introduction and Scope

This project started in winter of 2016, as a project for the 10+2 practical examinations. At the time, due to limitations in time, and knowledge, no video buffer for artifacts was used. So each time the screen had to be refreshed for the objects to render, real time. They were initialised, stored in memory, and destroyed sequentially; for each object resulting in horrible frame times, even for a DOSBox Emulator (the equivalent of a Pentium I PC).

When the project was restarted, video buffer in the form of the malloc(); command was used, alongside the imagesize(); function. This function enabled the object to be allocated some memory, so that it occupies memory in the video memory buffer, rather than the heap memory or far heap.

Due to this “revelation” the whole game structure and thus many routines were changed. Complications in exiting from inner pseudo-infinite loops have thus far posed as a challenge and hence multiple artefacts cannot be rendered simultaneously.

The Borland Graphics Interface, along with Turbo C++, is used as the development platform. Porting the platform to Visual Studio resulted in no appreciable gains, as WinBGIm and OpenBGI, and the associated .sln projects all were derived from the same base of routines used in C around the 90s. Although BGI is less powerful than modern graphics libraries like SDL or OpenGL, it is easier to code due to familiarity. BGI was mainly used for Presentation graphics instead of event-based 3D applications.

All of this possible due to the DOSBox emulator program, which emulates an IBM PC compatible computer running a DOS operating system; along with graphics, and sound cards.

Many kinks have been sorted since the birth of this project, but scope for improvement always exist. In the future builds, the plan is to include more walls. A timer could be used for gameplay. Mouse integration in the compiler for navigation (through menus or else) can be implemented to enhance the GUI. Double or Triple buffered video memory can be used so that movement of multiple artifacts can be rendered simultaneously. Procedurally generated mazes, using either graph theory based methods (depth-first, kruskal’s, prim’s etc.) or recursive division methods, can be used when the full implementation can be imported in the code-base. Even file streams can be used for score storing, save-games etc.

## Overview and Mechanisms

The program is currently standing at more than 3000 lines of code. The main aim of the game is to navigate ‘Pako’, the Pac-man, around a series of walls to escape the simulated prison cell. Header files in the program include:

1. *<iostream.h>* for *cout* and *cin* commands.
2. *<graphics.h>* for all graphics manipulation in viewport.
3. *<stdlib.h>* and *<stdio.h>* for other standard functions built into the compiler.
4. *<dos.h>* for DOS related manipulation like *sleep()*, *delay()*, and *malloc()*.
5. *<process.h>* for *exit()*.
6. *<math.h>* for the exit routine.

The flow of the program begins at *main()*, which is the driver function.

*init()* initialises the graphics system, *soundfun()* starts the program using a sound sequence resembling the Super Mario theme with a welcome screen, and *menu()* runs the menu function, which lists all the possible options of playing, along with the help menu, the ‘epilogue’ to the original Pac-man, and the utility of the escape function.

*history()* queues the story base of the game. A random generated ‘star-map’ is created along with a randomly moving saucer. The story of Pako is shown here.

*screensave()* is used during the exit of the program, and the bulk of the mathematics (math.h) is accomplished in this function routine. A pie shaped ball jumps across the screen with decreasing height; much like a dropped ball. A goodbye message is displayed.

*soundfun()* is used during the beginning of the program, where a welcome screen is shown along with a sound routine, using *Sound()* at a specified frequency for a specified period of time in milliseconds.

*struct wall* is used to define the dimensional aspects of the ‘kill-walls’ used in the game. The actual gameplay code is in *game(int&)* where the pie moves according to user input.
