#pragma once

#include "core/string/String.h"
#include "core/string/StringView.h"

namespace Ghurund::Core {
	class MemoryOutputStream {
	private:
		size_t pointer = 0;
		uint8_t* data;	// uint8_t instead of void to easily manipulate pointer position
		size_t capacity, initial;
		float increase;

		inline void ensureRemainingCapacity(size_t size) {
			if (capacity < pointer + size) {
				capacity = std::max((size_t)(capacity * increase), capacity + size);
				uint8_t* data2 = new uint8_t[capacity];
				memcpy(data2, data, pointer);
				delete[] data;
				data = data2;
			}
		}

		template<typename T>
		inline void writePrimitive(const T& value) {
			size_t size = sizeof(T);
			ensureRemainingCapacity(size);
			*(T*)(data + pointer) = value;
			pointer += size;
		}

		MemoryOutputStream& operator=(const MemoryOutputStream& other) = delete;

	public:
		MemoryOutputStream(
			size_t initialSizeBytes = 100,
			float sizeIncrease = 1.4f
		):
			capacity(initialSizeBytes), initial(initialSizeBytes),
			increase(sizeIncrease), data(new uint8_t[initialSizeBytes]) {
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

		inline void writeUInt8(uint8_t value) {
			writePrimitive(value);
		}

		inline void writeInt32(int32_t value) {
			writePrimitive(value);
		}

		inline void writeUInt32(uint32_t value) {
			writePrimitive(value);
		}

		inline void writeInt64(int64_t value) {
			writePrimitive(value);
		}

		inline void writeUInt64(uint64_t value) {
			writePrimitive(value);
		}

		inline void writeFloat(float value) {
			writePrimitive(value);
		}

		inline void writeDouble(double value) {
			writePrimitive(value);
		}

		inline void writeBoolean(bool value) {
			writePrimitive(value);
		}

		inline void writeChars(const char* str) {
			size_t length = (strlen(str) + 1) * sizeof(char);
			writeBytes(str, length);
		}

		inline void writeAString(const AString& str) {
			writeBytes(str.Data, str.Size);
		}

		inline void writeAStringView(const AStringView& str) {
			writeBytes(str.Data, str.Length);
			char nullTerminator = 0;
			writeBytes(&nullTerminator, sizeof(char));
		}

		inline void writeWChars(const wchar_t* str) {
			size_t length = (wcslen(str) + 1) * sizeof(wchar_t);
			writeBytes(str, length);
		}

		inline void writeWString(const WString& str) {
			writeBytes(str.Data, str.Size * sizeof(wchar_t));
		}

		inline void writeWStringView(const WStringView& str) {
			writeBytes(str.Data, str.Length * sizeof(wchar_t));
			wchar_t nullTerminator = 0;
			writeBytes(&nullTerminator, sizeof(wchar_t));
		}

		inline void writeBytes(const void* data, size_t size) {
			ensureRemainingCapacity(size);
			memcpy(this->data + pointer, data, size);
			pointer += size;
		}

		template<typename T>
		void write(const T& value) {
			size_t size = sizeof(T);
			ensureRemainingCapacity(size);
			memcpy(data + pointer, &value, size);
			pointer += size;
		}
	};
}
