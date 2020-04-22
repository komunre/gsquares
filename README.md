# gsquares
"Artifical life" project.

Libraries
============
* SFML-2.5.1

How to build
===================
g++
--------------
`g++ -o gsquares.exe -static-libstdc++ -Wall -L[SFML_lib_dir] -I[SFM_include_dir] src/main.cpp src/headers/bot.cpp src/headers/field.cpp -lsfml-graphics -lsfml-main -lsfml-window -lsfml-system -lwinmm -lgdi32 -lopenal32`

Future updates
==============
* Possible MakeFile or CMakeLists
