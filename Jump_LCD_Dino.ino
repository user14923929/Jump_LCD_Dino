#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = A1; // Jump button pin
const int resetPin = A0;  // Reset pin, connected to RESET through a resistor or transistor
const int buzzerPin = 3;   // Buzzer pin for sound

bool isJumping = false;     // Jump state
bool buttonReleased = true; // Button release flag
int jumpCounter = 0;        // Jump duration counter
int obstacleX = 15;         // Obstacle position (X)
bool gameOver = false;      // Game over flag
unsigned long lastUpdate = 0; // Timer for display update
const int interval = 200;     // Update interval in milliseconds
int score = 0;                // Current score
int highScore = 0;            // High score (stored in EEPROM)

// Play a beep sound
void beep(int duration = 100) {
  tone(buzzerPin, 1000);
  delay(duration);
  noTone(buzzerPin);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Button with pull-up resistor
  pinMode(resetPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(resetPin, HIGH); // Set HIGH to avoid reset

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jump LCD Dino");
  delay(2000);
  lcd.clear();

  EEPROM.get(0, highScore); // Load high score from EEPROM
}

void loop() {
  if (gameOver) return; // Exit if game is over

  bool buttonState = digitalRead(buttonPin) == LOW; // Read button state

  // Jump only once per press
  if (buttonState && buttonReleased && !isJumping) {
    isJumping = true;
    jumpCounter = 3;
    buttonReleased = false;
    beep(50); // Jump sound
  }

  // Allow next jump after button is released
  if (!buttonState) {
    buttonReleased = true;
  }

  // Display update timer
  if (millis() - lastUpdate > interval) {
    lastUpdate = millis();
    lcd.clear();

    // Show score and high score
    lcd.setCursor(0, 0);
    lcd.print("S:");
    lcd.print(score);
    lcd.setCursor(10, 0);
    lcd.print("R:");
    lcd.print(highScore);

    // Display player character (@)
    if (isJumping) {
      lcd.setCursor(0, 0); // Top row = jumping
      lcd.print("@");
      jumpCounter--;
      if (jumpCounter <= 0) {
        isJumping = false;
      }
    } else {
      lcd.setCursor(0, 1); // Bottom row = running
      lcd.print("@");
    }

    // Display obstacle (#)
    if (obstacleX >= 0) {
      lcd.setCursor(obstacleX, 1);
      lcd.print("#");
    } else {
      obstacleX = 16 + random(5); // New obstacle after 5+ ticks
    }

    // Collision detection
    if (obstacleX == 0 && !isJumping) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("GAME OVER");
      beep(300); // Game over sound

      if (score > highScore) {
        highScore = score;
        EEPROM.put(0, highScore); // Save new high score
      }

      gameOver = true;
      delay(3000);
      digitalWrite(resetPin, LOW); // Trigger reset
    }

    obstacleX--;
    score++; // Increase score
  }
}
