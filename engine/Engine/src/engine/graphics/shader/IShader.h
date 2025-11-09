#pragma once

#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class IShader:public Resource//, public ParameterProvider
    {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = IShader::GET_TYPE();
#pragma endregion

    private:
        bool isTransparencyEnabled = false;

        //Array<SharedPointer<Parameter>>* parameters = nullptr;
#ifdef _DEBUG
        bool* reported = nullptr;
#endif

        //void initConstants(ParameterManager& parameterManager);
        //void initConstants(ParameterManager& parameterManager, ShaderProgram& program);

    public:
        /*virtual void initParameters(ParameterManager& parameterManager) override;

        virtual void updateParameters() override {
            for (size_t i = 0; i < constantBuffers.Size; i++)
                constantBuffers[i]->updateParameters();
        }

        virtual const Array<SharedPointer<Parameter>>& getParameters() const override {
            return *parameters;
        }*/

        //bool set(Graphics& graphics, CommandList& commandList);

        bool getIsTransparencyEnabled() {
            return isTransparencyEnabled;
        }

        __declspec(property(get = getIsTransparencyEnabled)) bool IsTransparencyEnabled;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return IShader::FORMATS;
        }

    public:
		static const inline ResourceFormat FORMAT_SHADER = ResourceFormat(L"shader", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_HLSL = ResourceFormat(L"hlsl", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SHADER, FORMAT_HLSL };

        static const inline uint32_t VERSION = 1;
#pragma endregion
    };
}