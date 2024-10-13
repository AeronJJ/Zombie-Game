# Zombie Game

## Build

### Linux:
- Make sure SDL2 is installed on your system ([https://wiki.libsdl.org/SDL2/Installation](https://wiki.libsdl.org/SDL2/Installation))
- Download source code and run `make` in source root
- Done!

### Windows:
- Todo.

### Mac:
- Todo.

![Game Menu](media/SDL_menu.png)


## Background
This project started as an embedded systems project for Uni, the goal to be to create a game to run on an STM32L4 microcontroller using a Nucleo-L476RG development board and MBed OS. It utilised a Nokia-N5510 screen to display the game, and a joystick with some push buttons as primitive controls.

The game worked great and I received a good grade as a result, but then I had to hand the hardware back and suddenly had no way to play or show off my creation... So I decided to create a way to "emulate" the hardware so that it could be played on a computer and become accessible to anyone.

I wanted the emulator to be generic and not specific to my game, so that anyone that developed a project using the same hardware could use the emulator. If you want to use the emulator for your own project, see below.

The emulator uses SDL2 to handle the GUI and inputs.



## How to use the Emulator
The emulator is incomplete, it is missing a lot of functionality provided by MBed OS, if there is a specific feature that you would like to see implemented, please feel free to add it to Issues.

The emulator requires minor modifications to your project's source code and is not guaranteed to work with your porject. Specifically, it will require an extra condition in all of your `while` blocks that require inputs to be executed inside. This is because the inputs are handled in the same thread as the game is running, so in order to change the state of a button, the `checkInputs()` function of the `SDLInputHandling` object needs to be called. In the future, I would like this to be done in a separate thread to better emulate the action of inputs changing state. I would recommend for you to only use one while loop kept inside your main.cpp file. This is generally good game design (see: [https://gameprogrammingpatterns.com/game-loop.html](https://gameprogrammingpatterns.com/game-loop.html)) and will make using this emulator much easier.

To use the emulator, download the `emu` folder in this repository and put it in a new folder. Add all of your games source files to this folder as well EXCEPT from the `N5110` folder and any mbed files present in your project. If you are using Mbed Studio it might make more sense to create a symbolic link to your project files instead so that you do not have to keep copying files back and forth when you modify them. You could also add the files to a Visual Studio project instead which will not move them (This is what I recommend). Bear in mind you will likely have to keep two different `main.cpp` due to the modifications we will make now.

In your main.cpp, replace `int main() {` whith `int main(int argc, char* args[]){`, this allows SDL to "hook" into your program. Also add `#include "SDLInputHandling.h"` to the top of your file. You also need to create an instance of the `SDLInputHandling` object, I call this object `inputs`. This can be global if you have multiple while loops in different functions.

Now, find all the `while` loops in your code, and add this condition `&& !inputs.checkInputs()` to all of them.

You are now ready to compile and run your game. This will likely not be a simple process (at least in windows) due to the SDL requirement. I would recommend to use Visual Studio and follow this guide ([https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)) to set up your project. On Linux, just add the directories containing your header files to the `INCLUDES` variable and run `make`.