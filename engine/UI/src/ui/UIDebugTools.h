#pragma once

#include "ui/UIContext.h"

namespace Ghurund::UI {
	class UIDebugTools {
	private:
		static inline std::unique_ptr<IStrokeStyle> strokeStyle;
		static inline std::unique_ptr<IStrokeStyle> strokeStyle2;
		static inline std::unique_ptr<IStrokeStyle> strokeStyle3;

		UIDebugTools() = delete;

	public:
		static inline bool drawConstraints = false;
		static inline Color colorConstraints = 0xaf0a75ad;
		static inline Color colorConstraints2 = 0xafcc0000;
		static inline Color colorConstraints3 = 0xaf91f5ad;

		static void init(IUIContext& context) {
			if (strokeStyle != nullptr)
				return;

			Array<float> dashes = { 3.0f, 4.0f };
			strokeStyle.reset(context.makeStrokeStyle(dashes));
			Array<float> dashes2 = { 3.0f, 2.0f };
			strokeStyle2.reset(context.makeStrokeStyle(dashes2));
			Array<float> dashes3 = { 1.0f, 1.0f };
			strokeStyle3.reset(context.makeStrokeStyle(dashes3));
		}

		static void uninit() {
			strokeStyle.reset();
			strokeStyle2.reset();
			strokeStyle3.reset();
		}

		static inline IStrokeStyle* getStrokeStyle() {
			return strokeStyle.get();
		}

		static inline IStrokeStyle* getStrokeStyle2() {
			return strokeStyle2.get();
		}

		static inline IStrokeStyle* getStrokeStyle3() {
			return strokeStyle3.get();
		}
	};
}