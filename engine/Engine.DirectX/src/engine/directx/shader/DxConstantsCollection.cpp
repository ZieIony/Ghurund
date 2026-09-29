#include "ghedxpch.h"
#include "DxConstantsCollection.h"

#include "DxConstantBuffer.h"

#include <engine/directx/cubemap/DxCubeMap.h>
#include <engine/directx/texture/DxTexture.h>

namespace Ghurund::Engine::DirectX {
	void DxConstantsCollection::init(
		const List<DxBufferConstantInfo*>& bufferConstantInfos,
		const List<DxTextureConstantInfo*>& textureConstantInfos,
		const List<DxTextureConstantInfo*>& uavConstantInfos
	) {
		for (auto& cb : bufferConstantInfos) {
			List<ValueConstant> cbInputs;
			for (auto& v : cb->Fields)
				cbInputs.add(ValueConstant(v.name, v.makeInputType(), v.size, v.offset, v.defaultValue));
			bufferConstants.add(BufferConstant(cb->Name, cb->BindSlot, cb->Size, cbInputs));
		}
		for (auto& t : textureConstantInfos) {
			if (t->dimension == D3D_SRV_DIMENSION_TEXTURE2D) {
				textureConstants.add(TextureConstant(t->Name, t->BindSlot));
			} else {
				cubeMapConstants.add(CubeMapConstant(t->Name, t->BindSlot));
			}
		}
		for (auto& t : uavConstantInfos)
			uavConstants.add(TextureConstant(t->Name, t->BindSlot));
	}

	void DxConstantsCollection::apply(CommandList& commandList) {
		for (size_t i = 0; i < bufferConstants.Size; i++) {
			DxConstantBuffer* buffer = (DxConstantBuffer*)bufferConstants[i].constantBuffer;
			if (!buffer) {
				auto text = std::format(_T("No value for constant '{}'.\n"), bufferConstants[i].name);
				Logger::logOnce(LogType::WARNING, text.c_str(), (uint32_t)i);
				continue;
			}
			buffer->set(commandList, bufferConstants[i].bindSlot);
		}

		for (size_t i = 0; i < textureConstants.Size; i++) {
			DxTexture* texture = (DxTexture*)textureConstants[i].Value;
			if (!texture) {
				auto text = std::format(_T("No value for constant '{}'.\n"), textureConstants[i].name);
				Logger::logOnce(LogType::WARNING, text.c_str(), (uint32_t)i);
				continue;
			}
			texture->set(commandList, textureConstants[i].bindSlot);
		}

		for (size_t i = 0; i < cubeMapConstants.Size; i++) {
			DxCubeMap* cubeMap = (DxCubeMap*)cubeMapConstants[i].Value;
			if (!cubeMap) {
				auto text = std::format(_T("No value for constant '{}'.\n"), cubeMapConstants[i].name);
				Logger::logOnce(LogType::WARNING, text.c_str(), (uint32_t)i);
				continue;
			}
			cubeMap->set(commandList, cubeMapConstants[i].bindSlot);
		}

		for (size_t i = 0; i < uavConstants.Size; i++) {
			DxTexture* texture = (DxTexture*)uavConstants[i].Value;
			if (!texture) {
				auto text = std::format(_T("No value for constant '{}'.\n"), uavConstants[i].name);
				Logger::logOnce(LogType::WARNING, text.c_str(), (uint32_t)i);
				continue;
			}
			texture->set(commandList, uavConstants[i].bindSlot);
		}
	}
}
