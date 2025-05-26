#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, get_scale = 0,
      sign_res = 0;  // error - возврат s21_sub; sign_res=1 если оба числа "-"
  s21_zero_decimal(result);
  if (s21_get_sign(value_1) && s21_get_sign(value_2))
    sign_res = 1;  // одинаковые знаки "-" "-"
  if (s21_get_sign(value_1) !=
      s21_get_sign(value_2)) {  // разные знаки "+" и "-"
    int sign = 0;
    sign = s21_get_sign(value_1);
    value_1.bits[3] &= ~MINUS;  // устанавливаем бит знака 0 ("+"); прим.:
                                // значение числа не меняется
    value_2.bits[3] &= ~MINUS;
    error =
        sign ? s21_sub(value_2, value_1, result)
             : s21_sub(
                   value_1, value_2,
                   result);  // из положительного отнимаем отрицательное число
  } else {
    int scale = 0;  // +
    s21_big_decimal big_value_1 = {.bits = {0}};
    s21_import_to_big_decimal(value_1, &big_value_1);
    s21_big_decimal big_value_2 = {.bits = {0}};
    s21_import_to_big_decimal(value_2, &big_value_2);
    s21_big_decimal big_result = {{0}};
    int diff_scale = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (diff_scale > 0) {
      get_scale = s21_get_scale(value_1);
      s21_set_scale(&value_2, get_scale);
    } else {
      get_scale = s21_get_scale(value_2);
      s21_set_scale(&value_1, get_scale);
    }
    s21_normalization(&big_value_1, &big_value_2, diff_scale);
    s21_add_big_decimal(big_value_1, big_value_2, &big_result);
    scale = s21_post_normalization(&big_result, s21_get_scale(value_1));
    if (scale >= 0) {
      s21_import_to_decimal(result, big_result);
      s21_set_scale(result, scale);
    } else {
      error = 1;
    }
  }
  if (sign_res) s21_set_sign(result);
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

void s21_add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  unsigned memo = 0;
  for (int i = 0; i < 256; i++) {
    unsigned result_bit =
        s21_get_bit_big(value_1, i) + s21_get_bit_big(value_2, i) + memo;
    memo = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(result, i, result_bit);
  }
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, get = 0, scale = 0, sign_res = 0;
  s21_zero_decimal(result);
  if (s21_get_sign(value_1) && s21_get_sign(value_2)) {  // -2-(-4) -> 4-2
    s21_decimal temp_1 = {{0}};
    s21_copy_decimal(&temp_1, value_1);
    s21_copy_decimal(&value_1, value_2);
    s21_copy_decimal(&value_2, temp_1);
    s21_set_bit(&value_1, 127, 0);
    s21_set_bit(&value_2, 127, 0);
  }
  if (s21_get_sign(value_1) !=
      s21_get_sign(value_2)) {  // -2-4 -> (-)2+4 и 2-(-4) -> 2+4
    if (s21_get_sign(value_1)) sign_res = 1;
    s21_set_bit(&value_1, 127, 0);
    s21_set_bit(&value_2, 127, 0);
    error = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal big_value_1 = {.bits = {0}}, big_value_2 = {.bits = {0}},
                    big_result = {{0}};
    s21_import_to_big_decimal(value_1, &big_value_1);
    s21_import_to_big_decimal(value_2, &big_value_2);
    int diff = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (diff > 0) {
      get = s21_get_scale(value_1);
      s21_set_scale(&value_2, get);
    } else {
      get = s21_get_scale(value_2);
      s21_set_scale(&value_1, get);
    }
    s21_normalization(&big_value_1, &big_value_2, diff);
    if (s21_is_greater_big_decimal(big_value_2,
                                   big_value_1)) {  // 2-4 -> (-)result
      s21_big_decimal temp_2 = {{0}};
      s21_copy_big_decimal(&temp_2, big_value_1);
      s21_copy_big_decimal(&big_value_1, big_value_2);
      s21_copy_big_decimal(&big_value_2, temp_2);
      s21_set_sign(result);
    }
    s21_sub_big_decimal(big_value_1, big_value_2, &big_result);
    scale = s21_post_normalization(&big_result, s21_get_scale(value_1));
    if (scale >= 0) {
      s21_import_to_decimal(result, big_result);
      s21_set_scale(result, scale);
    } else
      error = 1;  // +
  }
  if (sign_res) s21_set_sign(result);
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  int memo = 0;
  for (int i = 0; i < 256; i++) {
    int bit_value_1 = s21_get_bit_big(value_1, i);
    int bit_value_2 = s21_get_bit_big(value_2, i);
    int result_bit = bit_value_1 - bit_value_2 - memo;
    if (result_bit < 0) {
      result_bit += 2;
      memo = 1;
    } else {
      memo = 0;
    }
    s21_set_bit_big(result, i, result_bit);
  }
}

