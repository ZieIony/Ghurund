#include "ghcpch.h"
#include "ApplicationWindow.h"

#include <windowsx.h>

namespace Ghurund::Core {
	const Ghurund::Core::Type& ApplicationWindow::GET_TYPE() {
		static auto PROPERTY_LAYERS = Property<ApplicationWindow, LayerList&>("Layers", &getLayers);
		static auto PROPERTY_APPLICATION = Property<ApplicationWindow, Ghurund::Core::Application*>("Application", &getApplication);

		static const Ghurund::Core::Type TYPE = TypeBuilder<ApplicationWindow>()
			.withProperty(PROPERTY_LAYERS)
			.withProperty(PROPERTY_APPLICATION)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool ApplicationWindow::onSizeChangedEvent() {
		__super::onSizeChangedEvent();
		layers.Size = Size;
		return true;
	}

	bool ApplicationWindow::onFocusedChangedEvent() {
		if (Focused) {
			layers.restoreFocus();
		} else {
			layers.clearFocus();
		}
		return true;
	}

	bool ApplicationWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
		bool consumed = layers.dispatchMouseButtonEvent(args);
		if (consumed && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
			SetCapture(Handle);
		} else {
			ReleaseCapture();
		}
		return consumed;
	}
}