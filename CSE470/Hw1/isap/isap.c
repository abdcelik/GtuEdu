#include "isap.h"
#include "ascon.h"
#include <string.h>

void IsapRK(BYTE *K, BYTE *IV, BYTE *input, SIZE input_len, BYTE *output,
            SIZE output_len) {

  BYTE state[STATE_SIZE];
  BYTE current_bit;
  memset(state, 0, STATE_SIZE);
  add_to_state(state, K, 0, 16);
  add_to_state(state, IV, 16, IV_SIZE);
  s_box(state, Sk);

  /*
  ** Absorbing
  */
  for (size_t i = 0; i < input_len * 8 - 1; i++) {
    size_t index_byte = i / 8;
    size_t index_bit = 7 - (i % 8);
    current_bit = ((input[index_byte] >> index_bit) & 0x01) << 7;
    add_to_state(state, &current_bit, 0, 1);
    s_box(state, Sb);
  }
  current_bit = (input[input_len - 1] & 0x01) << 7;
  add_to_state(state, (const unsigned char *)&current_bit, 0, 1);
  s_box(state, Sk);

  /*
  ** Squeezing
  */
  memcpy(output, state, output_len);
}

void IsapEnc(BYTE *K, BYTE *N, BYTE *M, SIZE M_len, BYTE *C) {
  BYTE state[STATE_SIZE];
  BYTE IVKe[] = {0x03, SEC_K, Rh, Rb, Sh, Sb, Se, Sk};
  size_t bytes_remain = 0;

  IsapRK(K, IVKe, N, 16, state, STATE_SIZE - 16);
  modify_state_buffer(state, N, STATE_SIZE - 16, 16);

  for (SIZE i = 0; i < M_len; i++) {
    if (bytes_remain == 0) {
      s_box(state, Se);
      bytes_remain = Rh_SIZE;
    }
    BYTE key_part;
    memcpy(&key_part, state + (i % Rh_SIZE), 1);
    C[i] = M[i] ^ key_part;
    --bytes_remain;
  }
}

void IsapMac(BYTE *K, BYTE *N, BYTE *A, SIZE A_len, BYTE *C, SIZE C_len,
             BYTE *T) {

  BYTE state[STATE_SIZE];
  BYTE IVA[] = {0x01, SEC_K, Rh, Rb, Sh, Sb, Se, Sk};

  memset(state, 0, STATE_SIZE);
  add_to_state(state, N, 0, 16);
  add_to_state(state, IVA, 16, IV_SIZE);
  s_box(state, Sh);

  /*
  ** IsapMac uses sponge-based hash function
  */
  // Absorbing Associated Data A
  size_t bytes_remain = Rh_SIZE;
  BYTE current_associated;
  for (SIZE i = 0; i < A_len; ++i) {
    if (bytes_remain == 0) {
      s_box(state, Sh);
      bytes_remain = Rh_SIZE;
    }
    current_associated = A[i];
    add_to_state(state, &current_associated, Rh_SIZE - bytes_remain, 1);
    --bytes_remain;
  }

  // Absorb Padding and domain seperate before Ciphertext
  if (bytes_remain == 0) {
    s_box(state, Sh);
    bytes_remain = Rh_SIZE;
  }

  BYTE padding = 0x80;   // 128 in hex MSB
  BYTE seperator = 0x01; // 1 in hex LSB
  add_to_state(state, &padding, Rh_SIZE - bytes_remain, 1);
  s_box(state, Sh);
  add_to_state(state, &seperator, STATE_SIZE - 1, 1);

  // Absorb Ciphertext
  BYTE current_Cipher;
  bytes_remain = Rh_SIZE;
  for (SIZE i = 0; i < C_len; ++i) {
    current_Cipher = C[i];
    add_to_state(state, &current_Cipher, Rh_SIZE - bytes_remain, 1);
    --bytes_remain;
    if (bytes_remain == 0) {
      s_box(state, Sh);
      bytes_remain = Rh_SIZE;
    }
  }
  // Padding again
  padding = 0x80;
  add_to_state(state, &padding, Rh_SIZE - bytes_remain, 1);
  s_box(state, Sh);

  // Get subkey K_A from state by splitting it to k-bit value and an (n-k)-bit
  // value then squeeze for tag
  BYTE subkey_KA[16], Y[16];
  memcpy(Y, state, 16);
  IsapRK(K, IVA, Y, 16, subkey_KA, 16);
  modify_state_buffer(state, subkey_KA, 0, 16);
  s_box(state, Sh);
  memcpy(T, state, 16);
}