int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2) {
  int isGreater = 0;
  int out = 0;
  for (int i = 7; i >= 0 && !out; i--) {
    if (value_1.bits[i] != value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) isGreater = 1;
      out = 1;  // break;
    }
  }
  return isGreater;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0, sign_res = 0;
  s21_zero_decimal(result);
  if (s21_is_zero(value_1) == 0 && s21_is_zero(value_2) == 0) {
    // if (s21_get_sign(value_1) && s21_get_sign(value_2)) sign_res = 0;
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) sign_res = 1;
    s21_big_decimal big_value_1 = {.bits = {0}};
    s21_import_to_big_decimal(value_1, &big_value_1);
    s21_big_decimal big_value_2 = {.bits = {0}};
    s21_import_to_big_decimal(value_2, &big_value_2);
    s21_big_decimal big_result = {{0}};
    scale = s21_get_scale(value_1) + s21_get_scale(value_2);  // ++
    error =
        s21_mul_big_decimal(big_value_1, big_value_2, &big_result);  // error =
    scale = s21_post_normalization(&big_result, scale);
    if (sign_res) s21_set_sign(result);
    if (scale >= 0) {
      s21_set_scale(result, scale);
      s21_import_to_decimal(result, big_result);
    } else {
      error = 1;
    }
    if (error == 1 && s21_get_sign(*result)) error = 2;
    if (error) s21_zero_decimal(result);
  }
  return error;
}

int s21_mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result) {
  int error = 0, count = 0;
  for (int i = 0; i < 256 && !error; i++) {
    if (s21_get_bit_big(value_2, i)) {
      error =
          s21_int_shift_left(&value_1, i - count);  // error = shift_left(...);
      s21_add_big_decimal(value_1, *result, result);
      count = i;
    }
  }
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, sign_res = 0;
  s21_zero_decimal(result);
  if (s21_is_zero(value_2) == 1) {
    error = 3;
  } else if (s21_is_zero(value_1) == 1) {
    s21_zero_decimal(result);  // делим 0, результат 0
  } else if (s21_is_zero(value_1) == 0 && s21_is_zero(value_2) == 0) {
    int scale = 0, res_scale = 0;
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) sign_res = 1;
    s21_big_decimal big_value_1 = {.bits = {0}};
    s21_import_to_big_decimal(value_1, &big_value_1);
    s21_big_decimal big_value_2 = {.bits = {0}};
    s21_import_to_big_decimal(value_2, &big_value_2);
    s21_big_decimal big_result = {{0}};
    scale = s21_div_big_decimal(big_value_1, big_value_2, &big_result);
    s21_set_scale(&value_1, s21_get_scale(value_1) + scale);
    res_scale = s21_get_scale(value_1) - s21_get_scale(value_2);
    if (res_scale > 0) {
      res_scale = s21_post_normalization(&big_result, res_scale);
    } else if (res_scale < 0) {
      s21_increase_scale_big_decimal(&big_result, abs(res_scale));
      res_scale = s21_post_normalization(&big_result, 0);
    }
    if (res_scale >= 0) {
      s21_import_to_decimal(result, big_result);
      s21_set_scale(result, res_scale);
    } else {
      error = 1;
    }
    if (sign_res) s21_set_sign(result);
  }
  if (error == 1 && s21_get_sign(*result)) error = 2;
  if (error) s21_zero_decimal(result);
  return error;
}

