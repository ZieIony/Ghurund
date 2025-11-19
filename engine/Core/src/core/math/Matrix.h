#pragma once

#include <memory>
#include <DirectXMath.h>

namespace Ghurund::Core {
	static inline const ::DirectX::XMFLOAT4X4 MATRIX_IDENTITY = [] {
		::DirectX::XMFLOAT4X4 identity;
		::DirectX::XMStoreFloat4x4(&identity, ::DirectX::XMMatrixIdentity());
		return identity;
	}();

	struct Matrix3x2 {
		union {
			struct {
				float m11, m12, m21, m22, dx, dy;
			};

			float m[3][2];
		};

		virtual bool operator==(const Matrix3x2& other) const {
			return memcmp(m, other.m, sizeof(float) * 6) == 0;
		}
	};
}
