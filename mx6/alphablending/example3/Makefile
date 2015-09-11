all: ipu-examples

ipu-examples: alpha_ex3.c
	$(CC) -g -O0 -o alpha_ex3 alpha_ex3.c -I /home/mporter/src/wistron/poky/build/tmp/sysroots/michelle2p/usr/src/kernel/include/uapi/ \
	-I /home/mporter/src/wistron/poky/build/tmp/sysroots/michelle2p/usr/src/kernel/include/

clean:
	-rm alpha_ex3

.PHONY: all clean

	
