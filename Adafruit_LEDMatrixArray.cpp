#include "Adafruit_LEDMatrixArray.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  } ///< 16-bit var swap
#endif

template <int rows, int cols>
Adafruit_LEDMatrixArray<rows, cols>::Adafruit_LEDMatrixArray(
  T *matrix,
  uint8_t *addresses
) : Adafruit_GFX(MATRIX_WIDTH, MATRIX_HEIGHT), matrix(matrix), addresses(addresses) {}

template <int rows, int cols>
void Adafruit_LEDMatrixArray<rows, cols>::begin() {
  for (int i = 0; i < rows*cols; i++) {
    matrix[i].begin(addresses[i]);
  }
}

template <int rows, int cols>
void Adafruit_LEDMatrixArray<rows, cols>::setBrightness(uint8_t b) {
  for (int i = 0; i < rows*cols; i++) {
    matrix[i].setBrightness(addresses[i]);
  }
}

template <int rows, int cols>
void Adafruit_LEDMatrixArray<rows, cols>::blinkRate(uint8_t b) {
  for (int i = 0; i < rows*cols; i++) {
    matrix[i].blinkRate(b);
  }
}

template <int rows, int cols>
void Adafruit_LEDMatrixArray<rows, cols>::writeDisplay() {
  for (int i = 0; i < rows*cols; i++) {
    matrix[i].writeDisplay();
  }
}

template <int rows, int cols>
void Adafruit_LEDMatrixArray<rows, cols>::clear() {
  for (int i = 0; i < rows*cols; i++) {
      matrix[i].clear();
  }
}

template <int rows, int cols>
void Adafruit_LEDMatrixArray<rows, cols>::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= MATRIX_WIDTH))
    return;
  if ((y < 0) || (y >= MATRIX_HEIGHT))
    return;

  switch (getRotation()) {
  case 1:
    _swap_int16_t(x, y);
    x = MATRIX_WIDTH - x - 1;
    break;
  case 2:
    x = MATRIX_WIDTH - x - 1;
    y = MATRIX_HEIGHT - y - 1;
    break;
  case 3:
    _swap_int16_t(x, y);
    y = MATRIX_HEIGHT - y - 1;
    break;
  }
  
  int16_t col = x / TILE_WIDTH;
  int16_t dpx = x % TILE_WIDTH;
  int16_t row = y / TILE_HEIGHT;
  int16_t dpy = y % TILE_HEIGHT;
  matrix[row*cols + col].drawPixel(dpx, dpy, color);
}

template <int rows, int cols>
int Adafruit_LEDMatrixArray<rows, cols>::textWidth(const String& text) {
  return text.length() * 6 * textsize_x;
}
