#include "ImageView.h"
#include <core\ScopedPointer.h>

namespace Ghurund::UI {
    void ImageView::onMeasure() {
        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.x = std::max(minSize.x, image ? image->Width : 0.0f);
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.x = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.y = std::max(minSize.y, image ? image->Height : 0.0f);
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.y = (float)preferredSize.height;
        }
    }

    ImageView* ImageView::inflate(LayoutInflater& inflater, json& json) {
        ImageView* imageView = ghnew ImageView();
        if (json.contains("image")) {
            nlohmann::json image = json["image"];
            if (image.is_string()) {
                std::string imageString = image;
                imageView->Image = inflater.loadImage(imageString.c_str());
            }
        }
        inflater.loadControl(imageView, json);
        return imageView;
    }
}