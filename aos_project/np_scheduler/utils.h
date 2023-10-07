#ifndef UTILS_H
#define UTILS_H

#include "types.h"

#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)

#define TICKS_S(n)  (int)(n*50)

void print(const char *format, ...);
void* memset(void *ptr, uint8_t value, size_t num);
extern void delay(int ticks); // 1Tick -> 20 ms 
extern void panic(void);

uint32_t strlen(char *src);
uint32_t strncpy(char *des, char *src, uint32_t n);
uint32_t strncmp(char *des, char *src, uint32_t n);

#endif