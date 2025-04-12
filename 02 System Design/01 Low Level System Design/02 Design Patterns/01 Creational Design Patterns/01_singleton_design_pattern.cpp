/* Singleton Design Pattern
 * 1. Goals :
 *    1.1 Have only a single object created throughout the program lifecycle
 *    1.2 Handle concurrency (for multi-threaded environment)
 *    1.3 Other aspects : Lazy loading (only create object if required), Post C++11 vs Pre C++11
 */
#include <iostream>
#include <mutex>

using namespace std;

/*
 * M1: Manual Singleton (Pre-C++11)
 * --------------------------------
 * 1. Private constructor, destructor, copy constructor, assignment operator - to prevent user from manually creating object or copies or manually deleting instantiated object
 * 2. static member function getInstance to initialize object, which therefore, also needs to be static datat member. - static member functions can only access static objects
 * 3. static mutex for thread-safety - take lock inside if (!m_instance) condition to prevent thread-safety overhead for all calls even after instance is created.
 */

class Singleton1 {
private:
    static Singleton1* m_instance;
    static std::mutex m_mutex;

    // Private constructor and destructor
    Singleton1() {}  // Pre-C++11: no '= default'
    ~Singleton1() {}

    // Private copy constructor and assignment operator
    Singleton1(const Singleton1&); // Pre-C++11: no '= delete' // Can leave the definition empty for copy constr and assignment if declared in private section (because compiler knows it won't be used)
    Singleton1& operator=(const Singleton1&);

public:
    static Singleton1* getInstance() {
        // Double-checked locking
        if (!m_instance) {
            m_mutex.lock();
            if (!m_instance)
                m_instance = new Singleton1();
            m_mutex.unlock();
        }
        return m_instance;
    }

    void print() {
        cout << "Printed from Singleton1\n";
    }
};

// Static member initialization
Singleton1* Singleton1::m_instance = nullptr;
std::mutex Singleton1::m_mutex;


/*
 * M2: Modern Singleton (C++11 and later)
 * --------------------------------------
 * 1. Uses local static variable which is thread-safe since C++11.
 * 2. Deleted copy constructor and assignment operator to prevent copies.
 */

class Singleton2 {
private:
    Singleton2() = default;
    ~Singleton2() = default;

public:
    Singleton2(const Singleton2&) = delete;
    Singleton2& operator=(const Singleton2&) = delete;

    // Will have to return reference, since deleted copy constructor
    static Singleton2& getInstance() {
        static Singleton2 instance; // Initialized only once, thread-safe
        return instance;
    }

    void print() {
        cout << "Printed from Singleton2\n";
    }
};


/*
 * Test and Demo
 */

int main() {
    // Singleton1 usage (Pre-C++11 style)
    Singleton1* instance1 = Singleton1::getInstance();
    Singleton1* instance1Again = Singleton1::getInstance();

    instance1->print();
    // Construction, Copy and assignment operations are not allowed:
    // Singleton1 instance;                            // Error : constructor is private
    // Singleton1 instanceCopy = *instance1;           // Error: copy constructor is private
    // *instance1Again = *instance1;                   // Error: assignment operator is private
    // delete instance1;                               // Error : private destructor

    // Singleton2 usage (Modern C++11+ style)
    Singleton2& instance2 = Singleton2::getInstance();
    Singleton2& instance2Ref = instance2;  // Allowed: referencing, not copying

    instance2.print();
    // Singleton2 instance;                           // Error: private constructor
    // Singleton2 instanceCopy = instance2;           // Error: copy constructor is deleted

    return 0;
}
