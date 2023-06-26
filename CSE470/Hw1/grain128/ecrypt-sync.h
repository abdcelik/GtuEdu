/* ecrypt-sync.h */


#ifndef ECRYPT_SYNC
#define ECRYPT_SYNC

#include "ecrypt-portable.h"


#define ECRYPT_NAME "Grain128"     
#define ECRYPT_PROFILE "CRYPTO"



#define ECRYPT_MAXKEYSIZE 128                 
#define ECRYPT_KEYSIZE(i) (128 + (i))      

#define ECRYPT_MAXIVSIZE 96                   
#define ECRYPT_IVSIZE(i) (96 + (i))        


// General structure for the LFSR and NFSR
typedef struct
{
	u8 LFSR[128];
	u8 NFSR[128];
	const u8* p_key;
	u32 keysize;
	u32 ivsize;

} ECRYPT_ctx;


void ECRYPT_init();


void ECRYPT_keysetup(ECRYPT_ctx* ctx, const u8* key,u32 keysize,u32 ivsize);                 


void ECRYPT_ivsetup(ECRYPT_ctx* ctx,const u8* iv);



void ECRYPT_encrypt_bytes(ECRYPT_ctx* ctx, const u8* plaintext, u8* ciphertext, u32 msglen);                

void ECRYPT_decrypt_bytes(ECRYPT_ctx* ctx, const u8* ciphertext, u8* plaintext, u32 msglen);               



#define ECRYPT_GENERATES_KEYSTREAM
#ifdef ECRYPT_GENERATES_KEYSTREAM

void ECRYPT_keystream_bytes(
  ECRYPT_ctx* ctx,
  u8* keystream,
  u32 length);          

#endif


#define ECRYPT_ALL       

void ECRYPT_encrypt_packet(ECRYPT_ctx* ctx, const u8* iv,const u8* plaintext, u8* ciphertext, u32 msglen);

void ECRYPT_decrypt_packet(ECRYPT_ctx* ctx, const u8* iv,const u8* ciphertext, u8* plaintext, u32 msglen);



#define ECRYPT_BLOCKLENGTH 4                  

#define ECRYPT_USES_DEFAULT_BLOCK_MACROS      
#ifdef ECRYPT_USES_DEFAULT_BLOCK_MACROS

#define ECRYPT_encrypt_blocks(ctx, plaintext, ciphertext, blocks)  \
  ECRYPT_encrypt_bytes(ctx, plaintext, ciphertext,                 \
    (blocks) * ECRYPT_BLOCKLENGTH)

#define ECRYPT_decrypt_blocks(ctx, ciphertext, plaintext, blocks)  \
  ECRYPT_decrypt_bytes(ctx, ciphertext, plaintext,                 \
    (blocks) * ECRYPT_BLOCKLENGTH)

#ifdef ECRYPT_GENERATES_KEYSTREAM

#define ECRYPT_keystream_blocks(ctx, keystream, blocks)            \
  ECRYPT_AE_keystream_bytes(ctx, keystream,                        \
    (blocks) * ECRYPT_BLOCKLENGTH)

#endif

#else

void ECRYPT_encrypt_blocks(ECRYPT_ctx* ctx, const u8* plaintext, u8* ciphertext, u32 blocks);                 

void ECRYPT_decrypt_blocks(ECRYPT_ctx* ctx, const u8* ciphertext, u8* plaintext, u32 blocks);                 

#ifdef ECRYPT_GENERATES_KEYSTREAM

void ECRYPT_keystream_blocks(ECRYPT_AE_ctx* ctx,const u8* keystream,u32 blocks);                

#endif

#endif

#endif
