#ifndef GSM_H
#define GSM_H

void send_sms(String number, String message, String message1)
{
  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+91" + String(number) + "\"\r");
  delay(1000);
  Serial.println(message);
  delay(1000);
  Serial.println(message1);
  delay(1000);
  Serial.println(char(26));
  delay(1000);

}
#endif
