#pragma once

#include "core/collection/Set.h"

namespace Ghurund::UI {
    class Control;
    class ConstraintGraph;

    using namespace Ghurund::Core;

    class Constraint {
    protected:
        float value = 0.0f, initial = 0.0f;
        bool constant = false, skipDependencies = false;
        Set<Constraint*> dependencies;

    public:
        Constraint() {}

        Constraint(float initial, bool constant, bool skipDependencies):value(initial), initial(initial), constant(constant), skipDependencies(skipDependencies) {}

        virtual ~Constraint()// = 0 
        {}

        inline bool isConstant() const {
            return constant;
        }

        __declspec(property(get = isConstant)) bool Constant;

        virtual void resolve(Control& control, ConstraintGraph& graph) {}

        virtual void evaluate() {}

        inline void reset() {
            value = initial;
        }

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
        OffsetConstraint() {}
      
        OffsetConstraint(float initial, bool constant, bool skipDependencies):Constraint(initial, constant, skipDependencies) {}

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
        RatioConstraint() {}

        RatioConstraint(float initial, bool constant, bool skipDependencies):OffsetConstraint(initial, constant, skipDependencies) {}

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
        float baseInitial;

    public:
        MinMaxConstraint() {}

        MinMaxConstraint(float initial, bool constant, bool skipDependencies):RatioConstraint(initial, constant, skipDependencies), baseInitial(initial) {}

        inline float getMin() const {
            return min;
        }

        inline void setMin(float min) {
            if (min > max)
                throw InvalidParamException();
            this->min = min;
            initial = std::max(baseInitial, min);
        }

        __declspec(property(get = getMin, put = setMin)) float Min;

        inline float getMax() const {
            return max;
        }

        inline void setMax(float max) {
            if (max < min)
                throw InvalidParamException();
            this->max = max;
            initial = std::min(baseInitial, min);
        }

        __declspec(property(get = getMax, put = setMax)) float Max;
    };
}
