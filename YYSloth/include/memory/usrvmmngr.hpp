#ifndef __USRVMMNGR_HPP_INCLUDED__
#define __USRVMMNGR_HPP_INCLUDED__

#include <core/cpprt.hpp>
#include <memory/vmbase.hpp>
#include <memory/vmmap.hpp>
#include <utils.hpp>

namespace memory {
    struct UserVirtualMemoryArea {
        UserVirtualMemoryArea *prev, *next;
        memory::vaddr_t start;
        uint64_t size;
        UserVirtualMemoryArea(memory::vaddr_t start, uint64_t size);
        UserVirtualMemoryArea(UserVirtualMemoryArea *area);
        bool in(memory::vaddr_t addr);
    };
    class UserVirtualAllocator {
        UserVirtualMemoryArea *m_head;
        uint64_t m_brkMin, m_brk;

        UserVirtualMemoryArea *findBestFit(uint64_t size);
        void cut(UserVirtualMemoryArea *area);
        bool cutFrom(UserVirtualMemoryArea *area, memory::vaddr_t start,
                     uint64_t size);
        void setBrkParams(uint64_t brk);
        uint64_t sbrk(int64_t size);
        UserVirtualMemoryArea *findLastBefore(memory::vaddr_t start);

    public:
        UserVirtualAllocator() = default;
        memory::vaddr_t alloc(uint64_t size);
        bool reserve(memory::vaddr_t addr, uint64_t size);
        bool free(memory::vaddr_t addr, uint64_t size);
        void trace();
        UserVirtualAllocator *copy();
        friend UserVirtualAllocator *newUserVirtualAllocator();
        ~UserVirtualAllocator();
    };
    UserVirtualAllocator *newUserVirtualAllocator();

}; // namespace memory

#endif