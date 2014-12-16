
# The following can be set at the command line
# ie: make DBG=true JACK=false
#
# install dependencies with make deps
DBG = false
JACK = true
LABJACK = false

ifeq ($(shell hostname),chupacabra)
	LABJACK = true
endif

CPP = g++
CC  = gcc
TARGET = /usr/local/bin

OBJS := src/main.o src/tdt_udp.o src/glInfo.o src/glFont.o src/polhemus.o \
	src/writematlab.o src/gettime.o 

CFLAGS := -Iinclude -I/usr/local/include -I../../myopen/common_host
CFLAGS += -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare \
-Wformat=2 -Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -Werror -pedantic -Wno-deprecated-declarations -std=c++11 
LDFLAGS := -lrt -lGL -lGLU -lGLEW -lusb-1.0 -lX11 -lpthread

ifeq ($(strip $(DBG)),true)
	CFLAGS  += -O0 -g -rdynamic -DDEBUG
	LDFLAGS += -rdynamic
else
	CFLAGS += -O3
endif

ifeq ($(strip $(JACK)),true)
	CFLAGS += -DJACK
	LDFLAGS += -ljack
	OBJS += src/jacksnd.o
endif

ifeq ($(strip $(LABJACK)),true)
	CFLAGS += -DLABJACK
	LDFLAGS += -llabjackusb
	OBJS += src/u6.o
endif
	
ifeq ($(shell lsb_release -sc), wheezy)
	HDFLIB = -lhdf5
else 
	ifeq ($(shell lsb_release -sc), jessie)
		HDFLIB = -lhdf5_serial
	endif
endif

GLIBS = gtk+-3.0 gsl
GTKFLAGS = `pkg-config --cflags $(GLIBS) `
GTKLD = `pkg-config --libs $(GLIBS) `

all: bmi5 glxgears

src/%.o: src/%.cpp 
	$(CPP) -c $(CFLAGS) $(GTKFLAGS) $< -o $@
	
src/%.o: ../../myopen/common_host/%.cpp
	$(CPP) -c $(CFLAGS) $(GTKFLAGS) $< -o $@

bmi5: $(OBJS)
	$(CPP) -o $@ $(GTKLD) $(LDFLAGS) $(HDFLIB) -lmatio -lpcap $(OBJS)
	
opto: bmi5 # enables packet-capture privelages on bmi5. 
	sudo setcap cap_net_raw,cap_net_admin=eip bmi5
	
glxgears: src/glxgears.c
	$(CPP) -O3 -o $@ -lrt -lGL -lX11 $<
	
clean:
	rm -rf src/*.o bmi5 glxgears
	
deps:
	sudo apt-get install gcc g++ gdb libboost-dev libgtk-3-dev \
	libgtkglext1-dev freeglut3-dev libusb-1.0-0-dev libglew-dev \
	libblas-dev liblapack-dev libfftw3-dev qjackctl \
	libjack-jackd2-dev libpcap-dev winbind astyle cppcheck \
	libhdf5-7 libhdf5-dev libhdf5-serial-dev zlib1g zlib1g-dev
	@echo ""
	@echo "  Note: please download and install libmatio version >= 1.50"

check:
	cppcheck -Iinclude -I/usr/local/include -I../../myopen/common_host \
	--enable=all \
	src/*.cpp

install:
	install -d $(TARGET)
	install bmi5 -t $(TARGET)
	install -d $(TARGET)/glsl
	install glsl/fragment.glsl -t $(TARGET)/glsl
	install glsl/vertex.glsl -t $(TARGET)/glsl
	install glsl/vertex_flatcolor.glsl -t $(TARGET)/glsl
	install -d $(TARGET)/matlab
	install matlab/bmi5_mmap.cpp -t $(TARGET)/matlab
	install -d /usr/local/include
	install ../../myopen/common_host/mmaphelp.h -t /usr/local/include

pretty:
	# "-rm" means that make ignores errors, if any
	astyle -A8 --indent=tab -H -k3 include/*.h
	-rm include/*.h.orig
	astyle -A8 --indent=tab -H -k3 src/*.cpp
	-rm src/*.cpp.orig
