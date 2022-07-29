//
// Created by theor on 2022-07-28.
//

#ifndef SIM_ARDUINO_H
#define SIM_ARDUINO_H

#include <cstdio>
#include <iostream>
#include <cstdint>
#include "SDL_config.h"
#include <string>
#include <stdarg.h>

#define PROGMEM
unsigned long millis();
unsigned long random();
unsigned long random(long max);
unsigned long random(long min, long max);

#define __FlashStringHelper char*
class String {

public:
    const char * c_str() const
    {
        return reinterpret_cast<const char *>(_s.c_str());
    }

    size_t length() const
    {
        return _s.length();
    }
private:
    std::string _s;
};

class Print {

public:
/* default implementation: may be overridden */
    size_t Print::write(const uint8_t *buffer, size_t size)
    {
        size_t n = 0;
        while(size--) {
            n += write(*buffer++);
        }
        return n;
    }
    size_t Print::write(const char *buffer, size_t size)
    {
        size_t n = 0;
        while(size--) {
            n += write(*buffer++);
        }
        return n;
    }
    size_t Print::write(const char *buffer)
    {
        size_t n = 0;
        while(*buffer != 0) {
            n += write(*buffer++);
        }
        return n;
    }

    size_t Print::printf(const char *format, ...)
    {
        char loc_buf[64];
        char * temp = loc_buf;
        va_list arg;
        va_list copy;
        va_start(arg, format);
        va_copy(copy, arg);
        int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
        va_end(copy);
        if(len < 0) {
            va_end(arg);
            return 0;
        };
        if(len >= sizeof(loc_buf)){
            temp = (char*) malloc(len+1);
            if(temp == NULL) {
                va_end(arg);
                return 0;
            }
            len = vsnprintf(temp, len+1, format, arg);
        }
        va_end(arg);
        len = write((uint8_t*)temp, len);
        if(temp != loc_buf){
            free(temp);
        }
        return len;
    }

//    size_t Print::print(const __FlashStringHelper *ifsh)
//    {
//        return print(reinterpret_cast<const char *>(ifsh));
//    }

    size_t Print::print(const String &s)
    {
        return write(s.c_str(), s.length());
    }

    size_t Print::print(const char* str)
    {
        return write(str);
    }

    size_t Print::print(char c)
    {
        return write(c);
    }

    size_t Print::print(unsigned char b, int base)
    {
        return print((unsigned long) b, base);
    }

    size_t Print::print(int n, int base)
    {
        return print((long) n, base);
    }

    size_t Print::print(unsigned int n, int base)
    {
        return print((unsigned long) n, base);
    }

    size_t Print::print(long n, int base)
    {
        int t = 0;
        if (base == 10 && n < 0) {
            t = print('-');
            n = -n;
        }
        return printNumber(static_cast<unsigned long>(n), base) + t;
    }

    size_t Print::print(unsigned long n, int base)
    {
        if(base == 0) {
            return write(n);
        } else {
            return printNumber(n, base);
        }
    }

    size_t Print::print(long long n, int base)
    {
        int t = 0;
        if (base == 10 && n < 0) {
            t = print('-');
            n = -n;
        }
        return printNumber(static_cast<unsigned long long>(n), base) + t;
    }

    size_t Print::print(unsigned long long n, int base)
    {
        if (base == 0) {
            return write(n);
        } else {
            return printNumber(n, base);
        }
    }

    size_t Print::print(double n, int digits)
    {
        return printFloat(n, digits);
    }

//    size_t Print::println(const __FlashStringHelper *ifsh)
//    {
//        size_t n = print(ifsh);
//        n += println();
//        return n;
//    }

//    size_t Print::print(const Printable& x)
//    {
//        return x.printTo(*this);
//    }

//    size_t Print::print(struct tm * timeinfo, const char * format)
//    {
//        const char * f = format;
//        if(!f){
//            f = "%c";
//        }
//        char buf[64];
//        size_t written = strftime(buf, 64, f, timeinfo);
//        if(written == 0){
//            return written;
//        }
//        return print(buf);
//    }

    size_t Print::println(void)
    {
        return print("\r\n");
    }

    size_t Print::println(const std::string &s)
    {
        return println(s.c_str());
    }

