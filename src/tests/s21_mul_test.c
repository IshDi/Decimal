#include "s21_tests.h"

// 0 x 0 = 0
START_TEST(mul_01) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 0
  value_1.bits[0] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 0
  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 0 x 0 = 0
  flag_error = s21_mul(value_1, value_2, &result);

  // 0
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// множитель 1 = 0
START_TEST(mul_02) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 0
  value_1.bits[0] = 0b00000000000000000000000000000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 5
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 0 x 5 = 0
  flag_error = s21_mul(value_1, value_2, &result);

  // 0
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// множитель 2 = 0
START_TEST(mul_03) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 4
  value_1.bits[0] = 0b00000000000000000000000000000100;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 0
  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 4 x 0 = 0
  flag_error = s21_mul(value_1, value_2, &result);

  // 0
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// числа + +
START_TEST(mul_04) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 12
  value_1.bits[0] = 0b00000000000000000000000000001100;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 12
  value_2.bits[0] = 0b00000000000000000000000000001100;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 12 x 12 = 144
  flag_error = s21_mul(value_1, value_2, &result);

  // 144
  origin.bits[0] = 0b00000000000000000000000010010000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// числа - -
START_TEST(mul_05) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 13
  value_1.bits[0] = 0b00000000000000000000000000001101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 13
  value_2.bits[0] = 0b00000000000000000000000000001101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 13 x 13 = 169
  flag_error = s21_mul(value_1, value_2, &result);

  // 169
  origin.bits[0] = 0b00000000000000000000000010101001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// числа + -
START_TEST(mul_06) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 12345678
  value_1.bits[0] = 0b00000000101111000110000101001110;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -87654321
  value_2.bits[0] = 0b00000101001110010111111110110001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 12345678 x -87654321 = -1082152022374638
  flag_error = s21_mul(value_1, value_2, &result);

  // -1082152022374638
  origin.bits[0] = 0b00100110111000101111100011101110;
  origin.bits[1] = 0b00000000000000111101100000110110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// числа - +
START_TEST(mul_07) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -2024
  value_1.bits[0] = 0b00000000000000000000011111101000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 84548758947598450975458
  value_2.bits[0] = 0b00110111010111100110001011100010;
  value_2.bits[1] = 0b01100101101111000111000001010001;
  value_2.bits[2] = 0b00000000000000000001000111100111;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // -2024 x 84548758947598450975458 = -171126688109939264774326992
  flag_error = s21_mul(value_1, value_2, &result);

  // -171126688109939264774326992
  origin.bits[0] = 0b11000010001111011100101011010000;
  origin.bits[1] = 0b01011001110110000000001000011101;
  origin.bits[2] = 0b00000000100011011000110101111100;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// 1 - число слишком велико или равно бесконечности
START_TEST(mul_08) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 5
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // error = 1
  flag_error = s21_mul(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(1, flag_error);
}
END_TEST

// 2 - число слишком мало или равно отрицательной бесконечности
START_TEST(mul_09) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -4
  value_1.bits[0] = 0b00000000000000000000000000000100;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // error = 2
  flag_error = s21_mul(value_1, value_2, &result);

  // error = 2
  ck_assert_int_eq(2, flag_error);
}
END_TEST

// 79228162514264337593543950335 x 1 = 79228162514264337593543950335
START_TEST(mul_10) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 1
  value_2.bits[0] = 0b00000000000000000000000000000001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 79228162514264337593543950335 x 1 = 79228162514264337593543950335
  flag_error = s21_mul(value_1, value_2, &result);

  // 79228162514264337593543950335
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b11111111111111111111111111111111;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// числа с точкой + +
START_TEST(mul_11) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 2.024 scale=3
  value_1.bits[0] = 0b00000000000000000000011111101000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000110000000000000000;

  // 8.4548758947598450975458 scale=22
  value_2.bits[0] = 0b00110111010111100110001011100010;
  value_2.bits[1] = 0b01100101101111000111000001010001;
  value_2.bits[2] = 0b00000000000000000001000111100111;
  value_2.bits[3] = 0b00000000000101100000000000000000;

  // 2.024 scale=3 x 8.4548758947598450975458 scale=22
  // = 17.1126688109939264774326992 scale=25
  flag_error = s21_mul(value_1, value_2, &result);

  // 17.1126688109939264774326992 scale=25
  origin.bits[0] = 0b11000010001111011100101011010000;
  origin.bits[1] = 0b01011001110110000000001000011101;
  origin.bits[2] = 0b00000000100011011000110101111100;
  origin.bits[3] = 0b00000000000110010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// числа с точкой + -
