#pragma once

#include "core/Exceptions.h"
#include "core/string/String.h"

#include <stdint.h>
#include <string.h>
#include <memory.h>
#include <algorithm>

namespace Ghurund::Core {
	class MemoryStream {
	protected:
		size_t pointer = 0;
	};

	class MemoryInputStream:public MemoryStream {
	private:
		const uint8_t* data;
		size_t size;

		template<typename T>
		inline void assertAvailable(size_t count = 1) {
#ifdef _DEBUG
			if (pointer + count * sizeof(T) > size)
				throw IOException("read out of range");
#endif
		}

	public:
		MemoryInputStream(const void* data, size_t size) {
			this->data = (uint8_t*)data;
			this->size = size;
		}

		inline void set(size_t bytes) {
			pointer = bytes;
		}

		inline size_t getBytesRead() const {
			return pointer;
		}

		__declspec(property(get = getBytesRead)) size_t BytesRead;

		inline size_t getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) size_t Size;

		inline size_t getAvailable() const {
			return size - pointer;
		}

		__declspec(property(get = getAvailable)) size_t Available;

		inline int32_t readInt() {
			assertAvailable<int32_t>();
			int32_t i = *(int32_t*)(data + pointer);
			pointer += sizeof(int32_t);
			return i;
		}
		inline uint32_t readUInt() {
			assertAvailable<uint32_t>();
			uint32_t i = *(uint32_t*)(data + pointer);
			pointer += sizeof(uint32_t);
			return i;
		}
		inline int64_t readLong() {
			assertAvailable<int64_t>();
			int64_t i = *(int64_t*)(data + pointer);
			pointer += sizeof(int64_t);
			return i;
		}
		inline uint64_t readULong() {
			assertAvailable<uint64_t>();
			uint64_t i = *(uint64_t*)(data + pointer);
			pointer += sizeof(uint64_t);
			return i;
		}
		inline float readFloat() {
			assertAvailable<float>();
			float i = *(float*)(data + pointer);
			pointer += sizeof(float);
			return i;
		}
		inline double readDouble() {
			assertAvailable<double>();
			double i = *(double*)(data + pointer);
			pointer += sizeof(double);
			return i;
		}
		inline bool readBoolean() {
			assertAvailable<bool>();
			bool i = *(bool*)(data + pointer);
			pointer += sizeof(bool);
			return i;
		}
		inline AString readASCII() {
			char* i = (char*)(data + pointer);
			size_t slen = strlen(i);
			size_t available = Available;
			if (slen >= available) {
				pointer += available * sizeof(char);
				return AString(i, available);
			} else {
				pointer += (slen + 1) * sizeof(char);
				return AString(i, slen);
			}
		}
		inline WString readUnicode() {
			wchar_t* i = (wchar_t*)(data + pointer);
			size_t slen = wcslen(i);
			size_t available = Available;
			if (slen >= available) {
				pointer += available * sizeof(wchar_t);
				return WString(i, available);
			} else {
				pointer += (slen + 1) * sizeof(wchar_t);
				return WString(i, slen);
			}
		}
		inline const void* readBytes(unsigned int length) {
			assertAvailable<int32_t>();
			void* dataToReturn = (void*)(data + pointer);
			pointer += length;
			return dataToReturn;
		}
		template<typename T>
		T& read() {
			assertAvailable<T>();
			T* dataToReturn = (T*)(data + pointer);
			pointer += sizeof(T);
			return *dataToReturn;
		}

		inline const void* getData() const {
			return (uint8_t*)data;
		}

		_declspec(property(get = getData)) const void* Data;
	};

	class MemoryOutputStream:public MemoryStream {
	private:
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