Using SFML - Visual C++ 15 (2017) 64-bit

To Setup Dynamic Linking for SFML

Open Project -> Preferences

In C/C++ -> General
Set configuration to All Configurations
Modify the field Additional Include Directories with this value: $(SolutionDir)\SFML-2.5.1\include
(these are the header files, which tell the compiler which symbols exist)

In Linker -> General
Set configuration to All Configurations
Modify the field Additional Library Directories with this value: $(SolutionDir)\SFML-2.5.1\lib
(these are the library files, which tell the linker where to find symbols in the DLLs)

In Linker -> Input
Set configuration to debug
Modify the field Additional Dependencies with this value: sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;
Set configuration to release
Modify the field Additional Dependencies with this value: sfml-graphics.lib;sfml-window.lib;sfml-system.lib;

In Debugging
Modify the field Environment with this value: PATH=$(SolutionDir)\SFML-2.5.1\bin;%PATH%
DONT FORGET TO INCLUDE "PATH="