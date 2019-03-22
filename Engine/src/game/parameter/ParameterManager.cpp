#include "ParameterManager.h"

namespace Ghurund {
    const Ghurund::Type& ParameterManager::TYPE = Ghurund::Type([]() {return ghnew ParameterManager(); }, "ParameterManager");

    ParameterManager::ParameterManager() {
        XMFLOAT4 red(1,0,0,1);
        add(Parameter::PARTY_COLOR, ParameterType::COLOR)->setValue(&red);

        float zero = 0.0f;
        add(Parameter::RANDOM, ParameterType::FLOAT)->setValue(&zero);

        XMFLOAT2 zero2;
        add(Parameter::VIEWPORT_SIZE, ParameterType::FLOAT2)->setValue(&zero2);

        XMMATRIX identity = XMMatrixIdentity();
        add(Parameter::WORLD, ParameterType::MATRIX)->setValue(&identity);
        add(Parameter::WORLD_IT, ParameterType::MATRIX)->setValue(&identity);
        add(Parameter::VIEW_PROJECTION, ParameterType::MATRIX)->setValue(&identity);
    }

    ParameterManager::~ParameterManager() {
        for(size_t i = 0; i<parameters.Size; i++)
            delete parameters.getValue(i);
    }

    Parameter * ParameterManager::add(const ASCIIString & name, const ParameterType & type) {
        if(parameters.contains(name))
            return parameters.get(name);
        Parameter *parameter = ghnew Parameter(name, type);
        parameter->manager = this;
        parameter->index = parameters.Size;
        parameters.set(name, parameter);
        return parameter;
    }

    Parameter * ParameterManager::get(const ASCIIString & name) const {
        size_t index = parameters.indexOf(name);
        if(index==parameters.Size) {
            Logger::log(LogType::WARNING, _T("Parameter of name '%hs' is missing\n"), name);
            return nullptr;
        }
        return parameters.getValue(index);
    }
}