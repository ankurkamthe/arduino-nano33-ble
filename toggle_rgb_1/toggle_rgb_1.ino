

/*
  
This sketch changes led colors on the board.
The sketch only uses the loop() and delay() to keep 
led in a particular state (color).

Note: 
Using the pinMode and digitalWrite function in an unconventional way.
Typically, setting HIGH should turn on the led, but my I played around
with this the opposite worked. Not spending too much time on this now...

*/

#define PIN_LED     (13u)
#define LED_BUILTIN PIN_LED
#define LEDR        (22u)
#define LEDG        (23u)
#define LEDB        (24u)
#define LED_PWR     (25u)

const int arr[] = {LED_BUILTIN, LEDR, LEDG, LEDB};

int adv_type = 0;

const int ledPin = LED_BUILTIN; // pin to use for the LED

char buffer[100];


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
  Serial.println("Setup Done");
}

void loop() {
  changeLeds(NULL);
}
