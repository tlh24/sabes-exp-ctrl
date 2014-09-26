
LDFLAGS = -lrt -lPO8eStreaming

CPP = g++

MODULE_DIR = /lib/modules/$(shell uname -r)/extra/
TARGET = /usr/local/lib

all: stream

stream: PO8eTest.cpp
	$(CPP) -o $@ -g $(LDFLAGS) $<

clean:
	rm -rf stream *.o
	
install:
	install -d $(TARGET)
	install libPO8eStreaming.so $(TARGET)
	install -d $(MODULE_DIR)
	install Plx9054.ko $(MODULE_DIR)
	install Plx9054.rules /etc/udev/rules.d
	install Plx9054.sh /lib/udev
	depmod
	modprobe Plx9054
