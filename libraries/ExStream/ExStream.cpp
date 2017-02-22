#include "ExStream.h"


ExStream* ExStream::sharedInstances[] = { 0 };

ExStream * ExStream::createInstance(uint8_t id, Stream * const stream) {
    if (id >= SHARED_INSTANCES)
        return NULL;

    return sharedInstances[id] = new ExStream(stream);
}

ExStream * ExStream::getInstance(uint8_t id) {
    if (id >= SHARED_INSTANCES)
        return NULL;

    return sharedInstances[id];
}

size_t ExStream::print(bool b) {
    return mStream->print((b)? "true" : "false");
}

size_t ExStream::println(bool b) {
    return mStream->println((b) ? "true" : "false");
}
