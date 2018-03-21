#include "Logger.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <process.h>
#include "dbghelp.h"

namespace Ghurund {
	HANDLE Logger::debugOutput;
	HANDLE Logger::file;
	LogOutput Logger::output;
	HANDLE Logger::process;
	SYMBOL_INFO *Logger::symbol;
    IMAGEHLP_LINE Logger::line;
    CriticalSection Logger::criticalSection;

	tchar *Logger::getFileLine() {
		tchar *buffer = nullptr;

		constexpr int frames = 1;
		void *stack;
		WORD numberOfFrames = CaptureStackBackTrace(2, frames, &stack, NULL);

		DWORD64 displacement = 0;
		address_t address = (address_t)stack;
		SymFromAddr(process, address, &displacement, symbol);

		DWORD displacement2 = 0;
		if (!SymGetLineFromAddr(process, address, &displacement2, &line))
			return nullptr;

		int index = strlen(line.FileName);
		for (index; index > 0 && line.FileName[index] != '\\'; index--);
		printToBuffer(&buffer, _T("%hs:%lu [%hs]: "), index == 0 ? line.FileName : (line.FileName + index + 1), line.LineNumber, symbol->Name);

		return buffer;
	}

	void Logger::log(const tchar *format, ...) {
#ifndef _DEBUG
		return;
#endif

        criticalSection.enter();

		va_list args;
		va_start(args, format);

		tchar *fileLine = getFileLine();
        tchar *buffer = nullptr;
        
        if (fileLine == nullptr)
			goto cleanUp;

		if (!printToBuffer(&buffer, format, args))
			goto cleanUp;

		va_end(args);

		DWORD cCharsWritten;

		switch (output) {
		case LogOutput::CUSTOM_CONSOLE:
			WriteConsole(debugOutput, fileLine, _tcslen(fileLine), &cCharsWritten, nullptr);
			WriteConsole(debugOutput, buffer, _tcslen(buffer), &cCharsWritten, nullptr);
			//OutputDebugString(msg);
			break;
		case LogOutput::SYSTEM_CONSOLE:
			_tprintf(_T("%s%s"), fileLine, buffer);
			break;
		case LogOutput::FILE:
			unsigned long bytes;
			WriteFile(file, fileLine, _tcslen(fileLine) * sizeof(tchar), &bytes, nullptr);
			WriteFile(file, buffer, _tcslen(buffer) * sizeof(tchar), &bytes, nullptr);
			break;
		}

    cleanUp:
        delete[] fileLine;
		delete[] buffer;

        criticalSection.leave();
	}

	void Logger::init(LogOutput output, const tchar *name) {
#ifndef _DEBUG
		return;
#endif

		Logger::output = output;

		if (symbol == nullptr) {
			constexpr int frames = 1;
			process = GetCurrentProcess();
			SymInitialize(process, NULL, TRUE);

			constexpr int symbolStructSize = sizeof(SYMBOL_INFO) + (MAX_SYM_NAME - 1) * sizeof(tchar);
			symbol = (SYMBOL_INFO*)(ghnew char[symbolStructSize]);
			symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
			symbol->MaxNameLen = MAX_SYM_NAME;

			line.SizeOfStruct = sizeof(IMAGEHLP_LINE);
		}

		switch (output) {
		case LogOutput::CUSTOM_CONSOLE:
		{
			AllocConsole();
			SetConsoleTitle(name != nullptr ? name : _T("Debug Window"));
			debugOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD co = { 80,25 };
			SetConsoleScreenBufferSize(debugOutput, co);
		}
		break;
		case LogOutput::SYSTEM_CONSOLE:
#ifdef UNICODE
			//_setmode(_fileno(stdout), _O_U16TEXT);
			SetConsoleOutputCP(65001);
#endif
			break;
		case LogOutput::FILE:
			file = CreateFile(name != nullptr ? name : _T("Ghurund.log"), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			break;
		}
	}

	void Logger::uninit() {
#ifndef _DEBUG
		return;
#endif

        if(symbol != nullptr) {
            delete[] symbol;
            SymCleanup(process);
        }

		switch (output) {
		case LogOutput::CUSTOM_CONSOLE:
            FreeConsole();
            break;
		case LogOutput::SYSTEM_CONSOLE:
			break;
		case LogOutput::FILE:
			CloseHandle(file);
			break;
		}
	}
}