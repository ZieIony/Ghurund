#pragma once

#include "ConstantBuffer.h"
#include "core/collection/Array.h"
#include "core/collection/List.h"
#include <core/object/OwnedNotNull.h>
#include "core/resource/ResourceManager.h"
#include "Sampler.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"
#include "core/IUnknownImpl.h"
#include <engine/graphics/mesh/VertexStream.h>
#include "engine/graphics/shader/IShader.h"

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;
	using namespace Microsoft::WRL;

	class DxShader:public IShader {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = DxShader::GET_TYPE();
#pragma endregion

	private:
		ID3D12RootSignature* rootSignature = nullptr;
		ID3D12PipelineState* pipelineState = nullptr;
		Array<VertexRole> layout;

		List<ConstantBuffer*> constantBuffers;
		List<TextureConstant*> textures;
		List<Sampler*> samplers;

		ParameterCollection parameters;

		void finalize();

	public:
		~DxShader();

		virtual void invalidate() override;

		virtual bool isValid() const {
			return pipelineState != nullptr && rootSignature != nullptr && __super::isValid();
		}

		void init(
			const Array<VertexRole>& layout,
			OwnedNotNull<ID3D12RootSignature, IUnknownDeleter> rootSignature,
			OwnedNotNull<ID3D12PipelineState, IUnknownDeleter> pipelineState,
			const List<ConstantBuffer*>& constantBuffers,
			const List<TextureConstant*>& textures,
			const List<Sampler*>& samplers,
			bool isTransparencyEnabled
		) {
			this->layout = layout;
			this->rootSignature = rootSignature.reset();
			this->pipelineState = pipelineState.reset();
			this->constantBuffers = constantBuffers;
			for (auto& cb : constantBuffers)
				parameters.putAll(cb->Parameters);
			this->textures = textures;
			for (auto& t : textures)
				parameters.put(t->Parameter);
			this->samplers = samplers;
			this->isTransparencyEnabled = isTransparencyEnabled;
		}

		inline const ParameterCollection& getParameters() const {
			return parameters;
		}

		__declspec(property(get = getParameters)) const ParameterCollection& Parameters;

		bool set(CommandList& commandList, ParameterManager& parameterManager);

		inline const Array<VertexRole>& getLayout() const {
			return layout;
		}

		__declspec(property(get = getLayout)) const Array<VertexRole>& Layout;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return DxShader::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_SHADER = ResourceFormat(L"shader", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_HLSL = ResourceFormat(L"hlsl", ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SHADER, FORMAT_HLSL };

		static const inline uint32_t VERSION = 0;
#pragma endregion
	};
}