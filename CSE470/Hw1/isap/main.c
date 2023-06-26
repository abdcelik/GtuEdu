#include "tests.h"

int main(int argc, char *argv[]) {

  test_enc_dec();
  test_cbc();
  test_ofb();

  return 0;
}
