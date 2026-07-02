/*
 * ============================================================
 * Project : Automatic Plant Watering System
 * Author  : Obito Justin
 * Platform: Arduino Uno
 * ============================================================
 * Description:
 * This system monitors soil moisture and automatically controls
 * a water pump. The LCD displays the moisture percentage and
 * pump status. LEDs indicate system status, and a buzzer alerts
 * when watering starts.
 * ============================================================
 */

#include <LiquidCrystal_I2C.h>

/*-------------------------------------------------------------
  Pin Definitions
-------------------------------------------------------------*/
const int SOIL_MOISTURE_SENSOR = A0;
const int WATER_PUMP           = 13;
const int GREEN_LED            = 11;
const int RED_LED              = 12;
const int BUZZER               = 10;

/*-------------------------------------------------------------
  LCD Configuration
-------------------------------------------------------------*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*-------------------------------------------------------------
  Function Prototypes
-------------------------------------------------------------*/
void displayWelcomeMessage();
void updateDisplay(int moisture);
void waterPlant();
void stopWaterPump();
void playBuzzer();

/*-------------------------------------------------------------
  Setup
-------------------------------------------------------------*/
void setup()
{
    pinMode(WATER_PUMP, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    lcd.init();
    lcd.backlight();

    displayWelcomeMessage();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture =");

    lcd.setCursor(0, 1);
    lcd.print("Water Pump =");
}

/*-------------------------------------------------------------
  Main Loop
-------------------------------------------------------------*/
void loop()
{
    int sensorValue = analogRead(SOIL_MOISTURE_SENSOR);

    // Convert sensor value to moisture percentage
    int moisture = map(sensorValue, 0, 876, 0, 99);

    updateDisplay(moisture);

    if (moisture < 50)
    {
        waterPlant();
    }
    else
    {
        stopWaterPump();
    }
}

/*-------------------------------------------------------------
  Display Welcome Message
-------------------------------------------------------------*/
void displayWelcomeMessage()
{
    lcd.clear();

    String line1 = "Automated Plant";
    String line2 = "Watering System";

    lcd.setCursor(0, 0);

    for (int i = 0; i < line1.length(); i++)
    {
        lcd.print(line1.charAt(i));
        delay(100);
    }

    lcd.setCursor(0, 1);

    for (int i = 0; i < line2.length(); i++)
    {
        lcd.print(line2.charAt(i));
        delay(100);
    }

    delay(2500);
}

/*-------------------------------------------------------------
  Update LCD
-------------------------------------------------------------*/
void updateDisplay(int moisture)
{
    lcd.setCursor(11, 0);
    lcd.print("   ");
    lcd.setCursor(11, 0);
    lcd.print(moisture);
    lcd.print("%");
}

/*-------------------------------------------------------------
  Water Plant
-------------------------------------------------------------*/
void waterPlant()
{
    digitalWrite(WATER_PUMP, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    lcd.setCursor(13, 1);
    lcd.print("ON ");

    playBuzzer();
}

/*-------------------------------------------------------------
  Stop Water Pump
-------------------------------------------------------------*/
void stopWaterPump()
{
    digitalWrite(WATER_PUMP, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    lcd.setCursor(13, 1);
    lcd.print("OFF");
}

/*-------------------------------------------------------------
  Buzzer Alert
-------------------------------------------------------------*/
void playBuzzer()
{
    tone(BUZZER, 500, 500);
    delay(1000);
}