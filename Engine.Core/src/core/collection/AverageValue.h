#pragma once

#include <deque>

namespace Ghurund {
    template<class Type> class Value {
    public:
        virtual void set(Type value) = 0;
        virtual Type get() const = 0;
    };

    template<class Type>
    class AverageValue:public Value<Type> {
    private:
        std::deque<Type> values;
        size_t avgCount, update;

    public:
        AverageValue(size_t avgCount, size_t update = 1) {
            this->avgCount = avgCount;
            this->update = update;
        }

        void set(Type value) {
            values.push_back(value);
            if (values.size() == avgCount + update) {
                for (size_t i = 0; i < update; i++)
                    values.pop_front();
            }
        }

        Type get() const {
            if (values.empty())
                return Type();

            Type sum = 0;
            float weightSum = 0;
            size_t valueCount = std::min(values.size(), avgCount);
            for (size_t i = 0; i < valueCount; i++) {
                Type value = values[i];
                sum += value;
                float weight = (float)(i + 1) / valueCount;
                weightSum += weight;
            }
            return (Type)(sum / weightSum);
        }
    };
}