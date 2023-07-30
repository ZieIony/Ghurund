#pragma once

#include "core/SharedPointer.h"
#include "core/collection/Set.h"

namespace Ghurund::UI {
    class Control;
    class ConstraintGraph;

    using namespace Ghurund::Core;

    class Constraint:public Pointer {
    protected:
        float value = 0.0f;
        bool constant = false, skipDependencies = false;
        Set<Constraint*> dependencies;

    public:
        Constraint() {}

        Constraint(bool constant, bool skipDependencies):constant(constant), skipDependencies(skipDependencies) {}

        virtual ~Constraint()// = 0 
        {}

        inline bool isConstant() const {
            return constant;
        }

        __declspec(property(get = isConstant)) bool Constant;

        virtual void resolve(Control& control, ConstraintGraph& graph) {}

        virtual void evaluate() {}

        Set<Constraint*>& getDependencies() {
            return dependencies;
        }

        __declspec(property(get = getDependencies)) Set<Constraint*>& Dependencies;

        inline void setValue(float value) {
            this->value = value;
        }

        inline float getValue() const {
            return value;
        }

        __declspec(property(get = getValue)) float Value;

        // for example wrap constraint can skip fill dependencies to not introduce cycles
        inline bool canSkipDependencies() const {
            return skipDependencies;
        }

        __declspec(property(get = canSkipDependencies)) bool CanSkipDependencies;
    };

    class OffsetConstraint:public Constraint {
    protected:
        float offset = 0.0f;

    public:
        OffsetConstraint() {}
      
        OffsetConstraint(bool constant, bool skipDependencies):Constraint(constant, skipDependencies) {}

        inline float getOffset() const {
            return offset;
        }

        inline void setOffset(float offset) {
            this->offset = offset;
        }

        __declspec(property(get = getOffset, put = setOffset)) float Offset;

        virtual void resolve(Control& control, ConstraintGraph& graph) override {
            value = offset;
        }
    };

    class RatioConstraint:public OffsetConstraint {
    protected:
        float ratio = 1.0f;

    public:
        RatioConstraint() {}

        RatioConstraint(bool constant, bool skipDependencies):OffsetConstraint(constant, skipDependencies) {}

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
        float min = std::numeric_limits<float>::lowest(), max = std::numeric_limits<float>::max();

    public:
        MinMaxConstraint() {}

        MinMaxConstraint(bool constant, bool skipDependencies):RatioConstraint(constant, skipDependencies) {}

        inline float getMin() const {
            return min;
        }

        inline void setMin(float min) {
            if (min > max)
                throw InvalidParamException();
            this->min = min;
            value = std::max(value, min);
        }

        __declspec(property(get = getMin, put = setMin)) float Min;

        inline float getMax() const {
            return max;
        }

        inline void setMax(float max) {
            if (max < min)
                throw InvalidParamException();
            this->max = max;
            value = std::min(value, min);
        }

        __declspec(property(get = getMax, put = setMax)) float Max;
    };
}
