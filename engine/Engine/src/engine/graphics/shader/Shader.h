#pragma once

#include "ShaderSource.h"
#include "ConstantsCollection.h"

#include "core/resource/Resource.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class Shader:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Shader::GET_TYPE();
#pragma endregion

    protected:
        ShaderSource* source = nullptr;
        ConstantsCollection* constants = nullptr;

        inline void finalize() {
            if (source)
                source->release();
            if (constants)
                delete constants;
        }

        virtual bool getIsValidInternal() const override {
            return __super::getIsValidInternal() && constants != nullptr;
        }

        ~Shader() {
            finalize();
        }

    public:
        inline const ShaderSource* getSource() const {
            return source;
        }

        __declspec(property(get = getSource)) const ShaderSource* Source;

        inline ConstantsCollection& getConstants() {
            return *constants;
        }

        __declspec(property(get = getConstants)) ConstantsCollection& Constants;

        virtual void invalidate() override {
            finalize();
            source = nullptr;
            constants = nullptr;
            
            __super::invalidate();
        }
    };
}
