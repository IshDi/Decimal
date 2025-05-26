#include "s21_tests.h"

// результат = 0
// второе слагаемое -
START_TEST(add_01) {
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

  // 5 + (-5) = 0
  flag_error = s21_add(value_1, value_2, &result);

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

// второе слагаемое = 0
START_TEST(add_02) {
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

  // 5 + 0 = 5
  flag_error = s21_add(value_1, value_2, &result);

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

// первое слагаемое = 0
START_TEST(add_03) {
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

  // 0 + 5 = 5
  flag_error = s21_add(value_1, value_2, &result);

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

// первое слагаемое -
// результат -
START_TEST(add_04) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -5
  value_1.bits[0] = 0b00000000000000000000000000000101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 1
  value_2.bits[0] = 0b00000000000000000000000000000001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // (-5) + 1 = (-4)
  flag_error = s21_add(value_1, value_2, &result);

  // -4
  origin.bits[0] = 0b00000000000000000000000000000100;
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

// первое и второе слагаемые -
START_TEST(add_05) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -5
  value_1.bits[0] = 0b00000000000000000000000000000101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // -5
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // (-5) + (-5) = (-10)
  flag_error = s21_add(value_1, value_2, &result);

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

// 0 + 0 = 0
START_TEST(add_06) {
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

  // 0 + 0 = 0
  flag_error = s21_add(value_1, value_2, &result);

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

// 1 - число слишком велико или равно бесконечности
START_TEST(add_07) {
  s21_decimal value_1, value_2;
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

  // 79228162514264337593543950335 + 79228162514264337593543950335) = error = 1
  flag_error = s21_add(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(1, flag_error);
}
END_TEST

// 2 - число слишком мало или равно отрицательной бесконечности
START_TEST(add_08) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // -79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111111;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // -79228162514264337593543950335 - 79228162514264337593543950335 = error = 2
  flag_error = s21_add(value_1, value_2, &result);

  // error = 2
  ck_assert_int_eq(2, flag_error);
}
END_TEST

// 2 - число слишком мало или равно отрицательной бесконечности
START_TEST(add_09) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // -2
  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // -79228162514264337593543950335 + (-2) = -79228162514264337593543950337 =
  // error = 2
  flag_error = s21_add(value_1, value_2, &result);

  // error = 2
  ck_assert_int_eq(2, flag_error);
}
END_TEST

// 1 - число слишком велико или равно бесконечности
START_TEST(add_10) {
  s21_decimal value_1, value_2;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 2
  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 79228162514264337593543950335 + 2 = 79228162514264337593543950337 = error =
  // 1
  flag_error = s21_add(value_1, value_2, &result);

  // error = 1
  ck_assert_int_eq(1, flag_error);
}
END_TEST

// большие числа + +
START_TEST(add_11) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 123456789123456789
  value_1.bits[0] = 0b10101100110100000101111100010101;
  value_1.bits[1] = 0b00000001101101101001101101001011;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 12345678912345
  value_2.bits[0] = 0b01110011110011100101101101011001;
  value_2.bits[1] = 0b00000000000000000000101100111010;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 123456789123456789 + 12345678912345 = 123469134802369134
  flag_error = s21_add(value_1, value_2, &result);

  // 123469134802369134
  origin.bits[0] = 0b00100000100111101011101001101110;
  origin.bits[1] = 0b00000001101101101010011010000110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа - -
START_TEST(add_12) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -123456789123456789
  value_1.bits[0] = 0b10101100110100000101111100010101;
  value_1.bits[1] = 0b00000001101101101001101101001011;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // -12345678912345
  value_2.bits[0] = 0b01110011110011100101101101011001;
  value_2.bits[1] = 0b00000000000000000000101100111010;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // -123456789123456789 + (-12345678912345) = -123469134802369134
  flag_error = s21_add(value_1, value_2, &result);

  // -123469134802369134
  origin.bits[0] = 0b00100000100111101011101001101110;
  origin.bits[1] = 0b00000001101101101010011010000110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа + -
// результат +
START_TEST(add_13) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 123456789123456789
  value_1.bits[0] = 0b10101100110100000101111100010101;
  value_1.bits[1] = 0b00000001101101101001101101001011;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -12345678912345
  value_2.bits[0] = 0b01110011110011100101101101011001;
  value_2.bits[1] = 0b00000000000000000000101100111010;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 123456789123456789 + (-12345678912345) = 123444443444544444
  flag_error = s21_add(value_1, value_2, &result);

  // 123444443444544444
  origin.bits[0] = 0b00111001000000100000001110111100;
  origin.bits[1] = 0b00000001101101101001000000010001;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа - +
// результат -
START_TEST(add_14) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -123456789123456789
  value_1.bits[0] = 0b10101100110100000101111100010101;
  value_1.bits[1] = 0b00000001101101101001101101001011;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  // 12345678912345
  value_2.bits[0] = 0b01110011110011100101101101011001;
  value_2.bits[1] = 0b00000000000000000000101100111010;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // -123456789123456789 + 12345678912345 = -123444443444544444
  flag_error = s21_add(value_1, value_2, &result);

  // -123444443444544444
  origin.bits[0] = 0b00111001000000100000001110111100;
  origin.bits[1] = 0b00000001101101101001000000010001;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// scale одинаковые, числа + +
START_TEST(add_15) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 0.10 scale=2
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000100000000000000000;

  // 0.20 scale=2
  value_2.bits[0] = 0b00000000000000000000000000010100;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 0.10 scale=2 + 0.20 scale=2 = 0.30 scale=2
  flag_error = s21_add(value_1, value_2, &result);

  // 0.30 scale=2
  origin.bits[0] = 0b00000000000000000000000000011110;
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

// scale одинаковые, числа - -
START_TEST(add_16) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -0.10 scale=2
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000100000000000000000;

  // -0.20 scale=2
  value_2.bits[0] = 0b00000000000000000000000000010100;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000100000000000000000;

  // -0.10 scale=2 + (-0.20) scale=2 = -0.30 scale=2
  flag_error = s21_add(value_1, value_2, &result);

  // -0.30 scale=2
  origin.bits[0] = 0b00000000000000000000000000011110;
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

// scale одинаковые, числа + -
START_TEST(add_17) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // -0.10 scale=2
  value_1.bits[0] = 0b00000000000000000000000000001010;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b10000000000000100000000000000000;

  // 0.20 scale=2
  value_2.bits[0] = 0b00000000000000000000000000010100;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // -0.10 scale=2 + 0.20 scale=2 = 0.10 scale=2
  flag_error = s21_add(value_1, value_2, &result);

  // 0.10 scale=2
  origin.bits[0] = 0b00000000000000000000000000001010;
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

// scale разные, числа + +
START_TEST(add_18) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 1000.0 scale=1
  value_1.bits[0] = 0b00000000000000000010011100010000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000100000000000000000;

  // 5.0000 scale=4
  value_2.bits[0] = 0b00000000000000001100001101010000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 1000.0 scale=1 + 5.0000 scale=4 = 6.0000 scale=4
  flag_error = s21_add(value_1, value_2, &result);

  // 6.0000 scale=4
  origin.bits[0] = 0b00000000000000001110101001100000;
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

// scale разные, числа + -
START_TEST(add_19) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 1000.0 scale=1
  value_1.bits[0] = 0b00000000000000000010011100010000;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000100000000000000000;

  // -5.0000 scale=4
  value_2.bits[0] = 0b00000000000000001100001101010000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000000100000000000000000;

  // 1000.0 scale=1 + (-5.0000) scale=4 = -4.0000 scale=4
  flag_error = s21_add(value_1, value_2, &result);

  // -4.0000 scale=4
  origin.bits[0] = 0b00000000000000001001110001000000;
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

// большие числа
// понижение scale результата (чтобы уместилось в мантису)
// округление
START_TEST(add_20) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 0.05 scale=2
  value_2.bits[0] = 0b00000000000000000000000000000101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 79228162514264337593543950335 + 0.05 scale=2 =
  // 79228162514264337593543950335
  flag_error = s21_add(value_1, value_2, &result);

  // 79228162514264337593543950335.05
  // округление до целого 79228162514264337593543950335
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

// большие числа, разный scale
START_TEST(add_21) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 1234567890.0123456789 scale=10
  value_1.bits[0] = 0b10101000111001001101010100010101;
  value_1.bits[1] = 0b10101011010101001010100110001100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010100000000000000000;

  // 1.0234567890123456789 scale=19
  value_2.bits[0] = 0b01100000011011011000000100010101;
  value_2.bits[1] = 0b10001110000010000111110101000101;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000100110000000000000000;

  // 1234567890.0123456789 scale=10 + 1.0234567890123456789 scale=19 =
  // 1234567891.0358024679123456789 scale=19
  flag_error = s21_add(value_1, value_2, &result);

  // 1234567891.0358024679123456789 scale=19
  origin.bits[0] = 0b11110110001100100001001100010101;
  origin.bits[1] = 0b11000101010110111101000101001101;
  origin.bits[2] = 0b00100111111001000001101100110010;
  origin.bits[3] = 0b00000000000100110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// большие числа, разный scale
// разные знаки + -
START_TEST(add_22) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 1234567890.0123456789 scale=10
  value_1.bits[0] = 0b10101000111001001101010100010101;
  value_1.bits[1] = 0b10101011010101001010100110001100;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000010100000000000000000;

  // -1.0234567890123456789 scale=19
  value_2.bits[0] = 0b01100000011011011000000100010101;
  value_2.bits[1] = 0b10001110000010000111110101000101;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b10000000000100110000000000000000;

  // 1234567890.0123456789 scale=10 + (-1.0234567890123456789) scale=19 =
  // 1234567888.9888888898876543211 scale=19
  flag_error = s21_add(value_1, value_2, &result);

  // 1234567888.9888888898876543211 scale=19
  origin.bits[0] = 0b00110101010101110001000011101011;
  origin.bits[1] = 0b10101001010010101101011011000011;
  origin.bits[2] = 0b00100111111001000001101100110001;
  origin.bits[3] = 0b00000000000100110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

// слагаемые максимальные числа, разные знаки + -
START_TEST(add_23) {
  s21_decimal value_1, value_2, origin;
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

  // 79228162514264337593543950335 + (-79228162514264337593543950335) = 0
  flag_error = s21_add(value_1, value_2, &result);

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

// слагаемые максимальные числа, разные знаки + -
// остаток 1
START_TEST(add_24) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950335
  value_1.bits[0] = 0b11111111111111111111111111111111;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // -79228162514264337593543950335
  value_2.bits[0] = 0b11111111111111111111111111111110;
  value_2.bits[1] = 0b11111111111111111111111111111111;
  value_2.bits[2] = 0b11111111111111111111111111111111;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  // 79228162514264337593543950335 + (-79228162514264337593543950334) = 1
  flag_error = s21_add(value_1, value_2, &result);

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

// add_25 - 29 все случаи банковского округления

START_TEST(add_25) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950000
  value_1.bits[0] = 0b11111111111111111111111010110000;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.9 scale=1
  value_2.bits[0] = 0b00000000000000000000110100010101;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950000 + 334.9 = 79228162514264337593543950335
  flag_error = s21_add(value_1, value_2, &result);

  // 79228162514264337593543950334.9 (9 > 5)
  // округление до 79228162514264337593543950335
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

START_TEST(add_26) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950000
  value_1.bits[0] = 0b11111111111111111111111010110000;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.4 scale=1
  value_2.bits[0] = 0b00000000000000000000110100010000;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950000 + 334.4 = 79228162514264337593543950334
  flag_error = s21_add(value_1, value_2, &result);

  // 79228162514264337593543950334.4 (4 < 5)
  // округление до 79228162514264337593543950334
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

START_TEST(add_27) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950000
  value_1.bits[0] = 0b11111111111111111111111010110000;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.5 scale=1
  value_2.bits[0] = 0b00000000000000000000110100010001;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950000 + 334.5 = 79228162514264337593543950334
  flag_error = s21_add(value_1, value_2, &result);

  // 79228162514264337593543950334.5 (5, четное до четного)
  // округление до 79228162514264337593543950334
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

START_TEST(add_28) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950000
  value_1.bits[0] = 0b11111111111111111111111010110000;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 333.5 scale=1
  value_2.bits[0] = 0b00000000000000000000110100000111;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  // 79228162514264337593543950000 + 333.5 = 79228162514264337593543950334
  flag_error = s21_add(value_1, value_2, &result);

  // 79228162514264337593543950333.9 (5, нечетное до четного)
  // округление до 79228162514264337593543950334
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

START_TEST(add_29) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 79228162514264337593543950000
  value_1.bits[0] = 0b11111111111111111111111010110000;
  value_1.bits[1] = 0b11111111111111111111111111111111;
  value_1.bits[2] = 0b11111111111111111111111111111111;
  value_1.bits[3] = 0b00000000000000000000000000000000;

  // 334.51 scale=2
  value_2.bits[0] = 0b00000000000000001000001010101011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000100000000000000000;

  // 79228162514264337593543950000 + 334.51 = 79228162514264337593543950335
  flag_error = s21_add(value_1, value_2, &result);

  // 79228162514264337593543950334.51 (5, после 5 цифра 1)
  // округление до 79228162514264337593543950335
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

// понижение скейла с 28 до 27
START_TEST(add_30) {
  s21_decimal value_1, value_2, origin;
  s21_decimal result = {{0, 0, 0, 0}};
  int flag_error = 0;

  // 0.0000000000000000000000000001 scale=28
  value_1.bits[0] = 0b00000000000000000000000000000001;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000111000000000000000000;

  // 11 scale=0
  value_2.bits[0] = 0b00000000000000000000000000001011;
  value_2.bits[1] = 0b00000000000000000000000000000000;
  value_2.bits[2] = 0b00000000000000000000000000000000;
  value_2.bits[3] = 0b00000000000000000000000000000000;

  // 0.0000000000000000000000000001 scale=28 + 11
  // = 11.000000000000000000000000000 scale=27
  flag_error = s21_add(value_1, value_2, &result);

  // 11.000000000000000000000000000 scale=27
  // банк. округление
  origin.bits[0] = 0b11111000000000000000000000000000;
  origin.bits[1] = 0b11011101111101011000001010011101;
  origin.bits[2] = 0b00100011100010101111110010011010;
  origin.bits[3] = 0b00000000000110110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

Suite* suite_add(void) {
  Suite* s = suite_create("suite_add");
  TCase* tc = tcase_create("case_add");

  tcase_add_test(tc, add_01);
  tcase_add_test(tc, add_02);
  tcase_add_test(tc, add_03);
  tcase_add_test(tc, add_04);
  tcase_add_test(tc, add_05);
  tcase_add_test(tc, add_06);
  tcase_add_test(tc, add_07);
  tcase_add_test(tc, add_08);
  tcase_add_test(tc, add_09);
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_11);
  tcase_add_test(tc, add_12);
  tcase_add_test(tc, add_13);
  tcase_add_test(tc, add_14);
  tcase_add_test(tc, add_15);
  tcase_add_test(tc, add_16);
  tcase_add_test(tc, add_17);
  tcase_add_test(tc, add_18);
  tcase_add_test(tc, add_19);
  tcase_add_test(tc, add_20);
  tcase_add_test(tc, add_21);
  tcase_add_test(tc, add_22);
  tcase_add_test(tc, add_23);
  tcase_add_test(tc, add_24);
  tcase_add_test(tc, add_25);
  tcase_add_test(tc, add_26);
  tcase_add_test(tc, add_27);
  tcase_add_test(tc, add_28);
  tcase_add_test(tc, add_29);
  tcase_add_test(tc, add_30);

  suite_add_tcase(s, tc);
  return s;
}
