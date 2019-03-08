// Visual Micro is in vMicro>General>Tutorial Mode
//


#include"max6675.h"

#define HEATER_TRIGGER 3
#define SET_POINT_1 210
#define MAX_TRIGGER_DELAY 7400 // bu değer deneyerek bulunacak
#define TEMP_READ_DELAY 500
#define thermoDO 9
#define thermoCS 10
#define thermoCLK 13
#define ZERO_CROSS 8
int last_CH1_state = 0;
bool zero_cross_detected = false;
  typedef struct {
  double PState;
  double iState;
  double DState;
  double iGain,
    dGain,
    pGain;

}PID;
PID pid_1;
double PID_error_1, PID_previous_error_1 = 0;
unsigned long current_millis = 0;
unsigned long previousMillis, previousMillis1 = 0;
double PID_value = 0;
float real_temperature = 0;
float elapsedTime, Time, timePrev;
bool func_trigger = false;

MAX6675 thermocouple_1(thermoCLK, thermoCS, thermoDO);
void setup()
{
  Serial.begin(9600);
  //timer_2_init();
  pinMode(HEATER_TRIGGER, OUTPUT);
  pinMode (ZERO_CROSS,INPUT); 
  digitalWrite(HEATER_TRIGGER, LOW);
  PCICR |= (1 << PCIE0);    //enable PCMSK0 scan                                                 
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 (zero cross input) trigger an interrupt on state change.
  pid_1.pGain = 125;
  pid_1.iGain = 2.5;
  pid_1.dGain =3;
}

void loop()
{
  current_millis = millis();

  if (current_millis - previousMillis >= TEMP_READ_DELAY)
  {
    previousMillis += TEMP_READ_DELAY;
    real_temperature = thermocouple_1.readCelsius();
    PID_error_1 = SET_POINT_1 - real_temperature;
    if (PID_error_1 > 30)
    {
      pid_1.iState = 0;
    }
    pid_1.PState = pid_1.pGain * PID_error_1;
    pid_1.iState += (pid_1.iGain*PID_error_1);
    timePrev = Time;
    Time = millis();
    elapsedTime = (Time - timePrev) / 1000;
    pid_1.DState = pid_1.dGain*((PID_error_1 - PID_previous_error_1) / elapsedTime);
    PID_value = pid_1.PState + pid_1.iState + pid_1.DState;
    if (PID_value < 0)
    {
      PID_value = 0;
    }
    if (PID_value > MAX_TRIGGER_DELAY)
    {
      PID_value = MAX_TRIGGER_DELAY;
    }
  /* Serial.print("Set: ");
    Serial.print(SET_POINT_1);
    Serial.print("    Real temp: ");
    Serial.print(real_temperature);
    Serial.print("   PID: ");
    Serial.print(PID_value);
    Serial.print("   p: ");
    Serial.print(pid_1.PState);
    Serial.print("   I: ");
    Serial.print(pid_1.iState);
    Serial.print("   D: ");
    Serial.println(pid_1.DState);*/
    Serial.println(real_temperature);
   //Serial.print("   PID: ");
   //Serial.println(PID_value);
    PID_previous_error_1 = PID_error_1;
  }
  if (zero_cross_detected)     
    {
    delayMicroseconds(MAX_TRIGGER_DELAY-PID_value);
     digitalWrite(HEATER_TRIGGER, HIGH);
    delayMicroseconds(100);
     digitalWrite(HEATER_TRIGGER, LOW);
     zero_cross_detected = false;
  }

}
ISR(PCINT0_vect){
  if(PINB & B00000001){            //We make an AND with the state register, We verify if pin D8 is HIGH???
    if(last_CH1_state == 0){       //If the last state was 0, then we have a state change...
      zero_cross_detected = true;  //We have detected a state change! We need both falling and rising edges
    }
  }
  else if(last_CH1_state == 1){    //If pin 8 is LOW and the last state was HIGH then we have a state change      
    zero_cross_detected = true;    //We haev detected a state change!  We need both falling and rising edges.
    last_CH1_state = 0;            //Store the current state into the last state for the next loop
    }
  }


