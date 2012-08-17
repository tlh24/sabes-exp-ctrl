CC = clang
OBJS = main.o tdt_udp.o glInfo.o glFont.o
CFLAGS=-I/usr/local/include
CFLAGS+=  -g
CFLAGS+= -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare -Wformat=2 \
-Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -pedantic -std=c++0x
LDFLAGS = -lrt -lGL -lGLU -llua5.2
GLIBS = gtk+-2.0 gtkglext-1.0 gtkglext-x11-1.0
GTKFLAGS = `pkg-config --cflags $(GLIBS) `
GTKLD = `pkg-config --libs $(GLIBS) `

all: bmi5

%.o : %.cpp 
	$(CC) -c -o $@ $(CFLAGS) $(GTKFLAGS) $<

bmi5: $(OBJS)
	$(CC) -o $@ $(GTKLD) $(LDFLAGS) -lmatio $(OBJS)
	
clean:
	rm -rf *.o bmi5
	
deps:
	sudo apt-get install libgtk2.0-dev libgtkgl2.0-dev liblua5.2-dev \
	libgtkglext1-dev freeglut3-dev nvidia-cg-toolkit libmatio-dev libsqlite3-dev
	echo "make sure /usr/lib64 is in /etc/ld.so.conf.d/libc.conf"
	echo "otherwise Cg may not be found. "