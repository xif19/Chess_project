#include <vector>
#include <functional>

template <typename T>
class ObservableVector : public std::vector<T> {
public:
    using std::vector<T>::vector; 

    using Callback = std::function<void()>;


    void push_back(const T& value) {
        std::vector<T>::push_back(value);
        notify();
    }

    void pop_back() {
        std::vector<T>::pop_back();
        notify();
    }

    void setCallback(const Callback& callback) {
        this->callback = callback;
    }

private:
    // Callback function to notify vector update
    Callback callback;

    // Method to notify callback function
    void notify() {
        if (callback) {
            callback();
        }
    }
};
