/**
 * The system requirements are as follows:
 * Design a proper data structure for the shared 3 banking tellers and the semaphore queue
 * Define a proper prototype (signature) for each semaphore operation (wait and signal)
 * Design a proper threading technique (extending Thread class or implementing proper interface)
 * Define a proper interface for input/output in your program (you can use a command line user interface or a graphical one preferably)
 * Measure the number of threads in your program with their life time (from the time being created until the time being detached) and save the results in a table
 * Measure the execution time of your program (the whole program) by changing the number of threads;
 * Run your program 5 times and find the average among the execution times and save the results in a table */

#include <pthread.h>
#include <semaphore.h>

#include <chrono>
#include <ctime>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

using namespace std;

/** Design:
 * The program uses a class `Teller` to represent each banking teller and a class Customer to represent each banking customer.
 * The program uses a class `Semaphore` to implement the Semaphore mechanism for controlling access to the tellers.
 * The program uses a class `BankingSystem` to manage the tellers and customers and to serve the customers.
 * The program initializes the tellers and adds the customers to the system.
 * The program uses a thread to serve the customers.
 * The program uses a queue to store the customers and a vector to store the tellers.
 * The program uses a Semaphore to control access to the tellers.
 * The program generates a random service time for each customer and waits for the service time before releasing the teller.
 */

//# Class Definition
class Teller {
public:
    Teller(int id, bool available) {
        this->id          = id;
        this->available   = available;
        this->finish_time = 0;
    }
    int id;
    bool available;
    double finish_time;
};

class Customer {
public:
    Customer(int id) { this->id = id; }
    int id;
};

// Define a class for the Semaphore
class Semaphore {
public:
    Semaphore(int count) {
        sem_init(&sem, 0, count);
        cout << "Semaphore initialized to " << count << endl;
    }
    ~Semaphore() { sem_destroy(&sem); }
    void wait() { sem_wait(&sem); }
    void signal() { sem_post(&sem); }

private:
    sem_t sem;
};

// Define a class for the banking system
class BankingSystem {
public:
    BankingSystem() {
        // Initialize the tellers
        for (int i = 0; i < 3; i++) {
            teller_v.push_back(Teller(i, true));
        }
        // Add customers to the system
        for (int i = 0; i < 10; i++) {
            customer_q.push(Customer(i));
        }
    }

    void serveAllCustomer() {
        while (!customer_q.empty()) {
            // Wait for an available teller
            teller_semaphore.wait();

            // Find an available teller
            int teller_idx = -1;
            for (int i = 0; i < teller_v.size(); i++) {
                if (teller_v[i].available) {
                    teller_idx = i;
                    break;
                }
            }

            // Get frontmost customer in the queue
            teller_v[teller_idx].available = false;
            Customer curr_customer         = customer_q.front();
            customer_q.pop();

            // Create a new thread to serve the customer
            thread t(&BankingSystem::serveCustomer, this, teller_idx, curr_customer);
            t.detach();
        }
    }


    void serveCustomer(int teller_idx, Customer customer) {
        // Generate a random service time
        int service_time_in_ms = rand() % 4000 + 1000;  // service time 1 to 5 seconds
        cout << "Teller " << teller_v[teller_idx].id << ": Customer " << customer.id + 1 << endl;
        cout << "\tStarts  : " << teller_v[teller_idx].finish_time << endl;
        cout << "\tDuration: " << double(service_time_in_ms) / 1000 << endl;
        teller_v[teller_idx].finish_time += double(service_time_in_ms) / 1000;
        cout << "\tEnds    : " << teller_v[teller_idx].finish_time << endl;

        // Wait for the service time
        this_thread::sleep_for(chrono::milliseconds(service_time_in_ms));

        // Release the teller
        teller_v[teller_idx].available = true;
        teller_semaphore.signal();
    }

private:
    vector<Teller> teller_v;
    queue<Customer> customer_q;
    Semaphore teller_semaphore = Semaphore(3);
};

int main() {
    srand(time(NULL));
    
    // Initialize the banking system
    BankingSystem bankingSystem;

    // Begin operation
    thread t(&BankingSystem::serveAllCustomer, &bankingSystem);
    t.join();

    return 0;
}
