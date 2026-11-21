#pragma once

#include "ShaderSource.h"
#include "ConstantCollection.h"

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
			sources.deleteItems();
		}

	protected:
		List<ShaderProgramSourceCode*> sources;
		ConstantCollection* constants = nullptr;

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
			dataSize.system = sizeof(*this);// +source->getDataSize();
		}

	public:
		inline void setSources(const List<ShaderProgramSourceCode*>& sources) {
			deinit();
			this->sources = sources;
			if (!sources.IsEmpty) {
				updateDataSize();
				State = ResourceState::LOADED;
			}
		}

		inline const List<ShaderProgramSourceCode*>& getSources() const {
			return sources;
		}

		__declspec(property(get = getSources, put = setSources)) const List<ShaderProgramSourceCode*>& Sources;

		inline ConstantCollection& getConstants() {
			return *constants;
		}

		__declspec(property(get = getConstants)) ConstantCollection& Constants;

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
