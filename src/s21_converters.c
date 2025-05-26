#include "s21_decimal.h"

void set_sign(s21_decimal *dec, unsigned int sign) {
  dec->bits[3] &= 0x7FFFFFFF;
  dec->bits[3] |= (sign & 1u) << 31;
}

// от 0 до 95! // index - индекс бита
int s21_get_bit(s21_decimal value, int index) {
  int mask = 1u << (index % 32);
  return (value.bits[index / 32] & mask) != 0;
}

int is_decimal_valid_to_convert_to_int(s21_decimal *dec) {
  return (dec->bits[1] == 0 && dec->bits[2] == 0 &&
          ((get_sign(dec) && dec->bits[0] <= 2147483648) ||
           (!get_sign(dec) && dec->bits[0] <= 2147483647)));
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = OK;
  if (dst != NULL) {
    if (is_decimal_valid(dst)) {
      s21_zero_decimal(dst);
      if (src < 0) {
        set_sign(dst, 1);
        src = -src;
      }
      dst->bits[0] = src;
    } else {
      result = ERROR;
    }
  } else {
    result = ERROR;
  }
  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = OK;
  if (dst && is_decimal_valid(&src)) {
    s21_decimal trunc;
    s21_zero_decimal(&trunc);
    result = s21_truncate(src, &trunc);
    if (!result && is_decimal_valid_to_convert_to_int(&trunc)) {
      *dst = (int)trunc.bits[0];
      if (get_sign(&src)) {
        *dst = -(*dst);
      }
    } else {
      result = ERROR;
    }
  } else {
    result = ERROR;
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result_conv = OK;
  if (dst && is_decimal_valid(&src)) {
    *dst = 0.0f;
    double temp = 0.0;
    for (int i = 0; i < 96; i++) {
      temp += s21_get_bit(src, i) * pow(2, i);
    }
    temp = temp * pow(10, -get_scale(&src));
    if (get_sign(&src)) {
      temp = -temp;
    }
    *dst = (float)temp;
  } else {
    result_conv = 1;
  }
  return result_conv;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result_conv = OK;
  s21_zero_decimal(dst);
  if (!isinf(src) && !isnan(src)) {
    if (src != 0) {
      int sign = (src < 0) ? 1 : 0;
      int exp;
      double temp = (double)fabsl(src);
      frexp(temp, &exp);

      int offset = 0;
      while (offset < MAX_EXP && (int)temp / (int)pow(2, 21) == 0) {
        temp *= 10;
        offset++;
      }
      temp = round(temp);
      if (offset <= MAX_EXP && (exp >= -95 && exp <= 96)) {
        f_bits f = {0};
        temp = (float)temp;
        while (fmod(temp, 10) == 0 && offset > 0) {
          temp /= 10;
          offset--;
        }
        f.f = (float)temp;
        frexp(temp, &exp);
        exp -= 1;
        dst->bits[exp / 32] |= 1 << exp % 32;
        for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
          if ((f.bits & (1 << j)) != 0) {
            dst->bits[i / 32] |= 1 << i % 32;
          }
        }
        set_sign(dst, sign);
        set_scale(dst, offset);
      }
    } else {
      int sign = (signbit(src) != 0) ? 1 : 0;
      set_sign(dst, sign);
    }
  } else {
    result_conv = ERROR;
  }
  return result_conv;
}
