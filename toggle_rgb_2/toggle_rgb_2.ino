/*

This sketch changes led colors on the board.
The sketch only uses the arduino-timer library to call 
the changeLeds() function every 5000ms to switch led colors.

Note: 
Using the pinMode and digitalWrite function in an unconventional way.
Typically, setting HIGH should turn on the led, but my I played around
with this the opposite worked. Not spending too much time on this now...

*/

#include <arduino-timer.h>


#define PIN_LED     (13u)
#define LED_BUILTIN PIN_LED
#define LEDR        (22u)
#define LEDG        (23u)
#define LEDB        (24u)
#define LED_PWR     (25u)

const int arr[] = {LED_BUILTIN, LEDR, LEDG, LEDB}; // store led pins in array

int adv_type = 0; // 

auto timer = timer_create_default(); // timer instance

char buffer[100]; // for storing formatted prints

void clear_leds()
{
  int arr_sz = sizeof(arr) / sizeof(arr[0]);
  int i;

  for (i = 0; i < arr_sz; i++) {
    pinMode(arr[i], OUTPUT);
    digitalWrite(arr[i], LOW);
    pinMode(arr[i], INPUT);
  }
}

void only_red()
{
  int led = arr[1];

  //sprintf(buffer, "toggle: %d", led);
  //Serial.println(buffer);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(5000);
  pinMode(led, INPUT);

}

void only_green()
{
  int led = arr[2];

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(5000);
  pinMode(led, INPUT);


}

void only_blue()
{
  int led = arr[3];

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  delay(5000);
  pinMode(led, INPUT);

}

bool changeLeds(void *)
{
  Serial.println("change colors...");
  switch (adv_type) {
    case 0:
      Serial.println("red");
      only_red();
      adv_type = 1;
      Serial.println("done");
      break;
    case 1:
      Serial.println("green");
      only_green();
      adv_type = 2;
      Serial.println("done");
      break;
    case 2:
      Serial.println("blue");
      only_blue();
      adv_type = 0;
      Serial.println("done");
      break;
    default:
      Serial.println("should not print");
      break;
  }
  return true;
}



void setup() {

  delay(5000);
  Serial.println("Setup Init...");
  
  timer.every(5000, changeLeds);
  
  Serial.println("Start loop");
}

void loop() {
  timer.tick();
}
