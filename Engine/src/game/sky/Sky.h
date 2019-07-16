#pragma once

#include "graphics/entity/Camera.h"

namespace Ghurund {
	/*class Sky :public Model {
	private:
		ValueParameter* parameterViewProjection = nullptr;
		ValueParameter* parameterCameraPosition = nullptr;

		void finalize() {
			if (camera)
				camera->release();
		}

	protected:
		Camera* camera = nullptr;
		Camera* virtualCamera = ghnew Ghurund::Camera();
		float innerRadius = 6371, outerRadius = 6371 + 80, heightScale = 0.0001;

	public:
		~Sky() {
			finalize();
			if (virtualCamera)
				virtualCamera->release();
			if (parameterViewProjection)
				parameterViewProjection->release();
			if (parameterCameraPosition)
				parameterCameraPosition->release();
		}

		void init(ResourceContext& context, Camera* camera) {
			mesh = ghnew SphereMesh();
			mesh->init(context.Graphics, context.CommandList, 3);

			CullingEnabled = false;

			this->Camera = camera;
		}

		virtual void invalidate() override {
			finalize();
			camera = nullptr;

			parameterViewProjection = nullptr;
			parameterCameraPosition = nullptr;

			__super::invalidate();
		}

		virtual void initParameters(ParameterManager& parameterManager) override {
			__super::initParameters(parameterManager);
			if (parameterViewProjection != nullptr)
				return;

			parameterViewProjection = (ValueParameter*)parameterManager.getParameter(ParameterId::VIEW_PROJECTION.ConstantName);
			parameterCameraPosition = (ValueParameter*)parameterManager.getParameter(ParameterId::CAMERA_POSITION.ConstantName);
		}

		virtual void updateParameters() override {
			Scale = { outerRadius, outerRadius, outerRadius };
			virtualCamera->setPositionDirectionDistanceUp({ 0,camera->Position.y * heightScale + innerRadius, 0 }, camera->Direction, 1, camera->Up);
			virtualCamera->rebuild();
			parameterViewProjection->Value = &virtualCamera->ViewProjection;
			parameterCameraPosition->Value = &virtualCamera->Position;
			__super::updateParameters();
		}


		void setCamera(Camera* camera) {
			setPointer(this->camera, camera);
		}

		Camera* getCamera() const {
			return camera;
		}

		__declspec(property(get = getCamera, put = setCamera)) Camera* Camera;

		void setHeightScale(float scale) {
			heightScale = scale;
		}

		float getHeightScale()const {
			return heightScale;
		}

		__declspec(property(get = getHeightScale, put = setHeightScale)) float HeightScale;

		void setInnerRadius(float radius) {
			innerRadius = radius;
		}

		float getInnerRadius()const {
			return innerRadius;
		}

		__declspec(property(get = getInnerRadius, put = setInnerRadius)) float InnerRadius;

		void setOuterRadius(float radius) {
			outerRadius = radius;
		}

		float getOuterRadius()const {
			return outerRadius;
		}

		__declspec(property(get = getOuterRadius, put = setOuterRadius)) float OuterRadius;
	};*/
}