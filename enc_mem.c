#include <stdio.h>
#include <stdlib.h>

#include "my_crypto.h"
#include "enc_mem.h"

struct _Enc_mem {
	unsigned char* _ptr;
	unsigned int _data_len;
};

Enc_mem* new_Enc_mem(unsigned int len) {
#ifdef DEBUG
	fprintf(stderr, "in new_Enc_mem\n");
#endif
	Enc_mem* ret = malloc(sizeof(Enc_mem));
	ret->_ptr = NULL;
	ret->_data_len = len;
	return ret;
}

void enc_ptr(Enc_mem* obj, unsigned char data[]) {
	unsigned char* _ptr2 = malloc(obj->_data_len);
	if(obj->_ptr != NULL) free(obj->_ptr);
	obj->_ptr = _ptr2;  // another address 
	fprintf(stderr, "another address = %p\n", obj->_ptr);

	My_crypto* my_crypto = new_My_crypto();
	init_My_crypto(my_crypto, "AES128", GCRY_CIPHER_MODE_CFB);
	unsigned int key_len = sizeof(unsigned char*);
	unsigned char key[key_len];
	int i = 0;
	for(i = 0; i<key_len; ++i) {
		unsigned int shift = 8*(key_len-i-1);
		key[i] = (unsigned char)((int)(obj->_ptr)>>shift);
	}
	my_enc(my_crypto, key, key_len, data, obj->_data_len, obj->_ptr);
	memset(key, '\0', key_len);
	delete_My_crypto(my_crypto);
}


void dec_ptr(Enc_mem* obj, unsigned char get_data[]){
	My_crypto* my_crypto = new_My_crypto();
	init_My_crypto(my_crypto, "AES128", GCRY_CIPHER_MODE_CFB);
	unsigned int key_len = sizeof(unsigned char*);
	unsigned char key[key_len];
	int i = 0;
	for(i = 0; i<key_len; ++i) {
		unsigned int shift = 8*(key_len-i-1);
		key[i] = (unsigned char)((int)(obj->_ptr)>>shift);
	}
	my_dec(my_crypto, key, key_len, obj->_ptr, obj->_data_len, get_data);
	memset(key, '\0', key_len);
	delete_My_crypto(my_crypto);

	memset(obj->_ptr, '\0', obj->_data_len);
	enc_ptr(obj, get_data);
}

void delete_Enc_mem(Enc_mem* obj) {
#ifdef DEBUG
	fprintf(stderr, "in delete_Enc_mem\n");
#endif
	if(obj->_ptr != NULL)
		free(obj->_ptr);

	free(obj);
	obj = NULL;
}


