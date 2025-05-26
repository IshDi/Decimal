#include "s21_tests.h"

START_TEST(round_01) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 5
  value.bits[0] = 0b00000000000000000000000000000101;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000000000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_02) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -5
  value.bits[0] = 0b00000000000000000000000000000101;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000000000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_03) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 0
  value.bits[0] = 0b00000000000000000000000000000000;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000000000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_04) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 7.9228162514264337593543950335 scale=28
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b00000000000111000000000000000000;

  flag_error = s21_round(value, &result);

  // 8
  origin.bits[0] = 0b00000000000000000000000000001000;
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

START_TEST(round_05) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -7.9228162514264337593543950335 scale=28
  value.bits[0] = 0b11111111111111111111111111111111;
  value.bits[1] = 0b11111111111111111111111111111111;
  value.bits[2] = 0b11111111111111111111111111111111;
  value.bits[3] = 0b10000000000111000000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_06) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 0.5456465465486476846545465485 scale=28
  value.bits[0] = 0b00001011000011110111000010001101;
  value.bits[1] = 0b10010110101100000101100101010001;
  value.bits[2] = 0b00010001101000010111101110000001;
  value.bits[3] = 0b00000000000111000000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_07) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 0.1442047049168038553454534515 scale=28
  value.bits[0] = 0b01011010101111100101111101110011;
  value.bits[1] = 0b00101101001111010011000001101000;
  value.bits[2] = 0b00000100101010001101010101010111;
  value.bits[3] = 0b00000000000111000000000000000000;

  //   // 0.14 scale=2
  //   value.bits[0] = 0b00000000000000000000000000001110;
  //   value.bits[1] = 0b00000000000000000000000000000000;
  //   value.bits[2] = 0b00000000000000000000000000000000;
  //   value.bits[3] = 0b00000000000000100000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_08) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 1.0
  value.bits[0] = 0b00000000000000000000000000001010;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000010000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_09) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -1.0
  value.bits[0] = 0b00000000000000000000000000001010;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b10000000000000010000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_10) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -0.5456465465486476846545465485 scale=28
  value.bits[0] = 0b00001011000011110111000010001101;
  value.bits[1] = 0b10010110101100000101100101010001;
  value.bits[2] = 0b00010001101000010111101110000001;
  value.bits[3] = 0b10000000000111000000000000000000;

  flag_error = s21_round(value, &result);

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

START_TEST(round_11) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // -0.1442047049168038553454534515 scale=28
  value.bits[0] = 0b01011010101111100101111101110011;
  value.bits[1] = 0b00101101001111010011000001101000;
  value.bits[2] = 0b00000100101010001101010101010111;
  value.bits[3] = 0b10000000000111000000000000000000;

  //   // 0.14 scale=2
  //   value.bits[0] = 0b00000000000000000000000000001110;
  //   value.bits[1] = 0b00000000000000000000000000000000;
  //   value.bits[2] = 0b00000000000000000000000000000000;
  //   value.bits[3] = 0b00000000000000100000000000000000;

  flag_error = s21_round(value, &result);

  // 0
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

START_TEST(round_12) {
  s21_decimal value, origin;
  s21_decimal result = {{0}};
  int flag_error = 0;

  // 1.2
  value.bits[0] = 0b00000000000000000000000000001100;
  value.bits[1] = 0b00000000000000000000000000000000;
  value.bits[2] = 0b00000000000000000000000000000000;
  value.bits[3] = 0b00000000000000010000000000000000;

  flag_error = s21_round(value, &result);

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

Suite *suite_round(void) {
  Suite *s = suite_create("suite_round");
  TCase *tc = tcase_create("case_round");

  tcase_add_test(tc, round_01);
  tcase_add_test(tc, round_02);
  tcase_add_test(tc, round_03);
  tcase_add_test(tc, round_04);
  tcase_add_test(tc, round_05);
  tcase_add_test(tc, round_06);
  tcase_add_test(tc, round_07);
  tcase_add_test(tc, round_08);
  tcase_add_test(tc, round_09);
  tcase_add_test(tc, round_10);
  tcase_add_test(tc, round_11);
  tcase_add_test(tc, round_12);

  suite_add_tcase(s, tc);
  return s;
}