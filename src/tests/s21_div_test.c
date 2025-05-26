#include "s21_tests.h"

// делимое и резульат 0
START_TEST(div_01) {
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

  // 0 / -5 = 0
  flag_error = s21_div(value_1, value_2, &result);

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

START_TEST(div_02) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 5
  value_1.bits[0] = 0b00000000000000000000000000000101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 0
  value_2.bits[0] = 0b00000000000000000000000000000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 5 / 0 = error = 3
  flag_error = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(3, flag_error);
}
END_TEST

// деление на 1
START_TEST(div_03) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 4294967295
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 1
  value_2.bits[0] = 0b00000000000000000000000000000001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 4294967295 / 1 = 1
  flag_error = s21_div(value_1, value_2, &result);

  // 4294967295
  origin.bits[0] = 0b11111111111111111111111111111111;
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

// деление на 1
START_TEST(div_04) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 8.4548758947598450975458 scale=22
  value_1.bits[0] = 0b00110111010111100110001011100010;
  value_1.bits[1] = 0b01100101101111000111000001010001;
  value_1.bits[2] = 0b00000000000000000001000111100111;
  value_1.bits[3] = 0b00000000000101100000000000000000;

  // 1
  value_2.bits[0] = 0b00000000000000000000000000000001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 8.4548758947598450975458 scale=22 / 1 = 8.4548758947598450975458 scale=22
  flag_error = s21_div(value_1, value_2, &result);

  // 8.4548758947598450975458 scale=22
  origin.bits[0] = 0b00110111010111100110001011100010;
  origin.bits[1] = 0b01100101101111000111000001010001;
  origin.bits[2] = 0b00000000000000000001000111100111;
  origin.bits[3] = 0b00000000000101100000000000000000;

  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// деление max на max
START_TEST(div_05) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 4294967295 / 1 = 1
  flag_error = s21_div(value_1, value_2, &result);

  // 1
  origin.bits[0] = 0b00000000000000000000000000000001;
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

// деление целых чисел без остатка
START_TEST(div_06) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 100
  value_1.bits[0] = 0b00000000000000000000000001100100;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 25
  value_2.bits[0] = 0b00000000000000000000000000011001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 100 / 25 = 4
  flag_error = s21_div(value_1, value_2, &result);

  // 4
  origin.bits[0] = 0b00000000000000000000000000000100;
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

// деление меньшего числа на большее (0 целых)
START_TEST(div_07) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 1
  value_1.bits[0] = 0b00000000000000000000000000000001;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 20
  value_2.bits[0] = 0b00000000000000000000000000010100;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 1 / 20 = 0.05 scale=2
  flag_error = s21_div(value_1, value_2, &result);

  // 0.05 scale=2
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// деление меньшего числа на большее (есть целые числа)
// делимое -
// результат -
START_TEST(div_08) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -35
  value_1.bits[0] = 0b00000000000000000000000000100011;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 8
  value_2.bits[0] = 0b00000000000000000000000000001000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // -35 / 8 = -4.375 scale=3
  flag_error = s21_div(value_1, value_2, &result);

  // -4.375 scale=3
  origin.bits[0] = 0b00000000000000000001000100010111;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// деление меньшего числа на большее (есть целые числа)
// деление дробных чисел
// делитель -
// результат -
START_TEST(div_09) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 4.3 scale=1
  value_1.bits[0] = 0b00000000000000000000000000101011;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000010000000000000000;

  // -0.5
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000010000000000000000;

  // 4.3 scale=1 / -0.5 = -8.6 scale=1
  flag_error = s21_div(value_1, value_2, &result);

  // -8.6 scale=1
  origin.bits[0] = 0b00000000000000000000000001010110;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000010000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// делимое и делитель отрицательные числа - -
START_TEST(div_10) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -10
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // -8
  value_2.bits[0] = 0b00000000000000000000000000001000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // -10 / -8 = 1.25 scale=2
  flag_error = s21_div(value_1, value_2, &result);

  // 1.25 scale=2
  origin.bits[0] = 0b00000000000000000000000001111101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// результат в периоде
// банковское округление
START_TEST(div_11) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 10
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 3
  value_2.bits[0] = 0b00000000000000000000000000000011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 10 / 3 = 3.3333333333333333333333333333 scale=28
  flag_error = s21_div(value_1, value_2, &result);

  // 3.3333333333333333333333333333_3 scale=28
  // округление 3 < 5
  origin.bits[0] = 0b00110101010101010101010101010101;
  origin.bits[1] = 0b11001111001001100000011111101110;
  origin.bits[2] = 0b01101011101101001010111111100100;
  origin.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// результат в периоде
