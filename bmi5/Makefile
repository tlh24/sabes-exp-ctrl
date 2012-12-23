CC = g++
OBJS = main.o tdt_udp.o glInfo.o glFont.o polhemus.o writematlab.o \
	../../myopen/common_host/jacksnd.o ../../myopen/common_host/gettime.o
CFLAGS=-I/usr/local/include -I../../myopen/common_host
CFLAGS+=  -O3 -DDEBUG
CFLAGS+= -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare -Wformat=2 \
-Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -pedantic -std=c++11 -rdynamic
LDFLAGS = -rdynamic -lrt -lGL -lGLU -lGLEW -lusb-1.0 -lhdf5 -ljack
GLIBS = gtk+-3.0
GTKFLAGS = `pkg-config --cflags $(GLIBS) `
GTKLD = `pkg-config --libs $(GLIBS) `
FIFOS = bmi5_in bmi5_out

all: bmi5

main.o : main.cpp shape.h gtkglx.h serialize.h

%.o : %.cpp 
	$(CC) -c -o $@ $(CFLAGS) $(GTKFLAGS) $<
	
%.o: ../../myopen/common_host/%.cpp\
	$(CC) -c -o $@ $(CFLAGS) $(GTKFLAGS) $<

bmi5: $(OBJS) $(FIFOS)
	$(CC) -o $@ $(GTKLD) $(LDFLAGS) -lmatio $(OBJS)
	
glxgears: glxgears.c
	$(CC) -O3 -o $@ -lrt -lGL $<
	
clean:
	rm -rf *.o bmi5 glxgears
	
bmi5_in: 
	mkfifo $@
	
bmi5_out:
	mkfifo $@
	
deps:
	sudo apt-get install gdb libgtk-3-dev libgtkglext1-dev freeglut3-dev \
<<<<<<< HEAD
	libusb-1.0-0-dev libglew-dev libjack-jackd2-dev \
	libblas-dev liblapack-dev libfftw3-dev libhdf5-dev
=======
	libmatio-dev libusb-1.0-0-dev libglew-dev libjack-jackd2-dev \
	libblas-dev liblapack-dev libfftw3-dev libhdf5-serial-dev qjackctl
>>>>>>> 1f38b94bfc8f6eff598aa8fdf97085092ce3221a
	mkfifo bmi5_out
	mkfifo bmi5_in
	