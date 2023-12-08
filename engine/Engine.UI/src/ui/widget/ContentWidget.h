#pragma once

#include "Widget.h"
#include "core/Observable.h"
#include <ui/control/ControlContainer.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class ContentWidget:public Widget {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ContentWidget::GET_TYPE();
#pragma endregion

	private:
		ControlContainer* container = nullptr;
		Control* content = nullptr;

		inline void updateContent() {
			if (container) {
				container->Child = content;
			} else if (content) {
				content->Parent = nullptr;
			}
		}

	protected:
		virtual void loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) override;

		virtual void onLayoutChanged() override {
			if (container) {
				container->Child = nullptr;
				container->release();
				container = nullptr;
			}
			Control* layoutControl = layout.get();
			if (layoutControl)
				setPointer(container, (Ghurund::UI::ControlContainer*)layoutControl->find("container"));
			updateContent();
		}

	public:
		ContentWidget() {}

		ContentWidget(const ContentWidget& other):Widget(other),
			container((ControlContainer*)other.container->clone()) {
			Content = (Control*)other.content->clone();
		}

		~ContentWidget() {
			if (container)
				container->release();
			if (content)
				content->release();
		}

		inline void setContent(Control* content) {
			setPointer(this->content, content);
			updateContent();
		}

		inline Control* getContent() {
			return content;
		}

		__declspec(property(get = getContent, put = setContent)) Control* Content;

		using Control::find;

		virtual Control* find(const Ghurund::Core::AString& name) override;

		virtual Control* find(const Ghurund::Core::Type& type) override;
	};
}
