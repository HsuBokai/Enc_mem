#ifndef ENC_MEM_H
#define ENC_MEM_H 1

typedef struct _Enc_mem	Enc_mem;
Enc_mem* new_Enc_mem();

void enc_ptr(Enc_mem* obj, unsigned char data[]);
void dec_ptr(Enc_mem* obj, unsigned char get_data[]);

void delete_Enc_mem(Enc_mem* obj);

#endif
