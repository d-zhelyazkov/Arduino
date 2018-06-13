#pragma once


template <typename T>
void deleteArray(T*& arr) { if (arr != nullptr) { delete[] arr; arr = nullptr; } }
template <typename T>
void deleteObject(T*& obj) { if (obj != nullptr) { delete obj; obj = nullptr; } }
template <typename T>
void deleteObject(T& obj) { delete &obj; }
