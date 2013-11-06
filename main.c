#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enc_mem.h"

#define ANS "123456789"

int main(int argc, char *argv[])
{
	printf("helloworld is running !!! \n");

	unsigned int data_len = strlen(ANS) + 1;
	char data[] = ANS;

	Enc_mem* obj = new_Enc_mem(data_len);
	enc_ptr(obj, data);
	memset(data, '\0', data_len);

	char get_data[data_len];
	int i = 0;
	for(i = 0; i<13; ++i)
	{
		dec_ptr(obj, get_data);
		if(strcmp(get_data, ANS)!=0) fprintf(stderr, "fail !!!\n");
		else fprintf(stderr, "success!!\n");
		memset(get_data, '\0', data_len);
	}	
	
	delete_Enc_mem(obj);
	return 0;
}
