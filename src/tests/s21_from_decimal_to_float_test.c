#include "s21_tests.h"

START_TEST(dst_null) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_from_decimal_to_float(decimal, NULL);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_1) {
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_2) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_3) {
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(invalid_dec_4) {
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(exp_over_limit) {
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);
  ck_assert_int_eq(code, ERROR);
}
END_TEST

START_TEST(dec_to_f_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_scale(&val, 5);
  float res = 1234.56789f;
  float tmp = 0.f;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(dec_to_f_2) {
  s21_decimal val = {{123456789, 0, 0, 0x80000000}};
  set_scale(&val, 5);
  float res = -1234.56789f;
  float tmp = 0.f;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(dec_to_f_3) {
  s21_decimal value = {{12, 0, 0, 0}};
  float result = 0;
  float check = 12;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(dec_to_f_4) {
  s21_decimal value = {{12, 0, 0, 0x80000000}};
  float result = 0;
  float check = -12;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(dec_to_f_5) {
  s21_decimal value = {{0x813F38F, 0x0, 0x0, 0x1C0000}};
  float check = 0.0000000000000000000135525263f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_6) {
  s21_decimal value = {{0x813F38F, 0x0, 0x0, 0x801C0000}};
  float check = -0.0000000000000000000135525263f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_7) {
  s21_decimal value = {{0x1, 0x0, 0x0, 0x1C0000}};
  float check = 0.0000000000000000000000000001f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_8) {
  s21_decimal value = {{0x1, 0x0, 0x0, 0x801C0000}};
  float check = -0.0000000000000000000000000001f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_9) {
  s21_decimal value = {{0xC3E7D2B4, 0xB1D38949, 0x24141BDA, 0x100000}};
  float check = 1116577040805.9696921400824500f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_10) {
  s21_decimal value = {{0xC3E7D2B4, 0xB1D38949, 0x24141BDA, 0x80100000}};
  float check = -1116577040805.9696921400824500f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_11) {
  s21_decimal value = {{0xEDBAC0B3, 0xC52D60D9, 0xF2494D19, 0x30000}};
  float check = 74983988059193276255107203.251f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_12) {
  s21_decimal value = {{0xEDBAC0B3, 0xC52D60D9, 0xF2494D19, 0x80030000}};
  float check = -74983988059193276255107203.251f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_13) {
  s21_decimal value = {{0x1, 0x0, 0x0, 0x10000}};
  float check = 0.1f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_14) {
  s21_decimal value = {{0x1, 0x0, 0x0, 0x80010000}};
  float check = -0.1f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_15) {
  s21_decimal value = {{0x20000000, 0x3B14F48, 0xB909834D, 0x130000}};
  float check = 5726622720.0000000000000000000f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_16) {
  s21_decimal value = {{0x20000000, 0x3B14F48, 0xB909834D, 0x80130000}};
  float check = -5726622720.0000000000000000000f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_17) {
  s21_decimal value = {{0x80000000, 0x18D, 0x0, 0x20000}};
  float check = 17072495001.60f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_18) {
  s21_decimal value = {{0x80000000, 0x18D, 0x0, 0x80020000}};
  float check = -17072495001.60f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_19) {
  s21_decimal value = {{0x80000000, 0x1, 0x0, 0x0}};
  long check = 6442450944;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_20) {
  s21_decimal value = {{0x80000000, 0x1, 0x0, 0x80000000}};
  long check = -6442450944;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_21) {
  s21_decimal value = {{0xDC000000, 0x42CE2944, 0x498D6158, 0x120000}};
  float check = 22763323955.200000000000000000f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_22) {
  s21_decimal value = {{0xDC000000, 0x42CE2944, 0x498D6158, 0x80120000}};
  float check = -22763323955.200000000000000000f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_23) {
  s21_decimal value = {{0x0, 0x5553F400, 0x161, 0x20000}};
  float check = 65178491842165997568.00f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_24) {
  s21_decimal value = {{0x0, 0x5553F400, 0x161, 0x80020000}};
  float check = -65178491842165997568.00f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_25) {
  s21_decimal value = {{0x0, 0x0, 0xF87, 0x30000}};
  float check = 73325807692995467673.600f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_26) {
  s21_decimal value = {{0x0, 0x0, 0xF87, 0x80030000}};
  float check = -73325807692995467673.600f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_27) {
  s21_decimal value = {{0x0, 0xD1AF0000, 0x1F972840, 0x80000}};
  float check = 97767731935837369139.20000000f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_28) {
  s21_decimal value = {{0x0, 0xD1AF0000, 0x1F972840, 0x80080000}};
  float check = -97767731935837369139.20000000f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_29) {
  s21_decimal value = {{0x0, 0x5553F400, 0x373, 0x20000}};
  float check = 162946235432826621132.80f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_30) {
  s21_decimal value = {{0x0, 0x5553F400, 0x373, 0x80020000}};
  float check = -162946235432826621132.80f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}

START_TEST(dec_to_f_31) {
  s21_decimal value = {{0x0, 0x12345678, 0x9ABCDEF0, 0x10000}};
  float check = 4.78890227e+27f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(dec_to_f_32) {
  s21_decimal value = {{0x0, 0x12345678, 0x9ABCDEF0, 0x80010000}};
  float check = -4.78890227e+27f;
  float result = 0;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *suite_from_decimal_to_float(void) {
  Suite *suite = suite_create("suite_from_decimal_to_float");
  TCase *tc = tcase_create("case_from_decimal_to_float");
  tcase_add_test(tc, dst_null);
  tcase_add_test(tc, invalid_dec_1);
  tcase_add_test(tc, invalid_dec_2);
  tcase_add_test(tc, invalid_dec_3);
  tcase_add_test(tc, invalid_dec_4);
  tcase_add_test(tc, exp_over_limit);
  tcase_add_test(tc, dec_to_f_1);
  tcase_add_test(tc, dec_to_f_2);
  tcase_add_test(tc, dec_to_f_3);
  tcase_add_test(tc, dec_to_f_4);
  tcase_add_test(tc, dec_to_f_5);
  tcase_add_test(tc, dec_to_f_6);
  tcase_add_test(tc, dec_to_f_7);
  tcase_add_test(tc, dec_to_f_8);
  tcase_add_test(tc, dec_to_f_9);
  tcase_add_test(tc, dec_to_f_10);
  tcase_add_test(tc, dec_to_f_11);
  tcase_add_test(tc, dec_to_f_12);
  tcase_add_test(tc, dec_to_f_13);
  tcase_add_test(tc, dec_to_f_14);
  tcase_add_test(tc, dec_to_f_15);
  tcase_add_test(tc, dec_to_f_16);
  tcase_add_test(tc, dec_to_f_17);
  tcase_add_test(tc, dec_to_f_18);
  tcase_add_test(tc, dec_to_f_19);
  tcase_add_test(tc, dec_to_f_20);
  tcase_add_test(tc, dec_to_f_21);
  tcase_add_test(tc, dec_to_f_22);
  tcase_add_test(tc, dec_to_f_23);
  tcase_add_test(tc, dec_to_f_24);
  tcase_add_test(tc, dec_to_f_25);
  tcase_add_test(tc, dec_to_f_26);
  tcase_add_test(tc, dec_to_f_27);
  tcase_add_test(tc, dec_to_f_28);
  tcase_add_test(tc, dec_to_f_29);
  tcase_add_test(tc, dec_to_f_30);
  tcase_add_test(tc, dec_to_f_31);
  tcase_add_test(tc, dec_to_f_32);

  suite_add_tcase(suite, tc);
  return suite;
}