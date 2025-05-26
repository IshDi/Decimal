#include "s21_tests.h"

START_TEST(zero_value) {
  s21_decimal dec = {0};
  int result;

  result = s21_from_int_to_decimal(0, &dec);
  ck_assert_uint_eq(dec.bits[0], 0);
  ck_assert_uint_eq(dec.bits[1], 0);
  ck_assert_uint_eq(dec.bits[2], 0);
  ck_assert_uint_eq(dec.bits[3], 0);
  ck_assert_uint_eq(result, 0);

  result = s21_from_int_to_decimal(-0, &dec);
  ck_assert_uint_eq(dec.bits[0], 0);
  ck_assert_uint_eq(dec.bits[1], 0);
  ck_assert_uint_eq(dec.bits[2], 0);
  ck_assert_uint_eq(dec.bits[3], 0);
  ck_assert_uint_eq(result, 0);
}
END_TEST

START_TEST(max_min_int_value) {
  s21_decimal dec = {0};
  int result;

  result = s21_from_int_to_decimal(INT_MAX, &dec);
  ck_assert_uint_eq(dec.bits[0], INT_MAX);
  ck_assert_uint_eq(dec.bits[1], 0);
  ck_assert_uint_eq(dec.bits[2], 0);
  ck_assert_uint_eq(dec.bits[3], 0);
  ck_assert_uint_eq(result, 0);

  result = s21_from_int_to_decimal(INT_MIN, &dec);
  ck_assert_uint_eq(dec.bits[0], 2147483648);
  ck_assert_uint_eq(dec.bits[1], 0);
  ck_assert_uint_eq(dec.bits[2], 0);
  ck_assert_uint_eq(dec.bits[3], 2147483648);
  ck_assert_uint_eq(result, 0);
}
END_TEST

START_TEST(one_pos_value) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int result;

  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b00000000000000000000000000000000;

  result = s21_from_int_to_decimal(1, &dec_2);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

START_TEST(one_neg_value) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int result;

  dec_1.bits[0] = 0b00000000000000000000000000000001;
  dec_1.bits[1] = 0b00000000000000000000000000000000;
  dec_1.bits[2] = 0b00000000000000000000000000000000;
  dec_1.bits[3] = 0b10000000000000000000000000000000;

  result = s21_from_int_to_decimal(-1, &dec_2);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

START_TEST(not_empty_dec) {
  s21_decimal dec = {0};
  int number = 499559;
  int result;

  dec.bits[0] = 0b00010001000010000010000010000001;
  dec.bits[1] = 0b01000100001110000001000000010000;
  dec.bits[2] = 0b00001000100100101000010001000100;
  dec.bits[3] = 0b10000000000000000000000000000000;

  result = s21_from_int_to_decimal(number, &dec);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dec.bits[0], number);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(null_pointer) {
  int result = s21_from_int_to_decimal(123456, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(random_values) {
  s21_decimal dec = {0};
  int result;
  const int values[12] = {-rand(), rand(), -rand(), rand(), -rand(), rand()};
  int i = _i;

  result = s21_from_int_to_decimal(values[i], &dec);
  ck_assert_uint_eq(dec.bits[0], abs(values[i]));
  ck_assert_uint_eq(dec.bits[1], 0);
  ck_assert_uint_eq(dec.bits[2], 0);
  ck_assert_uint_eq(dec.bits[3], values[i] > 0 ? 0 : 2147483648);
  ck_assert_uint_eq(result, 0);
}
END_TEST

Suite *suite_from_int_to_decimal(void) {
  Suite *suite = suite_create("suite_from_int_to_decimal");
  TCase *tc = tcase_create("case_from_int_to_decimal");

  tcase_add_test(tc, zero_value);
  tcase_add_test(tc, max_min_int_value);
  tcase_add_test(tc, one_pos_value);
  tcase_add_test(tc, one_neg_value);
  tcase_add_test(tc, not_empty_dec);
  tcase_add_test(tc, null_pointer);
  tcase_add_loop_test(tc, random_values, 0, 6);

  suite_add_tcase(suite, tc);
  return suite;
}
