#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);
  int sign = 0;
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  sign = s21_get_sign(value);  // плюс = 0, минус = 1;
  if (!sign) {
    result->bits[3] |= MINUS;
  } else {
    result->bits[3] &= ~MINUS;
  }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);  // +
  int error = 0;
  int ostatok = 0;
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  s21_get_scale(value);
  s21_big_decimal big_value = {.bits = {0}};
  s21_big_decimal one = {{0}};
  one.bits[0] = 1;
  s21_big_decimal ten = {{0}};  // ten
  ten.bits[0] = 10;             // ten
  s21_big_decimal temp_result = {{0}};
  if (scale != 0 || !s21_is_zero(value)) {
    s21_import_to_big_decimal(value, &big_value);
    for (int i = scale; i > 0; i--) {
      // ten
      if (s21_is_greater_big_decimal(ten, big_value)) {
        ostatok = big_value.bits[0];
        s21_zero_big_decimal(&big_value);
        break;
        // i--;
      }
      ostatok = s21_div_ostatok(&big_value);
    }
    if ((big_value.bits[3] || big_value.bits[4] || big_value.bits[5] ||
         big_value.bits[6] || big_value.bits[7])) {
      error = 1;
    }
    if (ostatok >= 5) {
      s21_add_big_decimal(big_value, one, &temp_result);
      s21_import_to_decimal(result, temp_result);
    } else {
      s21_import_to_decimal(result, big_value);
    }
    s21_set_scale(result, 0);
    if (sign) s21_set_sign(result);
  } else {
    s21_copy_decimal(result, value);
  }
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_zero_decimal(result);  // +
  int error = 0;
  int ostatok = 0;
  int scale = s21_get_scale(value);
  int sign = s21_get_sign(value);
  s21_get_scale(value);
  s21_big_decimal big_value = {.bits = {0}};
  s21_big_decimal one = {{0}};
  one.bits[0] = 1;
  s21_big_decimal ten = {{0}};  // ten
  ten.bits[0] = 10;             // ten
  s21_big_decimal temp_result = {{0}};
  if (scale != 0 || !s21_is_zero(value)) {
    s21_import_to_big_decimal(value, &big_value);
    for (int i = scale; i > 0; i--) {
      // ten
      if (s21_is_greater_big_decimal(ten, big_value)) {
        ostatok = big_value.bits[0];
        s21_zero_big_decimal(&big_value);
        break;
        // i--;
      }
      ostatok = s21_div_ostatok(&big_value);
    }
    if ((big_value.bits[3] || big_value.bits[4] || big_value.bits[5] ||
         big_value.bits[6] || big_value.bits[7])) {
      error = 1;
    }
    if (sign && ostatok != 0) {
      s21_add_big_decimal(big_value, one, &temp_result);
      s21_import_to_decimal(result, temp_result);
    } else {
      s21_import_to_decimal(result, big_value);
    }
    s21_set_scale(result, 0);
    if (sign) s21_set_sign(result);
  } else {
    s21_copy_decimal(result, value);
  }
  return error;
}

int get_sign(s21_decimal *dec) { return (dec->bits[3] & 1u << 31) != 0; }

int get_scale(s21_decimal *dec) { return ((dec->bits[3] >> 16) & EXP_HEX); }

int set_scale(s21_decimal *dec, int exponent) {
  int result = 1;
  if (dec && exponent < 29) {
    dec->bits[3] &= ~(0xFF << 16);
    dec->bits[3] |= exponent << 16;
  } else {
    result = 0;
  }
  return result;
}

int is_decimal_valid(s21_decimal *number) {  // unused fields wasnt filled
  int result = 1;
  if (number) {
    if ((number->bits[3] & 0xFFFF) != 0 ||
        (number->bits[3] >> 24 & 0x7F) != 0) {
      result = 0;
    }
    if (get_scale(number) > 28) {
      result = 0;
    }
  } else {
    result = 0;
  }
  return result;
}

int divide_by_integer(s21_decimal value, int num, s21_decimal *result) {
  uint64_t buffer = 0ull;
  for (int i = 2; i >= 0; i--) {
    uint32_t div = (buffer + value.bits[i]) % num;
    uint64_t div_buffer = (buffer + value.bits[i]) / num;
    result->bits[i] = (unsigned)div_buffer;
    buffer = div;
    buffer = buffer << 32;
  }
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = ERROR;
  if (is_decimal_valid(&value)) {
    int expon = get_scale(&value);
    s21_decimal temp = value;
    for (int i = 0; i < expon; i++) {
      divide_by_integer(temp, 10, &temp);
      set_scale(&temp, expon - i - 1);
    }
    *result = temp;
    flag = OK;
  }
  return flag;
}
