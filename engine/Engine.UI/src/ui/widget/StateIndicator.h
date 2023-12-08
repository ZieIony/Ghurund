#pragma once

#include "core/state/StateMachine.h"
#include "ui/animation/Animator.h"
#include "ui/animation/Animation.h"
#include "ui/control/ColorView.h"
#include "ui/control/InteractionHandler.h"

namespace Ghurund::UI {
	class StateIndicator:public Control {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = StateIndicator::GET_TYPE();
#pragma endregion

	private:
		struct IndicatorState {
			bool focused = false, pressed = false;

			auto operator<=>(const IndicatorState& other) const = default;
		};

		friend struct std::formatter<IndicatorState, char>;
		friend struct std::formatter<IndicatorState, wchar_t>;

		Color color;

	protected:
		Animator animator;
		ValueAnimation<Color> animation;
		State<bool> hoveredOrFocused = false;
		const InteractionHandler* interactionHandler = nullptr;
		StateMachine<IndicatorState> stateMachine = StateMachine<IndicatorState>({ false, false });

		EventHandler<State<bool>, bool> onHoveredFocusedHandler = [this](State<bool>&, const bool&) {
			hoveredOrFocused = interactionHandler->isHovered || interactionHandler->isFocused;
			return true;
		};

		EventHandler<State<bool>, bool> onStateChangedHandler = [this](State<bool>&, const bool&) {
			stateMachine.setState({ hoveredOrFocused, interactionHandler->isPressed });
			return true;
		};

		virtual void onThemeChanged() override;

		virtual void onDraw(ICanvas& canvas) override;

	public:
		Color idleColor = 0;
		Color focusedColor = 0;
		Color pressedColor = 0;

		StateIndicator();

		void setInteractionHandler(const InteractionHandler* interactionHandler);

		__declspec(property(put = setInteractionHandler)) const InteractionHandler& InteractionHandler;

		virtual void onUpdate(uint64_t time) override {
			animator.update(time);
		}

		inline const Color& getColor() {
			return color;
		}

		inline void setColor(const Color& color) {
			this->color = color;
		}

		__declspec(property(get = getColor, put = setColor)) const Color& Color;
	};

	class StateIndicatorOnAccent:public StateIndicator {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = StateIndicatorOnAccent::GET_TYPE();
#pragma endregion

	protected:
		virtual void onThemeChanged() override;
	};
}

template <>
struct std::formatter<Ghurund::UI::StateIndicator::IndicatorState, char>:std::formatter<const char*, char> {
	template <typename FormatContext>
	auto format(const Ghurund::UI::StateIndicator::IndicatorState& s, FormatContext& ctx) const {
		return std::string("{") + (s.focused ? "true" : "false") + ", " + (s.pressed ? "true" : "false") + "}";
	}
};

template <>
struct std::formatter<Ghurund::UI::StateIndicator::IndicatorState, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
	template <typename FormatContext>
	auto format(const Ghurund::UI::StateIndicator::IndicatorState& s, FormatContext& ctx) const {
		return std::wstring(_T("{")) + (s.focused ? _T("true") : _T("false")) + _T(", ") + (s.pressed ? _T("true") : _T("false")) + _T("}");
	}
};
