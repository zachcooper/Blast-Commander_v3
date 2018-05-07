CS 381
Blast Commander
Name: Zachary Cooper, Mike Mckissick, Phil Smith
Email: cooper.zachary.t@gmail.com

## Install Aditional Dependencies:  
	- audio: `sudo apt-get install libaudio-dev`  
	- openal: `sudo apt-get install libopenal-dev`  
## Add the following properties  
From GCC C++ Compiler -> Includes  
	- '/usr/include/AL'  
	- '/usr/include/audio'  
From GCC C++ Linker -> Libraries  
	- 'openal'  
	- 'audio'  