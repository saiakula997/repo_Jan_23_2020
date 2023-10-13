#include "utils.h"
#include "types.h"

typedef struct  print_struct{
    size_t count;
    char print_buf[1024];
} print_struct_t;
typedef __builtin_va_list va_list;

void _putchar(char ch);
void print(const char *format, ...);

volatile unsigned char * const UART0_PTR = (unsigned char *)0x101f1000;
volatile print_struct_t _print_hadler;

static void _print_uart0(const char *string)
{
    while (*string != '\0') {
        *UART0_PTR = *string;
        string++;
    }
}

void* memset(void *ptr, uint8_t value, size_t num){
    while (num){
        *((char*)ptr + (num--)) = value;
    }
    return NULL;
}

uint32_t strlen(char *src){
    uint32_t n=0;
    while (*(src+n) != '\0' && *(src+n) != '\n'){
        n++;
    }
    return n;
}

uint32_t strncpy(char *des, char *src, uint32_t n){
    while (n){
        *des = *src;
        des++;
        src++;
        n--;
    }  
    return n;
}

uint32_t strncmp(char *des, char *src, uint32_t n){
    while (n){
        if (*des != *src){
            break;
        }
        n--;
        des++;
        src++;
    }  
    return n;
}



void _putchar(char ch){
    _print_hadler.print_buf[_print_hadler.count++] = ch;   
}


void _print_uint32(uint32_t num){
    if(num<=0){
        return;
    }
    uint32_t digit = num%10;
    _print_uint32(num/10);
    _putchar('0'+digit);
}


void print(const char *format, ...){
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++; 
            if (*format == 'd') {
                int num = va_arg(args, int);
                if (num < 0) {
                    _putchar('-');
                    num = -num;
                }
                _print_uint32((uint32_t)num);
                // while (num > 0) {
                //     int digit = num % 10;
                //     _putchar('0' + digit);
                //     num /= 10;
                // }
            } else if (*format == 's') {
                char *str = va_arg(args, char *);
                while (*str) {
                    _putchar(*str);
                    str++;
                }
            } else if (*format == 'u') {
                unsigned int num = va_arg(args,  unsigned int);
                _print_uint32((uint32_t)num);
                //  while (num > 0) {
                //     int digit = num % 10;
                //     _putchar('0' + digit);
                //     num /= 10;
                // }
            }
        } else {
            _putchar(*format);
        }
        format++;
    }
    _print_uart0(_print_hadler.print_buf);
    memset(_print_hadler.print_buf, NULL, _print_hadler.count);
    _print_hadler.count=0;
    va_end(args);

}