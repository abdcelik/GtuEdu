#ifndef ENCDEC_H_
#define ENCDEC_H_
typedef unsigned long long SIZE;
typedef unsigned char BYTE;
int encrypt(BYTE *c, SIZE *clen, BYTE *m, SIZE mlen, BYTE *ad, SIZE adlen,
            BYTE *nsec, BYTE *npub, BYTE *k);

int decrypt(BYTE *m, SIZE *mlen, BYTE *nsec, BYTE *c, SIZE clen, BYTE *ad,
            SIZE adlen, BYTE *npub, BYTE *k);
BYTE *cbc_enc(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss);
BYTE *cbc_dec(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss);
BYTE *ofb_enc(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss);
BYTE *ofb_dec(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss);
#endif // ENCDEC_H_
