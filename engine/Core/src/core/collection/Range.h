#pragma once

namespace Ghurund::Core {
    template<typename Type>
    class Range {
    private:
        class iterator {
        private:
            Type i, b, step;
            int sign;

        public:
            iterator(Type i, Type b, int sign, Type step):i(i), b(b), sign(sign), step(step) {}

            inline Type operator*() const {
                return b + sign * i * step;
            }

            inline const iterator& operator++() {
                i++;
                return *this;
            }

            inline iterator operator++(int) {
                iterator copy(*this);
                i++;
                return copy;
            }

            inline bool operator==(const iterator& other) const {
                return i == other.i && b == other.b && sign == other.sign && step == other.step;
            }
        };

        Type b, step, count;
        int sign;

        inline Type getRange(Type begin, Type end) {
            return begin < end ? end - begin : begin - end;
        }

    public:
        Range(Type begin, Type end):b(begin), step(1) {
            sign = end > begin ? 1 : -1;
            count = getRange(begin, end);
        }

        Range(Type begin, Type end, Type step):b(begin), step(step) {
            if (step <= 0 || getRange(begin, end) < getRange(0, step))
                throw std::invalid_argument("step has to be > 0 and < abs(end-begin)");
            sign = end > begin ? 1 : -1;
            count = getRange(begin, end) / step;
        }

        inline iterator begin() {
            return iterator(0, b, sign, step);
        }

        inline iterator begin() const {
            return iterator(0, b, sign, step);
        }

        inline iterator end() {
            return iterator(count + 1, b, sign, step);
        }

        inline iterator end() const {
            return iterator(count + 1, b, sign, step);
        }
    };
}