int s21_div_big_decimal(s21_big_decimal big_value_1,
                        s21_big_decimal big_value_2,
                        s21_big_decimal *big_result) {
  int scale = 0, save_scale = 0, out = 0;
  int flag_result = 0;
  int new_temp = 0;
  int stavim_null = 0;
  int scale_memory = 0;  // scale_memory
  s21_big_decimal start_big_value_2 = {{0}}, temp = {{0}}, temp_result = {{0}},
                  temp_big_value_1 = {{0}};
  s21_copy_big_decimal(&start_big_value_2, big_value_2);
  for (int i = 0; i < 150 && !out &&
                  s21_is_big_decimal_not_empty(
                      big_value_1);) {  // i < 15 для 10 делить на 3
    scale = s21_equation_bits_big_decimal(&big_value_1, &big_value_2);
    stavim_null = scale;
    scale_memory += scale;  // scale_memory
    s21_sub_big_decimal(big_value_1, big_value_2, &temp_big_value_1);
    s21_copy_big_decimal(&big_value_1, temp_big_value_1);
    if (new_temp == 0) {
      s21_set_bit_big(&temp, 0, 1);
      new_temp = 1;
    } else {
      s21_shift_big_dec_left(&temp, 1);
      if (stavim_null) {                         // ++
        for (int i = 1; i < stavim_null; i++) {  // i = 1
          s21_shift_big_dec_left(&temp, 1);
          s21_increase_scale_big_decimal(big_result, 1);         // ++
          s21_add_big_decimal(*big_result, temp, &temp_result);  // ++
        }
      }
      s21_set_bit_big(&temp, 0, 1);
    }
    if (s21_is_greater_or_equal_big_decimal(start_big_value_2, big_value_1)) {
      save_scale += scale_memory;
      scale_memory = 0;
    }
    if (s21_is_greater_big_decimal(big_value_2, start_big_value_2)) {
      while (s21_is_greater_big_decimal(big_value_2, big_value_1) &&
             s21_is_greater_big_decimal(
                 big_value_2,
                 start_big_value_2)) {  // изменил больше чем биг_валью_1
        s21_shift_big_dec_right(&big_value_2, 1);
        if (s21_is_greater_big_decimal(big_value_2, big_value_1)) {
          s21_shift_big_dec_left(&temp, 1);
        }
      }
      flag_result = 1;
    }
    if (s21_is_greater_big_decimal(start_big_value_2, big_value_1)) {
      if (!flag_result) {
        s21_copy_big_decimal(big_result, temp);
        flag_result = 1;
        s21_zero_big_decimal(&temp);
      } else {
        s21_increase_scale_big_decimal(big_result, 1);
        s21_add_big_decimal(*big_result, temp, &temp_result);
        s21_copy_big_decimal(big_result, temp_result);
        s21_zero_big_decimal(&temp_result);
        s21_zero_big_decimal(&temp);
        s21_copy_big_decimal(&big_value_2, start_big_value_2);
      }
    }
    if (save_scale > 29) out = 1;  // break;
    i++;
  }
  return save_scale;
}
// scale_memory чтобы скейл прибавлялся только когда увеличиться число, а не
// до этого (когда увеличится число скейл не увеличивается) из-за этого
// неправильно показывает скейл промежуточного результата (число осталось
// еще не увеличенным, а скейл увеличился)

int s21_equation_bits_big_decimal(s21_big_decimal *big_value_1,
                                  s21_big_decimal *big_value_2) {
  s21_big_decimal temp = {{0}};
  s21_big_decimal temp_1 = {{0}};
  s21_copy_big_decimal(&temp, *big_value_2);
  int scale = 0;
  while (s21_is_greater_big_decimal(*big_value_2, *big_value_1)) {
    s21_increase_scale_big_decimal(big_value_1, 1);
    scale++;
  }
  while (s21_is_greater_or_equal_big_decimal(*big_value_1, *big_value_2)) {
    s21_shift_big_dec_left(big_value_2, 1);
    if (!s21_is_greater_big_decimal(*big_value_2, *big_value_1)) {
      s21_copy_big_decimal(&temp_1, *big_value_2);
    }
  }
  s21_shift_big_dec_right(big_value_2, 1);
  if (s21_is_greater_big_decimal(*big_value_2, *big_value_1)) {
    s21_copy_big_decimal(big_value_2, temp);
    if (s21_is_greater_big_decimal(temp_1, temp)) {
      s21_copy_big_decimal(big_value_2, temp_1);
    }
  }
  return scale;
}

