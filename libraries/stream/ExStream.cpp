#include "ExStream.h"
#include "Common.h"

#include <stdarg.h>


#define PRINTF_BUF 128
#define WORD_BUF 80

ExStream* ExStream::sharedInstances[] = { 0 };
ExStream ExSerial = ExStream(Serial);

ExStream * ExStream::createInstance(uint8_t id, Stream * const stream) {
    if (id >= SHARED_INSTANCES)
        return nullptr;

    return sharedInstances[id] = new ExStream(stream);
}

ExStream * ExStream::getInstance(uint8_t id) {
    if (id >= SHARED_INSTANCES)
        return nullptr;

    return sharedInstances[id];
}

size_t ExStream::clear()
{
    int bytes = available();
    if (bytes == 0)
        return 0;

    uint8_t* buffer = new uint8_t[bytes];
    size_t bytesRead = readBytes(buffer, bytes);
    deleteArray(buffer);

    //exSerial.printf("Cleared %d bytes of %d\n", bytesRead, bytes);
    return bytesRead;
}

size_t ExStream::print(bool b) {
    return print((b)? "true" : "false");
}

size_t ExStream::println(bool b) {
    return println((b) ? "true" : "false");
}

//https://playground.arduino.cc/Main/Printf
void ExStream::printf(const char * format, ...) {
    char buf[PRINTF_BUF];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, PRINTF_BUF, format, args);
    va_end(args);
    print(buf);
}

String ExStream::readWord()
{
    char word[WORD_BUF + 1] = { 0 };
    for (uint8_t i = 0; (i < WORD_BUF) && available(); i++) {
        char c = read();
        switch (c)
        {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            if (i == 0) {
                i--;                //whitespaces in the beginning; skip them
            }
            else {
                //printf("The read word is '%s'\n", word);
                return String(word);
            }
            break;

        default:
            word[i] = c;
        }

    }

    //printf("THE read word is '%s'\n", word);
    return String(word);
}
