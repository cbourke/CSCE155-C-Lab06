
#ifndef MODE_H
#define MODE_H

typedef enum {
  AVERAGE,
  LIGHTNESS,
  LUMINOSITY
} Mode;

#endif /* MODE_H */

/**
 * Returns the maximum value among the three given values
 */
int max(int a, int b, int c);

/**
 * Returns the minimum value among the three given values
 */
int min(int a, int b, int c);

/**
 * TODO: add documentation here
 */
int toGrayScale(int *r, int *g, int *b, Mode mode);

/**
 * TODO: add documentation here
 */
int toSepia(int *r, int *g, int *b);