int s21_is_big_decimal_not_empty(s21_big_decimal big_value) {
  return big_value.bits[0] + big_value.bits[1] + big_value.bits[2] +
         big_value.bits[3] + big_value.bits[4] + big_value.bits[5] +
         big_value.bits[6] + big_value.bits[7];
}

int s21_is_greater_or_equal_big_decimal(s21_big_decimal big_value_1,
                                        s21_big_decimal big_value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !out && !result; i--) {
    if (big_value_1.bits[i] != 0 || big_value_2.bits[i] != 0) {
      if (big_value_1.bits[i] >= big_value_2.bits[i]) {
        result = 1;
      }
      out = 1;
    }
  }
  return result;
}

void s21_shift_big_dec_right(s21_big_decimal *big_value, int num) {
  unsigned int buffer[7] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = s21_get_bit_big(*big_value, (i + 1) * 32);
    }
    for (int i = 0; i < 7; i++) {
      big_value->bits[i] >>= 1;
      s21_set_bit_big(big_value, (i + 1) * 32 - 1, buffer[i]);
    }
    big_value->bits[7] >>= 1;
  }
}

int s21_shift_big_dec_left(s21_big_decimal *big_value, int num) {
  int error = 0;
  unsigned int buffer[8] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = s21_get_bit_big(*big_value, (i + 1) * 32 - 1);
    }
    for (int i = 7; i > 0 && !error; i--) {
      if (s21_get_bit_big(*big_value, 255)) error = 1;
      big_value->bits[i] <<= 1;
      s21_set_bit_big(big_value, i * 32, buffer[i - 1]);
    }
    big_value->bits[0] <<= 1;
  }
  return error;
}

// Вспомогательные фукнции decimal ~~~~~~~~~~~~~~~

void s21_zero_decimal(s21_decimal *value) {
  value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] = 0;
}

int s21_get_sign(s21_decimal value) {
  return (value.bits[3] & MINUS) ? 1 : 0;  // плюс: 0, минус: 1
}

void s21_set_sign(s21_decimal *value) { value->bits[3] |= MINUS; }

int s21_get_scale(s21_decimal value) {
  int scale = (value.bits[3] & SC) >> 16;
  return scale;
}

void s21_set_scale(s21_decimal *value, int scale) {
  value->bits[3] &= MINUS;
  value->bits[3] |= (scale << 16) & SC;
}

// от 0 до 95! // index - индекс бита
// int s21_get_bit(s21_decimal value, int index) {
//   int mask = 1u << (index % 32);
//   return (value.bits[index / 32] & mask) != 0;
// }

void s21_set_bit(s21_decimal *value, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    value->bits[index / 32] = value->bits[index / 32] & ~mask;  // ставим 0
  else
    value->bits[index / 32] = value->bits[index / 32] | mask;  // ставим 1
}

int s21_is_zero(s21_decimal value) {
  int zero = 0;
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0) zero = 1;
  return zero;
}

// Вспомогательные фукнции big decimal ~~~~~~~~~~~~~~~

void s21_zero_big_decimal(s21_big_decimal *value) {
  value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] =
      value->bits[4] = value->bits[5] = value->bits[6] = value->bits[7] = 0;
}

int s21_get_bit_big(s21_big_decimal value, int index) {
  int mask = 1u << (index % 32);
  return (value.bits[index / 32] & mask) != 0;
}

void s21_set_bit_big(s21_big_decimal *value, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    value->bits[index / 32] = value->bits[index / 32] & ~mask;
  else
    value->bits[index / 32] = value->bits[index / 32] | mask;
}

void s21_import_to_big_decimal(s21_decimal value_1, s21_big_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
}

void s21_import_to_decimal(s21_decimal *value_1, s21_big_decimal value_2) {
  value_1->bits[0] = value_2.bits[0];
  value_1->bits[1] = value_2.bits[1];
  value_1->bits[2] = value_2.bits[2];
}

