#pragma once

#include "Feature.h"
#include "FeatureFactory.h"
#include "core/IntrusivePointer.h"
#include "core/SharedPointer.h"
#include "core/collection/Map.h"
#include "core/concepts/Concepts.h"
#include "core/logging/Formatter.h"

namespace Ghurund::Core {
	class FeatureNotAvailableException:public std::exception {
	public:
		FeatureNotAvailableException(const char* message = nullptr):std::exception(message) {}
	};

	class FeatureProvider {
	private:
		Application& app;
		Map<const Type*, SharedPointer<FeatureFactory>> factories;
		Map<const Type*, IntrusivePointer<Feature>> features;
		List<IntrusivePointer<Feature>> initialized;

		inline void init(IntrusivePointer<Feature>& feature) {
			if (!feature->Initialized) {
				try {
					feature->init();
					initialized.add(feature);
				} catch (std::exception e) {
					throw e;
				}
			}
		}

	public:
		FeatureProvider(Application& app):app(app) {}

		template<Derived<Feature> T>
		inline void add() {
			features.put(&T::TYPE, IntrusivePointer<Feature>(ghnew T()));
		}

		template<Derived<Feature> T, Derived<FeatureFactory> R>
		inline void add() {
			factories.put(&T::TYPE, SharedPointer<FeatureFactory>(ghnew R(app)));
		}

		template<Derived<Feature> T>
		inline T& get() {
			const Type& type = getType<T>();
			IntrusivePointer<Feature> feature = [&] {
				auto it = features.find(&type);
				if (it != features.end())
					return it->value;
				auto it2 = factories.find(&type);
				if (it2 == factories.end())
					throw FeatureNotAvailableException(std::format("feature '{}' is not available", T::TYPE.Name).c_str());
				auto feature = IntrusivePointer<Feature>(it2->value->make().release());
				features.put(&type, feature);
				return feature;
			}();

			init(feature);
			return (T&)*feature.get();
		}

		template<Derived<Feature> T>
		inline void remove() {
			const Type& type = getType<T>();
			features.remove(&type);
			factories.remove(&type);
		}

		void init() {
			for (auto& f : factories) {
				if (!features.contains(f.key))
					features.put(f.key, IntrusivePointer<Feature>(f.value->make().release()));
			}
			for (auto& f : features)
				init(f.value);
		}

		void uninit() {
			for (auto rit = initialized.rbegin(); rit != initialized.rend(); rit++)
				(*rit)->uninit();
			initialized.clear();
		}
	};
}