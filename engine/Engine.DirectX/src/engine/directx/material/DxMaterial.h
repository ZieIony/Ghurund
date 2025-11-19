#pragma once

#include "engine/directx/shader/DxShader.h"
#include "engine/graphics/IMaterial.h"
#include "engine/parameter/ParameterManager.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Engine::DirectX;

    class DxMaterial:public IMaterial {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxMaterial::GET_TYPE();
#pragma endregion

    private:
        DxShader* shader = nullptr;
        bool isTransparencyEnabled = false;

        void finalize() {
            safeRelease(shader);
        }

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

    public:

        DxMaterial() {}

        DxMaterial(DxShader* shader) {
            setPointer(this->shader, shader);
        }

        ~DxMaterial() {
            finalize();
        }

        virtual void invalidate() {
            finalize();
            __super::invalidate();
        }

        virtual bool isValid() const override {
            return shader != nullptr && shader->Valid && __super::Valid;
        }

        virtual const ParameterCollection& getParameters() const override {
            return shader->Parameters;
        }

        bool set(CommandList& commandList, ParameterManager& parameterManager) {
            return shader->set(commandList, parameterManager);
        }

        DxShader* getShader() {
            return shader;
        }

        void setShader(DxShader* shader) {
            setPointer(this->shader, shader);
        }

        __declspec(property(get = getShader, put = setShader)) DxShader* Shader;

        virtual bool getIsTransparencyEnabled() const override {
            return shader->IsTransparencyEnabled;
        }

        inline const Array<VertexRole>& getLayout() const {
            return shader->Layout;
        }

        __declspec(property(get = getLayout)) const Array<VertexRole>& Layout;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return DxMaterial::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_MATERIAL = ResourceFormat(L"material", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_MATERIAL };

        static const inline uint32_t VERSION = 0;
#pragma endregion
    };
}