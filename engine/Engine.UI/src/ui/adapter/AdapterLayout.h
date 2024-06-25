#pragma once

#include "ItemAdapter.h"
#include "ControlPool.h"

#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
	class AdapterLayout:public ControlGroup {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = AdapterLayout::GET_TYPE();
#pragma endregion

	private:
		ControlPool pool;
		ItemAdapter* itemAdapter = nullptr;

	protected:
		virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event);

		virtual void onDraw(ICanvas& canvas) override;

	public:
		Event<Control> onScrolled = Event<Control>(*this);

		inline ItemAdapter& getItemAdapter() {
			return *itemAdapter;
		}

		inline void setItemAdapter(ItemAdapter& itemAdapter) {
			if (this->itemAdapter != &itemAdapter) {
				//this->itemAdapter->removeAllChildren();
				this->itemAdapter = &itemAdapter;
			}
		}

		__declspec(property(get = getItemAdapter, put = setItemAdapter)) ItemAdapter& ItemAdapter;

		virtual void resolveConstraints(ConstraintGraph& graph, const Constraint& width, const Constraint& height) override;

		virtual void onLayout(float x, float y, float width, float height) override;

		void addChild(size_t adapterPosition, size_t groupPosition);

		void removeChild(size_t adapterPosition, size_t groupPosition);

		/*inline const FloatPoint& getScroll() const {
			return layoutManager->Scroll;
		}

		inline void setScroll(const FloatPoint& scroll) {
			setScroll(scroll.x, scroll.y);
		}

		inline void setScroll(float x, float y) {
			layoutManager->Scroll = { x, y };
		}

		__declspec(property(get = getScroll, put = setScroll)) const FloatPoint& Scroll;

		inline const FloatPoint& getMaxScroll() const {
			return layoutManager->MaxScroll;
		}

		__declspec(property(get = getMaxScroll)) const FloatPoint& MaxScroll;

		inline Event<Control>& getOnScrolled() {
			return onScrolled;
		}

		__declspec(property(get = getOnScrolled)) Event<Control>& OnScrolled;

		virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event);

		virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event);*/
	};
}