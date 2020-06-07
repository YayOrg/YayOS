# YYSloth Kernel

### Why it is named like this?
"YY_" is a prefix that stands for **Yay**Os. Sloth is one of the slowest animals on the earth, which kinda mimics YYSloth kernel performance in some cases.

### What system calls are currently available?

Here are all of them

```c++
//Exit process. Syscall number 0.
void YY_ExitProcess();

//Analogues to fork(). Syscall number 1.
void YY_DuplicateProcess();

//Print count symbols
//from buf string. Syscall number 2.
int64_t YY_ConsoleWrite(const char* buf, uint64_t count);

//Length limit for YY_SystemInfo strings
constexpr uint64_t YY_SystemInfoStringLimit = 64;

//System info struct used for getting system info
#pragma pack(1)
    struct YY_SystemInfo {
        char kernelName[YY_SystemInfoStringLimit + 1];
        char kernelRelease[YY_SystemInfoStringLimit + 1];
        char kernelVersion[YY_SystemInfoStringLimit + 1];
        char machine[YY_SystemInfoStringLimit + 1];
        char processor[YY_SystemInfoStringLimit + 1];
        char hardwarePlatform[YY_SystemInfoStringLimit + 1];
        char operatingSystem[YY_SystemInfoStringLimit + 1];
    };
#pragma pack(0)

//Get system info (analogues to uname). Syscall number 3
int64_t YY_GetSystemInfo(YY_SystemInfo* buf);

//Yield execution. Syscall number 4
void YY_Yield();

//Allocate pagesCount pages with specified permissions
//flags format: bit 0 - writable, bit 1 - executable
//Syscall number 5
void* YY_VirtualAlloc(uint64_t pagesCount, uint64_t flags);

//Deallocate pagesCount pages starting from address. Syscall number 6
int64_t YY_VirtualFree(void* start, uint64_t pagesCount);

//Get page size Syscall number 7
uint64_t YY_GetPageSize();
```

### How can I use these system calls in assembly?

YYSloth uses ```int 57h``` instruction for system calls. System call number is passed to ```rax``` and everything else is specified by SysV x86_64 calling convention. Here is an example:
```nasm

YY_ConsoleWrite: equ 2
YY_ExitProcess: equ 0

section .data
msg: db "Hello, world", 13, 10
msglen: equ $ - msg

section .text
    global _start
_start:
    ; output nice message to the screen
    mov rax, YY_ConsoleWrite ; syscall number
    mov rsi, msg ; pointer to message
    mov rdi, msglen ; length of the message
    int 57h
    ; exit process
    mov rax, YY_ExitProcess ; syscall number
    int 57h
```

### Any docs on the kernel source?

Perhaps one day...