#include "ghepch.h"
#include "TagManager.h"

namespace Ghurund::Engine {
	void TagManager::removeTag(TagData* tag) {
		for (auto& c : tag->children)
			removeTag(c.value);
		tags.remove(tag->name);
		delete tag;
	}

	void TagManager::registerTag(const AString& name) {
		TagData* parent = nullptr;
		size_t index = 0;
		while (index != name.Size) {
			index = name.find('.', index);
			auto tagName = name.substring(0, index);
			auto it = tags.find(tagName);
			if (it != tags.end()) {
				parent = it->value;
			} else {
				auto tagData = ghnew TagData(tagName, parent);
				if (parent)
					parent->children.put(tagName, tagData);
				parent = tagData;
				tags.put(tagName, tagData);
			}
			index++;
		}
	}

	void TagManager::unregisterTag(const AString& name) {
		auto it = tags.find(name);
		if (it == tags.end()) {
			auto message = std::format(_T("Tag '{}' is not registered.\n"), name);
			Logger::log(LogType::WARNING, message.c_str());
			return;
		}

		if (it->value->parent)
			it->value->parent->children.remove(name);
		removeTag(it->value);
	}
}
