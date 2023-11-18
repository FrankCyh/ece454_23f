#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Node {
public:
    int value;
    Node* next;
    std::mutex node_mutex;
    Node(int value) {
        this->value = value;
        this->next  = nullptr;
    }
};

class List {  // changed to a class implementation for easier member function
public:
    Node* head;  // point to head-node of the whole linked-list
    std::mutex list_mutex;  // lock status field for the whole linked-list

    List() : head(nullptr) {
    }

    /* Print all `Node` in `List` */
    void printList() const {
        Node* ptr = head;
        std::cout << "List: ";
        while (ptr) {
            std::cout << ptr->value << ' ';
            ptr = ptr->next;
        }
        std::cout << '\n';
    }

    /* Insert `Node` according according to `node->value` */
    void insertNode(Node* node) {
        if (head == nullptr) {
            head = node;
            return;
        }
        Node* ptr = head;
        Node* pre = nullptr;
        while (ptr && ptr->value < node->value) {
            pre = ptr;
            ptr = ptr->next;
        }
        node->next = ptr;
        if (pre == nullptr) {
            head = node;
        } else {
            pre->next = node;
        }
    }

    /* Insert `Node` according according to `node->value` with coarse-grained locking */
    void insertNodeCoarse(Node* node) {
        std::lock_guard<std::mutex> lock(list_mutex);  // The `std::lock_guard` lock automatically releases the lock when the `std::lock_guard` object is destroyed
        std::cout << "List locked (coarse) for node with value " << node->value << "\n";
        insertNode(node);
    }

    /* Insert `Node` according according to `node->value` with fine-grained locking */
    void insertNodeFine(Node* node) {
        Node* ptr = head;
        std::lock_guard<std::mutex> lock(node->node_mutex);  // The `std::lock_guard` lock automatically releases the lock when the `std::lock_guard` object is destroyed
        std::cout << "Node " << node->value << " locked (fine)\n";
        this->insertNode(node);
    }
};

int main(int argc, char** argv) {
    // Accept only one argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <0(coarse))|1(fine)>\n";
        return 1;
    }

    //# Create a node list
    // Implement a single-linked-list with sorted values using the Node and List structures below. Insert these values in the linked-list: 40, 50, 100, 120, 160, 180 using a regular insertion process.
    List node_l;
    node_l.insertNode((Node*)new Node(40));
    node_l.insertNode((Node*)new Node(50));
    node_l.insertNode((Node*)new Node(100));
    node_l.insertNode((Node*)new Node(120));
    node_l.insertNode((Node*)new Node(160));
    node_l.insertNode((Node*)new Node(180));
    node_l.printList();

    //# Create node to be inserted
    // Try to have two more insertions for values 65 and 77 but this time simultaneously. Both of these nodes should be inserted at the same time between the nodes 50 and 100 and so two threads should be considered for these operations, one for each node to be inserted. These two threads will try to operate on the same links at the same time and so one of the insertions may be lost. To protect your linked-list, provide the following two Locking algorithms
    Node* node_65 = (Node*)new Node(65);
    Node* node_77 = (Node*)new Node(77);

// #define MORE_NODES
#ifdef MORE_NODES
    std::vector<Node*> node_v;
    for (int i = 0; i < 180; ++i) {
        node_v.push_back((Node*)new Node(i));
    }
#endif

    //# Insert nodes with either coarse-grained or fine-grained locking
    bool coarse_0_fine_1 = std::stoi(argv[1]);
    auto start           = std::chrono::high_resolution_clock::now();
    if (coarse_0_fine_1 == 0) {
        // a) Implement a single Global-Lock on the whole linked-list data structure. Apply the lock before each insertion/deletion (before the operation is started) and unlock it after each insertion/deletion (after the operation is completed) where/when it is needed.
#ifndef MORE_NODES
        std::thread t1(&List::insertNodeCoarse, &node_l, node_65);
        std::thread t2(&List::insertNodeCoarse, &node_l, node_77);
        t1.join();
        t2.join();
#else
        std::vector<std::thread> thread_v;
        for (auto& node : node_v) {
            thread_v.push_back(std::thread(&List::insertNodeCoarse, &node_l, node));
        }
        for (auto& thread : thread_v) {
            thread.join();
        }
#endif
    } else {
        // b) Implement a Fine-grained Lock on the individual nodes of the linked-list data structure. Apply the locks (on the nodes before and after that specific node to be inserted/deleted) when/where needed.
#ifndef MORE_NODES
        std::thread t3(&List::insertNodeFine, &node_l, node_65);
        std::thread t4(&List::insertNodeFine, &node_l, node_77);
        t3.join();
        t4.join();
#else
        std::vector<std::thread> thread_v;
        for (auto& node : node_v) {
            thread_v.push_back(std::thread(&List::insertNodeFine, &node_l, node));
        }
        for (auto& thread : thread_v) {
            thread.join();
        }
#endif
    }

    //# Calculate time taken
    auto end      = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << (coarse_0_fine_1 ? "Fine-grained" : "Coarse-grained") << " locking time: " << duration.count() << " us\n";
    node_l.printList();

    return 0;
}