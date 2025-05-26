#include "s21_tests.h"

// пример из задания (с использованием банковскго округления)
// 0 - OK
START_TEST(sub_01) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 0.6
  value_2.bits[0] = 0b00000000000000000000000000000110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950335 - 0.6 = 79228162514264337593543950334
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543950334
  origin.bits[0] = 0b11111111111111111111111111111110;
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

// результат = 0
START_TEST(sub_02) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 5
  value_1.bits[0] = 0b00000000000000000000000000000101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 5
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 5 - 5 = 0
  flag_error = s21_sub(value_1, value_2, &result);

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

// вычитаемое = 0
START_TEST(sub_03) {
  s21_decimal value_1, value_2, origin;
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

  // 5 - 0 = 5
  flag_error = s21_sub(value_1, value_2, &result);

  // 5
  origin.bits[0] = 0b00000000000000000000000000000101;
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

// уменьшаемое = 0
// разность - (уменьшаемое меньше вычитаемого)
START_TEST(sub_04) {
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

  // 0 - 5 = -5
  flag_error = s21_sub(value_1, value_2, &result);

  // -5
  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// вычитаемое - (- на - дает +)
START_TEST(sub_05) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 5
  value_1.bits[0] = 0b00000000000000000000000000000101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -5
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 5 - (-5) = 10
  flag_error = s21_sub(value_1, value_2, &result);

  // 10
  origin.bits[0] = 0b00000000000000000000000000001010;
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

// уменьшаемое -
START_TEST(sub_06) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -5
  value_1.bits[0] = 0b00000000000000000000000000000101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 5
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // (-5) - 5 = 0
  flag_error = s21_sub(value_1, value_2, &result);

  // -10
  origin.bits[0] = 0b00000000000000000000000000001010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// уменьшаемое - и вычитаемое -
START_TEST(sub_07) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -5
  value_1.bits[0] = 0b00000000000000000000000000000101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // -7
  value_2.bits[0] = 0b00000000000000000000000000000111;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // -5 - (-7) = 2
  flag_error = s21_sub(value_1, value_2, &result);

  // 2
  origin.bits[0] = 0b00000000000000000000000000000010;
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

// 1 - число слишком велико или равно бесконечности
START_TEST(sub_08) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 79228162514264337593543950335 - (-79228162514264337593543950335) = error =
  // 1
  flag_error = s21_sub(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(1, flag_error);
}
END_TEST

// 2 - число слишком мало или равно отрицательной бесконечности
START_TEST(sub_09) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // -79228162514264337593543950335 - 79228162514264337593543950335 = error = 2
  flag_error = s21_sub(value_1, value_2, &result);

  // error = 2
  ck_assert_int_eq(2, flag_error);
}
END_TEST

// большие целые числа без scale, разница +
START_TEST(sub_10) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 162514264337593543950335
  value_2.bits[0] = 0b00000011111111111111111111111111;
  value_2.bits[1] = 0b11101010011110011110100110010001;
  value_2.bits[2] = 0b00000000000000000010001001101001;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 79228162514264337593543950335 - 162514264337593543950335 =
  // 79228000000000000000000000000
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228000000000000000000000000
  origin.bits[0] = 0b11111100000000000000000000000000;
  origin.bits[1] = 0b00010101100001100001011001101110;
  origin.bits[2] = 0b11111111111111111101110110010110;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие целые числа без scale, разница -
START_TEST(sub_11) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 162514264337593543950335
  value_1.bits[0] = 0b00000011111111111111111111111111;
  value_1.bits[1] = 0b11101010011110011110100110010001;
  value_1.bits[2] = 0b00000000000000000010001001101001;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 162514264337593543950335 - 79228162514264337593543950335 =
  // -79228000000000000000000000000
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228000000000000000000000000
  origin.bits[0] = 0b11111100000000000000000000000000;
  origin.bits[1] = 0b00010101100001100001011001101110;
  origin.bits[2] = 0b11111111111111111101110110010110;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// 2 - число слишком мало или равно отрицательной бесконечности
START_TEST(sub_12) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 2
  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // -79228162514264337593543950335 - 2 = -79228162514264337593543950337 = error
  // = 2
  flag_error = s21_sub(value_1, value_2, &result);

  // error = 2
  ck_assert_int_eq(2, flag_error);
}
END_TEST

