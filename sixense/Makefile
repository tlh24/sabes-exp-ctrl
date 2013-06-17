# ie: make DBG=true
DBG = false

CPP = g++
CC  = gcc

OBJS := src/demo.o 

CFLAGS := -Iinclude -Iinclude
CFLAGS += -Wall -Wcast-align -Wpointer-arith -Wshadow -Wsign-compare \
-Wformat=2 -Wno-format-y2k -Wmissing-braces -Wparentheses -Wtrigraphs \
-Wextra -Werror -pedantic -std=c++11 -Wno-unknown-pragmas
LDFLAGS := -lGL -lGLU -lglut -lsixense_x64 -lsixense_utils_x64

ifeq ($(strip $(DBG)),true)
	CFLAGS  += -g -rdynamic -DDEBUG
	LDFLAGS += -rdynamic
else
	CFLAGS += -O3
endif

all: demo

src/%.o : src/%.cpp 
	$(CPP) -c $(CFLAGS) $(GTKFLAGS) $< -o $@
	
demo: $(OBJS)
	$(CPP) -o $@ $(LDFLAGS) $(OBJS)
	
clean:
	rm -rf src/*.o demo
