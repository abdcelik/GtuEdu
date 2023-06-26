#include "encdec.h"
#include "isap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encrypt(BYTE *c, SIZE *clen, BYTE *m, SIZE mlen, BYTE *ad, SIZE adlen,
            BYTE *nsec, BYTE *npub, BYTE *k) {
  *clen = mlen + TAG_SIZE;

  if (mlen > 0) {
    IsapEnc(k, npub, m, mlen, c);
  }

  BYTE *tag = c + mlen;
  IsapMac(k, npub, ad, adlen, c, mlen, tag);
  return 0;
}

int decrypt(BYTE *m, SIZE *mlen, BYTE *nsec, BYTE *c, SIZE clen, BYTE *ad,
            SIZE adlen, BYTE *npub, BYTE *k) {
  *mlen = clen - TAG_SIZE;

  BYTE tag[TAG_SIZE];
  IsapMac(k, npub, ad, adlen, c, *mlen, tag);

  unsigned long eq_cnt = 0;
  for (unsigned int i = 0; i < TAG_SIZE; i++) {
    eq_cnt += (tag[i] == c[(*mlen) + i]);
  }

  if (eq_cnt == (unsigned long)TAG_SIZE) {
    if (*mlen > 0) {
      IsapEnc(k, npub, c, *mlen, m);
    }
    return 0;
  } else {
    return -1;
  }
}
BYTE *cbc_enc(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss) {
  int block_size = mlen / ss;
  int rem = mlen - block_size * ss;
  int start, end, i = 0;
  BYTE *blocks[ss];
  SIZE blocksizes[ss];

  for (start = 0, end = block_size; start < mlen;
       start = end, end = start + block_size) {
    if (rem) {
      end++;
      rem--;
    }

    blocks[i] = malloc((end - start) * sizeof(BYTE *));
    blocksizes[i] = end - start;

    for (int j = 0; j < end - start; j++) {
      blocks[i][j] = M[j + start];
    }
    ++i;
  }

  BYTE *ciphers[ss];
  BYTE *ived = malloc(blocksizes[0] * sizeof(BYTE));
  BYTE *x_tmp = malloc(blocksizes[0]);

  for (i = 0; i < ss; i++) {
    ciphers[i] = malloc(blocksizes[i] * sizeof(BYTE *));
  }

  for (i = 0; i < blocksizes[0]; i++) {
    ived[i] = blocks[0][i] ^ 0;
  }
  IsapEnc(kp, npubp, ived, blocksizes[0], ciphers[0]);

  for (i = 1; i < ss; ++i) {
    for (int j = 0; j < blocksizes[i]; j++) {
      x_tmp = realloc(x_tmp, blocksizes[i]);
      x_tmp[j] = ciphers[i - 1][j] ^ blocks[i][j];
    }
    IsapEnc(kp, npubp, x_tmp, blocksizes[i], ciphers[i]);
  }

  BYTE *final = malloc(sizeof(BYTE) * mlen);
  int cnt = 0;
  for (i = 0; i < ss; ++i) {
    memcpy(final + cnt, ciphers[i], blocksizes[i]);
    cnt += blocksizes[i];
  }

  printf("CBC Encrypted: ");
  for (i = 0; i < mlen; ++i) {
    printf("%x", final[i]);
  }
  printf("\n");
  return final;
}

BYTE *cbc_dec(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss) {
  int block_size = mlen / ss;
  int rem = mlen - block_size * ss;
  int start, end, i = 0;
  BYTE *blocks[ss];
  SIZE blocksizes[ss];

  for (start = 0, end = block_size; start < mlen;
       start = end, end = start + block_size) {
    if (rem) {
      end++;
      rem--;
    }

    blocks[i] = malloc((end - start) * sizeof(BYTE *));
    blocksizes[i] = end - start;

    for (int j = 0; j < end - start; j++) {
      blocks[i][j] = M[j + start];
    }
    ++i;
  }

  BYTE *ciphers[ss];
  BYTE *ived = malloc(blocksizes[0] * sizeof(BYTE));
  BYTE *x_tmp = malloc(blocksizes[0]);

  for (i = 0; i < ss; i++) {
    ciphers[i] = malloc(blocksizes[i] * sizeof(BYTE *));
  }

  for (i = ss - 1; i > 0; --i) {
    x_tmp = realloc(x_tmp, blocksizes[i]);
    IsapEnc(kp, npubp, blocks[i], blocksizes[i], x_tmp);

    for (int j = 0; j < blocksizes[i]; j++) {
      ciphers[i][j] = x_tmp[j] ^ blocks[i - 1][j];
    }
  }

  for (i = 0; i < blocksizes[0]; i++) {
    ived[i] = blocks[0][i] ^ 0;
  }
  IsapEnc(kp, npubp, ived, blocksizes[0], ciphers[0]);

  BYTE *final = malloc(sizeof(BYTE) * mlen);
  int cnt = 0;
  for (i = 0; i < ss; ++i) {
    memcpy(final + cnt, ciphers[i], blocksizes[i]);
    cnt += blocksizes[i];
  }

  printf("CBC Decrypted: ");
  for (i = 0; i < mlen; ++i) {
    printf("%c", final[i]);
  }
  printf("\n");
  return final;
}

