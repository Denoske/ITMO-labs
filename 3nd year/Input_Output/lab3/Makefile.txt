obj-m = virt_net_if.o
PWD = $(shell pwd)
all:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" clean
install: all
	sudo insmod virt_net_if.ko
uninstall:
	sudo rmmod virt_net_if.ko
