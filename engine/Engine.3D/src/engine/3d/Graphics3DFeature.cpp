#include "ghe3dpch.h"
#include "Graphics3DFeature.h"

#include "graphics/mesh/MeshComponentLoader.h"
#include "graphics/camera/CameraComponent3DLoader.h"
#include "graphics/transform/TransformComponent3DLoader.h"
#include "core/object/IntrusivePointer.h"

namespace Ghurund::Engine::_3D {
	using namespace Ghurund::Core;

    const Ghurund::Core::Type& Graphics3DFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Graphics3DFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

	void Graphics3DFeature::uninitGraphicsFeature() {
		/*sceneLoader.componentLoaders.remove(L"MeshComponent");
		sceneLoader.componentLoaders.remove(L"CameraComponent3D");
		sceneLoader.componentLoaders.remove(L"TransformComponent3D");*/
	}

	CoroutineTask<void> Graphics3DFeature::onInit() {
		sceneLoader.addComponentLoader(makeIntrusive<MeshComponentLoader>(resourceManager).ref());
		sceneLoader.addComponentLoader(makeIntrusive<CameraComponent3DLoader>().ref());
		sceneLoader.addComponentLoader(makeIntrusive<TransformComponent3DLoader>().ref());
		co_return;
	}

	void Graphics3DFeature::onDeinit() {
		uninitGraphicsFeature();
	}
}
