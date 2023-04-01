#include <Wire.h> // Librairy
#include <LiquidCrystal_I2C.h> // Librairy (Install here: https://github.com/fmalpartida/New-LiquidCrystal)

LiquidCrystal_I2C lcd(0x27,16,2); // Setting up the LCD

void setup() {
  Serial.begin(9600); // Setting up the Serial Monitor
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Tuen backlights on
  Serial.println("Setting up LCD, please wait...");
  lcd.begin(16,2); // Starts the LCD program
  lcd.clear(); // Clears the LCD
  lcd.print("Waiting prompt.");
  Serial.println("LCD online, type what you would like to display on the LCD, or type 'clear' to clear the LCD.");
}

void loop() {
  if (Serial.available() > 0) {  // Check if there is data available to read
    String input = Serial.readString();  // Read the data as a string
    input.trim(); // Clears the unessesary things
    if (input == "clear") {
      lcd.clear();
      Serial.println("Now clearing the LCD");
    } else {
    lcd.clear();
    lcd.print(input);  // Print the received data on the LCD
    Serial.println("Now displaying " + input);
    }
  }
}

// Made by @LeskaHub with the help of ChatGPT
