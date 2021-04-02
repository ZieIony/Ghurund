#pragma once

namespace Ghurund {
	class CompilationTarget {
	private:
        unsigned int value;
        const char *text;

	public:
		static const CompilationTarget &SHADER_5_0, &SHADER_4_1, &SHADER_4_0, &SHADER_4_0_LEVEL_9_3, &SHADER_4_0_LEVEL_9_1;

        static const CompilationTarget &fromValue(unsigned int value) {
            if(value==SHADER_5_0.value) {
                return SHADER_5_0;
            } else if(value==SHADER_4_1.value) {
                return SHADER_4_1;
            } else if(value==SHADER_4_0.value) {
                return SHADER_4_0;
            } else if(value==SHADER_4_0_LEVEL_9_3.value) {
                return SHADER_4_0_LEVEL_9_3;
            } else {
                return SHADER_4_0_LEVEL_9_1;
            }
        }

		CompilationTarget(unsigned int value, const char *text) {
            this->value = value;
            this->text = text;
		}

        unsigned int getValue() const {
            return value;
        }

        operator unsigned int() const { return value; }

		const char *toString() const {
			return text;
		}
	};

}