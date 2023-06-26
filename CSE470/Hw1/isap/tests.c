#include "tests.h"
#include "encdec.h"
#include "isap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BYTE K[16] = "0708090A0B0C0D0E";
BYTE M[10][32] = {
    "7B94EF35AE55AB272C9C44D6C1CF0102", "40FEAD6FDF1C2D6D6EAE40DEDDFF9F55",
    "CFCFA290EF310E3AC17F94E5FB6A6CB5", "6DCFE6F0AA3C033088ECC0B510A04621",
    "7EB2B5F0E99C87481B0D2B9EED843A6E", "DF2A631E42081B3484F88111E885102A",
    "426624B11EFA922063FFA2819D07B833", "E1634C37D738296C4D451010628F5A68",
    "A510A73839FD7778A28C57597D553835", "2A6734132A1A441D73595388ED99645A"};

BYTE A[16] = "060708090A0B0C0D";

int compare(BYTE *a, BYTE *b) {
  for (int i = 0; i < 32; ++i) {
    if (a[i] != b[i]) {
      return 0;
    }
  }
  return 1;
}

void test_enc_dec() {
  BYTE C[10][32 + TAG_SIZE];
  SIZE C_len[10];
  BYTE decrypted[32];
  SIZE dec_len;
  for (int i = 0; i < 10; i++) {
    encrypt(C[i], &C_len[i], M[i], 32, A, 16, NULL, K, K);
    printf("Message: ");
    for (int j = 0; j < 32; j++) {
      printf("%c", M[i][j]);
    }
    printf("\n");
    printf("Encrypted: ");
    for (int j = 0; j < C_len[i]; j++) {
      printf("%x", C[i][j]);
    }
    printf("\n");
    decrypt(decrypted, &dec_len, NULL, C[i], C_len[i], A, 16, K, K);
    printf("Decrypted: %s\n", decrypted);
    printf("Result: %s\n\n", (compare(M[i], decrypted)) ? "PASS" : "FAIL");
  }
}

void test_cbc() {
  BYTE C[10][32 + TAG_SIZE];
  SIZE C_len[10];
  BYTE *decrypted;
  SIZE dec_len;
  for (int i = 0; i < 10; i++) {
    printf("Message: ");
    for (int j = 0; j < 32; j++) {
      printf("%c", M[i][j]);
    }
    printf("\n");
    BYTE *cbc = cbc_enc(M[i], 32, K, K, 8);
    decrypted = cbc_dec(cbc, 32, K, K, 8);

    printf("Result: %s\n\n", (compare(M[i], decrypted)) ? "PASS" : "FAIL");
  }
}

void test_ofb() {
  BYTE C[10][32 + TAG_SIZE];
  SIZE C_len[10];
  BYTE *decrypted;
  SIZE dec_len;
  for (int i = 0; i < 10; i++) {
    printf("Message: ");
    for (int j = 0; j < 32; j++) {
      printf("%c", M[i][j]);
    }
    printf("\n");
    BYTE *ofb = ofb_enc(M[i], 32, K, K, 8);
    decrypted = ofb_dec(ofb, 32, K, K, 8);

    printf("Result: %s\n\n", (compare(M[i], decrypted)) ? "PASS" : "FAIL");
  }
}
