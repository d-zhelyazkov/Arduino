#pragma once

#include "Common.h"

template <typename T>
class Array {
    T* arr = nullptr;
    uint16_t elemCnt = 0;
    uint16_t capacity = 0;

public:
    Array(uint16_t capacity) : capacity(capacity) {
        arr = new T[capacity];
    }

    bool add(T element) {
        if (elemCnt == capacity)
            return false;

        arr[elemCnt++] = element;
        return true;
    }

    T get(uint16_t i) {
        if (i >= elemCnt)
            return arr[elemCnt -1];

        return arr[i];
    }

    bool remove(T element) {
        uint16_t i = getIx(element);
        return remove(i);
    }

    bool remove(uint16_t i) {
        if (i >= elemCnt)
            return false;

        elemCnt--;
        for (; i < elemCnt; i++) {
            arr[i] = arr[i + 1];
        }

        return true;
    }

    uint16_t getIx(T element) {
        uint16_t i;
        for (i = 0; i < elemCnt; i++) {
            if (element == arr[i])
                break;
        }
        return i;
    }

    uint16_t size() {
        return elemCnt;
    }

    ~Array() {
        deleteArray(arr);
    }
};