#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <snakegame.h>
#include <sound.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Console button pins
#define DOWN_BUTTON  D1
#define UP_BUTTON D2
#define LEFT_BUTTON  D6
#define RIGHT_BUTTON D5
#define SPKR_PIN D7

//I2C PINS
#define DISPLAY_SDA D3
#define DISPLAY_SCK D4

#define REFRESH_RATE 75


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int score = -1;
unsigned long nextTickTime;

Snake snake(SCREEN_WIDTH, SCREEN_HEIGHT);
Game game(
  snake, 
  [](uint8_t x, uint8_t y)
  { 
    display.drawPixel(x, y + HEIGHT_OFFSET, WHITE);
    display.display();
    score++;

    display.fillRect(0,0,WIDTH,HEIGHT_OFFSET, BLACK);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(2);
    display.print("score : ");
    display.print(score);
    tone(D7, 3000, 1000);
    delay(100);
    noTone(D7);
  }
);

Point p;

void setup() {
  Serial.begin(9600);
  Wire.begin(DISPLAY_SDA, DISPLAY_SCK);

  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(SPKR_PIN, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();


  game.start();

  //drawing snake
  game.field_for_each([](uint8_t x, uint8_t y, Game::Pixel p){
    if(p != Game::Pixel::Empty && p != Game::Pixel::Food)
    {
      display.drawPixel(x, y + HEIGHT_OFFSET, WHITE);
      delay(1); 
    }
  });
  
  display.display();
  nextTickTime =  millis() + REFRESH_RATE;
}



void loop() {

  if(game.isOver())
  { 
    playGameOverTune(SPKR_PIN);
    display.clearDisplay();
    delay(100);
    display.setCursor(10,10);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println("GAME OVER");
    display.setCursor(10,19);
    display.print("YOUR SCORE : ");
    display.print(score);
    display.display();
    delay(4000);
    ESP.restart();
  }

  if(isButtonPressed(UP_BUTTON))
  {
    snake.setDirection(Snake::Direction::UP);
  }

  if(isButtonPressed(DOWN_BUTTON))
  {
    snake.setDirection(Snake::Direction::DOWN);
  }
  if(isButtonPressed(LEFT_BUTTON))
  {
    snake.setDirection(Snake::Direction::LEFT);
  }

  if(isButtonPressed(RIGHT_BUTTON))
  {
    snake.setDirection(Snake::Direction::RIGHT);
  }
  delay(1);

  if(nextTickTime <= millis())
  {
    nextTickTime = millis() + REFRESH_RATE;
    display.drawPixel(snake.getTail().x, snake.getTail().y + HEIGHT_OFFSET, BLACK);
    delay(1);
    game.moveSnake();
    delay(1);
    display.drawPixel(snake.getHead().x, snake.getHead().y + HEIGHT_OFFSET, WHITE);
    delay(1);
    backgroundMusic(SPKR_PIN);
  }

  display.display();
}


