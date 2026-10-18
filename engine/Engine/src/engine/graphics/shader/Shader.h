#pragma once

#include "ShaderSource.h"
#include "ConstantsCollection.h"

#include "core/resource/Resource.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class Shader:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Shader::GET_TYPE();
#pragma endregion

	private:
		inline void deinit_internal() {
			if (constants)
				delete constants;
			constants = nullptr;
		}

		inline void unload_internal() {
			if (source)
				source->release();
			source = nullptr;
		}

	protected:
		ShaderSource* source = nullptr;
		ConstantsCollection* constants = nullptr;

		~Shader() {
			deinit();
			unload();
		}

		virtual void onDeinit() {
			deinit_internal();
		}

		virtual void onUnload() {
			unload_internal();
		}

		virtual void updateDataSize() {
			dataSize.system = sizeof(*this) + source->getDataSize();
		}

	public:
		inline void setSource(ShaderSource* source) {
			deinit();
			setPointer(this->source, source);
			if (source) {
				updateDataSize();
				State = ResourceState::LOADED;
			}
		}

		inline const ShaderSource* getSource() const {
			return source;
		}

		__declspec(property(get = getSource, put = setSource)) const ShaderSource* Source;

		inline ConstantsCollection& getConstants() {
			return *constants;
		}

		__declspec(property(get = getConstants)) ConstantsCollection& Constants;

		inline void deinit() {
			if (State != ResourceState::INITIALIZED)
				return;
			onDeinit();
			State = ResourceState::LOADED;
		}

		inline void unload() {
			if (State != ResourceState::LOADED)
				return;
			onUnload();
			State = ResourceState::EMPTY;
		}
	};
}
