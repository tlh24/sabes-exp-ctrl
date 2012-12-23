
LDFLAGS = -lrt -lPO8eStreaming

all: stream

stream: PO8eTest.cpp
	g++ -o $@ -g $(LDFLAGS) $<

clean:
	rm -rf stream *.o
	
install:
	sudo cp libPO8eStreaming.so /usr/local/lib/
	sudo ldconfig -v | grep PO8