// 1 - число слишком велико или равно бесконечности
START_TEST(sub_13) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -2
  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 79228162514264337593543950335 - (-2) = 79228162514264337593543950337 =
  // error = 1
  flag_error = s21_sub(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(1, flag_error);
}
END_TEST

// 1 - число слишком велико или равно бесконечности
START_TEST(sub_14) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 2
  value_1.bits[0] = 0b00000000000000000000000000000010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 2 - (-79228162514264337593543950335) = 79228162514264337593543950337 =
  // error = 1
  flag_error = s21_sub(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(1, flag_error);
}
END_TEST

// 2 - число слишком мало или равно отрицательной бесконечности
START_TEST(sub_15) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -2
  value_1.bits[0] = 0b00000000000000000000000000000010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // (-2) - 79228162514264337593543950335 -  = (-79228162514264337593543950337)
  // = error = 2
  flag_error = s21_sub(value_1, value_2, &result);

  // error = 2
  ck_assert_int_eq(2, flag_error);
}
END_TEST

// scale (разные)
START_TEST(sub_16) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 10000.00 scale = 2
  value_1.bits[0] = 0b00000000000011110100001001000000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000100000000000000000;

  // 3000.0000 scale = 4
  value_2.bits[0] = 0b00000001110010011100001110000000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000001000000000000000000;

  // 100.00 scale = 2 - 3000.0000 scale = 4 = 7000.0000 scale = 4
  flag_error = s21_sub(value_1, value_2, &result);

  // 7000.0000 scale = 4
  origin.bits[0] = 0b00000100001011000001110110000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000001000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// scale (разные)
START_TEST(sub_17) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -1.3 scale=1
  value_1.bits[0] = 0b00000000000000000000000000001101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000010000000000000000;

  // -2.86 scale=2
  value_2.bits[0] = 0b00000000000000000000000100011110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000100000000000000000;

  // -1.3 scale=1 - (-2.86) scale=2 = 1.56 scale=2
  flag_error = s21_sub(value_1, value_2, &result);

  // 156.00 scale = 2
  origin.bits[0] = 0b00000000000000000000000010011100;
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

// scale (разные)
START_TEST(sub_18) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -1.3 scale=1
  value_1.bits[0] = 0b00000000000000000000000000001101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000010000000000000000;

  // 2.86 scale=2
  value_2.bits[0] = 0b00000000000000000000000100011110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // -1.3 scale=1 - 2.86 scale=2 = -416.00 scale=2
  flag_error = s21_sub(value_1, value_2, &result);

  // -416.00 scale=2
  origin.bits[0] = 0b00000000000000000000000110100000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// scale (разные)
START_TEST(sub_19) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 6.4071 scale=4
  value_1.bits[0] = 0b00000000000000001111101001000111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000001000000000000000000;

  // 591.9 scale=1
  value_2.bits[0] = 0b00000000000000000001011100011111;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 6.4071 scale=4 - 591.9 scale=1 = -585.4929 scale=4
  flag_error = s21_sub(value_1, value_2, &result);

  // -585.4929 scale=4
  origin.bits[0] = 0b00000000010110010101011011010001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000001000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// scale (разные)
START_TEST(sub_20) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -9403 scale=0
  value_1.bits[0] = 0b00000000000000000010010010111011;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 202.098 scale=3
  value_2.bits[0] = 0b00000000000000110001010101110010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000110000000000000000;

  // -9403 scale=0 - 202.098 scale=3 = -9605.098 scale=3
  flag_error = s21_sub(value_1, value_2, &result);

  // -9605.098 scale=3
  origin.bits[0] = 0b00000000100100101000111111101010;
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

// scale (разные)
START_TEST(sub_21) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 2635.2 scale=1
  value_1.bits[0] = 0b00000000000000000110011011110000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000010000000000000000;

  // 283.094 scale=3
  value_2.bits[0] = 0b00000000000001000101000111010110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000110000000000000000;

  // 2635.2 scale=1 - 283.094 scale=3 = 2352.106 scale=3
  flag_error = s21_sub(value_1, value_2, &result);

  // 2352.106 scale=3
  origin.bits[0] = 0b00000000001000111110001111101010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа без scale, результат +
