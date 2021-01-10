.code

NtQueueApcThreadEx PROC
	mov rax, gs:[60h]                        ; Load PEB into RAX.
NtQueueApcThreadEx_Check_X_X_XXXX:               ; Check major version.
	cmp dword ptr [rax+118h], 10
	je  NtQueueApcThreadEx_Check_10_0_XXXX
	jmp NtQueueApcThreadEx_SystemCall_Unknown
NtQueueApcThreadEx_Check_10_0_XXXX:              ; Check build number for Windows 10.
	cmp word ptr [rax+120h], 10240
	je  NtQueueApcThreadEx_SystemCall_10_0_10240
	cmp word ptr [rax+120h], 10586
	je  NtQueueApcThreadEx_SystemCall_10_0_10586
	cmp word ptr [rax+120h], 14393
	je  NtQueueApcThreadEx_SystemCall_10_0_14393
	cmp word ptr [rax+120h], 15063
	je  NtQueueApcThreadEx_SystemCall_10_0_15063
	cmp word ptr [rax+120h], 16299
	je  NtQueueApcThreadEx_SystemCall_10_0_16299
	cmp word ptr [rax+120h], 17134
	je  NtQueueApcThreadEx_SystemCall_10_0_17134
	cmp word ptr [rax+120h], 17763
	je  NtQueueApcThreadEx_SystemCall_10_0_17763
	cmp word ptr [rax+120h], 18362
	je  NtQueueApcThreadEx_SystemCall_10_0_18362
	cmp word ptr [rax+120h], 18363
	je  NtQueueApcThreadEx_SystemCall_10_0_18363
	cmp word ptr [rax+120h], 19041
	je  NtQueueApcThreadEx_SystemCall_10_0_19041
	cmp word ptr [rax+120h], 19042
	je  NtQueueApcThreadEx_SystemCall_10_0_19042
	jmp NtQueueApcThreadEx_SystemCall_Unknown
NtQueueApcThreadEx_SystemCall_10_0_10240:        ; Windows 10.0.10240 (1507)
	mov eax, 014bh
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_10586:        ; Windows 10.0.10586 (1511)
	mov eax, 014eh
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_14393:        ; Windows 10.0.14393 (1607)
	mov eax, 0152h
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_15063:        ; Windows 10.0.15063 (1703)
	mov eax, 0158h
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_16299:        ; Windows 10.0.16299 (1709)
	mov eax, 015bh
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_17134:        ; Windows 10.0.17134 (1803)
	mov eax, 015dh
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_17763:        ; Windows 10.0.17763 (1809)
	mov eax, 015eh
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_18362:        ; Windows 10.0.18362 (1903)
	mov eax, 015fh
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_18363:        ; Windows 10.0.18363 (1909)
	mov eax, 015fh
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_19041:        ; Windows 10.0.19041 (2004)
	mov eax, 0165h
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_10_0_19042:        ; Windows 10.0.19042 (20H2)
	mov eax, 0165h
	jmp NtQueueApcThreadEx_Epilogue
NtQueueApcThreadEx_SystemCall_Unknown:           ; Unknown/unsupported version.
	ret
NtQueueApcThreadEx_Epilogue:
	mov r10, rcx
	syscall
	ret
NtQueueApcThreadEx ENDP

NtOpenProcess PROC
	mov rax, gs:[60h]                   ; Load PEB into RAX.
NtOpenProcess_Check_X_X_XXXX:               ; Check major version.
	cmp dword ptr [rax+118h], 10
	je  NtOpenProcess_Check_10_0_XXXX
	jmp NtOpenProcess_SystemCall_Unknown
NtOpenProcess_Check_10_0_XXXX:              ; Check build number for Windows 10.
	cmp word ptr [rax+120h], 10240
	je  NtOpenProcess_SystemCall_10_0_10240
	cmp word ptr [rax+120h], 10586
	je  NtOpenProcess_SystemCall_10_0_10586
	cmp word ptr [rax+120h], 14393
	je  NtOpenProcess_SystemCall_10_0_14393
	cmp word ptr [rax+120h], 15063
	je  NtOpenProcess_SystemCall_10_0_15063
	cmp word ptr [rax+120h], 16299
	je  NtOpenProcess_SystemCall_10_0_16299
	cmp word ptr [rax+120h], 17134
	je  NtOpenProcess_SystemCall_10_0_17134
	cmp word ptr [rax+120h], 17763
	je  NtOpenProcess_SystemCall_10_0_17763
	cmp word ptr [rax+120h], 18362
	je  NtOpenProcess_SystemCall_10_0_18362
	cmp word ptr [rax+120h], 18363
	je  NtOpenProcess_SystemCall_10_0_18363
	cmp word ptr [rax+120h], 19041
	je  NtOpenProcess_SystemCall_10_0_19041
	cmp word ptr [rax+120h], 19042
	je  NtOpenProcess_SystemCall_10_0_19042
	jmp NtOpenProcess_SystemCall_Unknown
