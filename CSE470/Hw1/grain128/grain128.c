// Grain 128 general purpose 
//Furkan Celen
#include "ecrypt-sync.h"




u8 grain_keystream(ECRYPT_ctx* ctx) {
	u8 i,NBit,LBit,outbit;
	
	outbit = ctx->NFSR[2]^ctx->NFSR[15]^ctx->NFSR[36]^ctx->NFSR[45]^ctx->NFSR[64]^ctx->NFSR[73]^ctx->NFSR[89]^ctx->LFSR[93]^(ctx->NFSR[12]&ctx->LFSR[8])^(ctx->LFSR[13]&ctx->LFSR[20])^(ctx->NFSR[95]&ctx->LFSR[42])^(ctx->LFSR[60]&ctx->LFSR[79])^(ctx->NFSR[12]&ctx->NFSR[95]&ctx->LFSR[95]);
	NBit=ctx->LFSR[0]^ctx->NFSR[0]^ctx->NFSR[26]^ctx->NFSR[56]^ctx->NFSR[91]^ctx->NFSR[96]^(ctx->NFSR[3]&ctx->NFSR[67])^(ctx->NFSR[11]&ctx->NFSR[13])^(ctx->NFSR[17]&ctx->NFSR[18])^(ctx->NFSR[27]&ctx->NFSR[59])^(ctx->NFSR[40]&ctx->NFSR[48])^(ctx->NFSR[61]&ctx->NFSR[65])^(ctx->NFSR[68]&ctx->NFSR[84]);
	LBit=ctx->LFSR[0]^ctx->LFSR[7]^ctx->LFSR[38]^ctx->LFSR[70]^ctx->LFSR[81]^ctx->LFSR[96];
	
	for (i=1;i<(ctx->keysize);++i) {
		ctx->NFSR[i-1]=ctx->NFSR[i];
		ctx->LFSR[i-1]=ctx->LFSR[i];
	}
	ctx->NFSR[(ctx->keysize)-1]=NBit;
	ctx->LFSR[(ctx->keysize)-1]=LBit;
	return outbit;
}



void ECRYPT_keysetup(ECRYPT_ctx* ctx, const u8* key, u32 keysize,u32 ivsize)			
{
	ctx->p_key=key;
	ctx->keysize=keysize;
	ctx->ivsize=ivsize;
}

//Load the key and perform initial clockings.
//registers are loaded for nfsr and lfsr with key and IV
void ECRYPT_ivsetup(ECRYPT_ctx* ctx, const u8* iv)
{
	u32 i,j;
	u8 outbit;
	
	for (i=0;i<(ctx->ivsize)/8;++i) {
		for (j=0;j<8;++j) {
			ctx->NFSR[i*8+j]=((ctx->p_key[i]>>j)&1);  
			ctx->LFSR[i*8+j]=((iv[i]>>j)&1);
		}
	}
	for (i=(ctx->ivsize)/8;i<(ctx->keysize)/8;++i) {
		for (j=0;j<8;++j) {
			ctx->NFSR[i*8+j]=((ctx->p_key[i]>>j)&1);
			ctx->LFSR[i*8+j]=1;
		}
	}
	
	for (i=0;i<256;++i) {
		outbit=grain_keystream(ctx);
		ctx->LFSR[127]^=outbit;
		ctx->NFSR[127]^=outbit;             
	}
}

//Generating keystream bytes
void ECRYPT_keystream_bytes(ECRYPT_ctx* ctx, u8* keystream, u32 msglen)
{
	u32 i,j;
	for (i = 0; i < msglen; ++i) {
		keystream[i]=0;
		for (j = 0; j < 8; ++j) {
			keystream[i]|=(grain_keystream(ctx)<<j);
		}
	}
}

//encryption process
void ECRYPT_encrypt_bytes(ECRYPT_ctx* ctx, const u8* plaintext, u8* ciphertext, u32 msglen)
{
	u32 i,j;
	u8 k=0;
	for (i=0;i<msglen;++i) {
		k=0;
		for (j=0;j<8;++j) {
			k|=(grain_keystream(ctx)<<j);
		}
		ciphertext[i]=plaintext[i]^k;
	}
}

//decryption process
void ECRYPT_decrypt_bytes(ECRYPT_ctx* ctx, const u8* ciphertext, u8* plaintext, u32 msglen)
{
	u32 i,j;
	u8 k=0;
	for (i=0;i<msglen;++i) {
		k=0;
		for (j = 0; j < 8; ++j) {
			k|=(grain_keystream(ctx)<<j);
		}
		plaintext[i]=ciphertext[i]^k;
	}
}

void ECRYPT_init(void){}