#pragma once

#include "VertexStream.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceManager.h"

#include <DirectXCollision.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;
	using namespace ::DirectX;

	class MeshData:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = MeshData::GET_TYPE();
#pragma endregion

	protected:
		Array<VertexStream> vertexStreams;
		uint32_t vertexCount = 0;
		Buffer indices;
		uint32_t indexCount = 0;

		BoundingBox boundingBox;

	public:
		MeshData() {}

		void init(Array<VertexStream> vertexStreams, uint32_t vertexCount, Buffer indices, uint32_t indexCount) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = indices;
			this->indexCount = indexCount;
		}

		template<typename T>
		void init(Array<VertexStream> vertexStreams, uint32_t vertexCount, const ArrayCollection<T>& indices) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = Buffer(indices.Data, sizeof(T) * indices.Size);
			this->indexCount = (uint32_t)(indices.Size);
		}

		template<typename T>
		void init(Array<VertexStream> vertexStreams, uint32_t vertexCount, const Array<T>& indices) {
			this->vertexStreams = vertexStreams;
			this->vertexCount = vertexCount;
			this->indices = Buffer(indices.Data, sizeof(T) * indices.Size);
			this->indexCount = (uint32_t)(indices.Size);
		}

		//virtual bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist);

		const Array<VertexStream>& getVertexStreams() const {
			return vertexStreams;
		}

		__declspec(property(get = getVertexStreams)) const Array<VertexStream>& VertexStreams;

		uint32_t getVertexCount() const {
			return vertexCount;
		}

		__declspec(property(get = getVertexCount)) uint32_t VertexCount;

		const Buffer& getIndices() const {
			return indices;
		}

		__declspec(property(get = getIndices)) const Buffer& Indices;

		uint32_t getIndexCount() const {
			return indexCount;
		}

		__declspec(property(get = getIndexCount)) uint32_t IndexCount;

		uint32_t getIndexSize() const {
			return (uint32_t)(indices.Size / indexCount);
		}

		__declspec(property(get = getIndexSize)) uint32_t IndexSize;

		BoundingBox& getBoundingBox() {
			return boundingBox;
		}

		__declspec(property(get = getBoundingBox)) BoundingBox& BoundingBox;


#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return MeshData::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_MESH = ResourceFormat(L"mesh", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_3DMF = ResourceFormat(L"3mf", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_COLLADA_DAE = ResourceFormat(L"dae", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_COLLADA_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_BIOVISION = ResourceFormat(L"bvh", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_3DS = ResourceFormat(L"3ds", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_ASE = ResourceFormat(L"ase", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_GLTF = ResourceFormat(L"glTF", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_FBX = ResourceFormat(L"fbx", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_PLY = ResourceFormat(L"ply", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_AUTOCAD_DXF = ResourceFormat(L"dxf", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_IFC = ResourceFormat(L"ifc", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_IQM = ResourceFormat(L"iqm", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_NEUTRAL_NFF = ResourceFormat(L"nff", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_SENSE8_NFF = ResourceFormat(L"nff", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_VALVE_SMD = ResourceFormat(L"smd", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_VALVE_VTA = ResourceFormat(L"vta", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_Q1 = ResourceFormat(L"mdl", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_Q2 = ResourceFormat(L"md2", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_Q3 = ResourceFormat(L"md3", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_Q3_BSP = ResourceFormat(L"pk3", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_RTCW_MDC = ResourceFormat(L"mdc", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_DOOM3_MESH = ResourceFormat(L"md5mesh", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_DOOM3_ANIM = ResourceFormat(L"md5anim", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_DOOM3_CAMERA = ResourceFormat(L"md5camera", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_X = ResourceFormat(L"x", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_QUICK3D_Q3O = ResourceFormat(L"q3o", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_QUICK3D_Q3S = ResourceFormat(L"q3s", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_RAW = ResourceFormat(L"raw", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_AC3D_AC = ResourceFormat(L"ac", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_AC3D_AC3D = ResourceFormat(L"ac3d", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_STL = ResourceFormat(L"stl", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_AUTODESK_DXF = ResourceFormat(L"dxf", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_IRRLICHT_MESH = ResourceFormat(L"irrmesh", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_IRRLICHT_MESH_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_IRRLICHT_SCENE = ResourceFormat(L"irr", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_IRRLICHT_SCENE_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_OFF = ResourceFormat(L"off", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_OBJ = ResourceFormat(L"obj", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_TER = ResourceFormat(L"ter", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_3DGAMESTUDIO_MODEL = ResourceFormat(L"mdl", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_3DGAMESTUDIO_TERRAIN = ResourceFormat(L"hmp", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_OGRE_MESH = ResourceFormat(L"mesh.xml", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_OGRE_SKELETON = ResourceFormat(L"skeleton.xml", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_OGRE_MATERIAL = ResourceFormat(L"material", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_OGEX = ResourceFormat(L"ogex", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_MS3D = ResourceFormat(L"ms3d", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_LWO = ResourceFormat(L"lwo", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_LWS = ResourceFormat(L"lws", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_LXO = ResourceFormat(L"lxo", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_CSM = ResourceFormat(L"csm", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_TRUESPACE_COB = ResourceFormat(L"cob", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_TRUESPACE_SCN = ResourceFormat(L"scn", ResourceFormatOptions::CAN_LOAD);
		static const inline ResourceFormat FORMAT_XGL = ResourceFormat(L"xgl", ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = {
			FORMAT_MESH,
			FORMAT_3DMF,
			FORMAT_COLLADA_DAE, FORMAT_COLLADA_XML,
			FORMAT_BIOVISION,
			FORMAT_3DS, FORMAT_ASE,
			FORMAT_GLTF,
			FORMAT_FBX,
			FORMAT_PLY,
			FORMAT_AUTOCAD_DXF,
			FORMAT_IFC,
			FORMAT_IQM,
			FORMAT_NEUTRAL_NFF,
			FORMAT_SENSE8_NFF,
			FORMAT_VALVE_SMD, FORMAT_VALVE_VTA,
			FORMAT_Q1, FORMAT_Q2, FORMAT_Q3, FORMAT_Q3_BSP,
			FORMAT_RTCW_MDC,
			FORMAT_DOOM3_MESH, FORMAT_DOOM3_ANIM, FORMAT_DOOM3_CAMERA,
			FORMAT_X,
			FORMAT_QUICK3D_Q3O,FORMAT_QUICK3D_Q3S,
			FORMAT_RAW,
			FORMAT_AC3D_AC,FORMAT_AC3D_AC3D,
			FORMAT_STL,
			FORMAT_AUTODESK_DXF,
			FORMAT_IRRLICHT_MESH, FORMAT_IRRLICHT_MESH_XML, FORMAT_IRRLICHT_SCENE, FORMAT_IRRLICHT_SCENE_XML,
			FORMAT_OFF,
			FORMAT_OBJ,
			FORMAT_TER,
			FORMAT_3DGAMESTUDIO_MODEL, FORMAT_3DGAMESTUDIO_TERRAIN,
			FORMAT_OGRE_MESH, FORMAT_OGRE_SKELETON, FORMAT_OGRE_MATERIAL,
			FORMAT_OGEX,
			FORMAT_MS3D,
			FORMAT_LWO, FORMAT_LWS,
			FORMAT_LXO,
			FORMAT_CSM,
			FORMAT_TRUESPACE_COB, FORMAT_TRUESPACE_SCN,
			FORMAT_XGL
		};

		static const inline uint32_t VERSION = 1;
#pragma endregion
	};
}