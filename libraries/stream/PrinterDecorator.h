#pragma once

#include "Print.h"


class PrinterDecorator : public Print {

    Print& decoratedPrinter;

public:

    PrinterDecorator(Print& decoratedPrinter) :
        decoratedPrinter(decoratedPrinter) {}


    virtual int getWriteError() {
        return decoratedPrinter.getWriteError(); 
    }
    virtual void clearWriteError() {
        decoratedPrinter.clearWriteError(); 
    }

    virtual size_t write(uint8_t B) {
        return decoratedPrinter.write(B); 
    }
    virtual size_t write(const char *str) {
        return decoratedPrinter.write(str);
    }
    virtual size_t write(const uint8_t *buffer, size_t size) {
        return decoratedPrinter.write(buffer, size);
    }
    virtual size_t write(const char *buffer, size_t size) {
        return decoratedPrinter.write(buffer, size);
    }

    // default to zero, meaning "a single write may block"
    // should be overriden by subclasses with buffering
    virtual int availableForWrite() {
        return decoratedPrinter.availableForWrite();
    }

    virtual size_t print(const __FlashStringHelper* helper) {
        return decoratedPrinter.print(helper);
    }
    virtual size_t print(const String& str) {
        return decoratedPrinter.print(str);
    }
    virtual size_t print(const char* str) {
        return decoratedPrinter.print(str);
    }
    virtual size_t print(char c) {
        return decoratedPrinter.print(c);
    }
    virtual size_t print(unsigned char num, int format = DEC) {
        return decoratedPrinter.print(num, format);
    }
    virtual size_t print(int num, int format = DEC) {
        return decoratedPrinter.print(num, format);
    }
    virtual size_t print(unsigned int num, int format = DEC) {
        return decoratedPrinter.print(num, format);
    }
    virtual size_t print(long num, int format = DEC) {
        return decoratedPrinter.print(num, format);
    }
    virtual size_t print(unsigned long num, int format = DEC) {
        return decoratedPrinter.print(num, format);
    }
    virtual size_t print(double num, int places = 2) {
        return decoratedPrinter.print(num, places);
    }
    virtual size_t print(const Printable& printable) {
        return decoratedPrinter.print(printable);
    }

    virtual size_t println(const __FlashStringHelper* helper) {
        return decoratedPrinter.println(helper);
    }
    virtual size_t println(const String& str) {
        return decoratedPrinter.println(str);
    }
    virtual size_t println(const char* str) {
        return decoratedPrinter.println(str);
    }
    virtual size_t println(char c) {
        return decoratedPrinter.println(c);
    }
    virtual size_t println(unsigned char num, int format = DEC) {
        return decoratedPrinter.println(num, format);
    }
    virtual size_t println(int num, int format = DEC) {
        return decoratedPrinter.println(num, format);
    }
    virtual size_t println(unsigned int num, int format = DEC) {
        return decoratedPrinter.println(num, format);
    }
    virtual size_t println(long num, int format = DEC) {
        return decoratedPrinter.println(num, format);
    }
    virtual size_t println(unsigned long num, int format = DEC) {
        return decoratedPrinter.println(num, format);
    }
    virtual size_t println(double num, int places = 2) {
        return decoratedPrinter.println(num, places);
    }
    virtual size_t println(const Printable& printable) {
        return decoratedPrinter.println(printable);
    }
    virtual size_t println() {
        return decoratedPrinter.println();
    }

    virtual void flush() { 
        decoratedPrinter.flush();
    }
};