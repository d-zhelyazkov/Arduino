#pragma once

#include "Arduino.h"
#include "Stream.h"

#define TIMEOUT 100
#define RECEIVE_TRIES 10
#define SHARED_INSTANCES 10

class ExStream
{

    static ExStream* sharedInstances[SHARED_INSTANCES];
    Stream* mStream;

public:

    static ExStream* createInstance(uint8_t id, Stream* const stream);
    static ExStream* getInstance(uint8_t id);

    ExStream(Stream* const stream) : mStream(stream) {}
    
    Stream* getBaseStream() {
        return mStream;
    }

    //returns:
    //0 - success
    //1 - timeout
    template<typename ObjectType>
    uint8_t ignore(uint16_t ignoreObjectsCount) {
        ObjectType receivedArray[ignoreObjectsCount];
        return this->readObjects<ObjectType>(receivedArray, ignoreObjectsCount);
    }

    //returns:
    //0 - success
    //1 - timeout
    template<typename ObjectType>
    uint8_t readObject(ObjectType* result) {
        const uint16_t bytesCount = sizeof(ObjectType);
        byte bytes[bytesCount];
        for (int i = bytesCount - 1; i >= 0; i--)
        {
            if (!mStream->available()) {
                for (int trY = RECEIVE_TRIES; !mStream->available(); trY--) {
                    if (!trY)
                        return 1;
                    delay(TIMEOUT);
                }
            }
            bytes[i] = mStream->read();
        }

        memcpy(result, &bytes, bytesCount);
        return 0;
    }

    //returns:
    //0 - success
    //1 - timeout
    template<typename ObjectType>
    uint8_t readObjects(ObjectType resultArray[], uint16_t arraySize) {
        for (int i = 0; i < arraySize; i++) {
            uint8_t res = readObject<ObjectType>(resultArray + i);
            if (res)
                return res;
        }

        return 0;
    }

    long parseInt_W() {
        delay(TIMEOUT);
        return mStream->parseInt();
    }

    // float version of parseInt
    float parseFloat_W() {
        delay(TIMEOUT);
        return mStream->parseFloat();
    }

    size_t print(bool b);
    size_t println(bool b);
};
