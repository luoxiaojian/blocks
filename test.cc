#include <stdio.h>

#include "block.h"

int main(int argc, char **argv) {
  printf("sizeof(Block16) = %d\n", sizeof(Block16));
  printf("sizeof(Block32) = %d\n", sizeof(Block32));
  printf("sizeof(ApplyInfo) = %d\n", sizeof(ApplyInfo));
  return 0;
}