#pragma once

#include "Feature.h"
#include "core/IntrusivePointer.h"
#include "core/collection/Map.h"
#include "core/concepts/Concepts.h"

#include <ranges>
#include <format>

namespace Ghurund::Core {
	class FeatureNotAvailableException:public std::exception {
	public:
		FeatureNotAvailableException(const char* message = nullptr):std::exception(message) {}
	};

	class FeatureCollection {
	private:
		List<IntrusivePointer<Feature>> features;

	public:
		inline void add(Feature* feature) {
			feature->addReference();
			features.add(IntrusivePointer(feature));
		}

		inline void addAll(std::initializer_list<Feature*> features) {
			for (Feature* f : features) {
				f->addReference();
				this->features.add(IntrusivePointer(f));
			}
		}

		template<Derived<Feature> T>
		inline T& get() {
			size_t index = features.find([](const IntrusivePointer<Feature>& f) {
				return f->Type == T::GET_TYPE();
				});
			if (index == features.Size)
				throw FeatureNotAvailableException(std::format("feature '{}' is not available", T::GET_TYPE().Name).c_str());
			IntrusivePointer<Feature> feature = features[index];
			if (!feature->Initialized) {
				size_t firstNotInitialized = features.find([](const IntrusivePointer<Feature>& f) {
					return !f->Initialized;
					});
				feature->init();
				features.removeAt(index);
				features.insert(firstNotInitialized, feature);
			}
			return *(T*)feature.get();
		}

		inline void remove(Feature& feature) {
			feature.addReference();
			features.remove(IntrusivePointer(&feature));
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