void s21_copy_big_decimal(s21_big_decimal *value_1, s21_big_decimal value_2) {
  value_1->bits[0] = value_2.bits[0];
  value_1->bits[1] = value_2.bits[1];
  value_1->bits[2] = value_2.bits[2];
  value_1->bits[3] = value_2.bits[3];
  value_1->bits[4] = value_2.bits[4];
  value_1->bits[5] = value_2.bits[5];
  value_1->bits[6] = value_2.bits[6];
  value_1->bits[7] = value_2.bits[7];
}

void s21_copy_decimal(s21_decimal *value_1, s21_decimal value_2) {
  value_1->bits[0] = value_2.bits[0];
  value_1->bits[1] = value_2.bits[1];
  value_1->bits[2] = value_2.bits[2];
  value_1->bits[3] = value_2.bits[3];
}

void s21_shift_left(s21_big_decimal *big_value, int shift_value) {
  unsigned memory = 0;
  for (int i = 0; i < 7;
       i++) {  // i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned) - 1)
    unsigned temp = big_value->bits[i];
    big_value->bits[i] <<= shift_value;
    big_value->bits[i] |= memory;
    memory = temp >> (32 - shift_value);
  }
}

int s21_int_shift_left(s21_big_decimal *big_value, int shift_value) {
  int error = 0;
  if (shift_value > 255) error = 1;
  unsigned memory = 0;
  int parts_big_decimal = 8;
  while (shift_value > 0 && shift_value <= 255) {
    int current_shift = (shift_value > 31) ? 31 : shift_value;
    for (int i = 0; i < parts_big_decimal; i++) {
      unsigned temp = big_value->bits[i];
      big_value->bits[i] <<= current_shift;
      big_value->bits[i] |= memory;
      memory = temp >> (32 - current_shift);
    }
    shift_value -= current_shift;
    if (memory != 0) error = 1;
  }
  return error;
}

// умножение на 10: a*10 = a*8 + a*2 или = a << 3 + a << 1; можно сделать через
// s21_mul
void s21_increase_scale_big_decimal(
    s21_big_decimal *big_value, int shift_value) {  // n -> shift_value = diff
  s21_big_decimal temp_1 = {{0}};
  s21_big_decimal temp_2 = {{0}};
  s21_big_decimal temp_res = {{0}};
  s21_zero_big_decimal(&temp_1);
  s21_zero_big_decimal(&temp_2);
  s21_zero_big_decimal(&temp_res);
  s21_copy_big_decimal(&temp_1, *big_value);
  s21_copy_big_decimal(&temp_2, *big_value);
  for (int i = 0; i < shift_value; i++) {
    s21_shift_left(&temp_1, 3);
    s21_shift_left(&temp_2, 1);
    s21_add_big_decimal(temp_1, temp_2, &temp_res);
    if (i < shift_value - 1)
      s21_copy_big_decimal(
          &temp_1, temp_res);  // если сдвиг > 1, то чтобы сдвигать новое число
    if (i < shift_value - 1) s21_copy_big_decimal(&temp_2, temp_res);
  }
  s21_copy_big_decimal(big_value, temp_res);
}

void s21_normalization(s21_big_decimal *big_value_1,
                       s21_big_decimal *big_value_2, int diff) {
  if (diff > 0) {
    s21_increase_scale_big_decimal(big_value_2, diff);
  } else if (diff < 0) {
    s21_increase_scale_big_decimal(big_value_1, -diff);
  }
}

