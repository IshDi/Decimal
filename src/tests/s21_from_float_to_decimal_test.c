#include "s21_tests.h"

int check_result(float f, s21_decimal *check) {
  int flag;
  s21_decimal result = {0};
  flag = s21_from_float_to_decimal(f, &result);
  if (!flag) {
    ck_assert_int_eq(result.bits[0], check->bits[0]);
    ck_assert_int_eq(result.bits[1], check->bits[1]);
    ck_assert_int_eq(result.bits[2], check->bits[2]);
    ck_assert_int_eq(result.bits[3], check->bits[3]);
  }
  return flag;
}

START_TEST(pos_zero) {
  float f = 0.0f;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(neg_zero) {
  float f = -0.0f;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);

  int sign_check = get_sign(&check);
  int sign_result = get_sign(&result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(sign_check, sign_result);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(pos_inf) {
  float f = INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(neg_inf) {
  float f = -INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(pos_nan) {
  float f = NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(neg_nan) {
  float f = -NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(f_to_dec_1) {
  float f = 2.28401628E-19f;
  s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}};
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_2) {
  float f = -2.28401628E-19f;
  s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x80190000}};
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_3) {
  float f = 5.92141241E+23f;
  s21_decimal decimal_check = {{0x0, 0xa800000, 0x7D64, 0x0}};
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_4) {
  float f = -5.92141241E+23f;
  s21_decimal decimal_check = {{0x0, 0xa800000, 0x7D64, 0x80000000}};
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_5) {
  float f = 2.1349025E-18f;
  s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x180000}};
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_6) {
  float f = -2.1349025E-18f;
  s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x80180000}};
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_inf_pos) {
  s21_decimal dec = {0};
  float f = 1.0 / 0.0;
  ck_assert_int_eq(check_result(f, &dec), ERROR);
}
END_TEST

START_TEST(f_to_dec_inf_neg) {
  s21_decimal dec = {0};
  float f = -1.0 / 0.0;
  ck_assert_int_eq(check_result(f, &dec), ERROR);
}
END_TEST

