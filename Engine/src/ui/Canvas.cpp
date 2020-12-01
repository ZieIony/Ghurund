#include "Canvas.h"

#include "application/log/Logger.h"
#include "graphics/SwapChain.h"

namespace Ghurund::UI {
    Status Canvas::init(Graphics2D& graphics2d) {
        this->deviceContext = graphics2d.DeviceContext;
        this->graphics2d = &graphics2d;

        deviceContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        if (FAILED(deviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &fillBrush)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateSolidColorBrush failed\n");

        if(FAILED(deviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &tintEffect)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, "CreateEffect failed\n");

        deviceContext->CreateEffect(CLSID_D2D1Shadow, &shadowEffect);

        deviceContext->CreateEffect(CLSID_D2D1Flood, &floodEffect);
        floodEffect->SetValue(D2D1_FLOOD_PROP_COLOR, D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f));

        return Status::OK;
    }
}
