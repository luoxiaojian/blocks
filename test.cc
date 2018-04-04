#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "block.h"

int main(int argc, char **argv) {
  ApplyInfo ai;
  char order_id[32];
  char id_number[32];
  std::string tsstr;
  sprintf(order_id, "ABC123");
  sprintf(id_number, "XYZ789");
  ai.GetOrderId().SetBuffer(order_id, sizeof(order_id));
  ai.GetIDNumber().SetBuffer(id_number, sizeof(id_number));
  ai.SetState(kAISOtherRefuse);
  ai.SetState2(kAIS2Refuse);
  ai.SetTimeStamp("2017-03-29 16:42:36.851");
  ai.SetLabel(1);
  ai.SetHistoryDays(12);
  ai.SetCurrentDays(3);

  printf("order_id: %s\n", ai.GetOrderId().GetBuffer());
  printf("id_number: %s\n", ai.GetIDNumber().GetBuffer());
  printf("state: %d, (%d)\n", ai.GetState(), kAISOtherRefuse);
  printf("state2: %d, (%d)\n", ai.GetState2(), kAIS2Refuse);
  tsstr.clear();
  ai.GetTimeStampString(tsstr);
  printf("timestamp: %s\n", tsstr.c_str());
  printf("timestamp-integer: %llu\n", ai.GetTimeStamp());
  printf("label: %d\n", ai.GetLabel());
  printf("HistoryDays: %d\n", ai.GetHistoryDays());
  printf("CurrentDays: %d\n", ai.GetCurrentDays());
  printf("=========================================\n");

  ApplyInfo ai2(ai);

  printf("order_id: %s\n", ai2.GetOrderId().GetBuffer());
  printf("id_number: %s\n", ai2.GetIDNumber().GetBuffer());
  printf("state: %d, (%d)\n", ai2.GetState(), kAISOtherRefuse);
  printf("state2: %d, (%d)\n", ai2.GetState2(), kAIS2Refuse);
  tsstr.clear();
  ai2.GetTimeStampString(tsstr);
  printf("timestamp: %s\n", tsstr.c_str());
  printf("timestamp-integer: %llu\n", ai2.GetTimeStamp());
  printf("label: %d\n", ai2.GetLabel());
  printf("HistoryDays: %d\n", ai2.GetHistoryDays());
  printf("CurrentDays: %d\n", ai2.GetCurrentDays());
  printf("=========================================\n");

  ApplyInfo ai3 = ai2;

  printf("order_id: %s\n", ai3.GetOrderId().GetBuffer());
  printf("id_number: %s\n", ai3.GetIDNumber().GetBuffer());
  printf("state: %d, (%d)\n", ai3.GetState(), kAISOtherRefuse);
  printf("state2: %d, (%d)\n", ai3.GetState2(), kAIS2Refuse);
  tsstr.clear();
  ai3.GetTimeStampString(tsstr);
  printf("timestamp: %s\n", tsstr.c_str());
  printf("timestamp-integer: %llu\n", ai3.GetTimeStamp());
  printf("label: %d\n", ai3.GetLabel());
  printf("HistoryDays: %d\n", ai3.GetHistoryDays());
  printf("CurrentDays: %d\n", ai3.GetCurrentDays());
  printf("=========================================\n");

  ai.Init(
      "XNW33822498346501120\0010\0012017-03-29 "
      "16:35:39.818\0010\0010\0010\00184f867cf22c8542782ff23260ca255f3\0012");

  printf("order_id: %s\n", ai.GetOrderId().GetBuffer());
  printf("id_number: %s\n", ai.GetIDNumber().GetBuffer());
  printf("state: %d, (%d)\n", ai.GetState(), kAISOtherRefuse);
  printf("state2: %d, (%d)\n", ai.GetState2(), kAIS2Refuse);
  tsstr.clear();
  ai.GetTimeStampString(tsstr);
  printf("timestamp: %s\n", tsstr.c_str());
  printf("timestamp-integer: %llu\n", ai.GetTimeStamp());
  printf("label: %d\n", ai.GetLabel());
  printf("HistoryDays: %d\n", ai.GetHistoryDays());
  printf("CurrentDays: %d\n", ai.GetCurrentDays());
  printf("=========================================\n");

  return 0;
}