NtOpenProcess_SystemCall_10_0_10240:        ; Windows 10.0.10240 (1507)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_10586:        ; Windows 10.0.10586 (1511)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_14393:        ; Windows 10.0.14393 (1607)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_15063:        ; Windows 10.0.15063 (1703)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_16299:        ; Windows 10.0.16299 (1709)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_17134:        ; Windows 10.0.17134 (1803)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_17763:        ; Windows 10.0.17763 (1809)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_18362:        ; Windows 10.0.18362 (1903)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_18363:        ; Windows 10.0.18363 (1909)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_19041:        ; Windows 10.0.19041 (2004)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_10_0_19042:        ; Windows 10.0.19042 (20H2)
	mov eax, 0026h
	jmp NtOpenProcess_Epilogue
NtOpenProcess_SystemCall_Unknown:           ; Unknown/unsupported version.
	ret
NtOpenProcess_Epilogue:
	mov r10, rcx
	syscall
	ret
NtOpenProcess ENDP

NtAllocateVirtualMemory PROC
	mov rax, gs:[60h]                             ; Load PEB into RAX.
NtAllocateVirtualMemory_Check_X_X_XXXX:               ; Check major version.
	cmp dword ptr [rax+118h], 10
	je  NtAllocateVirtualMemory_Check_10_0_XXXX
	jmp NtAllocateVirtualMemory_SystemCall_Unknown
NtAllocateVirtualMemory_Check_10_0_XXXX:              ; Check build number for Windows 10.
	cmp word ptr [rax+120h], 10240
	je  NtAllocateVirtualMemory_SystemCall_10_0_10240
	cmp word ptr [rax+120h], 10586
	je  NtAllocateVirtualMemory_SystemCall_10_0_10586
	cmp word ptr [rax+120h], 14393
	je  NtAllocateVirtualMemory_SystemCall_10_0_14393
	cmp word ptr [rax+120h], 15063
	je  NtAllocateVirtualMemory_SystemCall_10_0_15063
	cmp word ptr [rax+120h], 16299
	je  NtAllocateVirtualMemory_SystemCall_10_0_16299
	cmp word ptr [rax+120h], 17134
	je  NtAllocateVirtualMemory_SystemCall_10_0_17134
	cmp word ptr [rax+120h], 17763
	je  NtAllocateVirtualMemory_SystemCall_10_0_17763
	cmp word ptr [rax+120h], 18362
	je  NtAllocateVirtualMemory_SystemCall_10_0_18362
	cmp word ptr [rax+120h], 18363
	je  NtAllocateVirtualMemory_SystemCall_10_0_18363
	cmp word ptr [rax+120h], 19041
	je  NtAllocateVirtualMemory_SystemCall_10_0_19041
	cmp word ptr [rax+120h], 19042
	je  NtAllocateVirtualMemory_SystemCall_10_0_19042
	jmp NtAllocateVirtualMemory_SystemCall_Unknown
NtAllocateVirtualMemory_SystemCall_10_0_10240:        ; Windows 10.0.10240 (1507)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_10586:        ; Windows 10.0.10586 (1511)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_14393:        ; Windows 10.0.14393 (1607)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_15063:        ; Windows 10.0.15063 (1703)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_16299:        ; Windows 10.0.16299 (1709)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_17134:        ; Windows 10.0.17134 (1803)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_17763:        ; Windows 10.0.17763 (1809)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_18362:        ; Windows 10.0.18362 (1903)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_18363:        ; Windows 10.0.18363 (1909)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_19041:        ; Windows 10.0.19041 (2004)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_10_0_19042:        ; Windows 10.0.19042 (20H2)
	mov eax, 0018h
	jmp NtAllocateVirtualMemory_Epilogue
NtAllocateVirtualMemory_SystemCall_Unknown:           ; Unknown/unsupported version.
	ret
NtAllocateVirtualMemory_Epilogue:
	mov r10, rcx
	syscall
	ret
NtAllocateVirtualMemory ENDP

NtWriteVirtualMemory PROC
	mov rax, gs:[60h]                          ; Load PEB into RAX.
NtWriteVirtualMemory_Check_X_X_XXXX:               ; Check major version.
	cmp dword ptr [rax+118h], 10
	je  NtWriteVirtualMemory_Check_10_0_XXXX
	jmp NtWriteVirtualMemory_SystemCall_Unknown
