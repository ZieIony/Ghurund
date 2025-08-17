#pragma once

#include "VertexStream.h"
#include <core/Buffer.h>
#include <core/collection/Array.h>
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include "core/object/NotNull.h"
#include <core/collection/List.h>
#include <core/math/Vector.h>

namespace Ghurund::Engine {
    using namespace ::DirectX;

	class MeshProcessor {
	private:
		MeshProcessor() = delete;

	public:
        template<typename V, typename I>
        void removeDuplicates() {
            List<V> vertexData;
            List<I> indexData;

            for (I i = 0; i < indexCount; i++) {
                V& v = ((V*)vertices)[indices[i]];
                vindex_t index = (vindex_t)vertexData.Size;

                for (vindex_t j = 0; j < vertexData.Size; j++) {
                    if (v.equals(vertexData[j], 0.01f, 0.01f, 0.01f)) {
                        index = j;
                        break;
                    }
                }

                if (index == vertexData.Size)
                    vertexData.add(v);
                indexData.add(index);
            }

            delete[] vertices;
            vertexCount = (vindex_t)vertexData.Size;
            vertices = ghnew Vertex3D[vertexCount];
            memcpy(vertices, &(*(vertexData.begin())), vertexCount * vertexSize);

            delete[] indices;
            indexCount = (vindex_t)indexData.Size;
            indices = ghnew vindex_t[indexCount];
            memcpy(indices, &(*(indexData.begin())), sizeof(vindex_t) * indexCount);
        }

        template<typename I>
        void subdivide(NotNull<Array<VertexStream>> streams, NotNull<Buffer> indexBuffer) {
            I* indices = (I*)(indexBuffer->Data);
            size_t indexCount = indexBuffer->Size / sizeof(I);

            for (VertexStream& stream : *streams) {
                auto subdivideStream = [&]<typename V>(V* vertices) {
                    List<V> vertexData;
                    for (I i = 0, j = 0; i < indexCount; i += 3, j += 6) {
                        V v0 = vertices[indices[i]];
                        V v1 = vertices[indices[i + 1]];
                        V v2 = vertices[indices[i + 2]];

                        XMVECTOR v0v = XMLoadFloatN(&v0);
                        XMVECTOR v1v = XMLoadFloatN(&v1);
                        XMVECTOR v2v = XMLoadFloatN(&v2);
                        V v3;
                        XMStoreFloatN(&v3, (v0v + v1v) / 2);
                        V v4;
                        XMStoreFloatN(&v4, (v1v + v2v) / 2);
                        V v5;
                        XMStoreFloatN(&v5, (v0v + v2v) / 2);

                        vertexData.add(v0);
                        vertexData.add(v1);
                        vertexData.add(v2);
                        vertexData.add(v3);
                        vertexData.add(v4);
                        vertexData.add(v5);
                    }
                    stream.data.setData(vertexData.Data, vertexData.Size * sizeof(V));
                };
                if (stream.vertexSize == sizeof(XMFLOAT3)) {
                    subdivideStream((XMFLOAT3*)stream.data.Data);
                } else if (stream.vertexSize == sizeof(XMFLOAT2)) {
                    subdivideStream((XMFLOAT2*)stream.data.Data);
                }
            }

            List<I> indexData;
            for (I i = 0, j = 0; i < indexCount; i += 3, j += 6) {
                indexData.add(j);
                indexData.add(j + 3);
                indexData.add(j + 5);

                indexData.add(j + 1);
                indexData.add(j + 4);
                indexData.add(j + 3);

                indexData.add(j + 2);
                indexData.add(j + 5);
                indexData.add(j + 4);

                indexData.add(j + 3);
                indexData.add(j + 4);
                indexData.add(j + 5);
            }
            indexBuffer->setData(indexData.Data, indexData.Size*sizeof(I))
        }

        template<typename V, typename I>
        void spherify() {
            for (vindex_t i = 0; i < vertexCount; i++) {
                Vertex3D& v = ((Vertex3D*)vertices)[i];
                XMVECTOR pos = XMLoadFloat3(&v.position);
                XMStoreFloat3(&v.position, XMVector3Normalize(XMLoadFloat3(&v.position)));
            }
        }

        /*
        * smoothingTreshold maximum smooth angle in radians
        */
        template<typename V, typename I>
        void generateSmoothing(float smoothingTreshold) {
            Vertex3D* newVertices = ghnew Vertex3D[indexCount * 3];
            for (size_t i = 0; i < indexCount; i++) {
                newVertices[i] = ((Vertex3D*)vertices)[indices[i]];
                indices[i] = (vindex_t)i;
            }

            delete[] vertices;
            vertexCount = indexCount;
            vertices = newVertices;
        }

