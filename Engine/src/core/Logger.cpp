#include "Logger.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <process.h>
#include "dbghelp.h"
#include "collection/String.h"

namespace Ghurund {
	HANDLE Logger::debugOutput;
	HANDLE Logger::file;
	LogOutput Logger::output;
	HANDLE Logger::process;
	SYMBOL_INFO *Logger::symbol;
    IMAGEHLP_LINE Logger::line;
    CriticalSection Logger::criticalSection;
	List<String> *Logger::loggedOnce;

	address_t Logger::getAddress() {
		constexpr int frames = 1;
		void *stack;
		WORD numberOfFrames = CaptureStackBackTrace(3, frames, &stack, NULL);

		return (address_t)stack;
	}

	String Logger::getFileLine(address_t address) {
		tchar *buffer = nullptr;

		DWORD64 displacement = 0;
		if (!SymFromAddr(process, address, &displacement, symbol)) {
			printToBuffer(&buffer, _T("[%p]: "), address);
			goto cleanUp;
		}

		DWORD displacement2 = 0;
		if (!SymGetLineFromAddr(process, address, &displacement2, &line)) {
			printToBuffer(&buffer, _T("[%p:%hs]: "), address, symbol->Name);
			goto cleanUp;
		}

		printToBuffer(&buffer, _T("%hs(%lu): [0x%p %hs(..)] "), line.FileName, line.LineNumber, address, symbol->Name);

	cleanUp:
		String str(buffer);
		delete[] buffer;
		return str;
	}

	void Logger::log(const String &str){
		criticalSection.enter();
		switch (output) {
		case LogOutput::CUSTOM_CONSOLE:
			WriteConsole(debugOutput, str, str.Length, nullptr, nullptr);
			break;
		case LogOutput::SYSTEM_CONSOLE:
			OutputDebugString(str);
			break;
		case LogOutput::FILE:
			unsigned long bytes;
			WriteFile(file, str, str.Length * sizeof(tchar), &bytes, nullptr);
			break;
		}
		criticalSection.leave();
	}

    void Logger::logVA(const tchar *format, va_list args) {
        String fileLine = getFileLine(getAddress());
        tchar *buffer = nullptr;

        if(!printToBuffer(&buffer, format, args))
            goto cleanUp;

        fileLine.add(buffer);
        log(fileLine);

    cleanUp:
        delete[] buffer;
    }

	void Logger::log(const tchar *format, ...) {
#ifndef _DEBUG
		return;
#endif

		va_list args;
		va_start(args, format);

        logVA(format, args);

		va_end(args);
	}

    Status Logger::log(Status status, const tchar *format, ...) {
#ifndef _DEBUG
        return status;
#endif

        log(_T("%i "), status);

        va_list args;
        va_start(args, format);

        logVA(format, args);

        va_end(args);

        return status;
    }

    void Logger::logOnce(const tchar * format, ...) {
#ifndef _DEBUG
        return;
#endif

        va_list args;
        va_start(args, format);

        String fileLine = getFileLine(getAddress());
        tchar *buffer = nullptr;

        if(!printToBuffer(&buffer, format, args))
            goto cleanUp;

        fileLine.add(buffer);
        if(!loggedOnce->contains(fileLine)) {
            loggedOnce->add(fileLine);
            log(fileLine);
        }

    cleanUp:
        delete[] buffer;
        va_end(args);
    }

    void Logger::init(LogOutput output, const tchar *name) {
#ifndef _DEBUG
		return;
#endif

		Logger::output = output;
		loggedOnce = ghnew List<String>();

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

		delete loggedOnce;

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