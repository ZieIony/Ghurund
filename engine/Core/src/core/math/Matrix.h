#pragma once

#include <memory>
#include <DirectXMath.h>

namespace Ghurund::Core {
	static inline const ::DirectX::XMFLOAT4X4 makeIdentityMatrix() {
		static ::DirectX::XMFLOAT4X4 identity = [] -> ::DirectX::XMFLOAT4X4 {
			::DirectX::XMFLOAT4X4 identity;
			::DirectX::XMStoreFloat4x4(&identity, ::DirectX::XMMatrixIdentity());
			return identity;
		}();
		return identity;
	};

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

	inline ::DirectX::XMFLOAT4X4 makeSaturationMatrix(float sat) {
		::DirectX::XMFLOAT4X4 m = makeIdentityMatrix();

		float invSat = 1 - sat;
		float R = 0.213f * invSat;
		float G = 0.715f * invSat;
		float B = 0.072f * invSat;

		m.m[0][0] = R + sat;
		m.m[1][0] = G;
		m.m[2][0] = B;
		m.m[0][1] = R;
		m.m[1][1] = G + sat;
		m.m[2][1] = B;
		m.m[0][2] = R;
		m.m[1][2] = G;
		m.m[2][2] = B + sat;

		return m;
	}
}
