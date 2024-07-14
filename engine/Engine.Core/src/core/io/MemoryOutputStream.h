#pragma once

#include "core/string/String.h"

namespace Ghurund::Core {
	class MemoryOutputStream {
	private:
		size_t pointer = 0;
		uint8_t* data;
		size_t capacity, initial;

		inline void resize(size_t size) {
			if (capacity < pointer + size) {
				capacity += std::max(initial, size);
				uint8_t* data2 = new uint8_t[capacity];
				memcpy(data2, data, pointer);
				delete[] data;
				data = data2;
			}
		}

	public:
		MemoryOutputStream() {
			capacity = initial = 100;
			this->data = new uint8_t[initial];
		}

		~MemoryOutputStream() {
			delete[] data;
		}

		const void* getData() const {
			return data;
		}

		__declspec(property(get = getData)) const void* Data;

		inline size_t getBytesWritten() const {
			return pointer;
		}

		__declspec(property(get = getBytesWritten)) size_t BytesWritten;

		inline void writeInt(int32_t i) {
			resize(sizeof(int32_t));
			*(int32_t*)(data + pointer) = i;
			pointer += sizeof(int32_t);
		}
		inline void writeUInt(uint32_t i) {
			resize(sizeof(uint32_t));
			*(uint32_t*)(data + pointer) = i;
			pointer += sizeof(uint32_t);
		}
		inline void writeLong(int64_t i) {
			resize(sizeof(int64_t));
			*(int64_t*)(data + pointer) = i;
			pointer += sizeof(int64_t);
		}
		inline void writeULong(uint64_t i) {
			resize(sizeof(uint64_t));
			*(uint64_t*)(data + pointer) = i;
			pointer += sizeof(uint64_t);
		}
		inline void writeFloat(float i) {
			resize(sizeof(float));
			*(float*)(data + pointer) = i;
			pointer += sizeof(float);
		}
		inline void writeDouble(double i) {
			resize(sizeof(double));
			*(double*)(data + pointer) = i;
			pointer += sizeof(double);
		}
		inline void writeBoolean(bool i) {
			resize(sizeof(bool));
			*(bool*)(data + pointer) = i;
			pointer += sizeof(bool);
		}
		inline void writeASCII(const char* str) {
			size_t length = (strlen(str) + 1) * sizeof(char);
			writeBytes(str, length);
		}
		inline void writeUnicode(const wchar_t* str) {
			size_t length = (wcslen(str) + 1) * sizeof(wchar_t);
			writeBytes(str, length);
		}
		inline void writeBytes(const void* bytes, size_t length) {
			resize(length);
			memcpy((uint8_t*)data + pointer, bytes, length);
			pointer += length;
		}
		template<typename T>
		void write(const T& value) {
			size_t length = sizeof(T);
			resize(length);
			memcpy((uint8_t*)data + pointer, &value, length);
			pointer += length;
		}
	};
}