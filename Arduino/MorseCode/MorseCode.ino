#include "Protocol.h"
#include "Timer.h"
#include "Morse.h"

Timer t;

EntryGetCharCallback _GetCharCallback;

void GetChar(EntryGetCharCallback GetCharCallback) {
  _GetCharCallback = GetCharCallback;
}

void PutChar(const char c) {
 Serial.write(c);
}

void checkData(void)
{
 if (Serial.available())
{
  char c = Serial.read();
 _GetCharCallback(c);
} 
}

void MessageReceived(const char *data, const uint16_t len)
{
 for (uint16_t i = 0; i < len; i++)
 {
 MorseExecute(data[i]);
  Protocol::Send(i);
 }
}

void High(void)
{
  digitalWrite(13, HIGH);
}

void Low(void)
{
  digitalWrite(13, LOW);
}

void Delay(const int time)
{
  delay(time);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Protocol::Init(GetChar, PutChar, MessageReceived);
  t.every(20, checkData);
  MorseEntry(High, Low, Delay);
}

// the loop function runs over and over again forever
void loop() {
t.update();
}
