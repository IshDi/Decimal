#include "s21_tests.h"

START_TEST(test_truncate_1) {
  // 79228162514264337593543950335
  s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_2) {
  // -7922816251426.4337593543950335
  s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0xACA5F622, 0x00000734, 0x0, 0x80000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_3) {
  // 5.281877500950955839569596690
  s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x00000005, 0x0, 0x0, 0x00000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_4) {
  // -5.281877500950955839569596690
  s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x00000005, 0x0, 0x0, 0x80000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_5) {
  // -1.2297829382473034409
  s21_decimal dec1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x80000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_6) {
  // 1.2297829382473034409
  s21_decimal dec1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x00130000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x00000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_7) {
  s21_decimal dec1 = {{0x11111112, 0x11111111, 0x11111111, 0x11111111}};
  s21_decimal result;
  s21_zero_decimal(&result);

  uint8_t flag = s21_truncate(dec1, &result);
  ck_assert_int_eq(flag, 1);
}
END_TEST

START_TEST(test_truncate_8) {
  //  -0.0000000000000000000000000001
  s21_decimal dec1 = {{0x1, 0x0, 0x0, 0x801C0000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x80000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_9) {
  //  -0
  s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x80000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_10) {
  //  0
  s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x00000000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x00000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_11) {
  //  -0.00000000000000
  s21_decimal dec1 = {{0x0, 0x0, 0x0, 0x800E0000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x0, 0x0, 0x0, 0x80000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_12) {
  //  1.0
  s21_decimal dec1 = {{0xA, 0x0, 0x0, 0x00010000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x00000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

START_TEST(test_truncate_13) {
  //  -1.0
  s21_decimal dec1 = {{0xA, 0x0, 0x0, 0x80010000}};
  s21_decimal result;
  s21_zero_decimal(&result);
  s21_decimal dec2 = {{0x00000001, 0x0, 0x0, 0x80000000}};

  uint8_t flag = s21_truncate(dec1, &result);
  uint8_t res = s21_is_equal(result, dec2);
  ck_assert_int_eq(flag, 0);
  ck_assert_int_eq(res, TRUE);
}
END_TEST

Suite *suite_truncate(void) {
  Suite *c = suite_create("suite_truncate");
  TCase *tc = tcase_create("case_truncate");

  tcase_add_test(tc, test_truncate_1);
  tcase_add_test(tc, test_truncate_2);
  tcase_add_test(tc, test_truncate_3);
  tcase_add_test(tc, test_truncate_4);
  tcase_add_test(tc, test_truncate_5);
  tcase_add_test(tc, test_truncate_6);
  tcase_add_test(tc, test_truncate_7);
  tcase_add_test(tc, test_truncate_8);
  tcase_add_test(tc, test_truncate_9);
  tcase_add_test(tc, test_truncate_10);
  tcase_add_test(tc, test_truncate_11);
  tcase_add_test(tc, test_truncate_12);
  tcase_add_test(tc, test_truncate_13);

  suite_add_tcase(c, tc);
  return c;
}