START_TEST(f_to_dec_7) {
  s21_decimal dec = {0};
  float f = 1e-30f;
  s21_from_float_to_decimal(f, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(f_to_dec_8) {
  s21_decimal check = {{0x271, 0x0, 0x0, 0x40000}};
  float f = 0.0625f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_9) {
  s21_decimal check = {{0x271, 0x0, 0x0, 0x80040000}};
  float f = -0.0625f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_10) {
  s21_decimal check = {{0x3D09, 0x0, 0x0, 0x60000}};
  float f = 0.015625f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_11) {
  s21_decimal check = {{0x3D09, 0x0, 0x0, 0x80060000}};
  float f = -0.015625f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_12) {
  s21_decimal check = {{0x0, 0xEEF60000, 0x6B, 0x0}};
  float f = 1.99102057E+21f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_13) {
  s21_decimal check = {{0x0, 0xEEF60000, 0x6B, 0x80000000}};
  float f = -1.99102057E+21f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_14) {
  s21_decimal check = {{0x2DE, 0x0, 0x0, 0x1C0000}};
  float f = 7.34081171E-26f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_15) {
  s21_decimal check = {{0x2DE, 0x0, 0x0, 0x801C0000}};
  float f = -7.34081171E-26f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_16) {
  s21_decimal check = {{0x0, 0x0, 0xFFFFC000, 0x0}};
  float f = 7.92278603E+28f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_17) {
  s21_decimal check = {{0x0, 0x0, 0xFFFFC000, 0x80000000}};
  float f = -7.92278603E+28f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_18) {
  s21_decimal check = {{0x19D60C00, 0x3, 0x0, 0x0}};
  float f = 1.33183601E+10f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_19) {
  s21_decimal check = {{0x19D60C00, 0x3, 0x0, 0x80000000}};
  float f = -1.33183601E+10f;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_20) {
  s21_decimal check = {{0x7616E3, 0x0, 0x0, 0x0}};
  float f = 7739107;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_21) {
  s21_decimal check = {{0x7616E3, 0x0, 0x0, 0x80000000}};
  float f = -7739107;
  ck_assert_int_eq(check_result(f, &check), OK);
}
END_TEST

START_TEST(f_to_dec_22) {
  s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0xE0000}};
  float f = 2.38582807E-08f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_23) {
  s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0x800E0000}};
  float f = -2.38582807E-08f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_24) {
  s21_decimal decimal_check = {{0x501A0000, 0xB8, 0x0, 0x0}};
  float f = 7.91617864E+11f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_25) {
  s21_decimal decimal_check = {{0x501A0000, 0xB8, 0x0, 0x80000000}};
  float f = -7.91617864E+11f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_26) {
  s21_decimal decimal_check = {{0x0, 0xEEF60000, 0x6B, 0x0}};
  float f = 1.99102057E+21f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_27) {
  s21_decimal decimal_check = {{0x0, 0xEEF60000, 0x6B, 0x80000000}};
  float f = -1.99102057E+21f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_28) {
  s21_decimal decimal_check = {{0x0, 0x70000000, 0x7AFAD, 0x0}};
  float f = 9.29209423E+24f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

START_TEST(f_to_dec_29) {
  s21_decimal decimal_check = {{0x0, 0x70000000, 0x7AFAD, 0x80000000}};
  float f = -9.29209423E+24f;
  ck_assert_int_eq(check_result(f, &decimal_check), OK);
}
END_TEST

Suite *suite_from_float_to_decimal(void) {
  Suite *suite = suite_create("suite_from_float_to_decimal");
  TCase *tc = tcase_create("case_from_float_to_decimal");
  tcase_add_test(tc, pos_zero);
  tcase_add_test(tc, neg_zero);
  tcase_add_test(tc, pos_inf);
  tcase_add_test(tc, neg_inf);
  tcase_add_test(tc, pos_nan);
  tcase_add_test(tc, neg_nan);
  tcase_add_test(tc, f_to_dec_1);
  tcase_add_test(tc, f_to_dec_2);
  tcase_add_test(tc, f_to_dec_3);
  tcase_add_test(tc, f_to_dec_4);
  tcase_add_test(tc, f_to_dec_5);
  tcase_add_test(tc, f_to_dec_6);
  tcase_add_test(tc, f_to_dec_7);
  tcase_add_test(tc, f_to_dec_8);
  tcase_add_test(tc, f_to_dec_9);
  tcase_add_test(tc, f_to_dec_10);
  tcase_add_test(tc, f_to_dec_11);
  tcase_add_test(tc, f_to_dec_12);
  tcase_add_test(tc, f_to_dec_13);
  tcase_add_test(tc, f_to_dec_14);
  tcase_add_test(tc, f_to_dec_15);
  tcase_add_test(tc, f_to_dec_16);
  tcase_add_test(tc, f_to_dec_17);
  tcase_add_test(tc, f_to_dec_18);
  tcase_add_test(tc, f_to_dec_19);
  tcase_add_test(tc, f_to_dec_20);
  tcase_add_test(tc, f_to_dec_21);
  tcase_add_test(tc, f_to_dec_22);
  tcase_add_test(tc, f_to_dec_23);
  tcase_add_test(tc, f_to_dec_24);
  tcase_add_test(tc, f_to_dec_25);
  tcase_add_test(tc, f_to_dec_26);
  tcase_add_test(tc, f_to_dec_27);
  tcase_add_test(tc, f_to_dec_28);
  tcase_add_test(tc, f_to_dec_29);
  tcase_add_test(tc, f_to_dec_inf_pos);
  tcase_add_test(tc, f_to_dec_inf_neg);

  suite_add_tcase(suite, tc);
  return suite;
}