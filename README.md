# Practica2PA
University project from math degree student at UAB.

Consists in a library containing all the tools you would need to create a C++ project related to chess.
It has classes containing pieces, boards and the main class that is game which unites all the other classes
to create a fully functional set of chess pieces and boards. It will remember every move you made and save it.
With the game class functions you can navigate through all the diferent lines you've played.
You can also save your games as an encrypted .txt file so you can reload them at any time.
There's also some other useful functions for console display outside the classes.

This library is no use for speed because all the classes involved are really heavy and it wouldn't fit at
all in a chess engine which should be as simple and efficient as possible. On the other side this library
can be a really useful ground to create a nice chess app or display.

In that regard the Game class already contains an example console display game function including all the
library capabilities (in Catalan).

## Requirements
- [Visual Studio 2022](https://visualstudio.com)

## Getting Started
Once you've cloned, open the solution file you'll find in the main folder and compile the ChessInVS project. 
That will generate the library so you can link it to other projects that you want to use it for. The header 
you must include in the other projects is the phc ChessInVS.h. 

If you want an already linked project there's also one inside called FutureGUI, if you compile it and run it 
should work with no problem using the library and displaying the example function in a console.


