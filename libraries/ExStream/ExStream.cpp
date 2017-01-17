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

size_t ExStream::print(bool b)
{
	switch (b) {
	case true:
		return stream->print("true");
	case false:
		return stream->print("false");
	}
}

size_t ExStream::println(bool b)
{
	switch (b) {
	case true:
		return stream->println("true");
	case false:
		return stream->println("false");
	}
}
