#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'screensaver'
# 'make clean'  removes all .o and executable files
##

#Compiler in use
CC=g++

#Compile time Flags
CFLAGS= -pthread -g

#Libraries to include during Cmpilation 
LIBRARIES= -lglut -lGL -lGLU -lGLEW -lm

#The C++ source files
SOURCES= Main.cpp Graphics.cpp Balls.cpp Physics.cpp Image.cpp

#The C++ object files
objects= $(SOURCES:.c=.o)

#Main executable file screensaver
screensaver: $(objects)
	g++ $(CFLAGS) $(objects) $(LIBRARIES) -o ../screensaver

Main.o: Main.cpp Graphics.h
	g++ $(CFLAGS) Main.cpp $(LIBRARIES)

Graphics.o: Graphics.cpp 
	g++ $(CFLAGS) Graphics.cpp $(LIBRARIES)

Balls.o: Balls.cpp Balls.h 
	g++ $(CFLAGS) Balls.cpp $(LIBRARIES)

Physics.o: Physics.cpp 
	g++ $(CFLAGS) Physics.cpp $(LIBRARIES)

Image.o: Image.cpp 
	g++ $(CFLAGS) Image.cpp $(LIBRARIES)

.PHONY : clean
clean:
	rm screensaver	

.PHONY : print


#‘make print’ will execute the lpr command if either source file has changed
#since the last ‘make print’. The automatic variable ‘$?’ is used to print only those files
#that have changed
print: *.c
	lpr -p $?
	touch print
