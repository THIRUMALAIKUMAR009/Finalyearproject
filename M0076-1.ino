/*PROJECT CODE: M0076-1
   DEVOLOPER NAME : SARAVANAN
   MEASURING THE AC POWER CONLSUMPTION
*/

#include "global.h"
#include "lcd.h"
#include "accurrent.h"
#include "acvoltage.h"
#include"ss.h"
#include "gsm.h"
#include "iot.h"
#define RELAY_1 5

bool flag = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(RELAY_1, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  lcd.begin(16, 2);
  ac_voltage_init();
  ac_current_init();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MEASURE POWER");
  lcd.setCursor(0, 1);
  lcd.print("   CONSUMPTION");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (rx == 1)
  {
    digitalWrite(RELAY_1, LOW);
    ac_voltage();
    ac_current();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("V:");
    lcd.setCursor(2, 0);
    lcd.print(supply_voltage);
    lcd.setCursor(10, 0);
    lcd.print("I:");
    lcd.setCursor(12, 0);
    lcd.print(supply_current);

    //  Serial.print("VOLTAGE:");
    //  Serial.println(supply_voltage);
    //  Serial.print("CURRENT:");
    //  Serial.println(supply_current);

    float Power = supply_voltage * supply_current;

    //  Serial.print("POWER:");
    //  Serial.println(Power, 4);
    //
    //  Serial.println("P:" + String(Power));
    //  lcd.setCursor(0, 1);
    //  lcd.print("P:");
    //  lcd.setCursor(2, 1);
    //  lcd.print(Power);
    power_per_second = Power / 3600;
    //Serial.println("POWER_PER_SEC:" + String(power_per_second, DEC));
    consumed_power += power_per_second;
    // Serial.println(consumed_power, 3);
    lcd.setCursor(0, 1);
    lcd.print("CP:");
    lcd.setCursor(3, 1);
    lcd.print(consumed_power, 3);

    if ((int)consumed_power % 1000 == 0 && (int)consumed_power != 0 )
    {
      // Serial.println("hello");
      unit++;
    }
    lcd.setCursor(10, 1);
    lcd.print("U:");
    lcd.setCursor(12, 1);
    lcd.print(unit);

    if (consumed_power >= power_limit_watts)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ALERT SENT");
      send_sms("6379341607", "POWER CONSUMPTION=", String(unit));
    }
  }
  else
  {
    digitalWrite(RELAY_1, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("PLS ON SWITCH");
  }

  //  delay(1000);
}

void serialEvent(void)
{
  while (Serial.available() > 0)
  {
    inchar = Serial.read();
    //Serial.println(inchar);
    if (inchar == 'R')
    {
      send_iot("@" + String(supply_voltage) + "#" + "$" + String(supply_current) + "#" + "^" + String(consumed_power) + "#" + "&" + String(unit) + "#");
      inchar = 'X';
    }
    if (inchar == 'O')
    {
      rx = 1;
    }
    if (inchar == 'N')
    {
      lcd.clear();
      rx = 2;
    }
  }
}
