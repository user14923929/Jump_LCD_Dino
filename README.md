# Jump LCD Dino (Arduino Game)

Jump LCD Dino is a simple game for Arduino UNO that uses a 16x2 I2C LCD screen and a single button to control jumping. The objective is to avoid obstacles and get the highest score possible.

## Features
- Display-based endless runner game
- One-button jump mechanic
- Score and high score tracking
- High score saved in EEPROM
- Sound effects using a buzzer
- Automatic reset after game over

## Hardware Requirements
- Arduino UNO (or compatible board)
- 16x2 I2C LCD (address: 0x27)
- Push button (connected to pin A1)
- Buzzer (connected to pin 3)
- Jumper wire from pin A0 to RESET (optional, for auto-restart)

## Pin Configuration
| Component   | Arduino Pin |
|-------------|--------------|
| LCD         | I2C (SDA, SCL) |
| Button      | A1           |
| Buzzer      | 3            |
| Reset Link  | A0 -> RESET  |

## Installation
1. Connect all components according to the pin configuration.
2. Upload the sketch from `Jump Lcd Dino Game.ino` to your Arduino board.
3. Press the button to jump over obstacles!

## Controls
- **Jump:** Press the button (pin A1)
- **Avoid obstacles (#):** Time your jumps carefully

## Notes
- Holding the button will not allow repeated jumping — you must release it first.
- If you beat the high score, it is saved even after a power cycle (via EEPROM).
- The buzzer provides basic audio feedback for jumps and game over.

## License
This project is open-source and free to use for educational and hobby purposes.

