#pragma once

#include "ui/control/ControlGroup.h"
#include "ui/layout/LayoutInflater.h"
#include "ui/Gravity.h"
#include "ui/layout/LayoutManager.h"

namespace Ghurund::UI {
    class Layout :public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Layout);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Layout>();

        Gravity gravity;
        LayoutManager* layoutManager = nullptr;

    public:
        ~Layout() {
            delete layoutManager;
        }

        inline Gravity& getGravity() {
            return gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        inline LayoutManager* getLayoutManager() {
            return layoutManager;
        }

        inline void setLayoutManager(LayoutManager* layoutManager) {
            delete this->layoutManager;
            this->layoutManager = layoutManager;
        }

        __declspec(property(get = getLayoutManager, put = setLayoutManager)) LayoutManager* LayoutManager;

        virtual void measure() {

        }

        virtual void layout(float x, float y, float width, float height) override {

        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<Layout>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(ControlGroup::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static Layout* inflate(LayoutInflater& inflater, json& json) {
            Layout* layout = ghnew Layout();
            inflater.loadChildren(layout, json);
            inflater.loadControl(layout, json);
            inflater.loadGravity(layout, json);
            return layout;
        }
    };
}