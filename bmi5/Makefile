# The following can be set at the commandline
# ie: make USE_DEBUG=true
USE_DEBUG = false

CPP = g++
CC  = gcc

OBJS = main.o tdt_udp.o glInfo.o glFont.o polhemus.o writematlab.o \
	../../myopen/common_host/jacksnd.o ../../myopen/common_host/gettime.o

CFLAGS := -I/usr/local/include -I../../myopen/common_host
CFLAGS += -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare \
-Wformat=2 -Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -Werror -pedantic -std=c++11 -rdynamic

ifeq ($(strip $(USE_DEBUG)),true)
  CFLAGS += -g -DDEBUG
else
  CLFAGS += -O3
endif

LDFLAGS = -rdynamic -lrt -lGL -lGLU -lGLEW -lusb-1.0 -lhdf5 -ljack
GLIBS = gtk+-3.0
GTKFLAGS = `pkg-config --cflags $(GLIBS) `
GTKLD = `pkg-config --libs $(GLIBS) `

all: bmi5

main.o : main.cpp shape.h gtkglx.h serialize.h

%.o : %.cpp 
	$(CPP) -c $(CFLAGS) $(GTKFLAGS) $< -o $@
	
%.o: ../../myopen/common_host/%.cpp\
	$(CPP) -c $(CFLAGS) $(GTKFLAGS) $< -o $@

bmi5: $(OBJS)
	$(CPP) -o $@ $(GTKLD) $(LDFLAGS) -lmatio $(OBJS)
	
glxgears: glxgears.c
	$(CC) -O3 -o $@ -lrt -lGL $<
	
clean:
	rm -rf *.o bmi5 glxgears
	
deps:
	sudo apt-get install gdb libgtk-3-dev libgtkglext1-dev freeglut3-dev \
	libmatio-dev libusb-1.0-0-dev libglew-dev libjack-jackd2-dev \
	libblas-dev liblapack-dev libfftw3-dev libhdf5-serial-dev qjackctl
