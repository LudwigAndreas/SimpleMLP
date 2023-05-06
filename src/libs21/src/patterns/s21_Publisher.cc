#include <iostream>
#include <functional>
#include <vector>

// The Publisher class
class Publisher {
public:
    void add_listener(const std::function<void()>& listener) {
        listeners_.push_back(listener);
    }

    void remove_listener(const std::function<void()>& listener) {
        for (auto it = listeners_.begin(); it != listeners_.end(); ++it) {
            if (it->target<void(*)()>() == listener.target<void(*)()>()) {
                listeners_.erase(it);
                return;
            }
        }
    }

    void publish() {
        for (auto listener : listeners_) {
            listener();
        }
    }
private:
    std::vector<std::function<void()>> listeners_;
};


class Subscriber {
public:
    void notify() {
        std::cout << "Subscriber notified" << std::endl;
    }
};

class ConcretePublisher : public Publisher {
    void foo() {
        for (int i = 0; i < 3; ++i) {
            std::cout << "Publisher doing work";
        }
        std::cout << "Publisher finished";
    }

};

class ConcreteSubscriber : public Subscriber {

};

int main() {
    Publisher publisher;
    Subscriber subscriber1, subscriber2;
    publisher.add_listener([&]() {
        subscriber1.notify();
    });
    publisher.add_listener([&]() {
        subscriber2.notify();
    });
    publisher.publish();
    publisher.remove_listener([&]() {
        subscriber1.notify();
    });
    publisher.publish();
    return 0;
}