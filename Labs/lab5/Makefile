obj-m += module_a.o
obj-m += module_b.o
obj-m += module_c.o
all:
	make -C /lib/modules/5.4.0-58-generic/build M=$(PWD) modules
clean:
	make -C /lib/modules/5.4.0-58-generic/build M=$(PWD) clean
