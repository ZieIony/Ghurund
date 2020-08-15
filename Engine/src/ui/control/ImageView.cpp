#include "ImageView.h"

namespace Ghurund::UI {
    ImageView* ImageView::inflate(LayoutInflater& inflater, json& json) {
        ImageView* imageView = ghnew ImageView();
        if (json.contains("image")) {
            nlohmann::json image = json["image"];
            if (image.is_string()) {
                std::string imageString = image;
                Gdiplus::Image* image = Gdiplus::Image::FromFile(UnicodeString(imageString.c_str()));
                imageView->Image = image;
            }
        }
        inflater.loadControl(imageView, json);
        return imageView;
    }
}