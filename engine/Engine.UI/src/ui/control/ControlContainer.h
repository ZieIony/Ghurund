#pragma once

#include "ControlContainerBase.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund::UI {
    class ControlContainer:public ControlContainerBase {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ControlContainer::GET_TYPE();
#pragma endregion

    protected:
        virtual void loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) override;

    public:
        using Control::find;

        virtual Control* find(const Ghurund::Core::AString& name) override;

        virtual Control* find(const Ghurund::Core::Type& type) override;
    };
}