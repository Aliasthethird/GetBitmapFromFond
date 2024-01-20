#include <Arduino.h>
#include <Fonts/FreeMonoBold24pt7b.h>

// How to use the font:
// https://github.com/adafruit/Adafruit-GFX-Library/commit/80b1bc48cbaac8a33054383124db6d613cbde3c2
// https://tchapi.github.io/Adafruit-GFX-Font-Customiser/

#define LINE_DELAY 20

void setup()
{
  Serial.begin(115200); // Set serial speed to 115200 baud
}

void loop()
{
  // for(int i = -16; i < 79; i++) // entire font
  for (int i = 0; i < 9; i++) // only numbers
  {
    char ch = i + 48; // ASCII code of '0' is 48

    // Calculate the index in the glyph array
    int glyphIndex = ch - 32; // ASCII code of 'A' is 65 and font starts at ASCII code 32

    // Access the glyph data
    GFXglyph glyph = FreeMonoBold24pt7bGlyphs[glyphIndex];

    // Calculate the bit value for each pixel
    for (int y = 0; y < glyph.height; y++)
    {
      for (int x = 0; x < glyph.width; x++)
      {
        uint16_t i_bit = glyph.width * y + x;
        // Calculate the position in the bitmap array
        int i_byte = glyph.bitmapOffset + i_bit / 8; // rounding down the width to the nearest byte

        // Get the byte from the bitmap array
        uint8_t data = pgm_read_byte(&FreeMonoBold24pt7bBitmaps[i_byte]);

        // Check if the specific pixel is set
        bool pixelSet = data & (0x80 >> (i_bit % 8));
        Serial.print(pixelSet ? '.' : ' ');
      }
      Serial.println();
      delay(LINE_DELAY);
    }
    Serial.println();
    delay(LINE_DELAY);
    Serial.println();
    delay(LINE_DELAY);
    Serial.println();
    delay(LINE_DELAY);
  }
}
