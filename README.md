# Run or Crush
Run or Crush is a 2 player game created in C++ and SDL2. 

# Screenshots
![image](https://github.com/abbas-PM/Run-or-Crush/assets/116516812/885fc431-ebc3-4a7e-8402-da0f8fbae07f)
![image](https://github.com/abbas-PM/Run-or-Crush/assets/116516812/38411f3e-c3b7-43e1-8903-5aacd12470df)

# Background
Run or Crush is a 2 player game where one player acts as the runner and the other acts as the crusher. The runner controls their
character with the keyboard, while the crusher places blocks with the mouse. The goal for the runner is to survive for the full game, 
while the goal of the crusher is to crush the runner with their blocks.

# Compiling
To compile on windows, install Mingw64, SDL2, SDL2_Image and SDL2_TTF. Place all the C header files from SDL2, SDL2_Image and SDL2_TTF into the include folder, 
and create a new folder called lib and place all the library files, cmake files and pkgconfig files there. Finally create a bin folder and place the dll files
there, thats also where the .exe file will be created there. Run the line in the Makefile in the root directory to compile, then run the .exe file.






