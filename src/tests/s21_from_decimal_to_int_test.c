#include "s21_tests.h"

START_TEST(dst_null) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_from_decimal_to_int(decimal, NULL);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_1) {
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_2) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_3) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_4) {
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(exp_over_limit) {
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(zero_value) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int result;
  int dst = 0, expected = 0;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(max_int_src) {
  s21_decimal dec = {{INT_MAX, 0, 0, 0}};
  int result;
  int dst = 0, expected = INT_MAX;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(min_int_src) {
  s21_decimal dec = {{2147483648, 0, 0, 2147483648}};
  int result;
  int dst = 0, expected = INT_MIN;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(overflow_dst_0) {
  s21_decimal dec = {{UINT_MAX, 0, 0, 0}};
  int result;
  int dst = 0, expected = 0;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, ERROR);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(overflow_dst_1) {
  s21_decimal dec = {{UINT_MAX, 0, 0, 0x80000000}};
  int result;
  int dst = 0, expected = 0;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, ERROR);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(overflow_dst_2) {
  // 792281625142.64337593543950335
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
  int result;
  int dst = 0, expected = 0;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, ERROR);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(overflow_dst_3) {
  // -792281625142.64337593543950335
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
  int result;
  int dst = 0, expected = 0;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, ERROR);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(overflow_dst_4) {
  // 79228162514264337593543950334
  s21_decimal dec = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result;
  int dst = 0, expected = 0;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, ERROR);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(overflow_dst_5) {
  // -79228162514264337593543950334
  s21_decimal dec = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int result;
  int dst = 0, expected = 0;

  result = s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(result, ERROR);
  ck_assert_int_eq(dst, expected);
}
END_TEST

START_TEST(pos_with_exp) {
  // 214748364.8
  s21_decimal dec = {{0x80000000, 0x0, 0x0, 0x10000}};
  int dst = 0;
  int expected = 214748364;
  int result_conv = s21_from_decimal_to_int(dec, &dst);

  ck_assert_uint_eq(result_conv, OK);
  ck_assert_uint_eq(dst, expected);
}

START_TEST(neg_with_exp) {
  // -214748364.8
  s21_decimal dec = {{0x80000000, 0x0, 0x0, 0x80010000}};
  int dst = 0;
  int expected = -214748364;
  int result_conv = s21_from_decimal_to_int(dec, &dst);

  ck_assert_uint_eq(result_conv, OK);
  ck_assert_uint_eq(dst, expected);
}

START_TEST(pos_big_exp) {
  // 1.56064767562212695305426944
  s21_decimal dec = {{0x811800, 0x811800, 0x811800, 0x1A0000}};
  int dst = 0;
  int expected = 1;
  int result_conv = s21_from_decimal_to_int(dec, &dst);
  ck_assert_uint_eq(result_conv, OK);
  ck_assert_uint_eq(dst, expected);
}

START_TEST(neg_big_exp) {
  // -1.56064767562212695305426944
  s21_decimal dec = {{0x811800, 0x811800, 0x811800, 0x801A0000}};
  int dst = 0;
  int expected = -1;
  int result_conv = s21_from_decimal_to_int(dec, &dst);
  ck_assert_uint_eq(result_conv, OK);
  ck_assert_uint_eq(dst, expected);
}

START_TEST(dec_to_int_1) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
  int check = 79228;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_2) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
  int check = -79228;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_3) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1A0000}};
  int check = 792;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_4) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801A0000}};
  int check = -792;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_5) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1B0000}};
  int check = 79;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_6) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801B0000}};
  int check = -79;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_7) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int check = 7;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_8) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int check = -7;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_9) {
  s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x140000}};
  int check = 528187749;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_10) {
  s21_decimal decimal = {{0x0, 0x0, 0xAAAAAAAA, 0x80140000}};
  int check = -528187749;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_11) {
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  int check = 1;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_12) {
  s21_decimal decimal = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
  int check = -1;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_13) {
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0xB0000}};
  int check = 122978293;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_14) {
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0x0, 0x800B0000}};
  int check = -122978293;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_15) {
  s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0xA0000}};
  int check = 1;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_16) {
  s21_decimal decimal = {{0x540BE400, 0x2, 0x0, 0x800A0000}};
  int check = -1;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_17) {
  s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0xA0000}};
  int check = 0;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_18) {
  s21_decimal decimal = {{0x540BE3FF, 0x2, 0x0, 0x800A0000}};
  int check = 0;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_19) {
  s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x1C0000}};
  int check = 0;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_20) {
  s21_decimal decimal = {{0x7FFFFFFE, 0x0, 0x0, 0x801C0000}};
  int check = 0;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_21) {
  s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x20000}};
  int check = 2147483647;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_22) {
  s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x80020000}};
  int check = -2147483647;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_23) {
  s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x20000}};
  int check = 2147483647;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_24) {
  s21_decimal decimal = {{0xFFFFFFFF, 0x31, 0x0, 0x80020000}};
  int check = -2147483647;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_25) {
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
  int check = 21474836;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_26) {
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
  int check = -21474836;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_27) {
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x90000}};
  int check = 2;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_28) {
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80090000}};
  int check = -2;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_29) {
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x1C0000}};
  int check = 0;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_30) {
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x801C0000}};
  int check = 0;
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, OK);
  ck_assert_int_eq(dst, check);
}

