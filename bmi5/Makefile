CC = g++
OBJS = main.o tdt_udp.o gtkglx.o glInfo.o glFont.o srcView.o
CFLAGS=-I/usr/local/include
CFLAGS+=  -g
CFLAGS+= -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare -Wformat=2 \
-Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -pedantic -std=c++0x
LDFLAGS = -lrt -lGL -lGLU -llua5.1
GLIBS = gtk+-3.0 gtksourceview-3.0
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
	sudo apt-get install libgtk2.0-dev libgtkgl2.0-dev liblua5.1-dev \
	libgtkglext1-dev freeglut3-dev libmatio-dev libsqlite3-dev