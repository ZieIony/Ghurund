#pragma once

#include "Widget.h"
#include "core/Observable.h"
#include <ui/control/ControlContainer.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class ContentWidget:public Widget {
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

		virtual void load(LayoutLoader& loader, ResourceManager& resourceManager, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) override;

		using Control::find;

		virtual Control* find(const Ghurund::Core::AString& name) override;

		virtual Control* find(const Ghurund::Core::Type& type) override;

		static const Ghurund::Core::Type& GET_TYPE();

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;
	};
}