START_TEST(dec_to_int_fail_1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_3) {
  // 6148914691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x0}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_4) {
  // -6148914691236517205
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_5) {
  // -9999999999.9999999999
  s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x800A0000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_6) {
  // 18446744078004518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x0}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_7) {
  // -18446744078004518913
  s21_decimal decimal = {{0x1, 0x1, 0x1, 0x80000000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_8) {
  // 4294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x0}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_9) {
  // -4294967296
  s21_decimal decimal = {{0x0, 0x1, 0x0, 0x80000000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_10) {
  // 9999999999.9999999999
  s21_decimal decimal = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0xA0000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_11) {
  // 39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_12) {
  // -39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_13) {
  // 12345678901234.12345678901234
  s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0xE0000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(dec_to_int_fail_14) {
  // -12345678901234.12345678901234
  s21_decimal decimal = {{0xF91EAFF2, 0x6D795225, 0x3FD35EB, 0x800E0000}};
  int dst = 0;
  int result_conv = s21_from_decimal_to_int(decimal, &dst);
  ck_assert_int_eq(result_conv, ERROR);
}

START_TEST(random_values) {
  s21_decimal dec = {0};
  int dst = 0;
  int num = rand();
  dec.bits[0] = num;
  if (num < 0) {
    dec.bits[3] = 2147483648;
  }

  s21_from_decimal_to_int(dec, &dst);
  ck_assert_int_eq(num, dst);
}
END_TEST

Suite *suite_from_decimal_to_int(void) {
  Suite *suite = suite_create("suite_from_decimal_to_int");
  TCase *tc = tcase_create("case_from_decimal_to_int");

  tcase_add_test(tc, dst_null);
  tcase_add_test(tc, invalid_dec_1);
  tcase_add_test(tc, invalid_dec_2);
  tcase_add_test(tc, invalid_dec_3);
  tcase_add_test(tc, invalid_dec_4);
  tcase_add_test(tc, exp_over_limit);
  tcase_add_test(tc, zero_value);
  tcase_add_test(tc, max_int_src);
  tcase_add_test(tc, min_int_src);
  tcase_add_test(tc, overflow_dst_0);
  tcase_add_test(tc, overflow_dst_1);
  tcase_add_test(tc, overflow_dst_2);
  tcase_add_test(tc, overflow_dst_3);
  tcase_add_test(tc, overflow_dst_4);
  tcase_add_test(tc, overflow_dst_5);
  tcase_add_test(tc, pos_with_exp);
  tcase_add_test(tc, neg_with_exp);
  tcase_add_test(tc, pos_big_exp);
  tcase_add_test(tc, neg_big_exp);
  tcase_add_test(tc, dec_to_int_1);
  tcase_add_test(tc, dec_to_int_2);
  tcase_add_test(tc, dec_to_int_3);
  tcase_add_test(tc, dec_to_int_4);
  tcase_add_test(tc, dec_to_int_5);
  tcase_add_test(tc, dec_to_int_6);
  tcase_add_test(tc, dec_to_int_7);
  tcase_add_test(tc, dec_to_int_8);
  tcase_add_test(tc, dec_to_int_9);
  tcase_add_test(tc, dec_to_int_10);
  tcase_add_test(tc, dec_to_int_11);
  tcase_add_test(tc, dec_to_int_12);
  tcase_add_test(tc, dec_to_int_13);
  tcase_add_test(tc, dec_to_int_14);
  tcase_add_test(tc, dec_to_int_15);
  tcase_add_test(tc, dec_to_int_16);
  tcase_add_test(tc, dec_to_int_17);
  tcase_add_test(tc, dec_to_int_18);
  tcase_add_test(tc, dec_to_int_19);
  tcase_add_test(tc, dec_to_int_20);
  tcase_add_test(tc, dec_to_int_21);
  tcase_add_test(tc, dec_to_int_22);
  tcase_add_test(tc, dec_to_int_23);
  tcase_add_test(tc, dec_to_int_24);
  tcase_add_test(tc, dec_to_int_25);
  tcase_add_test(tc, dec_to_int_26);
  tcase_add_test(tc, dec_to_int_27);
  tcase_add_test(tc, dec_to_int_28);
  tcase_add_test(tc, dec_to_int_29);
  tcase_add_test(tc, dec_to_int_30);
  tcase_add_test(tc, dec_to_int_fail_1);
  tcase_add_test(tc, dec_to_int_fail_2);
  tcase_add_test(tc, dec_to_int_fail_3);
  tcase_add_test(tc, dec_to_int_fail_4);
  tcase_add_test(tc, dec_to_int_fail_5);
  tcase_add_test(tc, dec_to_int_fail_6);
  tcase_add_test(tc, dec_to_int_fail_7);
  tcase_add_test(tc, dec_to_int_fail_8);
  tcase_add_test(tc, dec_to_int_fail_9);
  tcase_add_test(tc, dec_to_int_fail_10);
  tcase_add_test(tc, dec_to_int_fail_11);
  tcase_add_test(tc, dec_to_int_fail_12);
  tcase_add_test(tc, dec_to_int_fail_13);
  tcase_add_test(tc, dec_to_int_fail_14);
  tcase_add_loop_test(tc, random_values, 0, 10);

  suite_add_tcase(suite, tc);
  return suite;
}
