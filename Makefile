all:
	gcc -c `pkg-config --cflags --libs glib-2.0` my_crypto.c enc_mem.c
	gcc main.c utils.c enc_mem.o  `pkg-config --libs glib-2.0`  -lgcrypt
clean:
	rm a.out *.o
