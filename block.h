#ifndef BLOCK_H_
#define BLOCK_H_

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <string>
#include <vector>

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define unlikely(x) __builtin_expect(!!(x), 0)

#define STD_TIME_STR_LENGTH 19
#define FULL_TIME_STR_LENGTH 23

template <int size>
class Block {
 public:
  Block() {}
  Block(char* str, int length) {
    memset(&buf[0], 0, size);
    memcpy(&buf[0], str, MIN(size, length));
  }

  inline void SetBuffer(char* str, int length) {
    memset(&buf[0], 0, size);
    memcpy(&buf[0], str, MIN(size, length));
  }

  inline char* GetBuffer() { return &buf[0]; }

  inline char operator[](int loc) { return buf[loc]; }

  inline Block& operator=(const Block& b) { memcpy(&buf[0], &b.buf[0], size); }

  friend bool operator==(const Block& b1, const Block& b2) {
    return (memcmp(&b1.buf[0], &b2.buf[0], size) == 0);
  }

  friend bool operator!=(const Block& b1, const Block& b2) {
    return (memcmp(&b1.buf[0], &b2.buf[0], size) != 0);
  }

 private:
  char buf[size];
};

enum ApplyInfoState {
  kAISOtherRefuse = 0,
  kAISQRefuse = 1,
  kAISNull = 2,
};

enum ApplyInfoState2 {
  kAIS2Refuse = 0,
  kAIS2Pass = 1,
};

class ApplyInfo {
 public:
  ApplyInfo() {}

  ApplyInfo(const ApplyInfo& rhs) { memcpy(this, &rhs, sizeof(ApplyInfo)); }

  ApplyInfo& operator=(const ApplyInfo& rhs) {
    memcpy(this, &rhs, sizeof(ApplyInfo));
    return *this;
  }

  inline void Init(char* line) {
    char* ptr1 = line;
    char* ptr2 = strchr(ptr1, '\001');
    order_id_.SetBuffer(ptr1, ptr2 - ptr1);
    ptr1 = ptr2 + 1;
    ptr2 = strchr(ptr1, '\001');
    SetState(ApplyInfoState(atoi(ptr1)));
    ptr1 = ptr2 + 1;
    ptr2 = strchr(ptr1, '\001');
    SetTimeStamp(ptr1);
    ptr1 = ptr2 + 1;
    ptr2 = strchr(ptr1, '\001');
    SetState2(ApplyInfoState2(atoi(ptr1)));
    ptr1 = ptr2 + 1;
    ptr2 = strchr(ptr1, '\001');
    SetHistoryDays(atoi(ptr1));
    ptr1 = ptr2 + 1;
    ptr2 = strchr(ptr1, '\001');
    SetCurrentDays(atoi(ptr1));
    ptr1 = ptr2 + 1;
    ptr2 = strchr(ptr1, '\001');
    id_.SetBuffer(ptr1, ptr2 - ptr1);
    ptr1 = ptr2 + 1;
    SetLabel(atoi(ptr1));
  }

  inline Block<32>& GetOrderId() { return order_id_; }
  inline Block<32>& GetIDNumber() { return id_; }

  inline ApplyInfoState GetState() {
    int res = (state_ & 65535u);
    return ApplyInfoState(res);
  }

  inline ApplyInfoState2 GetState2() {
    int res = (state_ >> 16);
    return ApplyInfoState2(res);
  }

  inline int GetLabel() { return label_; }

  inline void SetState(ApplyInfoState s) {
    unsigned x = s;
    state_ = ((state_ & 4294901760u) | x);
  }

  inline void SetState2(ApplyInfoState2 s) {
    unsigned x = s;
    state_ = ((x << 16) | (state_ & 65535u));
  }

  inline void SetLabel(int l) { label_ = l; }

  inline uint64_t GetTimeStamp() { return timestamp_; }

  inline void SetTimeStamp(char* str_time) {
    struct tm stm;
    int iY, iM, iD, iH, iMin, iS, iMs;
    memset(&stm, 0, sizeof(stm));
    iY = atoi(str_time);
    iM = atoi(str_time + 5);
    iD = atoi(str_time + 8);
    iH = atoi(str_time + 11);
    iMin = atoi(str_time + 14);
    iS = atoi(str_time + 17);
    iMs = atoi(str_time + 20);

    stm.tm_year = iY - 1900;
    stm.tm_mon = iM - 1;
    stm.tm_mday = iD;
    stm.tm_hour = iH;
    stm.tm_min = iMin;
    stm.tm_sec = iS;

    timestamp_ = mktime(&stm);
    timestamp_ = timestamp_ * 1000 + iMs;
  }

  inline void GetTimeStampString(std::string& str) {
    str.resize(FULL_TIME_STR_LENGTH + 1);
    int iMs = timestamp_ % 1000;
    time_t t = timestamp_ / 1000;
    struct tm* lmt = localtime(&t);
    strftime(&str[0], FULL_TIME_STR_LENGTH, "%Y-%m-%d %H:%M:%S", lmt);
    sprintf(&str[STD_TIME_STR_LENGTH], ".%03d", iMs);
  }

  inline void SetHistoryDays(int hd) { hist_days_ = hd; }

  inline void SetCurrentDays(int cd) { curr_days_ = cd; }

  inline int GetHistoryDays() { return hist_days_; }

  inline int GetCurrentDays() { return curr_days_; }

 private:
  unsigned state_;  // state_[0:15] - state, state_[16:31] - state2
  int label_;
  int hist_days_;
  int curr_days_;
  uint64_t timestamp_;
  Block<32> order_id_;
  Block<32> id_;
};

#define BSPACE_MIN_ITEM_NUM 128

template <typename T>
class BlockSpace {
 public:
  BlockSpace() : capacity_(0), cur_(0), head_(NULL) {}
  ~BlockSpace() { Clear(); }
  inline T* GetAnItem() {
    if (unlikely(cur_ == capacity_)) {
      head_ = new T[BSPACE_MIN_ITEM_NUM];
      data_.push_back(head_);
      capacity_ = BSPACE_MIN_ITEM_NUM;
      cur_ = 0;
    }
    return &head_[cur_++];
  }
  void Clear() {
    for (auto p : data_) delete[] p;
    data_.clear();
  }

 private:
  std::vector<T*> data_;
  int capacity_, cur_;
  T* head_;
};

#undef BSPACE_MIN_ITEM_NUM
#undef unlikely

#endif
