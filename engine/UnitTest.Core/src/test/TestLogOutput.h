#pragma once

#include "CppUnitTest.h"

#include "core/logging/Log.h"
#include "core/logging/Logger.h"
#include "core/logging/LogOutput.h"

#include <format>

namespace UnitTest::Utils {
    class TestLogOutput:public Ghurund::Core::LogOutput {
    public:
        virtual void log(const Ghurund::Core::Log& log) {
            auto text = std::format(_T("{}: {}\n"), log.fileLine, log.message);
            Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(text.c_str());
        }

        static int loggerReportHook(int reportType, char* message, int* returnValue) {
            int nRet = FALSE;

            Ghurund::Core::String text = Ghurund::Core::convertText<char, tchar>(Ghurund::Core::AString(message));

            switch (reportType) {
            case _CRT_ASSERT:
            {
                Ghurund::Core::Logger::log(Ghurund::Core::LogType::ERR0R, text.Data);
                nRet = TRUE;
                break;
            }

            case _CRT_WARN:
            {
                Ghurund::Core::Logger::log(Ghurund::Core::LogType::WARNING, text.Data);
                break;
            }

            case _CRT_ERROR:
            {
                Ghurund::Core::Logger::log(Ghurund::Core::LogType::ERR0R, text.Data);
                break;
            }

            default:
            {
                Ghurund::Core::Logger::log(Ghurund::Core::LogType::INFO, text.Data);
                break;
            }
            }

            if (returnValue)
                *returnValue = 0;

            return   nRet;
        }

        static void initReportHook() {
            _CrtSetReportHook(loggerReportHook);
        }
    };
}