    size_t Print::println(const String &s)
    {
        size_t n = print(s);
        n += println();
        return n;
    }

    size_t Print::println(const char c[])
    {
        size_t n = print(c);
        n += println();
        return n;
    }

    size_t Print::println(char c)
    {
        size_t n = print(c);
        n += println();
        return n;
    }

    size_t Print::println(unsigned char b, int base)
    {
        size_t n = print(b, base);
        n += println();
        return n;
    }

    size_t Print::println(int num, int base)
    {
        size_t n = print(num, base);
        n += println();
        return n;
    }

    size_t Print::println(unsigned int num, int base)
    {
        size_t n = print(num, base);
        n += println();
        return n;
    }

    size_t Print::println(long num, int base)
    {
        size_t n = print(num, base);
        n += println();
        return n;
    }

    size_t Print::println(unsigned long num, int base)
    {
        size_t n = print(num, base);
        n += println();
        return n;
    }

    size_t Print::println(long long num, int base)
    {
        size_t n = print(num, base);
        n += println();
        return n;
    }

    size_t Print::println(unsigned long long num, int base)
    {
        size_t n = print(num, base);
        n += println();
        return n;
    }

    size_t Print::println(double num, int digits)
    {
        size_t n = print(num, digits);
        n += println();
        return n;
    }

//    size_t Print::println(const Printable& x)
//    {
//        size_t n = print(x);
//        n += println();
//        return n;
//    }

//    size_t Print::println(struct tm * timeinfo, const char * format)
//    {
//        size_t n = print(timeinfo, format);
//        n += println();
//        return n;
//    }

// Private Methods /////////////////////////////////////////////////////////////

    size_t Print::printNumber(unsigned long n, uint8_t base)
    {
        char buf[8 * sizeof(n) + 1]; // Assumes 8-bit chars plus zero byte.
        char *str = &buf[sizeof(buf) - 1];

        *str = '\0';

        // prevent crash if called with base == 1
        if(base < 2) {
            base = 10;
        }

        do {
            char c = n % base;
            n /= base;

            *--str = c < 10 ? c + '0' : c + 'A' - 10;
        } while (n);

        return write(str);
    }

    size_t Print::printNumber(unsigned long long n, uint8_t base)
    {
        char buf[8 * sizeof(n) + 1]; // Assumes 8-bit chars plus zero byte.
        char* str = &buf[sizeof(buf) - 1];

        *str = '\0';

        // prevent crash if called with base == 1
        if (base < 2) {
            base = 10;
        }

        do {
            auto m = n;
            n /= base;
            char c = m - base * n;

            *--str = c < 10 ? c + '0' : c + 'A' - 10;
        } while (n);

        return write(str);
    }

    size_t Print::printFloat(double number, uint8_t digits)
    {
        size_t n = 0;

        if(isnan(number)) {
            return print("nan");
        }
        if(isinf(number)) {
            return print("inf");
        }
        if(number > 4294967040.0) {
            return print("ovf");    // constant determined empirically
        }
        if(number < -4294967040.0) {
            return print("ovf");    // constant determined empirically
        }

        // Handle negative numbers
        if(number < 0.0) {
            n += print('-');
            number = -number;
        }

        // Round correctly so that print(1.999, 2) prints as "2.00"
        double rounding = 0.5;
        for(uint8_t i = 0; i < digits; ++i) {
            rounding /= 10.0;
        }

        number += rounding;

        // Extract the integer part of the number and print it
        unsigned long int_part = (unsigned long) number;
        double remainder = number - (double) int_part;
        n += print(int_part);

        // Print the decimal point, but only if there are digits beyond
        if(digits > 0) {
            n += print(".");
        }

        // Extract digits from the remainder one at a time
        while(digits-- > 0) {
            remainder *= 10.0;
            int toPrint = int(remainder);
            n += print(toPrint);
            remainder -= toPrint;
        }

        return n;
    }

protected:
    virtual size_t write(uint8_t) = 0;
};

struct SerialT : public Print {
protected:

    virtual size_t write(uint8_t c){std::cout << (char)c; return 1; }
};
static SerialT Serial;
struct WifiT {
public:
   bool isConnected() { return true; }
};
static WifiT WiFi;

#endif //SIM_ARDUINO_H