START_TEST(sub_22) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 857648735878374875989439 scale=0
  value_1.bits[0] = 0b10100111001000000000010110111111;
  value_1.bits[1] = 0b00111011001010111000111110100001;
  value_1.bits[2] = 0b00000000000000001011010110011101;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 648735878374875989439 scale=0
  value_2.bits[0] = 0b01100001100000000000010110111111;
  value_2.bits[1] = 0b00101011000001001101010000111011;
  value_2.bits[2] = 0b00000000000000000000000000100011;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 857648735878374875989439 scale=0 - 648735878374875989439 scale=0 =
  // 857000000000000000000000 scale=0
  flag_error = s21_sub(value_1, value_2, &result);

  // 857000000000000000000000 scale=0
  origin.bits[0] = 0b01000101101000000000000000000000;
  origin.bits[1] = 0b00010000001001101011101101100110;
  origin.bits[2] = 0b00000000000000001011010101111010;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа без scale, результат -
START_TEST(sub_23) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 648735878374875989439 scale=0
  value_1.bits[0] = 0b01100001100000000000010110111111;
  value_1.bits[1] = 0b00101011000001001101010000111011;
  value_1.bits[2] = 0b00000000000000000000000000100011;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 857648735878374875989439 scale=0
  value_2.bits[0] = 0b10100111001000000000010110111111;
  value_2.bits[1] = 0b00111011001010111000111110100001;
  value_2.bits[2] = 0b00000000000000001011010110011101;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 648735878374875989439 scale=0 - 857648735878374875989439 scale=0 =
  // -857000000000000000000000 scale=0
  flag_error = s21_sub(value_1, value_2, &result);

  // -857000000000000000000000 scale=0
  origin.bits[0] = 0b01000101101000000000000000000000;
  origin.bits[1] = 0b00010000001001101011101101100110;
  origin.bits[2] = 0b00000000000000001011010101111010;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа, одно с scale, другое без scale
START_TEST(sub_24) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -545454512454545.35265454545645 scale=14
  value_1.bits[0] = 0b10000010111000100101101011101101;
  value_1.bits[1] = 0b11111001111010000010010110101101;
  value_1.bits[2] = 0b10110000001111101111000010010100;
  value_1.bits[3] = 0b10000000000011100000000000000000;

  // 54564654 scale=0
  value_2.bits[0] = 0b00000011010000001001011100101110;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // -545454512454545.35265454545645 scale=14 - 54564654 scale=0 =
  // -545454567019199.35265454545645 scale=14
  flag_error = s21_sub(value_1, value_2, &result);

  // -545454567019199.35265454545645 scale=14
  origin.bits[0] = 0b10010100100110011101101011101101;
  origin.bits[1] = 0b11000101100100110110100101100010;
  origin.bits[2] = 0b10110000001111101111000110111100;
  origin.bits[3] = 0b10000000000011100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа с scale
START_TEST(sub_25) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -545454512454545.35265454545645 scale=14
  value_1.bits[0] = 0b10000010111000100101101011101101;
  value_1.bits[1] = 0b11111001111010000010010110101101;
  value_1.bits[2] = 0b10110000001111101111000010010100;
  value_1.bits[3] = 0b10000000000011100000000000000000;

  // -5.352654545456454545645464 scale=24
  value_2.bits[0] = 0b01001000000110110001111110011000;
  value_2.bits[1] = 0b11111011111111011000100101101101;
  value_2.bits[2] = 0b00000000000001000110110101110111;
  value_2.bits[3] = 0b10000000000110000000000000000000;

  // -545454512454545.35265454545645 scale=14 - 54564654 scale=0 =
  // -545454567019199.35265454545645 scale=14
  flag_error = s21_sub(value_1, value_2, &result);

  // -545454512454539.99999999999999 exp 14
  //  545454512454539.9999999999999955 округляется 5
  //  545454512454540.00000000000000
  origin.bits[0] = 0b01001111100110110000000000000000;
  origin.bits[1] = 0b11111001111001100011111011011011;
  origin.bits[2] = 0b10110000001111101111000010010100;
  origin.bits[3] = 0b10000000000011100000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// уменьшаемое, вычитаемое и разность нули
