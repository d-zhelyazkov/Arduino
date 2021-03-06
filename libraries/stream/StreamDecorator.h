#pragma once

#include "Stream.h"


//a char not found in a valid ASCII numeric field
#define NO_IGNORE_CHAR  '\x01' 


class StreamDecorator : 
    public Stream {

    Stream& decoratedStream;
    
public:

    StreamDecorator(Stream& stream) : decoratedStream(stream) {}

    Stream* getBaseStream() {
        return &decoratedStream;
    }


    virtual int available() { return decoratedStream.available(); }
    virtual int read() { return decoratedStream.read(); }
    virtual int peek() { return decoratedStream.peek(); }

    // parsing methods

    // sets maximum milliseconds to wait for stream data, default is 1 second
    virtual void setTimeout(unsigned long timeout) {
        decoratedStream.setTimeout(timeout);
    }

    virtual unsigned long getTimeout() {
        return decoratedStream.getTimeout(); 
    }

    // reads data from the stream until the target string is found
    virtual bool find(char *target) {
        return decoratedStream.find(target); 
    }
    virtual bool find(uint8_t *target) { 
        return decoratedStream.find(target);
    }

    // returns true if target string is found, false if timed out (see setTimeout)
    // reads data from the stream until the target string of given length is found
    virtual bool find(char *target, size_t length) {
        return decoratedStream.find(target, length);
    }
    // returns true if target string is found, false if timed out
    virtual bool find(uint8_t *target, size_t length) {
        return decoratedStream.find(target, length);
    }

    virtual bool find(char target) {
        return decoratedStream.find(target); 
    }
    // as find but search ends if the terminator string is found
    virtual bool findUntil(char *target, char *terminator) {
        return decoratedStream.findUntil(target, terminator);
    }
    virtual bool findUntil(uint8_t *target, char *terminator) {
        return decoratedStream.findUntil(target, terminator);
    }
    // as above but search ends if the terminate string is found
    virtual bool findUntil(char *target, size_t targetLen, char *terminate, size_t termLen) {
        return decoratedStream.findUntil(target, targetLen, terminate, termLen);
    }
    virtual bool findUntil(uint8_t *target, size_t targetLen, char *terminate, size_t termLen) {
        return decoratedStream.findUntil(target, targetLen, terminate, termLen); 
    }

    // returns the first valid (long) integer value from the current position.
    // lookahead determines how parseInt looks ahead in the stream.
    // See LookaheadMode enumeration at the top of the file.
    // Lookahead is terminated by the first character that is not a valid part of an integer.
    // Once parsing commences, 'ignore' will be skipped in the stream.
    virtual long parseInt(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR) {
        return decoratedStream.parseInt(lookahead, ignore);
    }

    // float version of parseInt
    virtual float parseFloat(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR) {
        return decoratedStream.parseFloat(lookahead, ignore);
    }
    
    // read chars from stream into buffer
    virtual size_t readBytes(char *buffer, size_t length) {
        return decoratedStream.readBytes(buffer, length);
    }
    // terminates if length characters have been read or timeout (see setTimeout)
    // returns the number of characters placed in the buffer (0 means no valid data found)
    virtual size_t readBytes(uint8_t *buffer, size_t length) {
        return decoratedStream.readBytes(buffer, length); 
    }
    // as readBytes with terminator character
    virtual size_t readBytesUntil(char terminator, char *buffer, size_t length) {
        return decoratedStream.readBytesUntil(terminator, buffer, length);
    }
    // terminates if length characters have been read, timeout, or if the terminator character  detected
    // returns the number of characters placed in the buffer (0 means no valid data found)
    virtual size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length) {
        return decoratedStream.readBytesUntil(terminator, buffer, length); 
    }

    // Arduino String functions to be added here
    virtual String readString() {
        return decoratedStream.readString();
    }
    virtual String readStringUntil(char terminator) {
        return decoratedStream.readStringUntil(terminator);
    }
    
    virtual int getWriteError() {
        return decoratedStream.getWriteError();
    }
    virtual void clearWriteError() {
        decoratedStream.clearWriteError();
    }

    //Print abstract method
    virtual size_t write(uint8_t b) {
        return decoratedStream.write(b);
    }
    virtual size_t write(const char *str) {
        return decoratedStream.write(str);
    }
    virtual size_t write(const uint8_t *buffer, size_t size) {
        return decoratedStream.write(buffer, size);
    }
    virtual size_t write(const char *buffer, size_t size) {
        return decoratedStream.write(buffer, size);
    }

    // default to zero, meaning "a single write may block"
    // should be overriden by subclasses with buffering
    virtual int availableForWrite() {
        return decoratedStream.availableForWrite();
    }

    virtual size_t print(const __FlashStringHelper* helper) {
        return decoratedStream.print(helper);
    }
    virtual size_t print(const String& str) {
        return decoratedStream.print(str);
    }
    virtual size_t print(const char* str) {
        return decoratedStream.print(str);
    }
    virtual size_t print(char c) {
        return decoratedStream.print(c);
    }
    virtual size_t print(unsigned char num, int format = DEC) {
        return decoratedStream.print(num, format);
    }
    virtual size_t print(int num, int format = DEC) {
        return decoratedStream.print(num, format);
    }
    virtual size_t print(unsigned int num, int format = DEC) {
        return decoratedStream.print(num, format);
    }
    virtual size_t print(long num, int format = DEC) {
        return decoratedStream.print(num, format);
    }
    virtual size_t print(unsigned long num, int format = DEC) {
        return decoratedStream.print(num, format);
    }
    virtual size_t print(double num, int places = 2) {
        return decoratedStream.print(num, places);
    }
    virtual size_t print(const Printable& printable) {
        return decoratedStream.print(printable);
    }

    virtual size_t println(const __FlashStringHelper* helper) {
        return decoratedStream.println(helper);
    }
    virtual size_t println(const String& str) {
        return decoratedStream.println(str);
    }
    virtual size_t println(const char* str) {
        return decoratedStream.println(str);
    }
    virtual size_t println(char c) {
        return decoratedStream.println(c);
    }
    virtual size_t println(unsigned char num, int format = DEC) {
        return decoratedStream.println(num, format);
    }
    virtual size_t println(int num, int format = DEC) {
        return decoratedStream.println(num, format);
    }
    virtual size_t println(unsigned int num, int format = DEC) {
        return decoratedStream.println(num, format);
    }
    virtual size_t println(long num, int format = DEC) {
        return decoratedStream.println(num, format);
    }
    virtual size_t println(unsigned long num, int format = DEC) {
        return decoratedStream.println(num, format);
    }
    virtual size_t println(double num, int places = 2) {
        return decoratedStream.println(num, places);
    }
    virtual size_t println(const Printable& printable) {
        return decoratedStream.println(printable);
    }
    virtual size_t println() {
        return decoratedStream.println();
    }

    virtual void flush() {
        decoratedStream.flush();
    }
};