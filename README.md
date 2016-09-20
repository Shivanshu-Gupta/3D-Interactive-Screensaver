# 3D-Interactive-Screensaver

#################################################################

This is the HOW TO file for Screensaver v1.0.

#################################################################

Steps to run the Screensaver Applet:
	
	1. Extract the compressed file.
	2. Open the terminal in extracted folder.
	3. Execute the "make" command.
	4. Execute ./Screensaver to access the Screensaver Applet.

Steps to get the Desgin Document:
	
	1. Open the terminal in extracted folder.
	2. Execute the "make doc" command.
	3. This shall output a PDF File named Desgin.pdf
	4. Open the PDF to access the proposed design.
	5. The folder also contains a file Divergence.txt
	6. You can refer to Divergence.txt to check how much have 
	   we diverged from our proposed design.

Commands to access required features:

	1. Open the terminal in extracted folder.
	2. Execute the "make DEBUG" command to execute the Applet 
	   in DEBUG_MODE.
	3. Execute the "make clean" command to remove all the 
	   temporary and executables files generated.
	4. Execute the command "make execute NUM_THREADS = n",
	   where n must have an integer value, to get the 
	   Screensaver executables with n balls.

Commands to access Additional Features:
	
	1. Open the terminal in extracted folder.
	2. Execute the "make [Image 1 address] [Image 2 address] 
	   [Image 3 address] [Image 4 address] [Image 5 address]"
	   to execute the Applet with the provided images.

	NOTE: Arguments in [..] are optional.

#################################################################

Using the Screensaver Applet:

	1. Once inside an executable, you will see a cuboid, use
	    the Mouse to rotate it in any direction.
	2. You can zoom in and out of the cuboid using the Mouse 
	   Scroll Wheel.
	3. Press the Space Key (' ') at anytime to pause the balls
	   at their then postitions.
	4. Press '=' to add a new ball at a random position. 
	5. Press '-' to remove a random ball.
	6. Press 's' to enter/exit the select mode.
	7. In the select mode the ball selected is paused at it's
	   position and the following options are available:-
		i. Delete the ball by pressing '-'
		ii. To Increase/Decrease the speed of the selected ball, press
		   the Up Arrow Key/Down Arrow Key respectively.

#################################################################
