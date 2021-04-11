@page arduiono_installation Arduino installation

__1.__

Download this library as a .zip, or clone it.

__2.__

Create a new sketch in Arduino IDE and open its folder.

__3.__

![](arduino_install_lib_install.png)
Now copy interpreter.c and interpreter.h files from src folder in this repository, to your sketch folder.

__4.__

Because Arduino uses C++ not C, you have to rename the interpreter.c file to interpreter.cpp,
and the interpreter.h file to interpreter.hpp. My recommendation is to use a text editor for
this step like [Atom](https://atom.io/) or [Notepad++](https://notepad-plus-plus.org/downloads/).

__5.__

If Arduino IDE is opened __save all your work,__ then restart Arduino IDE.

__6.__

![](arduino_install_success.png)
Now you should see the interpreter.cpp and interpreter.hpp files on the top bar.
Than you just include interpreter.hpp as usual.

Congratulations you successfully added the library to your sketch.
