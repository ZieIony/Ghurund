#pragma once

#include "core/SharedPointer.h"
#include "ui/layout/constraint/Side.h"
#include "ui/Orientation.h"
#include "core/collection/Set.h"

namespace Ghurund::UI {
    class Control;
    class ControlGroup;
    class Guide;

    using namespace Ghurund::Core;

    class Constraint {
    protected:
        float value = 0.0f;
        bool skipDependencies = false;
        Set<Constraint*> dependencies;

    public:
        Constraint() {}

        Constraint(float initial, bool skipDependencies):value(initial), skipDependencies(skipDependencies) {}

        virtual ~Constraint()// = 0 
        {}

        virtual bool isConstant() const {
            return false;
        }

        __declspec(property(get = isConstant)) bool Constant;

        virtual void resolve(Control& control, List<Constraint*>& constraints) {}

        virtual void evaluate() {}

        Set<Constraint*>& getDependencies() {
            return dependencies;
        }

        __declspec(property(get = getDependencies)) Set<Constraint*>& Dependencies;

        inline float getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) float Value;

        inline bool canSkipDependencies() const {
            return skipDependencies;
        }

        __declspec(property(get = canSkipDependencies)) bool CanSkipDependencies;
    };

    class OffsetConstraint:public Constraint {
    protected:
        float offset = 0.0f;

    public:
        inline float getOffset() const {
            return offset;
        }

        inline void setOffset(float offset) {
            this->offset = offset;
        }

        __declspec(property(get = getOffset, put = setOffset)) float Offset;
    };

    class RatioConstraint:public OffsetConstraint {
    protected:
        float ratio = 1.0f;

    public:
        inline float getRatio() const {
            return ratio;
        }

        inline void setRatio(float ratio) {
            if (ratio <= 0.0f)
                throw InvalidParamException();
            this->ratio = ratio;
        }

        __declspec(property(get = getRatio, put = setRatio)) float Ratio;
    };

    class MinMaxConstraint:public RatioConstraint {
    protected:
        float min = 0.0f, max = std::numeric_limits<float>::max();

    public:
        inline float getMin() const {
            return min;
        }

        inline void setMin(float min) {
            if (min > max)
                throw InvalidParamException();
            this->min = min;
        }

        __declspec(property(get = getMin, put = setMin)) float Min;

        inline float getMax() const {
            return max;
        }

        inline void setMax(float max) {
            if (max < min)
                throw InvalidParamException();
            this->max = max;
        }

        __declspec(property(get = getMax, put = setMax)) float Max;
    };
}
