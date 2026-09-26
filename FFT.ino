#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SparkFunSi4703.h>
#include <arduinoFFT.h>

// ===================== Pins =====================
#define TFT_CS    10
#define TFT_DC     9
#define TFT_MOSI  11
#define TFT_CLK   13
#define TFT_MISO  12
#define TFT_RST   -1  
#define RESET_PIN A3
#define AUDIO_PIN A6

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
Si4703_Breakout radio(RESET_PIN, A4, A5, 2); 

// ===================== FFT Visualizer =====================
const uint16_t samples = 64; 
double vReal[samples], vImag[samples];
arduinoFFT FFT = arduinoFFT(vReal, vImag, samples, 5000);
unsigned long lastVizTime = 0;
int barH[8], lastBarH[8], lastLineY[31];

// ===================== State =====================
int freq10 = 958; // Default to 95.8 MHz
int lastFreq = -1;

// ===================== Smart Name Lookup =====================
const char* getStationName(int f) {
  switch(f) {
    case 888:  return "BBC Radio 2";
    case 910:  return "BBC Radio 3";
    case 932:  return "BBC Radio 4";
    case 949:  return "BBC London";
    case 958:  
    case 957:  return "Capital FM";
    case 964:  return "Eagle Radio"; 
    case 973:  return "LBC News";
    case 985:  return "BBC Radio 1";
    case 1006: return "Classic FM";
    case 1049: return "Radio X";
    case 1054: return "Magic FM";
    case 1062: return "Heart FM";
    case 1079: return "Radio Jackie";
    default:   return "FM Station"; 
  }
}

// ===================== Functions =====================

void updateUI() {
  if (freq10 != lastFreq) {
    // Clear the top area
    tft.fillRect(0, 0, 320, 100, ILI9341_BLACK);

    // Print Station Name
    tft.setCursor(20, 20);
    tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK); 
    tft.setTextSize(3);
    tft.print(getStationName(freq10));

    // Print Frequency
    tft.setCursor(20, 60);
    tft.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    tft.setTextSize(4);
    tft.print(freq10 / 10); tft.print('.'); tft.print(freq10 % 10); tft.print(F(" MHz"));

    lastFreq = freq10;
  }
}

void updateViz() {
  // Throttled to ~12 FPS
  if (millis() - lastVizTime < 80) return;
  lastVizTime = millis();

  // 1. Sample Audio
  for (int i = 0; i < samples; i++) {
    vReal[i] = analogRead(AUDIO_PIN) - 512.0;
    vImag[i] = 0.0;
    delayMicroseconds(100);
  }

  // 2. Compute FFT
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  int baseY = 200; // Moved further down since we have the whole screen!

  // 3. Draw Left Side (Bar Graph)
  for (int i = 0; i < 8; i++) {
    int h = constrain((int)vReal[i+1] / 6, 0, 60); // Made max height taller (60px)
    if (h != lastBarH[i]) {
      tft.fillRect(20 + (i * 15), baseY - 60, 12, 60, ILI9341_BLACK);
      tft.fillRect(20 + (i * 15), baseY - h, 12, h, ILI9341_GREEN);
      lastBarH[i] = h;
    }
  }

  // 4. Draw Right Side (Line Graph)
  for (int i = 0; i < 30; i++) {
    tft.drawLine(160 + (i * 5), lastLineY[i], 160 + ((i+1) * 5), lastLineY[i+1], ILI9341_BLACK);
  }
  
  for (int i = 0; i < 31; i++) {
    lastLineY[i] = baseY - constrain((int)vReal[i+1] / 5, 0, 60);
  }
  
  for (int i = 0; i < 30; i++) {
    tft.drawLine(160 + (i * 5), lastLineY[i], 160 + ((i+1) * 5), lastLineY[i+1], ILI9341_BLUE);
  }
}

// ===================== SETUP =====================
void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  
  tft.begin(); 
  tft.setRotation(1); 
  tft.fillScreen(ILI9341_BLACK);
  
  radio.powerOn(); 
  radio.setVolume(7); // Hardc
  radio.setChannel(freq10);
  
  updateUI();
  for(int i=0; i<31; i++) lastLineY[i] = 200;

  Serial.println(F("FFT Visualizer Ready."));
  Serial.println(F("Type 'U' and press Enter to tune UP. Type 'D' to tune DOWN."));
}

// ===================== LOOP =====================
void loop() {
  // Check Serial Monitor for channel changes
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'U' || c == 'u') {
      freq10 += 1;
      radio.setChannel(freq10);
      updateUI();
    } 
    else if (c == 'D' || c == 'd') {
      freq10 -= 1;
      radio.setChannel(freq10);
      updateUI();
    }
  }

  // Run the visualizer continuously
  updateViz();
}