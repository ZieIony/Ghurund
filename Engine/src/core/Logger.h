#pragma once

#include "../Ghurund.h"
#include "Noncopyable.h"
#include "dbghelp.h"
#include "CriticalSection.h"

namespace Ghurund {
	enum class LogOutput {
		SYSTEM_CONSOLE, CUSTOM_CONSOLE, FILE
	};

	class Logger :public Noncopyable {
	private:
		static HANDLE debugOutput;
        static HANDLE file;
        static LogOutput output;
		static HANDLE process;
		static SYMBOL_INFO *symbol;
		static IMAGEHLP_LINE line;
        static CriticalSection criticalSection;

        static tchar * getFileLine();

	public:
        static void init(LogOutput output = LogOutput::SYSTEM_CONSOLE, const tchar *name = nullptr);

        static void uninit();

		static void log(const tchar *format, ...);
    };

}