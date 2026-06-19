#include "ghepch.h"
#include "MeshDataLoader.h"

#include "core/logging/Logger.h"
#include "core/object/IntrusivePointer.h"
#include "core/exception/Exceptions.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <cstdlib>

namespace Ghurund::Engine {

	void MeshDataLoader::loadAssimp(MeshData& mesh, MemoryInputStream& stream) {

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFileFromMemory(stream.Data, stream.Available,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType,
			"fbx");

		if (!scene) {
			AString errorMessage = importer.GetErrorString();
			String message = convertText<char, tchar>(errorMessage);
			Logger::log(LogType::ERR0R, message.Data);
			throw CallFailedException();
		}

		List<XMFLOAT3> positions;
		List<XMFLOAT3> normals;
		List<XMFLOAT2> texCoords;
		List<uint32_t> indices;

		for (size_t i = 0; i < scene->mNumMeshes; i++) {
			auto aiMesh = scene->mMeshes[i];
			for (size_t j = 0; j < aiMesh->mNumVertices; j++) {
				auto& aiVertex = aiMesh->mVertices[j];
				positions.add({ aiVertex.x, aiVertex.y, aiVertex.z });
				auto& aiNormal = aiMesh->mNormals[j];
				normals.add({ aiNormal.x, aiNormal.y, aiNormal.z });
				auto& aiTexCoord = aiMesh->mTextureCoords[0][j];
				texCoords.add({ aiTexCoord.x, aiTexCoord.y });
			}
			for (size_t k = 0; k < aiMesh->mNumFaces; k++) {
				auto& aiFace = aiMesh->mFaces[k];
				indices.addAll({ aiFace.mIndices[0], aiFace.mIndices[1], aiFace.mIndices[2] });
			}
		}

		if (positions.Empty || normals.Empty || texCoords.Empty) {
			auto message = std::format(_T("One or more empty streams (positions: {}, normals: {}, texCoords)\n"), positions.Size, normals.Size, texCoords.Size);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}

		Array<VertexStream> vertexStreams = {
			VertexStream{Buffer(&positions[0], sizeof(XMFLOAT3) * positions.Size), sizeof(XMFLOAT3), VertexRole::POSITION},
			VertexStream{Buffer(&normals[0], sizeof(XMFLOAT3) * normals.Size), sizeof(XMFLOAT3), VertexRole::NORMAL},
			VertexStream{Buffer(&texCoords[0], sizeof(XMFLOAT2) * texCoords.Size), sizeof(XMFLOAT2), VertexRole::TEXCOORD},
		};

		mesh.init(
			vertexStreams,
			(uint32_t)positions.Size,
			Buffer(&indices[0], sizeof(uint32_t) * indices.Size),
			(uint32_t)indices.Size
		);
	}

	void MeshDataLoader::loadMesh(MeshData& mesh, MemoryInputStream& stream) {
		readHeader<MeshData>(stream);

		uint32_t vertexCount = stream.readUInt32();
		uint32_t streamCount = stream.readUInt32();
		Array<VertexStream> vertexStreams(streamCount);
		for (auto& vertexStream : vertexStreams) {
			uint32_t dataSize = stream.readUInt32();
			const void* data = stream.readBytes(dataSize);
			vertexStream.data.setData(data, dataSize);
			vertexStream.vertexSize = stream.readUInt32();
			vertexStream.role = (VertexRole)stream.read<uint16_t>();
		}

		uint32_t indexCount = stream.readUInt32();
		uint32_t indexSize = stream.readUInt32();
		const void* data = stream.readBytes(indexCount * indexSize);

		mesh.init(vertexStreams, vertexCount, Buffer(data, indexCount * indexSize), indexCount);
	}

	CoroutineTask<void> MeshDataLoader::loadInternal(
		MeshData& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const Ghurund::Core::ResourceFormat& format,
		Ghurund::Core::LoadOption options
	) {
		loadAssimp(resource, stream);
		co_return;
	}

	void MeshDataLoader::saveInternal(
		MeshData& resource,
		MemoryOutputStream& stream,
		const DirectoryPath& workingDir,
		const Ghurund::Core::ResourceFormat& format,
		Ghurund::Core::SaveOption options
	) const {
		writeHeader<MeshData>(stream);

		stream.writeUInt32(resource.VertexCount);
		stream.writeUInt32((uint32_t)resource.VertexStreams.Size);
		for (auto& vertexStream : resource.VertexStreams) {
			stream.writeUInt32((uint32_t)vertexStream.data.Size);
			stream.writeBytes(vertexStream.data.Data, vertexStream.data.Size);
			stream.writeUInt32(vertexStream.vertexSize);
			stream.write<uint16_t>((uint16_t)(vertexStream.role));
		}

		stream.write(resource.IndexCount);
		stream.write(resource.IndexSize);
		stream.writeBytes(resource.Indices.Data, resource.Indices.Size);

		//stream.write<XMFLOAT3>(boundingBox.Center);
		//stream.write<XMFLOAT3>(boundingBox.Extents);
	}
}
