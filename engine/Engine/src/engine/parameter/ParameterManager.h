#pragma once

#include "engine/parameter/Parameter.h"
#include "core/string/String.h"
#include "core/object/Object.h"
#include "ParameterCollection.h"
#include "engine/graphics/texture/ITextureProvider.h"
#include "TextureParameter.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class ParameterManager: public Object {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParameterManager::GET_TYPE();
#pragma endregion

	private:
		ParameterCollection parameters;

		inline static const AString DIFFUSE_TEXTURE = "diffuseTexture";
		inline static const AString SPECULAR_TEXTURE = "specularTexture";
		inline static const AString NORMAL_TEXTURE = "normalTexture";

		IntrusivePointer<TextureParameter> parameterDiffuse = makeIntrusive<TextureParameter>(DIFFUSE_TEXTURE);
		IntrusivePointer<TextureParameter> parameterSpecular = makeIntrusive<TextureParameter>(SPECULAR_TEXTURE);
		IntrusivePointer<TextureParameter> parameterNormal = makeIntrusive<TextureParameter>(NORMAL_TEXTURE);
		
		ParameterManager& operator=(const ParameterManager& other) = delete;

	public:
		ParameterManager();

		void initDefaultTextures(ITextureProvider& textureProvider);

		ParameterCollection& getParameters() {
			return parameters;
		}

		__declspec(property(get = getParameters)) ParameterCollection& Parameters;
	};
}