        template<typename V, typename I>
        void generateNormals() {
            for (size_t i = 0; i < vertexCount; i++)
                ((Vertex3D*)vertices)[i].normal = XMFLOAT3(0, 0, 0);
            for (size_t i = 0; i < indexCount; i += 3) {
                Vertex3D& v1 = ((Vertex3D*)vertices)[indices[i]];
                Vertex3D& v2 = ((Vertex3D*)vertices)[indices[i + 1]];
                Vertex3D& v3 = ((Vertex3D*)vertices)[indices[i + 2]];
                XMVECTOR pos1 = XMLoadFloat3(&v1.position);
                XMVECTOR pos2 = XMLoadFloat3(&v2.position);
                XMVECTOR pos3 = XMLoadFloat3(&v3.position);
                XMVECTOR normal = XMVector3Normalize(XMVector3Cross(pos2 - pos1, pos3 - pos1));
                XMStoreFloat3(&v1.normal, XMLoadFloat3(&v1.normal) + normal);
                XMStoreFloat3(&v2.normal, XMLoadFloat3(&v2.normal) + normal);
                XMStoreFloat3(&v3.normal, XMLoadFloat3(&v3.normal) + normal);
            }
            for (size_t i = 0; i < vertexCount; i++)
                XMStoreFloat3(&((Vertex3D*)vertices)[i].normal, XMVector3Normalize(XMLoadFloat3(&((Vertex3D*)vertices)[i].normal)));
        }

        template<typename V, typename I>
        void generateTangents() {
            static const float EPSILON = 0.0001f;
            //static const XMVECTORF32 s_flips = {{ { 1.f, -1.f, -1.f, 1.f } }};

            XMVECTOR* tangent1 = (XMVECTOR*)_aligned_malloc(sizeof(XMVECTOR) * vertexCount, 16);
            memset(tangent1, 0, sizeof(XMVECTOR) * vertexCount);
            XMVECTOR* tangent2 = (XMVECTOR*)_aligned_malloc(sizeof(XMVECTOR) * vertexCount, 16);
            memset(tangent2, 0, sizeof(XMVECTOR) * vertexCount);

            for (vindex_t i = 0; i < indexCount; i += 3) {
                vindex_t i0 = indices[i];
                vindex_t i1 = indices[i + 1];
                vindex_t i2 = indices[i + 2];

                XMVECTOR t0 = XMLoadFloat2(&((Vertex3D*)vertices)[i0].texCoord);
                XMVECTOR t1 = XMLoadFloat2(&((Vertex3D*)vertices)[i1].texCoord);
                XMVECTOR t2 = XMLoadFloat2(&((Vertex3D*)vertices)[i2].texCoord);

                XMVECTOR s = XMVectorMergeXY(XMVectorSubtract(t1, t0), XMVectorSubtract(t2, t0));

                XMFLOAT4A tmp;
                XMStoreFloat4A(&tmp, s);

                float d = tmp.x * tmp.w - tmp.z * tmp.y;
                d = (fabsf(d) <= EPSILON) ? 1.f : (1.f / d);
                s = XMVectorScale(s, d);
                //s = XMVectorMultiply(s, s_flips);

                XMMATRIX m0;
                m0.r[0] = XMVectorPermute<3, 2, 6, 7>(s, g_XMZero);
                m0.r[1] = XMVectorPermute<1, 0, 4, 5>(s, g_XMZero);
                m0.r[2] = m0.r[3] = g_XMZero;

                XMVECTOR p0 = XMLoadFloat3(&((Vertex3D*)vertices)[i0].position);
                XMVECTOR p1 = XMLoadFloat3(&((Vertex3D*)vertices)[i1].position);
                XMVECTOR p2 = XMLoadFloat3(&((Vertex3D*)vertices)[i2].position);

                XMMATRIX m1;
                m1.r[0] = XMVectorSubtract(p1, p0);
                m1.r[1] = XMVectorSubtract(p2, p0);
                m1.r[2] = m1.r[3] = g_XMZero;

                XMMATRIX uv = XMMatrixMultiply(m0, m1);

                tangent1[i0] = XMVectorAdd(tangent1[i0], uv.r[0]);
                tangent1[i1] = XMVectorAdd(tangent1[i1], uv.r[0]);
                tangent1[i2] = XMVectorAdd(tangent1[i2], uv.r[0]);

                tangent2[i0] = XMVectorAdd(tangent2[i0], uv.r[1]);
                tangent2[i1] = XMVectorAdd(tangent2[i1], uv.r[1]);
                tangent2[i2] = XMVectorAdd(tangent2[i2], uv.r[1]);
            }

            for (vindex_t j = 0; j < vertexCount; ++j) {
                // Gram-Schmidt orthonormalization
                XMVECTOR b0 = XMLoadFloat3(&((Vertex3D*)vertices)[j].normal);
                b0 = XMVector3Normalize(b0);

                XMVECTOR tan1 = tangent1[j];
                XMVECTOR b1 = XMVectorSubtract(tan1, XMVectorMultiply(XMVector3Dot(b0, tan1), b0));
                b1 = XMVector3Normalize(b1);

                XMVECTOR tan2 = tangent2[j];
                XMVECTOR b2 = XMVectorSubtract(XMVectorSubtract(tan2, XMVectorMultiply(XMVector3Dot(b0, tan2), b0)), XMVectorMultiply(XMVector3Dot(b1, tan2), b1));
                b2 = XMVector3Normalize(b2);

                // handle degenerate vectors
                float len1 = XMVectorGetX(XMVector3Length(b1));
                float len2 = XMVectorGetY(XMVector3Length(b2));

                if ((len1 <= EPSILON) || (len2 <= EPSILON)) {
                    if (len1 > 0.5f) {
                        // Reset bi-tangent from tangent and normal
                        b2 = XMVector3Cross(b0, b1);
                    } else if (len2 > 0.5f) {
                        // Reset tangent from bi-tangent and normal
                        b1 = XMVector3Cross(b2, b0);
                    } else {
                        // Reset both tangent and bi-tangent from normal
                        XMVECTOR axis;

                        float d0 = fabs(XMVectorGetX(XMVector3Dot(g_XMIdentityR0, b0)));
                        float d1 = fabs(XMVectorGetX(XMVector3Dot(g_XMIdentityR1, b0)));
                        float d2 = fabs(XMVectorGetX(XMVector3Dot(g_XMIdentityR2, b0)));
                        if (d0 < d1) {
                            axis = (d0 < d2) ? g_XMIdentityR0 : g_XMIdentityR2;
                        } else if (d1 < d2) {
                            axis = g_XMIdentityR1;
                        } else {
                            axis = g_XMIdentityR2;
                        }

                        b1 = XMVector3Cross(b0, axis);
                        b2 = XMVector3Cross(b0, b1);
                    }
                }

                XMStoreFloat3(&((Vertex3D*)vertices)[j].tangent, b1);

                /*
                if (tangents4) {
                    XMVECTOR bi = XMVector3Cross(b0, tan1);
                    float w = XMVector3Less(XMVector3Dot(bi, tan2), g_XMZero) ? -1.f : 1.f;

                    bi = XMVectorSetW(b1, w);
                    XMStoreFloat4(&tangents4[j], bi);
                }

                if (bitangents) {
                    XMStoreFloat3(&bitangents[j], b2);
                }*/
            }

            _aligned_free(tangent1);
            _aligned_free(tangent2);
        }

