#include <Adafruit_NeoPixel.h>

#define STRIPLENGTH 50
#define LEDPIN 0
#define FULLROWS 4
#define HALFROWS 4
#define COLUMNS 8
#define ROWS 8
#define MAX_INTENSITY 200
#define G_INCREMENT 32
#define B_INCREMENT 32
#define R_INCREMENT 16
#define WAIT 200


//#define ROWS FULLROWS+HALFROWS
byte ledMatrix [ROWS][COLUMNS];
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPLENGTH+1, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  if ((FULLROWS+(HALFROWS/2))*COLUMNS>STRIPLENGTH) {
    Serial.print("The number of neopixels in ledMatrix (");
    Serial.print((FULLROWS+(HALFROWS/2))*COLUMNS);
    Serial.println(") exceeds the number of neopixels in striplength (STRIPLENGTH).");
  }
  strip.begin();
  strip.show();
  delay(1);
  
  byte k=0;
  //strip.setPixelColor(4, strip.Color(0, 0, 255));
  //strip.show();
  //delay(1000);
  for(byte i=0; i<FULLROWS; i++) {
    for(byte j=0; j<COLUMNS; j++) {
      ledMatrix[i][j]=k;
      k++;
    }
  }
  
  for(byte i=FULLROWS; i<ROWS; i++) {
    for(byte j=0; j<COLUMNS; j+=2) {
      ledMatrix[i][j]=k;
      ledMatrix[i][j+1]=STRIPLENGTH;
      k++;
    }
  }
}

void loop() {
  for (int count=0; count<8; count++) {
    twoColorHSpin(strip.Color(0, 0, 255), strip.Color(127, 127, 127), 500); // Blue, White
  }
  for (int count=0; count<8; count++) {
    twoColorHSpin(strip.Color(255, 0, 0), strip.Color(0, 255, 0), 500); // Red, Green
  }
  for (int count=0; count<8; count++) {
    twoColorVSpin(strip.Color(0, 0, 255), strip.Color(127, 127, 127), 500); // Blue, White
  }
  for (int count=0; count<8; count++) {
    twoColorVSpin(strip.Color(255, 0, 0), strip.Color(0, 255, 0), 500); // Blue, White
  }
  for (int count=0; count<500; count++) {
    randompixel(25);
  }
  for (int b=0; b<MAX_INTENSITY; b+=B_INCREMENT) {
    for (int g=0; g<MAX_INTENSITY; g+=G_INCREMENT) {
      for (int r=0; r<MAX_INTENSITY; r+=R_INCREMENT) {
        vsweep(strip.Color(r, g, b), WAIT);
      }
    }
  }
  for (int b=0; b<MAX_INTENSITY; b+=B_INCREMENT) {
    for (int g=0; g<MAX_INTENSITY; g+=G_INCREMENT) {
      for (int r=0; r<MAX_INTENSITY; r+=R_INCREMENT) {
          hsweep(strip.Color(r, g, b), WAIT);
      }
    }
  }
}

void twoColorHSpin(uint32_t color1, uint32_t color2, int wait) {
  fourColorHSpin(color1, color1, color2, color2, wait);
}

void fourColorHSpin(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int wait) {
  uint32_t color[4][4]={{a,b,c,d},{d,a,b,c},{c,d,a,b},{b,c,d,a}};
  // loop thru positions
  for (byte k=0; k<4; k++) {
    // loop thru rows
    for (byte i=0; i<ROWS; i++) {
      // loop thru columns
      for (byte j=0; j<COLUMNS; j+=4) {
        // set column color
        for (byte l=0; l<4; l++) {
          strip.setPixelColor(ledMatrix [i][j+l], color[k][l]);
        }
      }
    }
    strip.show();
    delay(wait);
  }
}

void twoColorVSpin(uint32_t color1, uint32_t color2, int wait) {
  fourColorVSpin(color1, color1, color2, color2, wait);
}

void fourColorVSpin(uint32_t a, uint32_t b, uint32_t c, uint32_t d, int wait) {
  uint32_t color[4][4]={{a,b,c,d},{d,a,b,c},{c,d,a,b},{b,c,d,a}};
  // loop thru positions
  for (byte k=0; k<4; k++) {
    // loop thru rows
    for (byte i=0; i<ROWS; i+=4) {
      // loop thru columns
      for (byte j=0; j<COLUMNS; j++) {
        // set column color
        for (byte l=0; l<4; l++) {
          strip.setPixelColor(ledMatrix [i+l][j], color[k][l]);
        }
      }
    }
    strip.show();
    delay(wait);
  }
}

void randompixel(int wait) {
  int r;
  int g;
  int b;
  int pixel;
  r=random(MAX_INTENSITY);
  g=random(MAX_INTENSITY);
  b=random(MAX_INTENSITY);
  pixel=random(STRIPLENGTH);
  strip.setPixelColor(pixel, strip.Color(r, g, b));
  strip.show();
  delay(wait);
}

void vsweep(uint32_t a, int wait) {
  for (byte j=0; j<COLUMNS; j++) {
    for (byte i=0; i<ROWS; i++) {
      strip.setPixelColor(ledMatrix [i][j], a);
    }
    strip.show();
    delay(wait);
  }
}
void hsweep(uint32_t a, int wait) {
  for (byte i=0; i<ROWS; i++) {
    for (byte j=0; j<COLUMNS; j++) {
      strip.setPixelColor(ledMatrix [i][j], a);
    }
    strip.show();
    delay(wait);
  }
}
