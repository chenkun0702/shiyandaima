#KERNELDIR ?=/lib/modules/$(shell uname -r)/build
KERNELDIR ?=/home/linux/linux-2.6.35

modules:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules
clean:
	rm -rf *.ko *.o  *.mod*  module* Mo*  
obj-m=test1.o
