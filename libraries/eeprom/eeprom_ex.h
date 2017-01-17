#pragma once

#include "Arduino.h"
#include "EEPROM.h"

template <typename T>
bool eeprom_get(uint16_t ix, T& data) {
	uint16_t realIx = ix * sizeof(T);
	if (realIx + sizeof(T) >= EEPROM.length())
		return false;

	EEPROM.get(realIx, data);
	return true;
}

template <typename T>
bool eeprom_set(uint16_t ix, T data) {
	uint16_t realIx = ix * sizeof(T);
	if (realIx + sizeof(T) >= EEPROM.length())
		return false;

	EEPROM.put(realIx, data);
	return true;
}

void eeprom_clear() {
	for (uint16_t i = 0; i < EEPROM.length(); i++) {
		EEPROM.update(i, 0);
	}
}