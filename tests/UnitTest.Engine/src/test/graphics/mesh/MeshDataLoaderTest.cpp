#include "utepch.h"
#include "CppUnitTest.h"

#include "core/math/Vector.h"
#include "engine/graphics/mesh/MeshData.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Engine;
    using namespace UnitTest::Utils;
    using namespace std;

    TEST_CLASS(MeshDataLoaderTest) {
public:

    TEST_METHOD(MeshDataLoader_loadUnknownFormat) {
        AString data = "xyz";
        IntrusivePointer<MeshDataLoader> loader(ghnew MeshDataLoader());
        MemoryInputStream stream(data.Data, data.Size);

        try {
            auto meshData = makeIntrusive<MeshData>();
            runCoroutineBlocking(loader->load(meshData.ref(), stream));
        } catch (...) {
            return;
        }
        Assert::Fail(L"expected exception");
    }

    TEST_METHOD(MeshDataLoader_loadObj) {
        IntrusivePointer<MeshDataLoader> loader(ghnew MeshDataLoader());
        FilePath meshFilePath = FilePath(L"../../resources/models/cube.fbx");
        File meshFile = File(meshFilePath);
        Buffer buffer;
        meshFile.read(buffer);
        MemoryInputStream stream(buffer.Data, buffer.Size);
        auto mesh = makeIntrusive<MeshData>();
        runCoroutineBlocking(loader->load(mesh.ref(), stream));

        Assert::AreEqual(24u, mesh->VertexCount);
        Assert::AreEqual(36u, mesh->IndexCount);
        Assert::AreEqual((uint32_t)sizeof(uint32_t), mesh->IndexSize);
        Assert::AreEqual(4ull, mesh->VertexStreams.Size);   // positions, normals, texCoords, tangents
    }

    TEST_METHOD(MeshDataLoader_saveLoadNative) {
        IntrusivePointer<MeshDataLoader> loader(ghnew MeshDataLoader());

        List<XMFLOAT3> vertices = { {1,0,0}, {1,1,0}, {0,1,0} };
        List<uint32_t> indices = { 0,1,2 };
        VertexStream posStream = VertexStream{ Buffer(&vertices[0], sizeof(XMFLOAT3) * vertices.Size), sizeof(XMFLOAT3), VertexRole::POSITION };
        BoundingBox boundingBox = BoundingBox({ 0, 1, 2 }, { 3, 4, 5 });

        auto outMesh = makeIntrusive<MeshData>();
        outMesh->init({ posStream }, vertices.Size, Buffer(&indices[0], sizeof(uint32_t) * indices.Size), (uint32_t)indices.Size, boundingBox);
        MemoryOutputStream outStream;
        loader->save(outMesh.ref(), outStream);

        MemoryInputStream inStream(outStream.Data, outStream.BytesWritten);
        auto inMesh = makeIntrusive<MeshData>();
        runCoroutineBlocking(loader->load(inMesh.ref(), inStream));

        Assert::AreEqual(outMesh->VertexCount, inMesh->VertexCount);
        Assert::AreEqual(outMesh->IndexCount, inMesh->IndexCount);
        Assert::AreEqual(outMesh->IndexSize, inMesh->IndexSize);
        Assert::AreEqual(outMesh->VertexStreams.Size, inMesh->VertexStreams.Size);
        Assert::IsTrue(outMesh->BoundingBox.Center == inMesh->BoundingBox.Center);
        Assert::IsTrue(outMesh->BoundingBox.Extents == inMesh->BoundingBox.Extents);
    }
    };
}
