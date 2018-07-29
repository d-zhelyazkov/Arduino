#pragma once

#include "Arduino.h"
#include "StreamDecorator.h"

#define TIMEOUT 100
#define RECEIVE_TRIES 10
#define SHARED_INSTANCES 10


class ExStream : public StreamDecorator {

    static ExStream* sharedInstances[SHARED_INSTANCES];

public:

    static ExStream* createInstance(uint8_t id, Stream* const stream);
    static ExStream* getInstance(uint8_t id);

    ExStream(Stream& stream) : StreamDecorator(stream) {}
    ExStream(Stream* const stream) : StreamDecorator(*stream) {}

    using Stream::read;
    using Stream::print;
    using Stream::println;

    //returns:
    //0 - success
    //1 - timeout
    template<typename T>
    uint8_t ignore(uint16_t objectsCount) {
        T receivedArray[objectsCount];
        return read(receivedArray, objectsCount);
    }

    //returns:
    //0 - success
    //1 - timeout
    template<typename T>
    uint8_t read(T* result) {
        const uint16_t bytesCount = sizeof(T);
        byte bytes[bytesCount];
        for (int i = bytesCount - 1; i >= 0; i--)
        {
            if (!available()) {
                for (int trY = RECEIVE_TRIES; !available(); trY--) {
                    if (!trY)
                        return 1;
                    delay(TIMEOUT);
                }
            }
            bytes[i] = read();
        }

        memcpy(result, &bytes, bytesCount);
        return 0;
    }

    //returns:
    //0 - success
    //1 - timeout
    template<typename T>
    uint8_t read(T resultArray[], uint16_t arraySize) {
        for (int i = 0; i < arraySize; i++) {
            uint8_t res = read(&resultArray[i]);
            if (res)
                return res;
        }

        return 0;
    }

    String readWord();

    //clears the input stream
    //returns number of bytes cleared
    size_t clear();

    //prints "true"/"false"
    size_t print(bool b);

    //prints "true\n"/"false\n"
    size_t println(bool b);

    void printf(const char *format, ...);

};

extern ExStream ExSerial;