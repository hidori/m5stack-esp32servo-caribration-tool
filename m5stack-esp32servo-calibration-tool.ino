#include <M5Stack.h>
#include <ESP32Servo.h>

#define SERVO1_PIN 21
#define SERVO2_PIN 22
#define SERVO3_PIN 16
#define SERVO4_PIN 17

#define TEXT_POS_X 16
#define TEXT_POS_Y 16
#define TEXT_SIZE 7

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup()
{
  M5.begin();

  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Lcd.setTextSize(TEXT_SIZE);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);
  home();

  updateUI();
}

int angle;

void loop()
{
  M5.update();

  if (M5.BtnA.pressedFor(1000))
  {
    left(10);
    updateUI();
  }
  else if (M5.BtnA.wasPressed())
  {
    left(1);
    updateUI();
  }
  else if (M5.BtnB.wasPressed())
  {
    home();
    updateUI();
  }
  else if (M5.BtnC.pressedFor(1000))
  {
    right(10);
    updateUI();
  }
  else if (M5.BtnC.wasPressed())
  {
    right(1);
    updateUI();
  }

  delay(100);
}

void home()
{
  angle = 90;
  applyAngle();
}

void right(int delta)
{
  angle -= delta;
  if (angle < 0)
  {
    angle = 0;
  }
  applyAngle();
}

void left(int delta)
{
  angle += delta;
  if (angle > 180)
  {
    angle = 180;
  }
  applyAngle();
}

void applyAngle()
{
  servo1.write(angle);
  servo2.write(angle);
  servo3.write(angle);
  servo4.write(angle);
}

void updateUI()
{
  char buf[8];
  sprintf(buf, "%3d", angle);
  M5.Lcd.drawString(buf, TEXT_POS_X, TEXT_POS_Y);
}