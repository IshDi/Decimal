#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define MINUS 0x80000000     // 10000000 00000000 00000000 00000000
#define SC 0x00ff0000        // 00000000 11111111 00000000 00000000
#define MAX4BITE 0xffffffff  // 11111111 11111111 11111111 11111111

#define EXP_HEX 0xff
#define MINUS_HEX 0x1
#define PLUS_HEX 0x0
#define SCALE_HEX 0x0000ff00

#define FALSE 0
#define TRUE 1
#define MAX_EXP 28
#define OK 0
#define POSITIVE 0
#define ERROR 1
#define NEGATIVE 1
#define TOO_LARGE_OR_POS_INF 1
#define TOO_SMALL_OR_NEG_INF 2
#define DIV_BY_ZERO 3
#define INT256_MAX_BITS 256
#define DECIM_MAX_BITS 96

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

void s21_zero_decimal(s21_decimal *value);
int s21_get_sign(s21_decimal value);
void s21_set_sign(s21_decimal *value);
int s21_get_scale(s21_decimal value);
void s21_set_scale(s21_decimal *value, int scale);
int s21_get_bit(s21_decimal value, int index);  // см.
void s21_set_bit(s21_decimal *value, int index, int bit);
int s21_is_zero(s21_decimal value);
void s21_copy_decimal(s21_decimal *value_1, s21_decimal value_2);

void s21_zero_big_decimal(s21_big_decimal *value);
int s21_get_bit_big(s21_big_decimal value, int index);
void s21_set_bit_big(s21_big_decimal *value, int index, int bit);
void s21_import_to_big_decimal(s21_decimal value_1, s21_big_decimal *value_2);
void s21_import_to_decimal(s21_decimal *value_1, s21_big_decimal value_2);
void s21_copy_big_decimal(s21_big_decimal *value_1, s21_big_decimal value_2);
void s21_shift_left(s21_big_decimal *big_value, int shift_value);
int s21_int_shift_left(s21_big_decimal *big_value, int shift_value);
void s21_increase_scale_big_decimal(s21_big_decimal *big_value,
                                    int shift_value);

void s21_normalization(s21_big_decimal *big_value_1,
                       s21_big_decimal *big_value_2, int diff);
int s21_post_normalization(s21_big_decimal *result, int scale);
int s21_is_greater_big_decimal(s21_big_decimal value_1,
                               s21_big_decimal value_2);
int s21_equation_bits_big_decimal(s21_big_decimal *big_value_1,
                                  s21_big_decimal *big_value_2);
int s21_is_big_decimal_not_empty(s21_big_decimal value);
int s21_is_greater_or_equal_big_decimal(s21_big_decimal big_value_1,
                                        s21_big_decimal big_value_2);
void s21_shift_big_dec_right(s21_big_decimal *big_value, int num);
int s21_shift_big_dec_left(s21_big_decimal *big_value, int num);
int s21_div_ostatok(s21_big_decimal *big_value_1);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                        s21_big_decimal *result);

int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);

// void printBinary(unsigned int num);

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

int get_sign(s21_decimal *dec);
void set_sign(s21_decimal *dec, unsigned int sign);
int get_scale(s21_decimal *dec);
int set_scale(s21_decimal *dec, int exponent);
int is_decimal_valid(s21_decimal *number);
int is_decimal_valid_to_convert_to_int(s21_decimal *dec);

typedef union {
  float f;
  unsigned int bits;
} f_bits;

#endif  // S21_DECIMAL_H