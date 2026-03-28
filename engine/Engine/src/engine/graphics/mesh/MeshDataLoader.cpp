#include "ghepch.h"
#include "MeshDataLoader.h"

#include "core/logging/Logger.h"
#include "core/object/IntrusivePointer.h"
#include "core/exception/Exceptions.h"

#include <cstdlib>

namespace Ghurund::Engine {

	void MeshDataLoader::loadObj(MeshData& mesh, MemoryInputStream& stream) {
		List<XMFLOAT3> objPositions;
		List<XMFLOAT3> objNormals;
		List<XMFLOAT2> objTexCoords;
		List<ObjVert> objVerts;

		AString obj((char*)stream.Data, stream.Size);
		Array<AString> lines = obj.split("\n");
		for (AString& line : lines) {
			if (line.startsWith("#")) {
				continue;
			} else if (line.startsWith("v ")) {
				Array<AString> pos = line.substring(2).trim().split(" ");
				XMFLOAT3 v((float)atof(pos[0].Data), (float)atof(pos[1].Data), -(float)atof(pos[2].Data));
				objPositions.add(v);
			} else if (line.startsWith("vn ")) {
				Array<AString> normal = line.substring(2).trim().split(" ");
				XMFLOAT3 v((float)atof(normal[0].Data), (float)atof(normal[1].Data), -(float)atof(normal[2].Data));
				objNormals.add(v);
			} else if (line.startsWith("vt ")) {
				Array<AString> texCoord = line.substring(2).trim().split(" ");
				XMFLOAT2 v((float)atof(texCoord[0].Data), 1 - (float)atof(texCoord[1].Data));
				objTexCoords.add(v);
			} else if (line.startsWith("f ")) {
				// TODO: add support for faces without normals or textures
				// TODO: add support for more than 3 indices in one face
				Array<AString> face = line.substring(2).trim().split(" ");
				if (face.Size != 3)
					throw InvalidFormatException("only triangles are supported");

				for (size_t i = 0; i < face.Size; i++) {
					Array<AString> vert = face[i].split("/");
					objVerts.add(ObjVert{
						(uint32_t)(atoi(vert[0].Data) - 1),	// in obj indices start from 1, not from 0
						(uint32_t)(atoi(vert[1].Data) - 1),
						(uint32_t)(atoi(vert[2].Data) - 1),
						0
						});
				}
				/*Array<AString> vert = line.substring(2).trim().split(" ");

				triangleIndices.add((unsigned int)triangleVertices.Size);
				triangleIndices.add((unsigned int)(triangleVertices.Size + 2));
				triangleIndices.add((unsigned int)(triangleVertices.Size + 1));
				for (size_t j = 3; j < vert.Size; j++) {
					triangleIndices.add((unsigned int)triangleVertices.Size);
					triangleIndices.add((unsigned int)(j - 3 + triangleVertices.Size + 3));
					triangleIndices.add((unsigned int)(j - 3 + triangleVertices.Size + 2));
				}
				for (size_t j = 0; j < vert.Size; j++) {
					Array<AString> face = vert[j].split("/");
					Vertex3D v(objVerts[atoi(face[0].Data) - 1], objNorms[atoi(face[2].Data) - 1], objTexCoords[atoi(face[1].Data) - 1]);
					triangleVertices.add(v);
				}*/
			}
		}

		List<XMFLOAT3> positions;
		List<XMFLOAT3> normals;
		List<XMFLOAT2> texCoords;
		List<uint32_t> indices;
		for (size_t i = 0; i < objVerts.Size; i++) {
			auto& vert = objVerts[i];

			bool alreadyExists = false;
			for (size_t j = 0; j < i; j++) {
				if (vert.posIndex == objVerts[j].posIndex && vert.normalIndex == objVerts[j].normalIndex && vert.texCoordIndex == objVerts[j].texCoordIndex) {
					vert.vertexIndex = objVerts[j].vertexIndex;
					alreadyExists = true;
					break;
				}
			}

			if (!alreadyExists) {
				vert.vertexIndex = (uint32_t)positions.Size;
				positions.add(objPositions[vert.posIndex]);
				normals.add(objNormals[vert.normalIndex]);
				texCoords.add(objTexCoords[vert.texCoordIndex]);
			}

			indices.add(vert.vertexIndex);
		}

		/*computeBoundingBox();
		generateTangents();*/

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

		//IndexType indexType = indices.Size <= std::numeric_limits<uint16_t>::max() ? IndexType::INT16 : IndexType::INT32;
		//Buffer indexBuffer(((uint32_t)indexType) * indices.Size);

		mesh.init(
			vertexStreams,
			positions.Size,
			Buffer(&indices[0], sizeof(uint32_t) * indices.Size),
			indices.Size
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

		//XMFLOAT3 center = stream.read<XMFLOAT3>();
		//XMFLOAT3 extents = stream.read<XMFLOAT3>();
		//boundingBox = ::DirectX::BoundingBox(center, extents);

		mesh.init(vertexStreams, vertexCount, Buffer(data, indexCount * indexSize), indexCount);
	}

	void MeshDataLoader::loadInternal(
		MeshData& resource,
		MemoryInputStream& stream,
		const DirectoryPath& workingDir,
		const Ghurund::Core::ResourceFormat& format,
		Ghurund::Core::LoadOption options
	) {
		size_t bytesRead = stream.Position;
		try {
			loadMesh(resource, stream);
		} catch (...) {
			stream.Position = bytesRead;
			try {
				loadObj(resource, stream);
			} catch (...) {
				throw InvalidFormatException();
			}
		}
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
		stream.writeUInt32(resource.VertexStreams.Size);
		for (auto& vertexStream : resource.VertexStreams) {
			stream.writeUInt32(vertexStream.data.Size);
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
