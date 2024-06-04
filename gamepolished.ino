#include <Adafruit_CircuitPlayground.h>

#define NUM_PIXELS 10

int currentPixel = 0;
int direction = 1;
int level = 1;
int speed = 500;
int hits = 0;

enum GameState { START,
                 PLAY,
                 LEVEL_UP,
                 WIN,
                 GAME_OVER };
GameState gameState = START;

volatile bool leftButtonPressed = false;
volatile bool rightButtonPressed = false;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  resetGame();

  attachInterrupt(digitalPinToInterrupt(4), leftButtonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), rightButtonISR, FALLING);
}

void resetGame() {
  currentPixel = 0;
  direction = 1;
  level = 1;
  speed = 500;
  hits = 0;
  leftButtonPressed = false;
  rightButtonPressed = false;
  CircuitPlayground.clearPixels();
  gameState = START;
}

void loop() {
  switch (gameState) {
    case START:
      if (leftButtonPressed) {
        gameState = PLAY;
        hits = 0;
        leftButtonPressed = false;
        delay(50);
      }
      break;

    case PLAY:
      playGame();
      break;

    case LEVEL_UP:
      levelUp();
      break;

    case WIN:
      showWin();
      break;

    case GAME_OVER:
      showGameOver();
      break;
  }
}

void playGame() {
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(currentPixel, 255, 0, 0);
  CircuitPlayground.strip.show();
  delay(speed);

  if (currentPixel == 0  && direction == -1) {
    if (leftButtonPressed) {
      direction = 1;
      hits++;
      leftButtonPressed = false;
      delay(50);
    } else {
      gameState = GAME_OVER;
    }
  } else if (currentPixel == NUM_PIXELS - 1  && direction == 1) {
    if (rightButtonPressed) {
      direction = -1;
      hits++;
      rightButtonPressed = false;
      delay(50);
    } else {
      gameState = GAME_OVER;
    }
  } else {
    if (leftButtonPressed || rightButtonPressed) {
      gameState = GAME_OVER;
    }
  }

  if (hits >= 5) {
    gameState = LEVEL_UP;
  } else {
    currentPixel += direction;
    if (currentPixel < 0) currentPixel = 0;
    if (currentPixel >= NUM_PIXELS) currentPixel = NUM_PIXELS - 1;
  }
}

void levelUp() {
  if (level < 5) {
    level++;
    speed -= 100;
    hits = 0;
    gameState = PLAY;
  } else {
    gameState = WIN;
  }
}

void showWin() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0);
  }
  CircuitPlayground.strip.show();
  CircuitPlayground.playTone(5000, 3000);
  resetGame();
}

void showGameOver() {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  }
  CircuitPlayground.strip.show();
  CircuitPlayground.playTone(500, 3000);
  resetGame();
}

void leftButtonISR() {
  leftButtonPressed = true;
}

void rightButtonISR() {
  rightButtonPressed = true;
}
