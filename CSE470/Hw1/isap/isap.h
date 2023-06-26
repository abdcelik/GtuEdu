#ifndef ISAP_H_
#define ISAP_H_

#include "ascon.h"
/*
** ISAP-A-128A Ascon-p Rounds from reccommended parameter sets
*/
#define Sh 12
#define Sb 1
#define Se 6
#define Sk 12

/*
** Rate of permutations Ph and Pb
*/
#define Rh 64
#define Rb 1

#define STATE_SIZE 40          // 320 bit state size in bytes
#define Rh_SIZE ((Rh + 7) / 8) // 64 bit rH size in bytes

#define IV_SIZE 8
#define TAG_SIZE 16
#define SEC_K 128

void IsapMac(BYTE *K, BYTE *N, BYTE *A, SIZE A_len, BYTE *C, SIZE C_len,
             BYTE *T);

void IsapRK(BYTE *K, BYTE *IV, BYTE *input, SIZE input_len, BYTE *output,
            SIZE output_len);

void IsapEnc(BYTE *K, BYTE *N, BYTE *M, SIZE M_len, BYTE *C);

#endif // ISAP_H_
