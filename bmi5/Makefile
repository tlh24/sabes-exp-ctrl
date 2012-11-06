CC = g++
OBJS = main.o tdt_udp.o glInfo.o glFont.o polhemus.o writematlab.o \
	../../myopen/common_host/gettime.o
CFLAGS=-I/usr/local/include -I../../myopen/common_host
CFLAGS+=  -g
CFLAGS+= -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare -Wformat=2 \
-Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -pedantic -std=c++11 -rdynamic
LDFLAGS = -rdynamic -lrt -lGL -lGLU -lGLEW -lusb-1.0 -lhdf5
GLIBS = gtk+-3.0
GTKFLAGS = `pkg-config --cflags $(GLIBS) `
GTKLD = `pkg-config --libs $(GLIBS) `

all: bmi5

main.o : main.cpp shape.h gtkglx.h

%.o : %.cpp 
	$(CC) -c -o $@ $(CFLAGS) $(GTKFLAGS) $<
	
%.o: ../../myopen/common_host/%.cpp\
	$(CC) -c -o $@ $(CFLAGS) $(GTKFLAGS) $<

bmi5: $(OBJS)
	$(CC) -o $@ $(GTKLD) $(LDFLAGS) -lmatio $(OBJS)
	
clean:
	rm -rf *.o bmi5
	
deps:
	sudo apt-get install libgtk2.0-dev libgtkgl2.0-dev liblua5.1-dev \
	libgtkglext1-dev freeglut3-dev libmatio-dev libsqlite3-dev libusb-1.0-0.dev \
	libblas-dev liblapack-dev libfftw3-dev libhdf5-serial-dev
	echo "make sure /usr/lib64 is in /etc/ld.so.conf.d/libc.conf"
	echo "otherwise Cg may not be found. "
	