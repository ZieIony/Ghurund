#include "utepch.h"
#include "CppUnitTest.h"

#include "engine/graphics/mesh/MeshData.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Engine;
    using namespace std;

    TEST_CLASS(MeshDataLoaderTest) {
private:
    AString data = R"(
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -0.999999
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000
vt 1.000000 0.333333
vt 1.000000 0.666667
vt 0.666667 0.666667
vt 0.666667 0.333333
vt 0.666667 0.000000
vt 0.000000 0.333333
vt 0.000000 0.000000
vt 0.333333 0.000000
vt 0.333333 1.000000
vt 0.000000 1.000000
vt 0.000000 0.666667
vt 0.333333 0.333333
vt 0.333333 0.666667
vt 1.000000 0.000000
vn 0.000000 -1.000000 0.000000
vn 0.000000 1.000000 0.000000
vn 1.000000 0.000000 0.000000
vn -0.000000 0.000000 1.000000
vn -1.000000 -0.000000 -0.000000
vn 0.000000 0.000000 -1.000000
usemtl Material
s off
f 2/1/1 3/2/1 4/3/1
f 8/1/2 7/4/2 6/5/2
f 5/6/3 6/7/3 2/8/3
f 6/8/4 7/5/4 3/4/4
f 3/9/5 7/10/5 8/11/5
f 1/12/6 4/13/6 8/11/6
f 1/4/1 2/1/1 4/3/1
f 5/14/2 8/1/2 6/5/2
f 1/12/3 5/6/3 2/8/3
f 2/12/4 6/8/4 3/4/4
f 4/13/5 3/9/5 8/11/5
f 5/6/6 1/12/6 8/11/6
)";

    public:

        TEST_METHOD(MeshDataLoader_loadUnknownFormat) {
            AString data = "xyz";
            IntrusivePointer<MeshDataLoader> loader(ghnew MeshDataLoader());
            MemoryInputStream stream(data.Data, data.Size);

            Assert::ExpectException<InvalidFormatException>([&] {
                auto meshData = makeIntrusive<MeshData>();
                loader->load(meshData.ref(), stream);
            });
        }

        TEST_METHOD(MeshDataLoader_loadObj) {
            IntrusivePointer<MeshDataLoader> loader(ghnew MeshDataLoader());
            MemoryInputStream stream(data.Data, data.Size);
            auto mesh = makeIntrusive<MeshData>();
            loader->load(mesh.ref(), stream);

            Assert::AreEqual(24u, mesh->VertexCount);
            Assert::AreEqual(36u, mesh->IndexCount);
            Assert::AreEqual((uint32_t)sizeof(uint32_t), mesh->IndexSize);
            Assert::AreEqual(3ull, mesh->VertexStreams.Size);
        }

        TEST_METHOD(MeshDataLoader_saveLoadNative) {
            IntrusivePointer<MeshDataLoader> loader(ghnew MeshDataLoader());

            List<XMFLOAT3> vertices = { {1,0,0}, {1,1,0}, {0,1,0} };
            List<uint32_t> indices = { 0,1,2 };
            VertexStream posStream = VertexStream{ Buffer(&vertices[0], sizeof(XMFLOAT3)*vertices.Size), sizeof(XMFLOAT3), VertexRole::POSITION };
            auto outMesh = makeIntrusive<MeshData>();
            outMesh->init({ posStream }, vertices.Size, Buffer(&indices[0], sizeof(uint32_t) * indices.Size), (uint32_t)indices.Size);
            MemoryOutputStream outStream;
            loader->save(outMesh.ref(), outStream);

            MemoryInputStream inStream(outStream.Data, outStream.BytesWritten);
            auto inMesh = makeIntrusive<MeshData>();
            loader->load(inMesh.ref(), inStream);

            Assert::AreEqual(outMesh->VertexCount, inMesh->VertexCount);
            Assert::AreEqual(outMesh->IndexCount, inMesh->IndexCount);
            Assert::AreEqual(outMesh->IndexSize, inMesh->IndexSize);
            Assert::AreEqual(outMesh->VertexStreams.Size, inMesh->VertexStreams.Size);
        }
    };
}
