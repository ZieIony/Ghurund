#pragma once

#include "core/string/String.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class LayoutBinding {
    private:
        Control* root = nullptr;

    protected:
        inline void setRoot(Control* control) {
            setPointer(root, control);
        }

    public:
        LayoutBinding() {}

        LayoutBinding(Control* control) {
            root = control;
            root->addReference();
        }

        virtual ~LayoutBinding() = 0 {
            if (root)
                root->release();
        }

        inline Control* getRoot() {
            return root;
        }

        __declspec(property(get = getRoot, put = setRoot)) Control* Root;

        virtual Control* find(const AString& name) {
            return nullptr;
        }

        virtual Control* find(const Ghurund::Type& type) {
            return nullptr;
        }

        virtual Status loadContent(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
            return Status::OK;
        }
    };
}
