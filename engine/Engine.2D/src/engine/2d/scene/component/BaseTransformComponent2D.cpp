#include "ghe2dpch.h"
#include "BaseTransformComponent2D.h"

#include "core/math/Point.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& BaseTransformComponent2D::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BaseTransformComponent2D>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
		
	void BaseTransformComponent2D::update(const XMFLOAT4X4& parentTransformation, const Timer& timer) {
		auto scaling = XMMatrixScaling(Scale.x, Scale.y, 1);
		auto rotation = XMMatrixRotationZ(Rotation / 180 * XM_PI);
		auto translation = XMMatrixTranslation(Position.x, Position.y, 0);
		auto local = scaling * rotation * translation;
		XMStoreFloat4x4(&localTransformation, local);

		XMStoreFloat4x4(&worldTransformation, local * XMLoadFloat4x4(&parentTransformation));

		__super::update(worldTransformation, timer);
	}

#ifdef _DEBUG
	String BaseTransformComponent2D::printTree() const {
		String str = [&]() {
			if (Name) {
				return String(std::format(_T("{} '{}', pos: {}, rot: {}, scale: {}\n"), Type.Name, *Name, Position, Rotation, Scale).c_str());
			} else {
				return String(std::format(_T("{}, pos: {}, rot: {}, scale: {}\n"), Type.Name, Position, Rotation, Scale).c_str());
			}
		}();
		size_t len = 4;
		for (auto it = Components.begin(); it != Components.end(); ++it) {
			Component2D* c = *it;
			auto childStr = c->printTree().split(_T("\n"));
			for (size_t j = 0; j < len; j++)
				str.add(_T(" "));
			str.add(_T("\\-"));
			str.add(childStr[0]);
			for (size_t i = 1; i < childStr.Size; i++) {
				str.add(_T("\n"));
				for (size_t j = 0; j < len; j++)
					str.add(_T(" "));
				str.add(it != Components.end() ? _T("| ") : _T("  "));
				str.add(childStr[i]);
			}
			str.add(_T("\n"));
		}
		return str;
	}
#endif
}