        template<typename I>
        void invertWinding(NotNull<Array<VertexStream>> streams, NotNull<Buffer> indexBuffer) {
            for (VertexStream& stream : *streams) {
                if (stream.role == VertexRole::POSITION || stream.role == VertexRole::NORMAL || stream.role == VertexRole::TANGENT) {
                    XMFLOAT3* typedData = (XMFLOAT3*)stream.data.Data;
					for (size_t i = 0; i < stream.data.Size / stream.vertexSize; i++)
						typedData[i].z *= -1;
                }
            }

            I* indices = (I*)indexBuffer->Data;
            for (size_t i = 0; i < indexBuffer->Size/sizeof(I); i += 3) {
                I i0 = indices[i];
                I i1 = indices[i + 1];
                I i2 = indices[i + 2];
                indices[i] = i0;
                indices[i + 2] = i1;
                indices[i + 1] = i2;
            }
        }

        DirectX::BoundingBox computeBoundingBox(const VertexStream& positionStream) {
            Array<XMFLOAT3> positions((const XMFLOAT3*)positionStream.data.Data, positionStream.data.Size);
            XMFLOAT3 min = {}, max = {};
            if (positions.Size > 0) {
                XMFLOAT3& pos = positions[0];
                min = pos;
                max = pos;
            }
            for (size_t i = 1; i < positions.Size; i++) {
                XMFLOAT3& pos = positions[i];
                XMStoreFloat3(&min, XMVectorMin(XMLoadFloat3(&pos), XMLoadFloat3(&min)));
                XMStoreFloat3(&max, XMVectorMax(XMLoadFloat3(&pos), XMLoadFloat3(&max)));
            }
            XMFLOAT3 center;
            XMStoreFloat3(&center, XMVectorScale(XMVectorAdd(XMLoadFloat3(&min), XMLoadFloat3(&max)), 0.5f));
            XMFLOAT3 extents;
            XMStoreFloat3(&extents, XMVectorSubtract(XMLoadFloat3(&center), XMLoadFloat3(&min)));
            return DirectX::BoundingBox(center, extents);
        }
	};
}