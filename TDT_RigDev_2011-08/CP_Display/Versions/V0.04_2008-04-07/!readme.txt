GL_Engine  - creates/destroys GL window, renders VObjects, manages message queue and 
             provives synchronization.
			 Implemented in C, not a C++ class. Interface is via global functions and variables.

CVMain is the interface to GL_Engine

CP_Display - has the WinMain(). It registers/unregisters the server, sets up GL_Engine
             and calls the main loop subroutine implemented in GL_Engine.

VObject


OpenGL - coordinates, angles, etc. are stored as doubles in the objects. 
         Transform matrix is also in doubles. Physical coordinates are 
		 transformed to screen coordinates with double precision. 
		 
		 ?? and then converted to floats which are used by OpenGL
