#include "s21_tests.h"

START_TEST(negate_1) {
  s21_decimal value, origin, result;
  int flag_error = 0;

  // 5
  value.bits[0] = 0b00000000000000000000000000000101;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000000000000000000000;

  flag_error = s21_negate(value, &result);

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

START_TEST(negate_2) {
  s21_decimal value, origin, result;
  int flag_error = 0;

  // -5
  value.bits[0] = 0b00000000000000000000000000000101;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000000000000000000000;

  flag_error = s21_negate(value, &result);

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

START_TEST(negate_3) {
  s21_decimal value, origin, result;
  int flag_error = 0;

  // 79228162514264337593543950335
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b00000000000000000000000000000000;

  flag_error = s21_negate(value, &result);

  // -79228162514264337593543950335
  origin.bits[0] = 0b11111111111111111111111111111111;
  origin.bits[1] = 0b11111111111111111111111111111111;
  origin.bits[2] = 0b11111111111111111111111111111111;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

START_TEST(negate_4) {
  s21_decimal value, origin, result;
  int flag_error = 0;

  // -79228162514264337593543950335
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b10000000000000000000000000000000;

  flag_error = s21_negate(value, &result);

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

START_TEST(negate_5) {
  s21_decimal value, origin, result;
  int flag_error = 0;

  // 1234567891.0358024679123456789 scale=19
  value.bits[0] = 0b11110110001100100001001100010101;
  value.bits[1] = 0b11000101010110111101000101001101;
  value.bits[2] = 0b00100111111001000001101100110010;
  value.bits[3] = 0b00000000000100110000000000000000;

  flag_error = s21_negate(value, &result);

  // -1234567891.0358024679123456789 scale=19
  origin.bits[0] = 0b11110110001100100001001100010101;
  origin.bits[1] = 0b11000101010110111101000101001101;
  origin.bits[2] = 0b00100111111001000001101100110010;
  origin.bits[3] = 0b10000000000100110000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
  ck_assert_int_eq(0, flag_error);
}
END_TEST

START_TEST(negate_6) {
  s21_decimal value, origin, result;
  int flag_error = 0;

  // -1234567891.0358024679123456789 scale=19
  value.bits[0] = 0b11110110001100100001001100010101;
  value.bits[1] = 0b11000101010110111101000101001101;
  value.bits[2] = 0b00100111111001000001101100110010;
  value.bits[3] = 0b10000000000100110000000000000000;

  flag_error = s21_negate(value, &result);

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

Suite *suite_negate(void) {
  Suite *s = suite_create("suite_negate");
  TCase *tc = tcase_create("negate_tc");

  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);
  tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);

  suite_add_tcase(s, tc);
  return s;
}