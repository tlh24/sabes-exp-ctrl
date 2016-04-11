
# The following can be set at the command line
# ie: make DBG=true JACK=false
#
# install dependencies with make deps
DBG = false
JACK = true
LABJACK = false
OPTO = false

ifeq ($(shell hostname),chupacabra)
	LABJACK = true
endif

ifeq	($(shell hostname),task2go)
	LABJACK = true
endif

ifeq	($(shell hostname),inCage)
	LABJACK = true
endif

ifeq ($(shell lsb_release -sc), jessie)
        CC = clang-3.5
        CPP = clang++-3.5
endif
CC  = clang-3.8
CPP = clang++-3.8
LD  = clang++-3.8

TARGET = /usr/local/bin
BUILDDIR = ./bin
SRCDIR = ./src

SOURCES=$(shell find ./src/ -name *.cpp \
	! -name *u6.cpp \
	! -name *glxgears.cpp)

HEADERS=$(shell find ./include/ -name *.h)

OBJS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:%.cpp=%.o))
OBJS += $(BUILDDIR)/gettime.o $(BUILDDIR)/lconf.o $(BUILDDIR)/random.o

CFLAGS := -Iinclude -I/usr/local/include -I../../myopen/common_host

CFLAGS += -Wall -Wextra -pedantic -Wshadow
CFLAGS += -std=c++11 -Wno-int-to-pointer-cast -Wtrigraphs
CFLAGS += -Wstrict-overflow -fno-strict-aliasing
CFLAGS += -Wcast-align -Wpointer-arith -Wsign-compare
CFLAGS += -Wformat=2 -Wno-format-y2k -Wmissing-braces -Wparentheses
CFLAGS += -Wno-missing-field-initializers
CFLAGS += -Wno-deprecated-declarations #-stdlib=libstdc++
CFLAGS += -Wno-braced-scalar-init -Wno-unused-result

LDFLAGS := -lrt -lGL -lglut -lGLU -lGLEW -lusb-1.0 -lX11 -lpthread

ifeq ($(strip $(DBG)),true)
	CFLAGS  += -O1 -g -DDEBUG -fsanitize=address -fno-inline -fno-omit-frame-pointer
	LDFLAGS += -fsanitize=address -fno-inline -fno-omit-frame-pointer
	JACK = false
else
	CFLAGS += -O3 -march=native -fslp-vectorize-aggressive
endif

ifeq ($(strip $(JACK)),true)
	CFLAGS += -DJACK
	LDFLAGS += -ljack
	OBJS += $(BUILDDIR)/jacksnd.o
endif

ifeq ($(strip $(LABJACK)),true)
	CFLAGS += -DLABJACK
	LDFLAGS += -llabjackusb
	OBJS += $(BUILDDIR)/u6.o
endif

ifeq ($(strip $(OPTO)),true)
	CFLAGS += -DOPTO
endif

# DEPENDENCIES: WE REQUIRE AT LEAST DEBIAN JESSIE
DEPS = clang lldb gcc g++ gdb astyle cppcheck libboost-dev libgtk-3-dev \
libgtkglext1-dev freeglut3-dev libglew-dev libusb-1.0-0-dev \
libmatio-dev libhdf5-7 libhdf5-dev libhdf5-serial-dev \
libblas-dev liblapack-dev libfftw3-dev libgsl0-dev \
libxdg-basedir-dev liblua5.1-0-dev libprocps3-dev \
libpcap-dev winbind zlib1g-dev \
qjackctl libjack-jackd2-dev

LIBS=gtk+-3.0 gsl libxdg-basedir lua5.1 libprocps hdf5 matio
CFLAGS += $(shell pkg-config --cflags $(LIBS))
LDFLAGS += $(shell pkg-config --libs $(LIBS))

all: directories bmi5 glxgears

$(BUILDDIR)/%.o: src/%.cpp
	$(CPP) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: ../../myopen/common_host/%.cpp
	$(CPP) -c $(CFLAGS) $< -o $@

bmi5: $(OBJS)
	$(CPP) -o $@ $(LDFLAGS) -lpcap $(OBJS)

opto: bmi5 # enables packet-capture privelages on bmi5.
	sudo setcap cap_net_raw,cap_net_admin=eip bmi5

glxgears: $(BUILDDIR)/glxgears.o
	$(CPP) -o $@ $(LDFLAGS) $(BUILDDIR)/glxgears.o

clean:
	rm -rf bmi5 glxgears bin/*.o bin/Serialize/*.o bin/Shape/*.o

deps:
	sudo apt-get install $(DEPS)

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

conf:
	install -d $(HOME)/.config/bmi5
	install rc/bmi5.rc -t $(HOME)/.config/bmi5

pretty:
	# "-rm" means that make ignores errors, if any
	astyle -A8 --indent=tab -H -k3 $(HEADERS)
	-rm $(shell find ./include/ -name *.h.orig)

	astyle -A8 --indent=tab -H -k3 $(SOURCES)
	-rm $(shell find ./src/ -name *.cpp.orig)

#Make the Directories
directories:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/Shape
	mkdir -p $(BUILDDIR)/Serialize

#Generate doxygen documentation
doc : ; @echo "Generating program and doc."
	doxygen doc/doxy_config

print-%  : ; @echo $* = $($*)

.PHONY: all clean doc
