obj-m = my_driver.o
PWD = $(shell pwd)
all:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" clean
install: all
	sudo insmod my_driver.ko
uninstall:
	sudo rmmod my_driver.ko

