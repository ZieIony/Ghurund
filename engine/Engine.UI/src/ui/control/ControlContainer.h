#pragma once

#include "ControlContainerBase.h"

namespace Ghurund::Core {
    class ResourceManager;
}

namespace Ghurund::UI {
    class ControlContainer:public ControlContainerBase {
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ControlContainerBase::GET_TYPE();

    protected:
        virtual void onChildChanged() {}

    public:
        Event<ControlContainer> childChanged = Event<ControlContainer>(*this);
        
        inline Control* getChild() {
            return child;
        }

        inline const Control* getChild() const {
            return child;
        }

        inline void setChild(Control* child) {
            __super::setChild(child);
            onChildChanged();
            childChanged();
        }

        __declspec(property(get = getChild, put = setChild)) Control* Child;

        using Control::find;

        virtual Control* find(const Ghurund::Core::AString& name) override;

        virtual Control* find(const Ghurund::Core::Type& type) override;

        virtual void load(LayoutLoader& loader, ResourceManager& resourceManager, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) override;
    };
}