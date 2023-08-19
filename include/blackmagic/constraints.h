#pragma once

#include <stdint.h>

typedef long double         float80;

#define Interface(...) __VA_ARGS__

#define Float    Interface(float, double, float80)
#define Signed   Interface(char, short, int, long)
#define Unsigned Interface(uint8_t, uint16_t, unsigned, uint64_t)
#define Integer  Interface(Signed, Unsigned)
#define Number   Interface(Integer, Float)
