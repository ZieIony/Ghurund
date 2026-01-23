#pragma once

#include "ui/control/ControlContainerBase.h"
#include "ui/theme/ThemedValueProperty.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	using LayoutKey = AttributeKey<Control>;
	using ThemedLayout = ThemedValue<LayoutKey, IntrusivePointer<Control>>;

	template<>
	IntrusivePointer<Control> resolveThemeValue(const Theme& theme, const LayoutKey& key);

	class Widget:public ControlContainerBase {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Widget::GET_TYPE();
#pragma endregion

	private:
		inline void setThemedLayout(const ThemedLayout& layout) {
			if (layout.Key) {
				setLayout(*layout.Key);
			} else {
				setLayout(layout.Value.get());
			}
		}

	protected:
		ThemedValueProperty<LayoutKey, IntrusivePointer<Control>> layout;

		Widget() {}

		Widget(const Widget& other):ControlContainerBase(other), layout(other.layout) {}

		void updateLayout();

		virtual void onLoaded() override;

		virtual void onThemeChanged() override;

		virtual void onLayoutChanged() {}

	public:
		inline void setLayout(LayoutKey layout) {
			this->layout.set(layout);
			updateLayout();
		}

		inline void setLayout(NotNull<Control> layout) {
			this->layout.set(IntrusivePointer(layout.get()));
			layout->addReference();
			updateLayout();
		}

		__declspec(property(put = setLayout)) Control* Layout;

		virtual PartialConstraintSet makeDefaultConstraints() const override {
			return ConstraintSetInitializer{
				.width = makeIntrusive<ParentWidthConstraint>(),
				.height = makeIntrusive<ParentHeightConstraint>()
			};
		}
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::ThemedLayout>();
}
