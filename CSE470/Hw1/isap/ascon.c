#include "ascon.h"

void add_to_state(BYTE *state, const BYTE *data, int index, int len) {
  for (int i = 0; i < len; ++i) {
    state[index + i] = state[index + i] ^ data[i];
  }
}

void modify_state_buffer(BYTE *state, const BYTE *data, int index, int len) {
  for (int i = 0; i < len; ++i) {
    state[index + i] = data[i];
  }
}

void s_box(BYTE *state, int nRound) {
  int offset = 12 - nRound;
  SIZE x0 = 0, x1 = 0, x2 = 0, x3 = 0, x4 = 0;
  SIZE tmp0, tmp1, tmp2, tmp3, tmp4;

  /*
  ** Divide State to 5 parts
  */
  for (int i = 0; i < 8; i++) {
    x0 |= ((state + 0)[i] << (56 - i * 8));
    x1 |= ((state + 8)[i] << (56 - i * 8));
    x2 |= ((state + 16)[i] << (56 - i * 8));
    x3 |= ((state + 24)[i] << (56 - i * 8));
    x4 |= ((state + 32)[i] << (56 - i * 8));
  }

  for (unsigned int i = offset; i < nRound + offset; i++) {
    /*
    ** Addition of Constants
    **
    ** x2 = x2 xor constant_r
    **
    */
    x2 = x2 ^ ((0xfull - i) << 4) | i;

    /*
    ** Substitution Layer
    ** Ascons 5-bit S-Box
    */
    x0 = x0 ^ x4;
    x4 = x4 ^ x3;
    x2 = x2 ^ x1;

    tmp0 = ~x0 & x1;
    tmp1 = ~x1 & x2;
    tmp2 = ~x2 & x3;
    tmp3 = ~x3 & x4;
    tmp4 = ~x4 & x0;

    x0 = x0 ^ tmp1;
    x1 = x1 ^ tmp2;
    x2 = x2 ^ tmp3;
    x3 = x3 ^ tmp4;
    x4 = x4 ^ tmp0;

    x1 = x1 ^ x0;
    x0 = x0 ^ x4;
    x3 = x3 ^ x2;
    x2 = ~x2;

    /*
    ** Linear Diffusion Layer
    **
    ** x0 <- Σ_0(x0) = x0 xor ( x0 right_rotate 19) xor ( x0 right_rotate 28)
    ** x1 <- Σ_1(x1) = x1 xor ( x1 right_rotate 61) xor ( x1 right_rotate 39)
    ** x2 <- Σ_2(x2) = x2 xor ( x2 right_rotate 1 ) xor ( x2 right_rotate 6)
    ** x3 <- Σ_3(x3) = x3 xor ( x3 right_rotate 10) xor ( x3 right_rotate 17)
    ** x4 <- Σ_4(x4) = x4 xor ( x4 right_rotate 7 ) xor ( x4 right_rotate 41)
    */
    x0 = x0 ^ rotate_right(x0, 19) ^ rotate_right(x0, 28);
    x1 = x1 ^ rotate_right(x1, 61) ^ rotate_right(x1, 39);
    x2 = x2 ^ rotate_right(x2, 1) ^ rotate_right(x2, 6);
    x3 = x3 ^ rotate_right(x3, 10) ^ rotate_right(x3, 17);
    x4 = x4 ^ rotate_right(x4, 7) ^ rotate_right(x4, 41);
  }
  /*
  ** Layers Done
  ** So get back calculated values to state
  */
  for (int i = 0; i < 8; ++i) {
    (state + 0)[i] = (x0 >> (56 - i * 8));
    (state + 8)[i] = (x1 >> (56 - i * 8));
    (state + 16)[i] = (x2 >> (56 - i * 8));
    (state + 24)[i] = (x3 >> (56 - i * 8));
    (state + 32)[i] = (x4 >> (56 - i * 8));
  }
}
