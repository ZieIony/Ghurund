#pragma once

namespace Ghurund {
    template<class Value>class BufferedValue {
    protected:
        size_t size;
        size_t index = 0;
        Value *v;

    public:
        BufferedValue() {
            v = nullptr;
            this->size = 0;
        }

        BufferedValue(Value *values, size_t size) {
            v = values;
            this->size = size;
        }

        BufferedValue(const BufferedValue &t1) {
            size = t1.size;
            index = t1.index;
            v = t1.v;
        }

        void init(Value *values, size_t size) {
            v = values;
            index = 0;
            this->size = size;
        }

        inline size_t getSize()const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        void next() {
            index++;
            index %= size;
        }

        Value &get() {
            return v[index];
        }

        Value *operator->() const {
            return &v[index];
        }

        size_t getCurrentIndex() {
            return index;
        }
    };

}