START_TEST(sub_26) {
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

  // 0 - 0 = 0
  flag_error = s21_sub(value_1, value_2, &result);

  //  0
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

// большие числа со scale
START_TEST(sub_27) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -9798956154578676.797564534156 scale=12
  value_1.bits[0] = 0b01010100010000000011110110001100;
  value_1.bits[1] = 0b10001011010100100000010101011001;
  value_1.bits[2] = 0b00011111101010011000000110101101;
  value_1.bits[3] = 0b10000000000011000000000000000000;

  // -2156878451.854764 scale=6
  value_2.bits[0] = 0b01100101111100100100110110101100;
  value_2.bits[1] = 0b00000000000001111010100110101011;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000001100000000000000000;

  // -9798956154578676.797564534156 scale=12 - -2156878451.854764 scale=6 =
  // -9798953997700224.942800534156 scale=12
  flag_error = s21_sub(value_1, value_2, &result);

  //  -9798953997700224.942800534156 scale=12
  origin.bits[0] = 0b11010010100100100111101010001100;
  origin.bits[1] = 0b10011110100111100111000100000100;
  origin.bits[2] = 0b00011111101010011000000100111000;
  origin.bits[3] = 0b10000000000011000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа со scale
START_TEST(sub_28) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 0.5456465465486476846545465485 scale=28
  value_1.bits[0] = 0b00001011000011110111000010001101;
  value_1.bits[1] = 0b10010110101100000101100101010001;
  value_1.bits[2] = 0b00010001101000010111101110000001;
  value_1.bits[3] = 0b00000000000111000000000000000000;

  // 0.68985125146545154 scale=17
  value_2.bits[0] = 0b00010111001001010100110000000010;
  value_2.bits[1] = 0b00000000111101010001010110011011;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000100010000000000000000;

  // 0.5456465465486476846545465485 scale=28 - 0.68985125146545154 scale=17 =
  // -0.1442047049168038553454534515 scale=28
  flag_error = s21_sub(value_1, value_2, &result);

  // -0.1442047049168038553454534515 scale=28
  origin.bits[0] = 0b01011010101111100101111101110011;
  origin.bits[1] = 0b00101101001111010011000001101000;
  origin.bits[2] = 0b00000100101010001101010101010111;
  origin.bits[3] = 0b10000000000111000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// уменьшение мантисы и банк. округление
START_TEST(sub_29) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 0.5456465465486476846545465485 scale=28
  value_1.bits[0] = 0b00001011000011110111000010001101;
  value_1.bits[1] = 0b10010110101100000101100101010001;
  value_1.bits[2] = 0b00010001101000010111101110000001;
  value_1.bits[3] = 0b00000000000111000000000000000000;

  // 11 scale=0
  value_2.bits[0] = 0b00000000000000000000000000001011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // -9798956154578676.797564534156 scale=12 - -2156878451.854764 scale=6 =
  // -9798953997700224.942800534156 scale=12
  flag_error = s21_sub(value_1, value_2, &result);

  // 10.4543534534513523153454534515 scale=28
  // округление 10.454353453451352315345453452 scale=27
  origin.bits[0] = 0b11011101010010110100000110001100;
  origin.bits[1] = 0b01001110111000111110000000010101;
  origin.bits[2] = 0b00100001110001111010001101110100;
  origin.bits[3] = 0b10000000000110110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// уменьшаемое и вычитаемое максимальные числа
START_TEST(sub_30) {
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

  // 79228162514264337593543950335 - 79228162514264337593543950335 = 0
  flag_error = s21_sub(value_1, value_2, &result);

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

// sub_31 - 37 все случаи банковского округления

START_TEST(sub_31) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.9 scale=1
  value_2.bits[0] = 0b00000000000000000000110100010101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950335 - 334.9 = 79228162514264337593543950000
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543950000.1 (1 < 5)
  // округление до 79228162514264337593543950000
  origin.bits[0] = 0b11111111111111111111111010110000;
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

START_TEST(sub_32) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.4 scale=1
  value_2.bits[0] = 0b00000000000000000000110100010000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950335 - 334.4 = 79228162514264337593543950001
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543950000.6 (6 > 5)
  // округление до 79228162514264337593543950001
  origin.bits[0] = 0b11111111111111111111111010110001;
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

START_TEST(sub_33) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.5 scale=1
  value_2.bits[0] = 0b00000000000000000000110100010001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950335 - 334.5 = 79228162514264337593543950000
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543950000.5 (5 - до четного)
  // округление до 7922816251426433759354395000 (четное / до четного)
  origin.bits[0] = 0b11111111111111111111111010110000;
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

START_TEST(sub_34) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 335.5 scale=1
  value_2.bits[0] = 0b00000000000000000000110100011011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950335 - 335.5 = 79228162514264337593543950000
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543949999.5 (5 - до четного)
  // округление до 79228162514264337593543950000 (нечетное / до четного)
  origin.bits[0] = 0b11111111111111111111111010110000;
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

START_TEST(sub_35) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.45 scale=2
  value_2.bits[0] = 0b00000000000000001000001010100101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 79228162514264337593543950335 - 334.45 = 79228162514264337593543950001
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543950000.55 (5 и дальше цифры 5)
  // округление до 79228162514264337593543950001
  origin.bits[0] = 0b11111111111111111111111010110001;
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

START_TEST(sub_36) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.49 scale=2
  value_2.bits[0] = 0b00000000000000001000001010101001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 79228162514264337593543950335 - 334.49 = 79228162514264337593543950001
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543950000.51 (5 и дальше цифры 1)
  // округление до 79228162514264337593543950001
  origin.bits[0] = 0b11111111111111111111111010110001;
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

START_TEST(sub_37) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.499 scale=3
  value_2.bits[0] = 0b00000000000001010001101010100011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000110000000000000000;

  // 79228162514264337593543950335 - 334.499 = 79228162514264337593543950001
  flag_error = s21_sub(value_1, value_2, &result);

  // 79228162514264337593543950000.501 (5 и дальше цифры 01)
  // округление до 79228162514264337593543950001
  origin.bits[0] = 0b11111111111111111111111010110001;
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

// вычитание, одинаковые scale
START_TEST(sub_38) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 7 scale=2
  value_1.bits[0] = 0b00000000000000000000000000000111;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000100000000000000000;

  // 5 scale=2
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 7 scale=2 - 5 scale=2 = 2 scale=2
  flag_error = s21_sub(value_1, value_2, &result);

  // 2 scale=2
  origin.bits[0] = 0b00000000000000000000000000000010;
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

Suite* suite_sub(void) {
  Suite* s = suite_create("suite_sub");
  TCase* tc = tcase_create("log_tc");

  tcase_add_test(tc, sub_01);
  tcase_add_test(tc, sub_02);
  tcase_add_test(tc, sub_03);
  tcase_add_test(tc, sub_04);
  tcase_add_test(tc, sub_05);
  tcase_add_test(tc, sub_06);
  tcase_add_test(tc, sub_07);
  tcase_add_test(tc, sub_08);
  tcase_add_test(tc, sub_09);
  tcase_add_test(tc, sub_10);
  tcase_add_test(tc, sub_11);
  tcase_add_test(tc, sub_12);
  tcase_add_test(tc, sub_13);
  tcase_add_test(tc, sub_14);
  tcase_add_test(tc, sub_15);
  tcase_add_test(tc, sub_16);
  tcase_add_test(tc, sub_17);
  tcase_add_test(tc, sub_18);
  tcase_add_test(tc, sub_19);
  tcase_add_test(tc, sub_20);
  tcase_add_test(tc, sub_21);
  tcase_add_test(tc, sub_22);
  tcase_add_test(tc, sub_23);
  tcase_add_test(tc, sub_24);
  tcase_add_test(tc, sub_25);
  tcase_add_test(tc, sub_26);
  tcase_add_test(tc, sub_27);
  tcase_add_test(tc, sub_28);
  tcase_add_test(tc, sub_29);
  tcase_add_test(tc, sub_30);
  tcase_add_test(tc, sub_31);
  tcase_add_test(tc, sub_32);
  tcase_add_test(tc, sub_33);
  tcase_add_test(tc, sub_34);
  tcase_add_test(tc, sub_35);
  tcase_add_test(tc, sub_36);
  tcase_add_test(tc, sub_37);
  tcase_add_test(tc, sub_38);

  suite_add_tcase(s, tc);
  return s;
}