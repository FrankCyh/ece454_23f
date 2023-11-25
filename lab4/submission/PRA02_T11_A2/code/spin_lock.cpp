#include <atomic>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>


class Spinlock {
    /** Implement a class named “Spinlock” containing: two methods “lock()” and ”unlock()”, and an attribute with atomic type to represent the status of a shared part of memory: if it is in the acquired mode (locked) or in the released mode (unlock).
     * Implement the locks using std::memory_order_ defined in header <atomic> for: `memory_order_acquire`, `memory_order_release`
     */
public:
    void lock() {
        while (lock_status.test_and_set(std::memory_order_acquire)) {
        }
    }

    void unlock() {
        lock_status.clear(std::memory_order_release);
    }

private:
    std::atomic_flag lock_status = ATOMIC_FLAG_INIT;
};


void Task(Spinlock& spinlock, std::chrono::duration<double, std::milli>& spin_time, std::chrono::duration<double, std::milli>& total_time) {
    /* Each thread's task , first waiting for the spin lock, and then sleep for 5ms and release lock */
    auto start_spin  = std::chrono::high_resolution_clock::now();
    auto start_total = start_spin;

    // Try to acquire lock; start spinning if it's already acquired
    spinlock.lock();

    auto end_spin = std::chrono::high_resolution_clock::now();
    spin_time     = end_spin - start_spin;  // Measure the time for the spinning mode of each thread, starting at the time the spinning starts or its related counter starts to count until the time the spinning is done.

    // Simulate a fixed delay of 5ms
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    // Release lock
    spinlock.unlock();

    auto end_total = std::chrono::high_resolution_clock::now();
    total_time     = end_total - start_total;  // Also measure the total time for each thread’s working, from being activated and then going to spinning mode, to working with function Task() and being done/inactive
    // Q: What difference does `spin_time` and `total_time` make? `total_time` is just `spin_time` + 5ms
}

int main() {
    const int num_run    = 5;
    const int num_thread = 5;

    Spinlock spinlock;
    std::vector<std::thread> thread_v(num_thread);
    std::vector<std::vector<std::chrono::duration<double, std::milli>>> spin_time_v(num_run, std::vector<std::chrono::duration<double, std::milli>>(num_thread));  // A `num_run` * `num_thread` vector to measure the time for the spinning mode of each thread
    std::vector<std::vector<std::chrono::duration<double, std::milli>>> total_time_v(num_run, std::vector<std::chrono::duration<double, std::milli>>(num_thread));  // A `num_run` * `num_thread` vector to measure the total time for each thread’s working

    /** Simulate the Spin-Lock process while those threads (#5) trying to have access to a shared function Task() in the program.
     * - For each thread if it cannot lock the Task() because it was already acquired by another thread, it should go to the spinning mode. In this mode, a related counter to that thread (could be a simple counter variable) will start counting incrementally from zero until the time that thread is out of the spinning mode.
     * - Once that thread is out of the spinning mode or the Task() is released from its previous lock, that thread can acquire the Task() this time and lock it. */

    for (int j = 0; j < num_run; j++) {
        for (int i = 0; i < num_thread; ++i) {
            thread_v[i] = std::thread(Task, std::ref(spinlock), std::ref(spin_time_v[j][i]), std::ref(total_time_v[j][i]));
        }

        for (auto& t : thread_v) {
            t.join();
        }

        // Output the results after each run
        for (int i = 0; i < num_thread; ++i) {
            std::cout << "Thread " << i << " - Spin Time: " << spin_time_v[j][i].count() << "ms, Total Time: " << total_time_v[j][i].count() << "ms\n";
        }
        std::cout << "-------------------\n";
    }

    // Calculate averages
    std::vector<double> avg_spin_times(num_thread, 0.0);
    std::vector<double> avg_total_times(num_thread, 0.0);

    for (int i = 0; i < num_thread; ++i) {
        for (int j = 0; j < num_run; j++) {
            avg_spin_times[i] += spin_time_v[j][i].count();
            avg_total_times[i] += total_time_v[j][i].count();
        }
    }
    for (int i = 0; i < num_thread; ++i) {
        avg_spin_times[i] /= num_run;
        avg_total_times[i] /= num_run;
        std::cout << "Thread " << i << " - Average Spin Time: " << avg_spin_times[i] << "ms, Average Total Time: " << avg_total_times[i] << "ms\n";
    }

    return 0;
}