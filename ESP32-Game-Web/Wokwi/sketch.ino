#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ---------------- OLED ---------------- */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oledCmd(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 oledHUD(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ---------------- PINS ---------------- */
#define BTN_PIN     4
#define BUZZER_PIN  26

#define LED_R 14
#define LED_G 12
#define LED_B 27

/* ---------------- GAME ---------------- */
int lives = 5;
unsigned long gameStart;
const unsigned long GAME_TIME = 90000;

String commands[] = {
  "PRESS BUTTON",
  "DO NOT PRESS",
  "PRESS FAST",
  "WAIT"
};

int currentCmd = 0;

/* ---------------- LED UTILS ---------------- */
void setRGB(bool r, bool g, bool b) {
  digitalWrite(LED_R, r);
  digitalWrite(LED_G, g);
  digitalWrite(LED_B, b);
}

void blinkRGB(bool r, bool g, bool b, int times, int d) {
  for (int i = 0; i < times; i++) {
    setRGB(r, g, b);
    delay(d);
    setRGB(0, 0, 0);
    delay(d);
  }
}

/* ---------------- BUZZER ---------------- */
void beep(int ms) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(ms);
  digitalWrite(BUZZER_PIN, LOW);
}

/* ---------------- DISPLAY ---------------- */
void showCommand(String text) {
  oledCmd.clearDisplay();
  oledCmd.setTextSize(2);
  oledCmd.setTextColor(SSD1306_WHITE);
  oledCmd.setCursor(0, 20);
  oledCmd.println(text);
  oledCmd.display();
}

void showHUD() {
  oledHUD.clearDisplay();
  oledHUD.setTextSize(1);
  oledHUD.setTextColor(SSD1306_WHITE);

  oledHUD.setCursor(0, 0);
  oledHUD.print("Lives: ");
  for (int i = 0; i < lives; i++) oledHUD.print("\x03 ");

  int remaining = (GAME_TIME - (millis() - gameStart)) / 1000;
  if (remaining < 0) remaining = 0;

  oledHUD.setCursor(0, 20);
  oledHUD.print("Time: ");
  oledHUD.print(remaining);
  oledHUD.print("s");

  oledHUD.display();
}

/* ---------------- GAME LOGIC ---------------- */
void nextCommand() {
  currentCmd = random(0, 4);
  showCommand(commands[currentCmd]);

  // LED indication per command
  if (commands[currentCmd] == "PRESS BUTTON") {
    setRGB(0, 1, 0); // GREEN
  }
  else if (commands[currentCmd] == "DO NOT PRESS") {
    setRGB(1, 0, 0); // RED
  }
  else if (commands[currentCmd] == "PRESS FAST") {
    blinkRGB(1, 1, 0, 3, 120); // YELLOW BLINK
  }
  else if (commands[currentCmd] == "WAIT") {
    blinkRGB(0, 0, 1, 2, 300); // BLUE SLOW BLINK
  }
}

void fail() {
  lives--;
  blinkRGB(1, 0, 0, 3, 150); // RED BLINK
  beep(300);
}

void success() {
  blinkRGB(0, 1, 0, 2, 120); // GREEN BLINK
  beep(150);
}

/* ---------------- SETUP ---------------- */
void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  Wire.begin();

  oledCmd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oledHUD.begin(SSD1306_SWITCHCAPVCC, 0x3D);

  randomSeed(millis());

  gameStart = millis();
  showCommand("START!");
  blinkRGB(0, 0, 1, 2, 200); // BLUE START BLINK
  beep(200);
  delay(1000);

  nextCommand();
}

/* ---------------- LOOP ---------------- */
void loop() {
  showHUD();

  if (lives <= 0) {
    showCommand("GAME OVER");
    setRGB(1, 0, 0);
    while (1);
  }

  if (millis() - gameStart > GAME_TIME) {
    showCommand("YOU WIN!");
    setRGB(0, 0, 1);
    beep(500);
    while (1);
  }

  if (digitalRead(BTN_PIN) == LOW) {
    delay(200);

    if (commands[currentCmd] == "PRESS BUTTON" ||
        commands[currentCmd] == "PRESS FAST") {
      success();
    } else {
      fail();
    }

    setRGB(0, 0, 0);
    nextCommand();
  }
}
