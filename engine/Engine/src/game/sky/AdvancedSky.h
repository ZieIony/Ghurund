#pragma once

#include "Sky.h"
#include "graphics/Materials.h"

namespace Ghurund {
	/*class AdvancedSky :public Sky {
	private:
		XMFLOAT3 sunDirection = { 1,1,1 };

		ValueParameter* parameterSunDirection = nullptr;
		ValueParameter* parameterInnerRadius = nullptr;
		ValueParameter* parameterOuterRadius = nullptr;

		void finalize() {
			if (parameterSunDirection)
				parameterSunDirection->release();
			if (parameterInnerRadius)
				parameterInnerRadius->release();
			if (parameterOuterRadius)
				parameterOuterRadius->release();
		}

	public:
		~AdvancedSky() {
			finalize();
		}

		void init(Ghurund::Camera* camera) {
			__super::init(context, camera);

			material = Materials::makeAdvancedSky(context);

			initParameters(context.ParameterManager);
			material->OnParametersChanged.add([&](ParameterProvider& provider) {
				initParameters(context.ParameterManager);
				});
			Valid = true;
		}

		virtual void invalidate() override {
			finalize();
			parameterSunDirection = nullptr;
			parameterInnerRadius = nullptr;
			parameterOuterRadius = nullptr;

			__super::invalidate();
		}

		virtual void initParameters(ParameterManager& parameterManager) override {
			if (parameterSunDirection != nullptr)
				return;

			parameterSunDirection = (ValueParameter*)material->getParameter("sunDirection");
			parameterInnerRadius = (ValueParameter*)material->getParameter("innerRadius");
			parameterOuterRadius = (ValueParameter*)material->getParameter("outerRadius");
			__super::initParameters(parameterManager);
		}

		virtual void updateParameters() override {
			parameterSunDirection->setValue(&sunDirection);
			parameterInnerRadius->setValue(&innerRadius);
			parameterOuterRadius->setValue(&outerRadius);
			__super::updateParameters();
		}

		void setSunDirection(const XMFLOAT3& dir) {
			sunDirection = dir;
		}

		const XMFLOAT3& getSunDirection() const {
			return sunDirection;
		}

		__declspec(property(get = getSunDirection, put = setSunDirection)) XMFLOAT3 SunDirection;
	};*/
}