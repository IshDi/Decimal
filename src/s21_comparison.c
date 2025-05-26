#include "s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int zero_1, zero_2, sign_1, sign_2, diff_scale, get_scale,
      isGreater = 0;  // zero,
  zero_1 = s21_is_zero(value_1);
  zero_2 = s21_is_zero(value_2);
  sign_1 = s21_get_sign(value_1);
  if (zero_1 && sign_1) value_1.bits[3] &= ~MINUS;
  sign_2 = s21_get_sign(value_2);
  if (zero_2 && sign_2) value_2.bits[3] &= ~MINUS;
  int equal = 0;
  equal = s21_is_equal(value_1, value_2);
  if (sign_1 == sign_2 && !equal) {
    s21_big_decimal big_value_1 = {.bits = {0}};
    s21_import_to_big_decimal(value_1, &big_value_1);
    s21_big_decimal big_value_2 = {.bits = {0}};
    s21_import_to_big_decimal(value_2, &big_value_2);
    diff_scale = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (diff_scale > 0) {
      get_scale = s21_get_scale(value_1);
      s21_set_scale(&value_2, get_scale);
    } else {
      get_scale = s21_get_scale(value_2);
      s21_set_scale(&value_1, get_scale);
    }
    s21_normalization(&big_value_1, &big_value_2, diff_scale);
    int flag = 0, out = 0;
    for (int i = 7; i >= 0 && !out; i--) {
      if (big_value_1.bits[i] != big_value_2.bits[i]) {
        if (big_value_1.bits[i] > big_value_2.bits[i]) {
          isGreater = 1;
          flag = 1;
        }
        out = 1;
      }
    }
    if (sign_1 && sign_2 && flag) isGreater = 0;
    if (sign_1 && sign_2 && !flag) isGreater = 1;
  }
  if (sign_1 != sign_2) {
    if (sign_1 < sign_2)
      isGreater = 1;
    else
      isGreater = 0;
  }
  if (sign_1 == 1 && zero_2) isGreater = 0;
  if (sign_2 == 1 && zero_1) isGreater = 1;
  if (equal) isGreater = 0;
  if (zero_1 && zero_2) isGreater = 0;
  return isGreater;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int zero_1, zero_2, sign_1, sign_2, diff_scale, get_scale = 0;
  int isEqual = 1;
  zero_1 = s21_is_zero(value_1);
  zero_2 = s21_is_zero(value_2);
  sign_1 = s21_get_sign(value_1);
  if (zero_1 && sign_1) value_1.bits[3] &= ~MINUS;
  sign_2 = s21_get_sign(value_2);
  if (zero_2 && sign_2) value_2.bits[3] &= ~MINUS;
  if (sign_1 == sign_2) {
    s21_big_decimal big_value_1 = {.bits = {0}};
    s21_import_to_big_decimal(value_1, &big_value_1);
    s21_big_decimal big_value_2 = {.bits = {0}};
    s21_import_to_big_decimal(value_2, &big_value_2);
    diff_scale = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (diff_scale > 0) {
      get_scale = s21_get_scale(value_1);
      s21_set_scale(&value_2, get_scale);
    } else {
      get_scale = s21_get_scale(value_2);
      s21_set_scale(&value_1, get_scale);
    }
    s21_normalization(&big_value_1, &big_value_2, diff_scale);
    for (int i = 7; i >= 0; i--) {
      if (big_value_1.bits[i] != big_value_2.bits[i]) {
        isEqual = 0;
      }
    }
  }
  if (sign_1 != sign_2) {
    isEqual = 0;
  }
  if (zero_1 && zero_2) isEqual = 1;
  return isEqual;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int notEqual = 0;
  if (s21_is_equal(value_1, value_2) == 0) notEqual = 1;
  return notEqual;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int isGreaterEqual = 0;
  int temp_1 = 0;
  int temp_2 = 0;
  if (s21_is_greater(value_1, value_2) == 1) temp_1 = 1;
  if (s21_is_equal(value_1, value_2) == 1) temp_2 = 1;
  if (temp_1 || temp_2) isGreaterEqual = 1;
  return isGreaterEqual;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int isLess = 0;
  int temp_1 = 0;
  int temp_2 = 0;
  if (s21_is_greater(value_1, value_2) == 0) temp_1 = 1;
  if (s21_is_equal(value_1, value_2) == 0) temp_2 = 1;
  if (temp_1 && temp_2) isLess = 1;
  return isLess;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int isLessEqual = 0;
  int temp_1 = 0;
  int temp_2 = 0;
  if (s21_is_less(value_1, value_2) == 1) temp_1 = 1;
  if (s21_is_equal(value_1, value_2) == 1) temp_2 = 1;
  if (temp_1 || temp_2) isLessEqual = 1;
  return isLessEqual;
}