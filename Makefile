obj-m += apeshit.o
EXTRA_CFLAGS=-I$(PWD)/tracks 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
