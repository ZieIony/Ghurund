#pragma once

#include <deque>

namespace Ghurund {
    template<class Type> class Value {
    public:
        virtual void set(Type value) = 0;
        virtual Type get() const = 0;
    };

    template<class Type> class AverageValue:Value<Type> {
    private:
        std::deque<Type> values;
        size_t totalValues;

    public:
        AverageValue(size_t totalValues) {
            this->totalValues = totalValues;
        }

        void set(Type value) {
            values.push_back(value);
            if(values.size()>totalValues)
                values.pop_front();
        }

        Type get() const {
            if(values.empty())
                return TYPE;

            Type sum = 0;
            float weightSum = 0;
            size_t valueCount = values.size();
            for(size_t i = 0; i<valueCount; i++) {
                Type value = values[i];
                sum += value;
                float weight = (float)(i+1)/valueCount;
                weightSum += weight;
            }
            return (Type)(sum/weightSum);
        }
    };
}