#include <stdio.h>
#include <string.h>
#include "ecrypt-sync.h"




void printData(u8 *key, u8 *IV, u8 *ks,u8 *plain,u8 *ciphert,int mode);
void tests();
int main(int argc, char **argv) {	
	printf("GRAIN-128AED:\n");
	tests();

	return 0;
}



void tests() {
	
	ECRYPT_ctx ctx;
	u8 key1[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		IV1[12] = {0xfe,0xea,0xdf,0x00,0xae,0xcd,0x00,0xed,0xdb,0x67,0x00,0x00},
	    ks[16],
	    ptext[16]={0x07,0x27,0x47,0x67,0x87,0xa7,0xc7,0xe7,0x17,0x37,0x57,0x77,0x97,0xb7,0xd7,0xf7},//{"Hello friend."},
	    ctext[16],dectext[16];

	u8 key2[16] = {0x07,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x12,0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0},
		IV2[12] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x12,0x34,0x56,0x78};
	u32 len=16;
	ECRYPT_keysetup(&ctx,key2,128,96);
	ECRYPT_ivsetup(&ctx,IV1);
	ECRYPT_keystream_bytes(&ctx,ks,16);
	ECRYPT_encrypt_bytes(&ctx,ctext,ptext,len);
	int mode=0;
	printf("\nPart1:\nEncryption process");
	//printf(plain);
	
	printData(key2,IV1,ks,ptext,ctext,mode);

	printf("\n\nDecryption process");
	ECRYPT_decrypt_bytes(&ctx,ptext,ctext,len );
	printf("\nPlaintext:  ");	
	for (int i=0;i<16;++i) printf("%02x",ptext[i]);



	printf("\n");
	ECRYPT_keysetup(&ctx,key2,128,96);
	ECRYPT_ivsetup(&ctx,IV2);
	ECRYPT_keystream_bytes(&ctx,ks,16);
	ECRYPT_encrypt_bytes(&ctx,ctext,ptext,len);
	mode=1;
	printf("\nPart2:\nOFB Encryption process");
	//printf(plain);
	printData(key2,IV1,ks,ptext,ctext,mode);

	printf("\n\nDecryption process");
	ECRYPT_decrypt_bytes(&ctx,ptext,ctext,len );
	printf("\nPlaintext:  ");	
	for (int i=0;i<16;++i) printf("%02x",ptext[i]);

	printf("\n");
	mode=2;	
	printf("\nPart3:\nCBC Encryption process");
	//printf(plain);
	ECRYPT_ivsetup(&ctx,IV1);
	ECRYPT_keysetup(&ctx,key2,128,96);
	
	ECRYPT_keystream_bytes(&ctx,ks,16);
	ECRYPT_encrypt_bytes(&ctx,ctext,ptext,len);
	printData(key2,IV1,ks,ptext,ctext,mode);

	printf("\n\nDecryption process");
	ECRYPT_decrypt_bytes(&ctx,ptext,ctext,len );
	printf("\nPlaintext:  ");	
	for (int i=0;i<16;++i) printf("%02x",ptext[i]);
		printf("\n");
	
}

void printData(u8 *key, u8 *IV, u8 *ks,u8 *plain,u8 *ciphert,const int mode) {
	u32 i;
	printf("\n\nkey:        ");
	for (i=0;i<16;++i) printf("%02x",key[i]);
	if(mode==2){
	printf("\nGenerated ıv:        ");
	for (i=0;i<12;++i) printf("%02x",IV[i]);
	}	
	printf("\nGenerated keystream:  ");
	for (i=0;i<16;++i) printf("%02x",ks[i]);
	printf("\nPlaintext:  ");	
	for (i=0;i<16;++i) printf("%02x",plain[i]);
	printf("\n\nCipheredtext:  ");	
	for (i=0;i<16;++i) printf("%02x",ciphert[i]);	
		

}