NtWriteVirtualMemory_Check_10_0_XXXX:              ; Check build number for Windows 10.
	cmp word ptr [rax+120h], 10240
	je  NtWriteVirtualMemory_SystemCall_10_0_10240
	cmp word ptr [rax+120h], 10586
	je  NtWriteVirtualMemory_SystemCall_10_0_10586
	cmp word ptr [rax+120h], 14393
	je  NtWriteVirtualMemory_SystemCall_10_0_14393
	cmp word ptr [rax+120h], 15063
	je  NtWriteVirtualMemory_SystemCall_10_0_15063
	cmp word ptr [rax+120h], 16299
	je  NtWriteVirtualMemory_SystemCall_10_0_16299
	cmp word ptr [rax+120h], 17134
	je  NtWriteVirtualMemory_SystemCall_10_0_17134
	cmp word ptr [rax+120h], 17763
	je  NtWriteVirtualMemory_SystemCall_10_0_17763
	cmp word ptr [rax+120h], 18362
	je  NtWriteVirtualMemory_SystemCall_10_0_18362
	cmp word ptr [rax+120h], 18363
	je  NtWriteVirtualMemory_SystemCall_10_0_18363
	cmp word ptr [rax+120h], 19041
	je  NtWriteVirtualMemory_SystemCall_10_0_19041
	cmp word ptr [rax+120h], 19042
	je  NtWriteVirtualMemory_SystemCall_10_0_19042
	jmp NtWriteVirtualMemory_SystemCall_Unknown
NtWriteVirtualMemory_SystemCall_10_0_10240:        ; Windows 10.0.10240 (1507)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_10586:        ; Windows 10.0.10586 (1511)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_14393:        ; Windows 10.0.14393 (1607)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_15063:        ; Windows 10.0.15063 (1703)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_16299:        ; Windows 10.0.16299 (1709)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_17134:        ; Windows 10.0.17134 (1803)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_17763:        ; Windows 10.0.17763 (1809)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_18362:        ; Windows 10.0.18362 (1903)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_18363:        ; Windows 10.0.18363 (1909)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_19041:        ; Windows 10.0.19041 (2004)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_10_0_19042:        ; Windows 10.0.19042 (20H2)
	mov eax, 003ah
	jmp NtWriteVirtualMemory_Epilogue
NtWriteVirtualMemory_SystemCall_Unknown:           ; Unknown/unsupported version.
	ret
NtWriteVirtualMemory_Epilogue:
	mov r10, rcx
	syscall
	ret
NtWriteVirtualMemory ENDP

NtOpenThread PROC
	mov rax, gs:[60h]                  ; Load PEB into RAX.
NtOpenThread_Check_X_X_XXXX:               ; Check major version.
	cmp dword ptr [rax+118h], 10
	je  NtOpenThread_Check_10_0_XXXX
	jmp NtOpenThread_SystemCall_Unknown
NtOpenThread_Check_10_0_XXXX:              ; Check build number for Windows 10.
	cmp word ptr [rax+120h], 10240
	je  NtOpenThread_SystemCall_10_0_10240
	cmp word ptr [rax+120h], 10586
	je  NtOpenThread_SystemCall_10_0_10586
	cmp word ptr [rax+120h], 14393
	je  NtOpenThread_SystemCall_10_0_14393
	cmp word ptr [rax+120h], 15063
	je  NtOpenThread_SystemCall_10_0_15063
	cmp word ptr [rax+120h], 16299
	je  NtOpenThread_SystemCall_10_0_16299
	cmp word ptr [rax+120h], 17134
	je  NtOpenThread_SystemCall_10_0_17134
	cmp word ptr [rax+120h], 17763
	je  NtOpenThread_SystemCall_10_0_17763
	cmp word ptr [rax+120h], 18362
	je  NtOpenThread_SystemCall_10_0_18362
	cmp word ptr [rax+120h], 18363
	je  NtOpenThread_SystemCall_10_0_18363
	cmp word ptr [rax+120h], 19041
	je  NtOpenThread_SystemCall_10_0_19041
	cmp word ptr [rax+120h], 19042
	je  NtOpenThread_SystemCall_10_0_19042
	jmp NtOpenThread_SystemCall_Unknown
NtOpenThread_SystemCall_10_0_10240:        ; Windows 10.0.10240 (1507)
	mov eax, 0119h
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_10586:        ; Windows 10.0.10586 (1511)
	mov eax, 011ch
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_14393:        ; Windows 10.0.14393 (1607)
	mov eax, 011fh
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_15063:        ; Windows 10.0.15063 (1703)
	mov eax, 0123h
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_16299:        ; Windows 10.0.16299 (1709)
	mov eax, 0125h
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_17134:        ; Windows 10.0.17134 (1803)
	mov eax, 0127h
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_17763:        ; Windows 10.0.17763 (1809)
	mov eax, 0128h
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_18362:        ; Windows 10.0.18362 (1903)
	mov eax, 0129h
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_18363:        ; Windows 10.0.18363 (1909)
	mov eax, 0129h
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_19041:        ; Windows 10.0.19041 (2004)
	mov eax, 012eh
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_10_0_19042:        ; Windows 10.0.19042 (20H2)
	mov eax, 012eh
	jmp NtOpenThread_Epilogue
NtOpenThread_SystemCall_Unknown:           ; Unknown/unsupported version.
	ret
NtOpenThread_Epilogue:
	mov r10, rcx
	syscall
	ret
NtOpenThread ENDP

end