int s21_post_normalization(s21_big_decimal *result, int scale) {
  s21_big_decimal one = {{0}};
  one.bits[0] = 1;
  s21_big_decimal temp_result = {{0}};
  int need_correction = 0;
  int ostatok = 0, ostatok_numbers = 0;
  while ((result->bits[0] || result->bits[1] || result->bits[2] ||
          result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 28) {
    if (ostatok == 5) ostatok_numbers = 1;
    ostatok = s21_div_ostatok(
        result);  // запоминаем остаток от деления на 10 // див_остаток_2
    if (ostatok != 0 && ostatok != 5) ostatok_numbers = 1;
    scale--;
    int ok = 1;
    if (result->bits[3] || result->bits[4] || result->bits[5] ||
        result->bits[6] || result->bits[7])
      ok = 0;
    if (scale == 28 && ok) {
      need_correction = 2;
    }
  }
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 0) {
    if (ostatok == 5) ostatok_numbers = 1;
    ostatok = s21_div_ostatok(result);
    if (ostatok != 0 && ostatok != 5) ostatok_numbers = 1;
    need_correction = 1;
    scale--;
  }
  if ((need_correction == 1) || need_correction == 2) {
    int nado = 0;
    if (ostatok > 5) nado = 1;
    if (ostatok == 5 && ostatok_numbers) nado = 1;
    if (ostatok == 5 && !ostatok_numbers && s21_get_bit_big(*result, 0)) {
      nado = 1;
    }
    if (nado == 1) {
      s21_add_big_decimal(*result, one, &temp_result);
      s21_copy_big_decimal(result, temp_result);
    }
  }
  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6] || result->bits[7])) {
    scale = -1;
  }
  return scale;
}

int s21_div_ostatok(s21_big_decimal *big_value_1) {
  unsigned int div_ostatok = 0;
  s21_big_decimal big_value_2 = {{0}}, big_result = {{0}};
  big_value_2.bits[0] = 10;
  int scale = 0, save_scale = 0, out = 0;
  int flag_result = 0;
  int new_temp = 0;
  int stavim_null = 0;
  int scale_memory = 0;  // scale_memory
  s21_big_decimal start_big_value_2 = {{0}}, temp = {{0}}, temp_result = {{0}},
                  temp_big_value_1 = {{0}};
  s21_copy_big_decimal(&start_big_value_2, big_value_2);
  for (int i = 0;
       i < 100 && s21_is_big_decimal_not_empty(*big_value_1) && !out;) {
    scale = s21_equation_bits_big_decimal(big_value_1, &big_value_2);
    stavim_null = scale;
    scale_memory += scale;
    s21_sub_big_decimal(*big_value_1, big_value_2, &temp_big_value_1);
    s21_copy_big_decimal(big_value_1, temp_big_value_1);
    if (new_temp == 0) {
      s21_set_bit_big(&temp, 0, 1);
      new_temp = 1;
    } else {
      s21_shift_big_dec_left(&temp, 1);
      if (stavim_null) {
        for (int i = 0; i < stavim_null; i++) {
          s21_shift_big_dec_left(&temp, 1);
        }
      }
      s21_set_bit_big(&temp, 0, 1);
    }
    if (s21_is_greater_or_equal_big_decimal(start_big_value_2, *big_value_1)) {
      save_scale += scale_memory;
      scale_memory = 0;
    }
    if (s21_is_greater_big_decimal(big_value_2, start_big_value_2)) {
      while (s21_is_greater_big_decimal(big_value_2, *big_value_1) &&
             s21_is_greater_big_decimal(
                 big_value_2,
                 start_big_value_2)) {  // изменил больше чем биг_валью_1
        s21_shift_big_dec_right(&big_value_2, 1);
        if (s21_is_greater_big_decimal(big_value_2, *big_value_1)) {
          s21_shift_big_dec_left(&temp, 1);
        }
      }
      flag_result = 1;
    }
    if (s21_is_greater_big_decimal(start_big_value_2, *big_value_1)) {
      if (!flag_result) {
        s21_copy_big_decimal(&big_result, temp);
        flag_result = 1;
        s21_zero_big_decimal(&temp);
      } else if (save_scale == 1) {
        div_ostatok = temp.bits[0];
        s21_zero_big_decimal(
            big_value_1);  // занулил результат, так как больше не надо !!!
        s21_copy_big_decimal(&big_value_2, start_big_value_2);
      } else {
        s21_increase_scale_big_decimal(&big_result, 1);
        s21_add_big_decimal(big_result, temp, &temp_result);
        s21_copy_big_decimal(&big_result, temp_result);
        s21_zero_big_decimal(&temp_result);
        div_ostatok = temp.bits[0];  // +++
        s21_zero_big_decimal(&temp);
        s21_copy_big_decimal(&big_value_2, start_big_value_2);
      }
    }
    if (save_scale == 28) out = 1;  // break;
    i++;
  }
  s21_copy_big_decimal(big_value_1, big_result);
  return div_ostatok;
}