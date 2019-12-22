#include <Arduino.h>
#include <Joystick.h>

int deadzone = 15;
double newval[5];
Joystick_ Joystick(0x05,JOYSTICK_TYPE_GAMEPAD,0,0,true,true,false,true,true,false,false,true,false,false,false);  // No accelerator, brake, or steering

double aux, gear, rudo, elev, aile, thro;
// aux,2 | gear,3 | rudo,4 | elev,5 | aile,6 | thro,7)
double signal[5];
double prevsignal[5];
void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);  

  Joystick.begin();
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0,1023);
}

void loop() 
{

  for(int i = 2; i <=7; i++)
  {
    int x = i == 4 ? 1100-25 : 1100;
    signal[i-2] = pulseIn(i, HIGH);

    prevsignal[i-2]=signal[i-2];

    signal[i-2] = map(signal[i-2], x, 1895, 1023, 0);
    
  }
  for(int i = 0; i <= 5; i++)
  {
    Serial.print(signal[i]);
    Serial.print(" | ");
  }
  Serial.println();
  // Send those vals into joystick
  Joystick.setXAxis(signal[2]);
  Joystick.setYAxis(signal[3]);
  Joystick.setRxAxis(signal[4]);
  Joystick.setRyAxis(signal[5]);
  // Send all states
  Joystick.sendState();

}