# gsquares
"Artifical life" project.

Libraries
============
* SFML-2.5.1

How to build
===================
g++ windows
--------------
`g++ -o gsquares.exe -static-libstdc++ -Wall -L[SFML_lib_dir] -I[SFM_include_dir] src/main.cpp src/headers/bot.cpp src/headers/field.cpp -lsfml-graphics -lsfml-main -lsfml-window -lsfml-system -lwinmm -lgdi32 -lopenal32`

gcc linux
----------------
`gcc -xc++ -lstdc++ -L[SFML_lib_dir] -I[SFML_include_dir] src/main.cpp src/headers/bot.cpp src/headers/field.cpp -lsfml-graphicws -lsfml-window -lsfml-system`

dll
----------------
* openal32.dll
* sfml-graphics-2.dll
* sfml-system-2.dll
* sfml-window-2.dll

Future updates
==============
* Possible MakeFile or CMakeLists
