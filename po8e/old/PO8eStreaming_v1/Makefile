
LDFLAGS = -lrt -lPO8eStreaming

CPP = g++

all: stream

stream: PO8eTest.cpp
	$(CPP) -o $@ -g $(LDFLAGS) $<

clean:
	rm -rf stream *.o
	
install:
	sudo cp libPO8eStreaming.so /usr/local/lib
	sudo ./mkdevs
