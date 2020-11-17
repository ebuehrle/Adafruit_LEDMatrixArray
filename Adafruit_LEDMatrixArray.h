#ifndef ADAFRUIT_LEDMATRIXARRAY_H
#define ADAFRUIT_LEDMATRIXARRAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

typedef Adafruit_BicolorMatrix T; // would prefer a common base class of LED matrix types

template <int rows, int cols>
class Adafruit_LEDMatrixArray : public Adafruit_GFX {
public:
  static const int TILE_WIDTH = 8;
  static const int TILE_HEIGHT = 8;
  static const int MATRIX_WIDTH = TILE_WIDTH * cols;
  static const int MATRIX_HEIGHT = TILE_HEIGHT * rows;

  Adafruit_LEDMatrixArray(
    T *matrix,
    uint8_t *addresses
  );

  void begin();
  void setBrightness(uint8_t b);
  void blinkRate(uint8_t b);
  void writeDisplay();
  void clear();

  virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
  virtual int textWidth(const String& text);

private:
  T *matrix;
  uint8_t *addresses;
};

#endif //ADAFRUIT_LEDMATRIXARRAY_H
