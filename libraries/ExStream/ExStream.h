#pragma once

#include "Arduino.h"
#include "Stream.h"

#define TIMEOUT 100
#define RECEIVE_TRIES 10
#define SHARED_INSTANCES 10

class ExStream : Stream
{

	static ExStream* sharedInstances[SHARED_INSTANCES];
	Stream* stream;

public:

	static ExStream* createInstance(uint8_t id, Stream* const stream);
	static ExStream* getInstance(uint8_t id);

	ExStream(Stream* const stream) : stream(stream) {}

	int available() { return stream->available(); }
	int read() { return stream->read(); }
	int peek() { return stream->peek(); }
	void flush() { stream->flush(); }
	size_t write(uint8_t byte) { return stream->write(byte); }
	size_t print(const char* text) { return stream->print(text); }
	size_t println(const char* text) { return stream->println(text); }
	size_t print(double real, int a = 2) { return stream->print(real, a); }
	size_t println(double real , int a = 2) { return stream->println(real, a); }
	size_t print(long num, int a = DEC) { return stream->print(num, a); }
	size_t println(long num, int a = DEC) { return stream->println(num, a); }
	size_t print(char ch) { return stream->print(ch); }
	size_t println(char ch) { return stream->println(ch); }
	size_t print(int num, int a = DEC) { return stream->print(num, a); }
	size_t println(int num, int a = DEC) { return stream->println(num, a); }
	size_t print(unsigned int num, int a = DEC) { return stream->print(num, a); }
	size_t println(unsigned int num, int a = DEC) { return stream->println(num, a); }

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
			if (!this->available()) {
				for (int trY = RECEIVE_TRIES; !this->available(); trY--) {
					if (!trY)
						return 1;
					delay(TIMEOUT);
				}
			}
			bytes[i] = this->read();
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
		return stream->parseInt();
	}

	float parseFloat_W() {
		delay(TIMEOUT);
		return stream->parseFloat();
	}
	// float version of parseInt

	size_t print(bool b);
	size_t println(bool b);
};
