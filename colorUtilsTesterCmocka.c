/**
 * This is a collection of unit tests for the
 * color utils library using the cmocka unit
 * test framework.
 *
 */
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <math.h>
#include <cmocka.h>

#include "colorUtils.h"

/**
 * This function is a generic testing function for min()
 * in which the passed state is expected to have 4 integer values
 * corresponding to the 3 input values and the expected output
 * value.
 */
static void testMinValues(void **state) {
  //cast the generic state to an int array
  int *values = *((int **)state);
  assert_true( min(values[0], values[1], values[2]) == values[3]);
}

/**
 * This function is a generic testing function for max()
 * in which the passed state is expected to have 4 integer values
 * corresponding to the 3 input values and the expected output
 * value.
 */
static void testMaxValues(void **state) {
  //cast the generic state to an int array
  int *values = *((int **)state);
  assert_true( max(values[0], values[1], values[2]) == values[3]);
}

/**
 * This function tests toSepia's error handling of NULL
 * values for its pass-by-reference parameters.  Each of
 * the three parameters are tested independently.  The function
 * should return a non-zero error value so we assert that the
 * return value is not equal to zero.
 *
 */
static void testToSepiaNull(void **state) {
  int r = 0, g = 0, b = 0;
  assert_int_not_equal(toSepia(NULL,&g,&b), 0);
  assert_int_not_equal(toSepia(&r,NULL,&b), 0);
  assert_int_not_equal(toSepia(&r,&g,NULL), 0);

}

/**
 * This function tests toSepia's error handling of out-of-range
 * values for the r, g, b parameters, each tested independently.
 * two values are tested each: a less-than-zero value and a value
 * greater than 255.
 */
static void testToSepiaOutOfBounds(void **state) {
  int r = 0, g = 0, b = 0, big = 256, neg = -1;
  assert_int_not_equal(toSepia(&neg,&g,&b), 0);
  assert_int_not_equal(toSepia(&big,&g,&b), 0);
  assert_int_not_equal(toSepia(&r,&neg,&b), 0);
  assert_int_not_equal(toSepia(&r,&big,&b), 0);
  assert_int_not_equal(toSepia(&r,&g,&neg), 0);
  assert_int_not_equal(toSepia(&r,&g,&big), 0);
  assert_int_equal(toSepia(&r,&g,&g), 0);
}

/**
 * This function tests toSepia passing a single, hard-coded
 * rgb-value (Steele Blue, 70, 130, 180).
 */
static void testToSepia001(void **state) {
  //steel blue:
  int r = 70, g = 130, b = 180;
  toSepia(&r,&g,&b);
  assert_true(r == 162 && g == 144 && b == 112);
}

/**
 * This function is a generic testing function for toSepia
 * in which the passed state is expected to have 6 integer values
 * corresponding to 3 RGB input values and 3 result values
 * that are known to be equivalent.
 *
 */
static void testToSepiaValues(void **state) {
  //cast the generic state to an int array
  int *values = *((int **)state);
  int r = values[0];
  int g = values[1];
  int b = values[2];
  toSepia(&r, &g, &b);
  assert_true(r == values[3] && g == values[4] && b == values[5]);
}

/**
 * This function tests toGrayScale's error handling of NULL
 * values for its pass-by-reference parameters.  Each of
 * the three parameters are tested independently.  The function
 * should return a non-zero error value so we assert that the
 * return value is not equal to zero.
 *
 */
static void testToGrayScaleNull(void **state) {
  int r = 0, g = 0, b = 0;
  assert_int_not_equal(toGrayScale(NULL,&g,&b,AVERAGE), 0);
  assert_int_not_equal(toGrayScale(&r,NULL,&b,AVERAGE), 0);
  assert_int_not_equal(toGrayScale(&r,&g,NULL,AVERAGE), 0);
}

/**
 * This function tests toGrayScale's error handling of invalid
 * values for its Mode parameter.  The function
 * should return a non-zero error value so we assert that the
 * return value is not equal to zero.
 *
 */
static void testToGrayScaleMode(void **state) {
  int r = 0, g = 0, b = 0;
  assert_int_not_equal(toGrayScale(NULL,&g,&b,0), 0);
  assert_int_not_equal(toGrayScale(&r,NULL,&b,4), 0);
}

/**
 * This function tests toGrayScale's error handling of out-of-range
 * values for the r, g, b parameters, each tested independently.
 * two values are tested each: a less-than-zero value and a value
 * greater than 255.
 */
