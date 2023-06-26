#ifndef ASCON_H_
#define ASCON_H_

#define rotate_right(x, i) ((x >> i) | (x << (64 - i)))

typedef unsigned long long SIZE;
typedef unsigned char BYTE;

void add_to_state(BYTE *state, const BYTE *constant_data, int index, int len);
void modify_state_buffer(BYTE *state, const BYTE *constant_data, int index,
                         int len);
void s_box(BYTE *state, int round);
void extract_bytes(BYTE *state, BYTE *constant_data, int index, int len);

#endif // ASCON_H_
