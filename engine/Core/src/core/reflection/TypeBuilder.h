#pragma once

#include "Type.h"
#include "core/exception/Exceptions.h"

#include <typeinfo>

namespace Ghurund::Core {
	struct TypeName {
		AString _namespace;
		AString name;
		List<AString> templateParams;

		static TypeName parse(const AString& typeidName);
	};

	template<class T>
	class TypeBuilder {
	private:
		TypeModifier modifiers = (TypeModifier)0;
		const AString _namespace;
		const AString name;
		Type* supertype = nullptr;
		size_t size;
		List<std::reference_wrapper<const BaseConstructor>> constructors;
		List<std::reference_wrapper<const BaseProperty>> properties;
		List<std::reference_wrapper<const BaseMethod>> methods;
		List<std::reference_wrapper<const Type>> templateParams;
		//size_t numberOfTemplateParams = 0;

		TypeBuilder(const TypeName& typeName): TypeBuilder(typeName._namespace, typeName.name) {
			if (!typeName.templateParams.Empty) {
				//numberOfTemplateParams = typeName.templateParams.Size;
				// this is really cool, but doesn't work because certain types may not be available in the list of types yet
				/*for (const AString& param : typeName.templateParams) {
					const TypeName& paramTypeName = TypeName::parse(param);
					const Type& paramType = Type::byName(paramTypeName._namespace, paramTypeName.name);
					templateParams.add(std::reference_wrapper<const Type>(paramType));
				}*/
				modifiers |= TypeModifier::TEMPLATE;
			}
			if (std::is_abstract<T>::value) {
				modifiers |= TypeModifier::ABSTRACT;
			}
		}

		TypeBuilder(const AString& _namespace, const AString& name) requires std::is_default_constructible<T>::value && !std::is_abstract<T>::value
			: _namespace(_namespace), name(name), size(sizeof(T)) {
			static const auto CONSTRUCTOR = Constructor<T>();
			constructors.add(CONSTRUCTOR);
		}

		TypeBuilder(const AString& _namespace, const AString& name): _namespace(_namespace), name(name), size(sizeof(T)) {}

	public:
		TypeBuilder():TypeBuilder(TypeName::parse(typeid(T).name())) {}

		template<typename... ArgsT>
		inline TypeBuilder& withConstructor(const Constructor<T, ArgsT...>& constructor) {
			constructors.add(constructor);
			return *this;
		}

		/*inline TypeBuilder& withZeroArgsConstructor() {
			static const auto CONSTRUCTOR = Constructor<T>();
			constructors.add(CONSTRUCTOR);
			return *this;
		}*/

		/*inline TypeBuilder& withModifiers(TypeModifier modifiers) {
			this->modifiers = modifiers;
			return *this;
		}

		inline TypeBuilder& withModifier(TypeModifier modifier) {
			this->modifiers = this->modifiers | modifier;
			return *this;
		}*/

		inline TypeBuilder& withSupertype(const Type& supertype) {
			this->supertype = (Type*)&supertype;
			return *this;
		}

		inline TypeBuilder& withProperty(const BaseProperty& property) {
			properties.add(property);
			return *this;
		}

		inline TypeBuilder& withMethod(const BaseMethod& method) {
			methods.add(method);
			return *this;
		}

		template<typename... ArgsT>
		inline TypeBuilder& withTemplateParams() {
			const Array<std::reference_wrapper<const Type>> types = { getType<ArgsT>()... };
			for (const Type& type : types)
				templateParams.add(type);
			modifiers |= TypeModifier::TEMPLATE;
			return *this;
		}

		template<typename T>
		inline TypeBuilder& withTemplateParam() {
			templateParams.add(getType<T>());
			modifiers |= TypeModifier::TEMPLATE;
			return *this;
		}

		inline TypeBuilder& withTemplateParam(const Type& type) {
			templateParams.add(type);
			modifiers |= TypeModifier::TEMPLATE;
			return *this;
		}

		operator Type() const {
			TypeModifier m = constructors.Empty ? modifiers | TypeModifier::ABSTRACT : modifiers;
			// this gives problems with more complex template parameters like collection traits and pointer deleters
			/*if (templateParams.Size != numberOfTemplateParams) {
				auto message = std::format("this type has {} template params, but {} are defined", numberOfTemplateParams, templateParams.Size);
				throw InvalidStateException(message.c_str());
			}*/
			return Type(_namespace, name, size, m, supertype, constructors, properties, methods, templateParams);
		}
	};
}