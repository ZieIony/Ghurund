#include "ghuipch.h"
#include "TextBlock.h"

#include "core/reflection/Property.h"
#include "core/reflection/UniqueProperty.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	void TextBlock::refreshLayout() {
		auto theme = Theme;
		auto context = Context;
		if (theme && context) {
			this->textStyle.resolve(*theme);
			this->color.resolve(*theme);
			textLayout.Document = makeIntrusive<Ghurund::UI::TextDocument>(text, textStyle.get(), *color.get()).get();
			textLayout.PreferredSize = { std::numeric_limits<uint32_t>::max(), std::numeric_limits<uint32_t>::max() };
			textLayout.refresh();

			auto materialProvider = theme->Materials.get(Theme::MATERIAL_TEXT);
			auto material = materialProvider->get();
			textLayout.initMeshes(context->TextMeshFactory, context->TextureFactory, material.ref());
		}
	}

	void TextBlock::onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		textLayout.draw(group, parentPosition + Position);
	}

	const Ghurund::Core::Type& TextBlock::GET_TYPE() {
		static auto PROPERTY_TEXT = Property<TextBlock, const WString&>("Text", &getText, &setText);
		static auto PROPERTY_TEXT_STYLE = UniqueProperty<TextBlock, std::unique_ptr<TextStyleAttr>>("TextStyle", &setTextStyle);
		static auto PROPERTY_COLOR = Property<TextBlock, const ColorAttr&>("TextColor", &setTextColor);

		static const Ghurund::Core::Type TYPE = TypeBuilder<TextBlock>()
			.withProperty(PROPERTY_TEXT)
			.withProperty(PROPERTY_TEXT_STYLE)
			.withProperty(PROPERTY_COLOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void TextBlock::setTextColor(const ColorAttr& color) {
		this->color.set(color);
		refreshLayout();
	}

	void TextBlock::setTextStyle(std::unique_ptr<Ghurund::UI::TextStyleAttr> textStyle) {
		this->textStyle.set(std::move(textStyle));
		refreshLayout();
	}

	void TextBlock::dispatchContextChanged() {
		__super::dispatchContextChanged();
		refreshLayout();
	}
}