START_TEST(mul_12) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 10.123456789 scale=9
  value_1.bits[0] = 0b01011011011001111011000100010101;
  value_1.bits[1] = 0b00000000000000000000000000000010;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010010000000000000000;

  // -20.01999999998 scale=11
  value_2.bits[0] = 0b00100000011111111011001111111110;
  value_2.bits[1] = 0b00000000000000000000000111010010;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000010110000000000000000;

  // 10.123456789 scale=9 x -20.01999999998 scale=11 = -202.67160491557753086422
  // scale=20
  flag_error = s21_mul(value_1, value_2, &result);

  // -202.67160491557753086422 scale=20
  origin.bits[0] = 0b10101011000111100110000111010110;
  origin.bits[1] = 0b10101111010110100100111100001101;
  origin.bits[2] = 0b00000000000000000000010001001010;
  origin.bits[3] = 0b10000000000101000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// числа с точкой - +
START_TEST(mul_13) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -20.01999999998 scale=11
  value_1.bits[0] = 0b00100000011111111011001111111110;
  value_1.bits[1] = 0b00000000000000000000000111010010;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000010110000000000000000;

  // 10.123456789 scale=9
  value_2.bits[0] = 0b01011011011001111011000100010101;
  value_2.bits[1] = 0b00000000000000000000000000000010;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000010010000000000000000;

  // -20.01999999998 scale=11 x 10.123456789 scale=9 = -202.67160491557753086422
  // scale=20
  flag_error = s21_mul(value_1, value_2, &result);

  // -202.67160491557753086422 scale=20
  origin.bits[0] = 0b10101011000111100110000111010110;
  origin.bits[1] = 0b10101111010110100100111100001101;
  origin.bits[2] = 0b00000000000000000000010001001010;
  origin.bits[3] = 0b10000000000101000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// переполнение скейл error = 1
START_TEST(mul_14) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 812.3456789012345678901234567 scale=25
  value_1.bits[0] = 0b01101100100111110100101110000111;
  value_1.bits[1] = 0b11101111110111001111010010001111;
  value_1.bits[2] = 0b00011010001111111001000011100010;
  value_1.bits[3] = 0b00000000000110010000000000000000;

  // 8123456789012345678901234567
  value_2.bits[0] = 0b01101100100111110100101110000111;
  value_2.bits[1] = 0b11101111110111001111010010001111;
  value_2.bits[2] = 0b00011010001111111001000011100010;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // flag_error = 1;
  flag_error = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(1, flag_error);
}
END_TEST

// переполнение скейл error = 2
START_TEST(mul_15) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 812.3456789012345678901234567 scale=25
  value_1.bits[0] = 0b01101100100111110100101110000111;
  value_1.bits[1] = 0b11101111110111001111010010001111;
  value_1.bits[2] = 0b00011010001111111001000011100010;
  value_1.bits[3] = 0b10000000000110010000000000000000;

  // 8123456789012345678901234567
  value_2.bits[0] = 0b01101100100111110100101110000111;
  value_2.bits[1] = 0b11101111110111001111010010001111;
  value_2.bits[2] = 0b00011010001111111001000011100010;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // flag_error = 2;
  flag_error = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(2, flag_error);
}
END_TEST

// банковское округление
START_TEST(mul_16) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 8.123456789012345678901234567 scale=27
  value_1.bits[0] = 0b01101100100111110100101110000111;
  value_1.bits[1] = 0b11101111110111001111010010001111;
  value_1.bits[2] = 0b00011010001111111001000011100010;
  value_1.bits[3] = 0b00000000000110110000000000000000;

  // 81234567890123456789012345.67 scale=2
  value_2.bits[0] = 0b01101100100111110100101110000111;
  value_2.bits[1] = 0b11101111110111001111010010001111;
  value_2.bits[2] = 0b00011010001111111001000011100010;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 8.123456789012345678901234567 scale=27 x 81234567890123456789012345.67
  // scale=2 = 0
  flag_error = s21_mul(value_1, value_2, &result);

  // scale=2
  // 659905502029507696991702484.23_342783114345526596755677489
  // 659905502029507696991702484.23 (3 < 5 округляем до 3)
  origin.bits[0] = 0b11101100111001110110011011100111;
  origin.bits[1] = 0b10101101011110100101111101001010;
  origin.bits[2] = 0b11010101001110100001101010001110;
  origin.bits[3] = 0b00000000000000100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

Suite *suite_mul(void) {
  Suite *s = suite_create("suite_mul");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, mul_01);
  tcase_add_test(tc, mul_02);
  tcase_add_test(tc, mul_03);
  tcase_add_test(tc, mul_04);
  tcase_add_test(tc, mul_05);
  tcase_add_test(tc, mul_06);
  tcase_add_test(tc, mul_07);
  tcase_add_test(tc, mul_08);
  tcase_add_test(tc, mul_09);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);
  tcase_add_test(tc, mul_13);
  tcase_add_test(tc, mul_14);
  tcase_add_test(tc, mul_15);
  tcase_add_test(tc, mul_16);

  suite_add_tcase(s, tc);
  return s;
}