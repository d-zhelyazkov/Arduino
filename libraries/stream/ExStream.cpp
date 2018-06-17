#include "ExStream.h"
#include "Common.h"


#define PRINTF_BUF 80


ExStream* ExStream::sharedInstances[] = { 0 };
ExStream ExStream::exSerial = ExStream(Serial);

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

void ExStream::printf(const char * format, ...) {
    char buf[PRINTF_BUF];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, sizeof(buf), format, ap);
    for (char *p = &buf[0]; *p; p++) // emulate cooked mode for newlines
    {
        if (*p == '\n')
            write('\r');
        write(*p);
    }
    va_end(ap);
}
