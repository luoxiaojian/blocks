#ifndef BLOCK_H_
#define BLOCK_H_

#include <stdint.h>

class Block16 {
 public:
  char buf[16];
};

class Block32 {
 public:
  char buf[32];
};

class ApplyInfo {
 public:
  unsigned char state;
  unsigned char label;
  unsigned short state2;
  int history_days;
  int current_days;
  uint64_t timestamp;
  char index[32];
  char id_num[32];
};

#endif