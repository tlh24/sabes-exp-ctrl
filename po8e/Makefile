
KERNEL = $(shell uname -r)
PLX_SDK_DIR = PO8e_v2/Linux/PlxSdk
MODULE_DIR = /lib/modules/$(KERNEL)/extra
TARGET = /usr/local/lib

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
	install PO8e_v2/Linux/libPO8eStreaming.so $(TARGET)
	install -d $(MODULE_DIR)
	install PO8e_v2/Linux/drivers/$(KERNEL)/Plx9054.ko $(MODULE_DIR)
	install etc/Plx9054.rules /etc/udev/rules.d
	install etc/Plx9054.sh /lib/udev
	depmod
	modprobe Plx9054