// банковское округление
START_TEST(div_12) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 55
  value_1.bits[0] = 0b00000000000000000000000000110111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 6
  value_2.bits[0] = 0b00000000000000000000000000000110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 55 / 6 = 9.166666666666666666666666666_6 scale=27
  flag_error = s21_div(value_1, value_2, &result);

  // 9.166666666666666666666666667 scale=27
  // банковское округление до 7 так как остаток 6 > 5
  origin.bits[0] = 0b01001110101010101010101010101011;
  origin.bits[1] = 0b10111000111101110100001000101110;
  origin.bits[2] = 0b00011101100111100111110100101011;
  origin.bits[3] = 0b00000000000110110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// результат в периоде
// банковское округление
START_TEST(div_13) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 10
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 9
  value_2.bits[0] = 0b00000000000000000000000000001001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 10 / 9 = 1.1111111111111111111111111111 scale=28
  flag_error = s21_div(value_1, value_2, &result);

  // 1.1111111111111111111111111111_1 scale=28
  // округление 1 < 5
  origin.bits[0] = 0b01100111000111000111000111000111;
  origin.bits[1] = 0b01000101000011001010110101001111;
  origin.bits[2] = 0b00100011111001101110010101001100;
  origin.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// результат в периоде
// банковское округление
START_TEST(div_14) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 10
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 6
  value_2.bits[0] = 0b00000000000000000000000000000110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 10 / 6 = 1.6666666666666666666666666666_6 scale=28
  flag_error = s21_div(value_1, value_2, &result);

  // 1.6666666666666666666666666667 scale=28
  // банковское округление до 7 так как остаток 6 > 5
  origin.bits[0] = 0b00011010101010101010101010101011;
  origin.bits[1] = 0b01100111100100110000001111110111;
  origin.bits[2] = 0b00110101110110100101011111110010;
  origin.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// результат в периоде
// банковское округление
START_TEST(div_15) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 10
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 7
  value_2.bits[0] = 0b00000000000000000000000000000111;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 10 / 7 = 1.4285714285714285714285714285_7 scale=28
  flag_error = s21_div(value_1, value_2, &result);

  // 1.4285714285714285714285714286 scale=28
  // банковское округление до 6 так как остаток 7 > 5
  origin.bits[0] = 0b11001101101101101101101101101110;
  origin.bits[1] = 0b00110100001101001101111011010011;
  origin.bits[2] = 0b00101110001010001101110110101011;
  origin.bits[3] = 0b00000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

START_TEST(div_16) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 98765432109876543210
  value_1.bits[0] = 0b11100101001001100111111011101010;
  value_1.bits[1] = 0b01011010101001010100110100111000;
  value_1.bits[2] = 0b00000000000000000000000000000101;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 10
  value_2.bits[0] = 0b00000000000000000000000000001010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 98765432109876543210 / 10 = 9876543210987654321
  flag_error = s21_div(value_1, value_2, &result);

  // 9876543210987654321
  origin.bits[0] = 0b11100011101101110000110010110001;
  origin.bits[1] = 0b10001001000100001000011110111000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// 1 - число слишком велико или равно бесконечности
START_TEST(div_17) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 0.5 scale=1
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950335 / 0.5
  flag_error = s21_div(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(1, flag_error);
}
END_TEST

// 2 - число слишком мало или равно отрицательной бесконечности
START_TEST(div_18) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -0.5 scale=1
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000010000000000000000;

  // 79228162514264337593543950335 / -0.5
  flag_error = s21_div(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(2, flag_error);
}
END_TEST

Suite *suite_div(void) {
  Suite *s = suite_create("suite_div");
  TCase *tc = tcase_create("case_div");

  tcase_add_test(tc, div_01);
  tcase_add_test(tc, div_02);
  tcase_add_test(tc, div_03);
  tcase_add_test(tc, div_04);
  tcase_add_test(tc, div_05);
  tcase_add_test(tc, div_06);
  tcase_add_test(tc, div_07);
  tcase_add_test(tc, div_08);
  tcase_add_test(tc, div_09);
  tcase_add_test(tc, div_10);
  tcase_add_test(tc, div_11);
  tcase_add_test(tc, div_12);
  tcase_add_test(tc, div_13);
  tcase_add_test(tc, div_14);
  tcase_add_test(tc, div_15);
  tcase_add_test(tc, div_16);
  tcase_add_test(tc, div_17);
  tcase_add_test(tc, div_18);

  suite_add_tcase(s, tc);
  return s;
}
