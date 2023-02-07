#pragma once

#include "Feature.h"
#include "core/Concepts.h"
#include "core/SharedPointer.h"
#include "core/collection/Map.h"

#include <ranges>
#include <format>

namespace Ghurund::Core {
    class FeatureNotAvailableException:public std::exception {
    public:
        FeatureNotAvailableException(const char* message = nullptr):std::exception(message) {}
    };

    class FeatureCollection {
    private:
        List<SharedPointer<Feature>> features;

    public:
        inline void add(Feature* feature) {
            feature->addReference();
            features.add(SharedPointer(feature));
        }

        template<Derived<Feature> Type>
        inline Type& get() {
            size_t index = features.find([](const SharedPointer<Feature>& f) {
                return f->Type == Type::GET_TYPE();
            });
            if (index == features.Size)
                throw FeatureNotAvailableException(std::format("feature '{}' is not available", Type::GET_TYPE().Name).c_str());
            SharedPointer<Feature> feature = features[index];
            if (!feature->Initialized) {
                size_t firstNotInitialized = features.find([](const SharedPointer<Feature>& f) {
                    return !f->Initialized;
                });
                feature->init();
                features.removeAt(index);
                features.insert(firstNotInitialized, feature);
            }
            return *(Type*)feature.get();
        }

        inline void remove(Feature& feature) {
            feature.addReference();
            features.remove(SharedPointer(&feature));
        }

        void init() {
            for (auto& f : features)
                f->init();
        }

        void uninit() {
            for (auto& f : features | std::views::reverse)
                f->uninit();
        }
    };
}