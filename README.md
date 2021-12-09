# Project-3-Movies
To run, copy the github repo into a new visual studio project. everything (including SFML) should be inside the repo.
There are two file paths you have to change in the project properties in order for SFML to properly work. 

In project->properties->C/C++->additional incldue directories, point to 
*beginning of file path*\Project-3-Movies\Project 3 (Movies)\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\include.

In project->properties->linker->additional library directories, point to
*beginning of file path*\Project-3-Movies\Project 3 (Movies)\SFML-2.5.1-windows-vc15-64-bit\SFML-2.5.1\lib.

After these two paths are changed, SFML should run flawlessly! (It may take a minute or two to run during the first compilation).
