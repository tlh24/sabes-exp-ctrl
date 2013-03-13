# The following can be set at the command line
# ie: make DBG=true JACK=false
DBG = true
JACK = false

CPP = g++
CC  = gcc

OBJS := src/main.o src/tdt_udp.o src/glInfo.o src/glFont.o src/polhemus.o \
	src/writematlab.o ../../myopen/common_host/gettime.o

CFLAGS := -Iinclude -I/usr/local/include -I../../myopen/common_host
CFLAGS += -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare \
-Wformat=2 -Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -Werror -pedantic -std=c++11 
LDFLAGS := -lrt -lGL -lGLU -lGLEW -lusb-1.0

ifeq ($(strip $(DBG)),true)
	CFLAGS  += -g -rdynamic -DDEBUG
	LDFLAGS += -rdynamic
else
	CFLAGS += -O3
endif

ifeq ($(strip $(JACK)),true)
	CFLAGS += -DJACK
	LDFLAGS += -ljack
	OBJS += ../../myopen/common_host/jacksnd.o
endif
	
GLIBS = gtk+-3.0
GTKFLAGS = `pkg-config --cflags $(GLIBS) `
GTKLD = `pkg-config --libs $(GLIBS) `

all: bmi5 glxgears

src/%.o : src/%.cpp 
	$(CPP) -c $(CFLAGS) $(GTKFLAGS) $< -o $@
	
%.o: ../../myopen/common_host/%.cpp\
	$(CPP) -c $(CFLAGS) $(GTKFLAGS) $< -o $@

bmi5: $(OBJS)
	$(CPP) -o $@ $(GTKLD) $(LDFLAGS) -lmatio -lpcap $(OBJS)
	
opto: bmi5 # enables packet-capture privelages on bmi5. 
	sudo setcap cap_net_raw,cap_net_admin=eip bmi5
	sudo setcap cap_net_raw,cap_net_admin=eip /usr/bin/gdb
	
glxgears: src/glxgears.c
	$(CPP) -O3 -o $@ -lrt -lGL $<
	
clean:
	rm -rf src/*.o bmi5 glxgears
	
deps:
	sudo apt-get install gcc g++ gdb libboost-dev libgtk-3-dev \
	libgtkglext1-dev freeglut3-dev libmatio-dev libusb-1.0-0-dev libglew-dev \
	libblas-dev liblapack-dev libfftw3-dev libhdf5-serial-dev qjackctl \
	libjack-jackd2-dev libpcap-dev winbind
