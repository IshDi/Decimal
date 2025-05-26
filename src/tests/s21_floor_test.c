#include "s21_tests.h"

START_TEST(floor_01) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 5
  value.bits[0] = 0b00000000000000000000000000000101;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000000000000000000000;

  flag_error = s21_floor(value, &result);

  // 5 целое число, не округляет
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

START_TEST(floor_02) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -5
  value.bits[0] = 0b00000000000000000000000000000101;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000000000000000000000;

  flag_error = s21_floor(value, &result);

  // -5 целое число, не округляет
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

START_TEST(floor_03) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 0
  value.bits[0] = 0b00000000000000000000000000000000;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000000000000000000000;

  flag_error = s21_floor(value, &result);

  // 0 целое число, не округляет
  origin.bits[0] = 0b00000000000000000000000000000000;
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

START_TEST(floor_04) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 7.9228162514264337593543950335 scale=28
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b00000000000111000000000000000000;

  flag_error = s21_floor(value, &result);

  // 7
  origin.bits[0] = 0b00000000000000000000000000000111;
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

START_TEST(floor_05) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -7.9228162514264337593543950335 scale=28
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b10000000000111000000000000000000;

  flag_error = s21_floor(value, &result);

  // -8
  origin.bits[0] = 0b00000000000000000000000000001000;
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

START_TEST(floor_06) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -1.1
  value.bits[0] = 0b00000000000000000000000000001011;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000010000000000000000;

  flag_error = s21_floor(value, &result);

  // -2 целое число
  origin.bits[0] = 0b00000000000000000000000000000010;
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

START_TEST(floor_07) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 1.1
  value.bits[0] = 0b00000000000000000000000000001011;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000010000000000000000;

  flag_error = s21_floor(value, &result);

  // 1 целое число
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

START_TEST(floor_08) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 1.0
  value.bits[0] = 0b00000000000000000000000000001010;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000010000000000000000;

  flag_error = s21_floor(value, &result);

  // 1 целое число
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

START_TEST(floor_09) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -1.0
  value.bits[0] = 0b00000000000000000000000000001010;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000010000000000000000;

  flag_error = s21_floor(value, &result);

  // -1 целое число
  origin.bits[0] = 0b00000000000000000000000000000001;
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

START_TEST(floor_10) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 0.5456465465486476846545465485 scale=28
  value.bits[0] = 0b00001011000011110111000010001101;
  value.bits[1] = 0b10010110101100000101100101010001;
  value.bits[2] = 0b00010001101000010111101110000001;
  value.bits[3] = 0b00000000000111000000000000000000;

  flag_error = s21_floor(value, &result);

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

START_TEST(floor_11) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -0.5456465465486476846545465485 scale=28
  value.bits[0] = 0b00001011000011110111000010001101;
  value.bits[1] = 0b10010110101100000101100101010001;
  value.bits[2] = 0b00010001101000010111101110000001;
  value.bits[3] = 0b10000000000111000000000000000000;

  flag_error = s21_floor(value, &result);

  // -1
  origin.bits[0] = 0b00000000000000000000000000000001;
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

START_TEST(floor_12) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -0.12
  value.bits[0] = 0b00000000000000000000000000001100;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000100000000000000000;

  flag_error = s21_floor(value, &result);

  // -1
  origin.bits[0] = 0b00000000000000000000000000000001;
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

START_TEST(floor_13) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 0.12
  value.bits[0] = 0b00000000000000000000000000001100;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000100000000000000000;

  flag_error = s21_floor(value, &result);

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

Suite *suite_floor(void) {
  Suite *s = suite_create("suite_floor");
  TCase *tc = tcase_create("case_floor");

  tcase_add_test(tc, floor_01);
  tcase_add_test(tc, floor_02);
  tcase_add_test(tc, floor_03);
  tcase_add_test(tc, floor_04);
  tcase_add_test(tc, floor_05);
  tcase_add_test(tc, floor_06);
  tcase_add_test(tc, floor_07);
  tcase_add_test(tc, floor_08);
  tcase_add_test(tc, floor_09);
  tcase_add_test(tc, floor_10);
  tcase_add_test(tc, floor_11);
  tcase_add_test(tc, floor_12);
  tcase_add_test(tc, floor_13);

  suite_add_tcase(s, tc);
  return s;
}