#ifndef IOT_H
#define IOT_H
#include"ss.h"

void send_iot(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    ss.write(s[i]);
  }
  delay(3000);
}
#endif
