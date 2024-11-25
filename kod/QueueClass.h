#include <vector>
using namespace std;
template <typename T>

// queue implementation
class QueueClass {
private:
    vector<T> data;

public:
    // pushes an element to the back of a queue
    void push(const T& value) {
        data.push_back(value);
    }

    // removes the front element
    void pop() {
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }

    // returns the front element
    T& front() {
        return data.front();
    }

    // checks if the queue is empty
    bool empty() const {
        return data.empty();
    }
};