static void testToGrayScaleOutOfBounds(void **state) {
  int r = 0, g = 0, b = 0, big = 256, neg = -1;
  assert_int_not_equal(toGrayScale(&neg,&g,&b,AVERAGE), 0);
  assert_int_not_equal(toGrayScale(&big,&g,&b,AVERAGE), 0);
  assert_int_not_equal(toGrayScale(&r,&neg,&b,AVERAGE), 0);
  assert_int_not_equal(toGrayScale(&r,&big,&b,AVERAGE), 0);
  assert_int_not_equal(toGrayScale(&r,&g,&neg,AVERAGE), 0);
  assert_int_not_equal(toGrayScale(&r,&g,&big,AVERAGE), 0);
  assert_int_equal(toGrayScale(&r,&g,&g,AVERAGE), 0);
  assert_int_equal(toGrayScale(&r,&g,&g,LUMINOSITY), 0);
  assert_int_equal(toGrayScale(&r,&g,&g,LIGHTNESS), 0);
}

/**
 * This function tests toGrayScale passing a single, hard-coded
 * rgb-value (Steele Blue, 70, 130, 180) using the average
 * method.
 */
static void testToGrayScale001(void **state) {
  //steel blue:
  int r = 70, g = 130, b = 180;
  toGrayScale(&r,&g,&b,AVERAGE);
  assert_true(r == 127 && g == 127 && b == 127);
}

/**
 * This function is a generic testing function for toGrayScale
 * in which the passed state is expected to have 6 integer values
 * corresponding to 3 RGB input values and 3 result values
 * that are known to be equivalent.
 *
 */
static void testToGrayScaleValues(void **state) {
  //cast the generic state to an int array
  int *values = *((int **)state);

  int r = values[0], g = values[1], b = values[2];

  toGrayScale(&r, &g, &b, values[3]);
  assert_true(
              r == values[4] &&
              g == values[5] &&
              b == values[6]);

}


