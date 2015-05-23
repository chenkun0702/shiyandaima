KERNELDIR ?=/lib/modules/$(shell uname -r)/build

modules:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules
clean:
	rm -rf *.ko *.o  *.mod*  module* Mo*  
obj-m=test.o
