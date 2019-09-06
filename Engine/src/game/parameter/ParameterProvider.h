#pragma once

#include "core/Event.h"
#include "Parameter.h"
#include "core/collection/PointerArray.h"
#include "ParameterManager.h"

namespace Ghurund {
    class ResourceContext;
    class ResourceManager;
    class DirectoryPath;
    class MemoryInputStream;
    class MemoryOutputStream;
    
    enum class LoadOption;
    enum class SaveOption;

    class ParameterProvider {
    private:
        Event<ParameterProvider> onParametersChanged;

    protected:
        Status loadParameters(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        Status saveParameters(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

    public:
        virtual ~ParameterProvider() = default;

        virtual void initParameters(ParameterManager& parameterManager) {}

        virtual void updateParameters() {}

        virtual const PointerArray<Parameter*>& getParameters() const = 0;

        __declspec(property(get = getParameters)) PointerArray<Parameter*>& Parameters;

        Parameter* getParameter(const ASCIIString& name) {
            for (Parameter* p : Parameters) {
                if (p != nullptr && strcmp(p->ConstantName, name)==0)
                    return p;
            }

            return nullptr;
        }

        // called when parameter names or types were changed
        Event<ParameterProvider>& getOnParametersChanged() {
            return onParametersChanged;
        }

        __declspec(property(get = getOnParametersChanged)) Event<ParameterProvider>& OnParametersChanged;
    };
}