int main(int argc, char **argv) {

  int maxTestCases[][4] = {
    {10, 20, 30, 30},
    {10, 30, 20, 30},
    {20, 10, 30, 30},
    {20, 30, 10, 30},
    {30, 10, 20, 30},
    {30, 20, 10, 30},
    {10, 10, 30, 30},
    {10, 30, 10, 30},
    {30, 10, 10, 30},
    {30, 30, 30, 30},
  };

  int minTestCases[][4] = {
    {10, 20, 30, 10},
    {10, 30, 20, 10},
    {20, 10, 30, 10},
    {20, 30, 10, 10},
    {30, 10, 20, 10},
    {30, 20, 10, 10},
    {10, 10, 30, 10},
    {10, 30, 10, 10},
    {30, 10, 10, 10},
    {30, 30, 30, 30},
  };

  // color -> sepia tone
  // r,g,b (inputs), r,g,b (expected results)
  int sepiaTests[][6] = {
          // Pure RGB
          { 255, 0,   0, 100,  89,  69},
          { 0, 255,   0, 196, 175, 136},
          { 0,   0, 255,  48,  43,  33},

          // Errors should not change the r, g, and b values
          {  355,    0,    0,  355,    0,    0 },
          {    0,  355,    0,    0,  355,    0 },
          {    0,    0,  355,    0,    0,  355 },
          { -355,    0,    0, -355,    0,    0 },
          {    0, -355,    0,    0, -355,    0 },
          {    0,    0, -355,    0,    0, -355 },

          // General tests
          { 123, 100,  20, 129, 115,  89},
          { 200, 128,  64, 189, 168, 131},
          {  16,  32,  64,  43,  38,  30},
          {  90, 190, 228, 225, 200, 156},
          {  12,  36,  75,  47,  41,  32},
          {  47,  41,  32,  56,  50,  39},
          {  56, 187, 132, 191, 170, 132},
  };

  // gray scale test values
  // r,g,b (inputs), mode, r,g,b (expected results)
  int greyScaleTests[][7] = {
          // Pure RGB
          {255, 0, 0,    AVERAGE,  85,  85,  85},
          {255, 0, 0,  LIGHTNESS, 128, 128, 128},
          {255, 0, 0, LUMINOSITY,  54,  54,  54},
          {0, 255, 0,    AVERAGE,  85,  85,  85},
          {0, 255, 0,  LIGHTNESS, 128, 128, 128},
          {0, 255, 0, LUMINOSITY, 184, 184, 184},
          {0, 0, 255,    AVERAGE,  85,  85,  85},
          {0, 0, 255,  LIGHTNESS, 128, 128, 128},
          {0, 0, 255, LUMINOSITY,  18,  18,  18},

          // Errors should not change the r, g, and b values
          { 300, 300, 300,    AVERAGE, 300, 300, 300},
          { 300, 300, 300,  LIGHTNESS, 300, 300, 300},
          { 300, 300, 300, LUMINOSITY, 300, 300, 300},

          // General tests
          {  42,  17,   9,    AVERAGE,  23,  23,  23},
          { 250, 128, 212,    AVERAGE, 197, 197, 197},
          {  11, 204, 160,    AVERAGE, 125, 125, 125},
          { 218, 232, 249,    AVERAGE, 233, 233, 233},
          { 130, 248,   0,    AVERAGE, 126, 126, 126},
          {  35, 102, 157,    AVERAGE,  98,  98,  98},
          {   4,  10, 180,    AVERAGE,  65,  65,  65},
          {  71,  77, 227,    AVERAGE, 125, 125, 125},
          { 233, 119, 131,    AVERAGE, 161, 161, 161},
          { 219,  47, 219,    AVERAGE, 162, 162, 162},
          { 103, 177, 202,    AVERAGE, 161, 161, 161},
          { 123, 177, 125,    AVERAGE, 142, 142, 142},
          {  12, 105, 219,    AVERAGE, 112, 112, 112},
          { 115, 106,  80,    AVERAGE, 100, 100, 100},
          { 253, 231,  22,    AVERAGE, 169, 169, 169},

          {  36, 118, 102,  LIGHTNESS,  77,  77,  77},
          { 244,  75, 177,  LIGHTNESS, 160, 160, 160},
          { 150,  83, 249,  LIGHTNESS, 166, 166, 166},
          {   9,  45,  49,  LIGHTNESS,  29,  29,  29},
          {  56, 145, 123,  LIGHTNESS, 101, 101, 101},
          { 157,  15,  61,  LIGHTNESS,  86,  86,  86},
          { 148,  37,   9,  LIGHTNESS,  79,  79,  79},
          {  28, 196, 130,  LIGHTNESS, 112, 112, 112},
          {  22, 219,  87,  LIGHTNESS, 121, 121, 121},
          { 183, 202,  22,  LIGHTNESS, 112, 112, 112},
          { 115,  86, 176,  LIGHTNESS, 131, 131, 131},
          {  24, 168,   2,  LIGHTNESS,  85,  85,  85},
          { 252, 191,   3,  LIGHTNESS, 128, 128, 128},
          { 163,   7, 150,  LIGHTNESS,  85,  85,  85},
          { 105, 217, 235,  LIGHTNESS, 170, 170, 170},

          { 240,  84, 127, LUMINOSITY, 120, 120, 120},
          { 109,  30, 130, LUMINOSITY,  54,  54,  54},
          { 121,   1, 118, LUMINOSITY,  34,  34,  34},
          { 144,  24, 177, LUMINOSITY,  60,  60,  60},
          { 183,  38,  96, LUMINOSITY,  73,  73,  73},
          { 167,  20,  73, LUMINOSITY,  55,  55,  55},
          { 252, 200,  75, LUMINOSITY, 202, 202, 202},
          {  98, 140, 164, LUMINOSITY, 133, 133, 133},
          {  21, 207,  91, LUMINOSITY, 160, 160, 160},
          {  52, 203, 128, LUMINOSITY, 166, 166, 166},
          {  39, 181, 125, LUMINOSITY, 147, 147, 147},
          {  27, 230, 245, LUMINOSITY, 188, 188, 188},
          { 132, 182,  77, LUMINOSITY, 164, 164, 164},
          { 194, 182, 246, LUMINOSITY, 189, 189, 189},
          {  21,  10,   4, LUMINOSITY,  12,  12,  12}
  };

  const struct CMUnitTest tests[] = {
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[0]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[1]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[2]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[3]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[4]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[5]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[6]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[7]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[8]),
    cmocka_unit_test_prestate(testMaxValues, &maxTestCases[9]),

    cmocka_unit_test_prestate(testMinValues, &minTestCases[0]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[1]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[2]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[3]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[4]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[5]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[6]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[7]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[8]),
    cmocka_unit_test_prestate(testMinValues, &minTestCases[9]),

    cmocka_unit_test(testToSepiaNull),
    cmocka_unit_test(testToSepiaOutOfBounds),
    cmocka_unit_test(testToSepia001),

    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[0]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[1]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[2]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[3]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[4]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[5]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[6]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[7]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[8]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[9]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[10]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[11]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[12]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[13]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[14]),
    cmocka_unit_test_prestate(testToSepiaValues, &sepiaTests[15]),

    cmocka_unit_test(testToGrayScaleNull),
    cmocka_unit_test(testToGrayScaleMode),
    cmocka_unit_test(testToGrayScaleOutOfBounds),
    cmocka_unit_test(testToGrayScale001),

    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[0]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[1]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[2]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[3]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[4]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[5]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[6]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[7]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[8]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[9]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[10]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[11]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[12]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[13]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[14]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[15]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[16]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[17]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[18]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[19]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[20]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[21]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[22]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[23]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[24]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[25]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[26]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[27]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[28]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[29]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[30]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[31]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[32]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[33]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[34]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[35]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[36]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[37]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[38]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[39]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[40]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[41]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[42]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[43]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[44]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[45]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[46]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[47]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[48]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[49]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[50]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[51]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[52]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[53]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[54]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[55]),
    cmocka_unit_test_prestate(testToGrayScaleValues, &greyScaleTests[56])
  };

  return cmocka_run_group_tests(tests, NULL, NULL);

}
