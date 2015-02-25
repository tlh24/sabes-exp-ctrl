
KERNEL = $(shell uname -r)
PLX_SDK_DIR = PO8e_v2/Linux/PlxSdk
DEBIAN_VERSION = $(shell lsb_release -sc)

MODULE_DIR = /lib/modules/$(KERNEL)/extra
TARGET = /usr/local/lib

ifeq ($(DEBIAN_VERSION), jessie) 
	# eglibc 2.14
	STREAMING_LIB = PO8e_v2/Linux/libPO8eStreaming.so
else
	ifeq ($(DEBIAN_VERSION), wheezy)
		# eglibc 2.13
		STREAMING_LIB = old/PO8e-for-3.2.0-3-amd64/libPO8eStreaming.so
	endif
endif


all: driver

driver:
	cd $(PLX_SDK_DIR)/Driver ; \
	./builddriver 9054
	install -d PO8e_v2/Linux/drivers/$(KERNEL)
	install $(PLX_SDK_DIR)/Driver/Plx9054/Plx9054.ko PO8e_v2/Linux/drivers/$(KERNEL)
	
clean:
	cd $(PLX_SDK_DIR)/Driver ; \
	./builddriver 9054 cleanall

install:
	install -d $(TARGET)
	install $(STREAMING_LIB) $(TARGET)
	install -d $(MODULE_DIR)
	install PO8e_v2/Linux/drivers/$(KERNEL)/Plx9054.ko $(MODULE_DIR)
	install etc/Plx9054.rules /etc/udev/rules.d
	install etc/Plx9054.sh /lib/udev
	depmod
	modprobe Plx9054
