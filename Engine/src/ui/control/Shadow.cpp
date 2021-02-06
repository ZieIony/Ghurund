#include "Shadow.h"
#include "ui/LayoutLoader.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI {
    void Shadow::onLayout(float x, float y, float width, float height) {
        __super::onLayout(x, y, width, height);
        auto deviceContext = Context->Graphics.DeviceContext;
        if (FAILED(deviceContext->CreateSolidColorBrush(D2D1::ColorF(color), &fillBrush))) {
            Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateSolidColorBrush failed\n");
            return;
        }
        fillBrush->SetColor(D2D1::ColorF(color));
        fillBrush->SetOpacity((color >> 24) / 255.0f);

        image->invalidate();
        image->init(Context->Graphics, { (uint32_t)(width + ceil(radius) * 2), (uint32_t)(height + ceil(radius) * 2) }, DXGI_FORMAT_R8G8B8A8_UNORM);
        deviceContext->SetTarget(image->Data);
        deviceContext->BeginDraw();
        deviceContext->Clear();
        if (!shape)
            shape = ghnew Rect(Context->Graphics);
        shape->Bounds = D2D1::RectF(ceil(radius), ceil(radius), width + ceil(radius), height + ceil(radius));
        deviceContext->FillGeometry(shape->Path, fillBrush);
        deviceContext->EndDraw();
    }

    void Shadow::onDraw(Canvas& canvas) {
        if (!Color || Radius < 0.1f || !image)
            return;
        canvas.save();
        canvas.translate(-ceil(radius), -ceil(radius) + radius / 2);
        canvas.drawShadow(*image, radius, color);
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
            Color = loader.loadColor(colorAttr->Value());
        auto radiusAttr = xml.FindAttribute("radius");
        if (radiusAttr)
            Radius = radiusAttr->FloatValue();
        return Status::OK;
    }
}