BYTE *ofb_enc(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss) {
  int block_size = mlen / ss;
  int rem = mlen - block_size * ss;
  int start, end, i = 0;
  BYTE *blocks[ss];
  SIZE blocksizes[ss];

  for (start = 0, end = block_size; start < mlen;
       start = end, end = start + block_size) {
    if (rem) {
      end++;
      rem--;
    }

    blocks[i] = malloc((end - start) * sizeof(BYTE *));
    blocksizes[i] = end - start;

    for (int j = 0; j < end - start; j++) {
      blocks[i][j] = M[j + start];
    }
    ++i;
  }

  BYTE *ciphers[ss];
  BYTE *ived = malloc(blocksizes[0] * sizeof(BYTE));
  BYTE *x_tmp = malloc(blocksizes[0]);

  for (i = 0; i < ss; i++) {
    ciphers[i] = malloc(blocksizes[i] * sizeof(BYTE *));
  }

  for (i = 0; i < blocksizes[0]; i++) {
    ived[i] = 0;
  }
  IsapEnc(kp, npubp, ived, blocksizes[0], x_tmp);

  for (i = 0; i < blocksizes[0]; i++) {
    ciphers[0][i] = x_tmp[i] ^ blocks[0][i];
  }

  for (i = 1; i < ss; ++i) {
    x_tmp = realloc(x_tmp, blocksizes[i - 1]);
    IsapEnc(kp, npubp, ciphers[i - 1], blocksizes[i - 1], x_tmp);
    for (int j = 0; j < blocksizes[i]; j++) {
      ciphers[i][j] = x_tmp[j] ^ blocks[i][j];
    }
  }
  BYTE *final = malloc(sizeof(BYTE) * mlen);
  int cnt = 0;
  for (i = 0; i < ss; ++i) {
    memcpy(final + cnt, ciphers[i], blocksizes[i]);
    cnt += blocksizes[i];
  }

  printf("OFB Encrypted: ");
  for (i = 0; i < mlen; ++i) {
    printf("%x", final[i]);
  }
  printf("\n");
  return final;
}

BYTE *ofb_dec(BYTE *M, SIZE mlen, BYTE *npubp, BYTE *kp, int ss) {
  int block_size = mlen / ss;
  int rem = mlen - block_size * ss;
  int start, end, i = 0;
  BYTE *blocks[ss];
  SIZE blocksizes[ss];

  for (start = 0, end = block_size; start < mlen;
       start = end, end = start + block_size) {
    if (rem) {
      end++;
      rem--;
    }

    blocks[i] = malloc((end - start) * sizeof(BYTE *));
    blocksizes[i] = end - start;

    for (int j = 0; j < end - start; j++) {
      blocks[i][j] = M[j + start];
    }
    ++i;
  }

  BYTE *ciphers[ss];
  BYTE *ived = malloc(blocksizes[0] * sizeof(BYTE));
  BYTE *x_tmp = malloc(blocksizes[0]);

  for (i = 0; i < ss; i++) {
    ciphers[i] = malloc(blocksizes[i] * sizeof(BYTE *));
  }

  for (i = ss - 1; i > 0; --i) {
    x_tmp = realloc(x_tmp, blocksizes[i]);
    IsapEnc(kp, npubp, blocks[i], blocksizes[i], x_tmp);

    for (int j = 0; j < blocksizes[i]; j++) {
      ciphers[i][j] = x_tmp[j] ^ blocks[i - 1][j];
    }
  }

  for (i = 0; i < blocksizes[0]; i++) {
    ived[i] = blocks[0][i] ^ 0;
  }
  IsapEnc(kp, npubp, ived, blocksizes[0], ciphers[0]);

  BYTE *final = malloc(sizeof(BYTE) * mlen);
  int cnt = 0;
  for (i = 0; i < ss; ++i) {
    memcpy(final + cnt, ciphers[i], blocksizes[i]);
    cnt += blocksizes[i];
  }

  printf("OFB Decrypted: ");
  for (i = 0; i < mlen; ++i) {
    printf("%c", final[i]);
  }
  printf("\n");
  return final;
}
