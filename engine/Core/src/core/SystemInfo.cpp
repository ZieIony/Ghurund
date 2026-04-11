#include "ghcpch.h"
#include "SystemInfo.h"

#include <Windows.h>
#include <psapi.h>

namespace Ghurund::Core {
	AString SystemInfo::getProcessorArchitecture() {
		SYSTEM_INFO siSysInfo;
		GetSystemInfo(&siSysInfo);
		switch (siSysInfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_AMD64:
			return "x64";
		case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
			return "WOW64";
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			return "Intel Itanium Processor Family (IPF)";
		case PROCESSOR_ARCHITECTURE_INTEL:
			return "x86";
			break;
		default:
			return "unknown";
		}
	}

	ProcessorInfo SystemInfo::getProcessorInfo() {
		ProcessorInfo info = {};
		SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = nullptr, * ptr = nullptr;
		DWORD returnLength = 0;
		DWORD byteOffset = 0;

		DWORD rc = GetLogicalProcessorInformation(buffer, &returnLength);
		buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)ghnew uint8_t[returnLength];
		rc = GetLogicalProcessorInformation(buffer, &returnLength);

		ptr = buffer;

		while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength) {
			switch (ptr->Relationship) {
			case RelationProcessorCore:
				info.cores++;
				info.logicalProcessors += countSetBits(ptr->ProcessorMask);
				break;
			default:
				break;
			}
			byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
			ptr++;
		}

		delete[] buffer;

		info.architecture = getProcessorArchitecture();

		return info;
	}

	MemoryInfo SystemInfo::getMemoryInfo() {
		MemoryInfo info = {};

		ULONGLONG total;
		GetPhysicallyInstalledSystemMemory(&total);
		info.totalKb = total;

		HANDLE hProcess = GetCurrentProcess();
		PROCESS_MEMORY_COUNTERS pmc;

		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
			info.file = pmc.PagefileUsage;
			info.paged = pmc.QuotaPagedPoolUsage;
			info.nonPaged = pmc.QuotaNonPagedPoolUsage;
			info.workingSet = pmc.WorkingSetSize;
		}

		return info;
	}
}
