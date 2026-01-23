#include "ghuipch.h"
#include "TextBlock.h"

#include "core/reflection/Property.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	void TextBlock::refreshLayout() {
		auto theme = Theme;
		auto context = Context;
		if (theme && context) {
			this->textStyle.resolve(*theme);
			this->color.resolve(*theme);
			textLayout.Document = makeIntrusive<Ghurund::UI::TextDocument>(text, textStyle.get().get(), color.get()).get();
			textLayout.PreferredSize = { std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max() };
			textLayout.refresh();

			auto materialProvider = theme->Materials.get(Theme::MATERIAL_TEXT);
			UIMaterial* material = materialProvider->get();
			textLayout.initMeshes(context->TextMeshFactory, context->TextureFactory, material);
			material->release();
		}
	}

	void TextBlock::onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		textLayout.draw(group, parentPosition + Position);
	}

	const Ghurund::Core::Type& TextBlock::GET_TYPE() {
		static auto PROPERTY_TEXT = Property<TextBlock, const WString&>("Text", &getText, &setText);
		static auto PROPERTY_TEXT_STYLE = Property<TextBlock, const ThemedTextStyle&>("TextStyle", &setThemedTextStyle);
		static auto PROPERTY_COLOR = Property<TextBlock, const ThemedColor&>("TextColor", &setThemedTextColor);

		static const Ghurund::Core::Type TYPE = TypeBuilder<TextBlock>()
			.withProperty(PROPERTY_TEXT)
			.withProperty(PROPERTY_TEXT_STYLE)
			.withProperty(PROPERTY_COLOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void TextBlock::setTextStyle(Ghurund::UI::TextStyleKey textStyle) {
		this->textStyle.set(textStyle);
		refreshLayout();
	}

	void TextBlock::setTextStyle(IntrusivePointer<Ghurund::UI::TextStyle> textStyle) {
		this->textStyle.set(textStyle);
		refreshLayout();
	}

	void TextBlock::dispatchContextChanged() {
		__super::dispatchContextChanged();
		refreshLayout();
	}
}