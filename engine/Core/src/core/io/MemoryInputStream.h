#pragma once

#include "core/exception/Exceptions.h"
#include "core/string/String.h"

namespace Ghurund::Core {
	class MemoryInputStream {
	private:
		size_t pointer = 0;
		const uint8_t* data;
		size_t size;

		template<typename T>
		inline void assertAvailable(size_t count = 1) {
#ifdef _DEBUG
			if (pointer + count * sizeof(T) > size)
				throw IOException("read out of range");
#endif
		}

		template<typename T>
		inline T readPrimitive() {
			size_t size = sizeof(T);
			assertAvailable<T>();
			T value = *(T*)(data + pointer);
			pointer += size;
			return value;
		}

		MemoryInputStream& operator=(const MemoryInputStream& other) = delete;

	public:
		MemoryInputStream(const void* data, size_t size) {
			this->data = (uint8_t*)data;
			this->size = size;
		}

		inline void setPosition(size_t position) {
			pointer = position;
		}

		inline size_t getPosition() const {
			return pointer;
		}

		__declspec(property(get = getPosition, put = setPosition)) size_t Position;

		inline size_t getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) size_t Size;

		inline size_t getAvailable() const {
			return size - pointer;
		}

		__declspec(property(get = getAvailable)) size_t Available;

		inline uint8_t readUInt8() {
			return readPrimitive<uint8_t>();
		}

		inline int32_t readInt32() {
			return readPrimitive<int32_t>();
		}

		inline uint32_t readUInt32() {
			return readPrimitive<uint32_t>();
		}

		inline int64_t readInt64() {
			return readPrimitive<int64_t>();
		}

		inline uint64_t readUInt64() {
			return readPrimitive<uint64_t>();
		}

		inline float readFloat() {
			return readPrimitive<float>();
		}

		inline double readDouble() {
			return readPrimitive<double>();
		}

		inline bool readBoolean() {
			return readPrimitive<bool>();
		}

		inline AString readAString() {
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

		inline WString readWString() {
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

		inline const void* readBytes(size_t size) {
			assertAvailable<uint8_t>(size);
			void* dataToReturn = (void*)(data + pointer);
			pointer += size;
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
			return data;
		}

		_declspec(property(get = getData)) const void* Data;
	};
}
