#include "ghedxpch.h"
#include "DxShader.h"

#include "core/object/IntrusivePointer.h"
#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"
#include <core/Finally.h>

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& DxShader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<DxShader>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool DxShader::set(DxGraphics& graphics, CommandList& commandList) {
		bool rsChanged = commandList.setGraphicsRootSignature(rootSignature);
		bool psChanged = commandList.setPipelineState(pipelineState);

		for (size_t i = 0; i < constants->constantBuffers.Size; i++)
			constants->constantBuffers[i]->set(graphics, commandList);

		for (size_t i = 0; i < constants->textures.Size; i++) {
			/*TextureParameter* parameter = (TextureParameter*)parameters->get(i + parameters->Size - textures.Size);
			Texture* texture = (Texture*)parameter->getValue();
#ifdef _DEBUG
			if (!texture) {
				if (!reported[i]) {
					Logger::log(LogType::WARNING, _T("Parameter for variable '%hs' is missing.\n"), textures[i]->Name);
					reported[i] = true;
				}
				continue;
			}
#endif
			texture->set(commandList, textures[i]->BindSlot);*/
		}

		return rsChanged || psChanged;
	}

	void DxShader::finalize() {
		if (rootSignature != nullptr)
			rootSignature->Release();
		if (pipelineState != nullptr)
			pipelineState->Release();

		delete constants;
		constants = nullptr;

#ifdef _DEBUG
		delete[] reported;
#endif
	}

	DxShader::~DxShader() {
		finalize();
	}

	/*void Shader::reload() {
		size_t paramCount = this->parameters ? this->parameters->Size : 0;
		PointerArray<Parameter*> parameters(paramCount);
		if (this->parameters)
			this->parameters->copyTo(parameters);
		__super::reload();
		if (this->parameters) {
			for (Parameter* p2 : parameters) {
				if (p2->Empty)
					continue;
				for (Parameter* p : *this->parameters) {
					if (p->ConstantName == p2->ConstantName && p->ValueType == p2->ValueType) {
						if (p->ValueType == ParameterType::TEXTURE) {
							((TextureParameter*)p)->Value = ((TextureParameter*)p2)->Value;
						} else {
							((ValueParameter*)p)->Value = ((ValueParameter*)p2)->Value;
						}
						break;
					}
				}
			}
		}
	}*/

	void DxShader::invalidate() {
		finalize();

		rootSignature = nullptr;
		pipelineState = nullptr;

#ifdef _DEBUG
		reported = nullptr;
#endif

		__super::invalidate();
	}

	/*void Shader::initParameters(ParameterManager& parameterManager) {
		if (parameters != nullptr)
			return;

		size_t constantsCount = 0;
		for (size_t i = 0; i < constantBuffers.Size; i++) {
			constantBuffers[i]->initParameters(parameterManager);
			constantsCount += constantBuffers[i]->Parameters.Size;
		}
		parameters = ghnew PointerArray<Parameter*>(constantsCount + textures.Size);    // TODO: correct number of parameters  +textureBuffers.Size+textures.Size
#ifdef _DEBUG
		reported = ghnew bool[textures.Size];
#endif

		size_t paramOffset = 0;
		for (size_t i = 0; i < constantBuffers.Size; i++) {
			constantBuffers[i]->Parameters.copyTo(*parameters, paramOffset);
			paramOffset += constantBuffers[i]->Parameters.Size;
		}

		for (size_t i = 0; i < textures.Size; i++) {
			Parameter* p = parameterManager.getParameter(textures[i]->Name);
#ifdef _DEBUG
			reported[i] = false;
#endif
			TextureParameter* tp = ghnew TextureParameter(textures[i]->Name.Data);
			if (p && p->ValueType == ParameterType::TEXTURE)
				tp->DefaultValue = ((TextureParameter*)p)->Value;
			parameters->set(i + constantsCount, tp);
			tp->release();
		}
	}*/

}