# Process Injection: APC Injection
this repository contains POC for three variants of APC Injection.

- Simple APC Injection or Queue an APC to all of the target process threads.
    - Using Standard Win32 APIs (Win32API)
    - Using Native APIS (NTAPI)
    - Using Direct Syscalls (Syscall)
- Early Bird (Queue an APC to the main thread of a newly created process)
- Special User APC or NtQueueApcThreadEx
