#include "ghepch.h"
#include "MeshData.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& MeshData::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<MeshData>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    /*bool MeshData::intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
        XMVECTOR pos2 = XMLoadFloat3(&pos);
        XMVECTOR dir2 = XMLoadFloat3(&dir);
        for (size_t i = 0; i < indexCount / 3; i++) {
            Vertex3D& v0 = ((Vertex3D*)vertices)[indices[i]];
            Vertex3D& v1 = ((Vertex3D*)vertices)[indices[i + 1]];
            Vertex3D& v2 = ((Vertex3D*)vertices)[indices[i + 2]];
            if (TriangleTests::Intersects(pos2, dir2, XMLoadFloat3(&v0.position), XMLoadFloat3(&v1.position), XMLoadFloat3(&v2.position), dist))
                return true;
        }
        return false;
    }*/
}