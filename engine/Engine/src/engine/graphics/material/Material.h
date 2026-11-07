#pragma once

#include "core/object/NotNull.h"
#include "core/resource/Resource.h"
#include "engine/graphics/memory/IGPUMemoryManager.h"
#include "MaterialVariantType.h"
#include "engine/graphics/rendering/GraphicsShader.h"

namespace Ghurund::Engine {

	class Material:public Ghurund::Core::Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Material::GET_TYPE();
#pragma endregion

	private:
		Array<IntrusivePointer<GraphicsShader>> variants = (size_t)MaterialVariantType::NUM_VARIANTS;

	protected:
		Material(const Material& other):Resource(other) {
			variants = other.variants;
		}

		~Material() {
			unload();
		}

	public:
		Material() {}

		inline void unload() {
			State = ResourceState::EMPTY;	// TODO: fix this
		}

		inline GraphicsShader* getShader(MaterialVariantType variantType) const {
			return variants[(size_t)variantType].get();
		}

		inline void setShader(MaterialVariantType variantType, GraphicsShader* variant) {
			variants[(size_t)variantType].set(variant);
			if (variant) {
				variant->addReference();
				dataSize.system = sizeof(*this);	// TODO: fix this
				State = ResourceState::INITIALIZED;
			} else {
				dataSize.system = sizeof(*this);
				State = ResourceState::EMPTY;	// TODO: fix this
			}
		}

		virtual Material* clone() const override {
			return ghnew Material(*this);
		}
#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return Material::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD, 2);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };
#pragma endregion
	};
}
