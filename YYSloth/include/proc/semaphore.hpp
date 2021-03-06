#ifndef __SEMAPHORE_HPP_INCLUDED__
#define __SEMAPHORE_HPP_INCLUDED__

#include <proc/taskqueue.hpp>
#include <utils.hpp>

namespace proc {
    class Semaphore {
        uint64_t m_num;
        ProcessQueue m_queue;
        bool m_aquired;

    public:
        Semaphore(uint64_t max);
        void acquire(uint64_t num = 1);
        void release(uint64_t num = 1);
        bool someoneWaiting();
    };
}; // namespace proc

#endif