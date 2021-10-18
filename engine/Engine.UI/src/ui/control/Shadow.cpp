#include "ghuipch.h"
#include "Shadow.h"

#include "ui/layout/LayoutLoader.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Shadow::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Shadow>();
        static const Ghurund::Core::Type& TYPE = TypeBuilder<Shadow>(NAMESPACE_NAME, GH_STRINGIFY(Shadow))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Shadow::Shadow(const ColorAttr& color) {
        preferredSize.width = PreferredSize::Width::FILL;
        preferredSize.height = PreferredSize::Height::FILL;
        Color = color;
        bitmap = ghnew Bitmap();
    }

    Shadow::~Shadow() {
        delete shape;
        delete color;
        if (bitmap)
            bitmap->release();
    }

    void Shadow::onLayout(float x, float y, float width, float height) {
        __super::onLayout(x, y, width, height);
        Ghurund::UI::Color c = color->getValue(*this);
        if (c.A == 0.0f || Radius < 0.1f || !Context)
            return;
        auto &deviceContext = Context->DeviceContext;
        if (!fillBrush && FAILED(deviceContext.CreateSolidColorBrush(D2D1::ColorF(c), &fillBrush))) {
            Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateSolidColorBrush failed\n");
            return;
        }
        fillBrush->SetColor(D2D1::ColorF(c));
        fillBrush->SetOpacity(c.A);

        bitmap->invalidate();
        bitmap->init(Context->DeviceContext, { (uint32_t)(width + ceil(radius) * 2), (uint32_t)(height + ceil(radius) * 2) }, DXGI_FORMAT_R8G8B8A8_UNORM);
        deviceContext.SetTarget(bitmap->Data);
        deviceContext.BeginDraw();
        deviceContext.Clear();
        if (!shape)
            shape = ghnew Rect(Context->D2DFactory);
        shape->Bounds = FloatRect{ ceil(radius), ceil(radius), width + ceil(radius), height + ceil(radius) };
        deviceContext.FillGeometry(shape->Path, fillBrush.Get());
        deviceContext.EndDraw();
    }

    void Shadow::onDraw(Canvas& canvas) {
        Ghurund::UI::Color c = color->getValue(*this);
        if (c.A == 0.0f || Radius < 0.1f || !bitmap)
            return;
        canvas.save();
        canvas.translate(-ceil(radius), -ceil(radius) + radius / 2);
        canvas.drawShadow(bitmap->Data, radius, c.Value);
        canvas.restore();
    }

    Status Shadow::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto shapeAttr = xml.FindAttribute("shape");
        if (shapeAttr)
            Shape = loader.loadShape(shapeAttr->Value());
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr)
            Color = *loader.loadColor(colorAttr->Value());
        auto radiusAttr = xml.FindAttribute("radius");
        if (radiusAttr)
            Radius = radiusAttr->FloatValue();
        return Status::OK;
    }
}