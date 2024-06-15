#include <exception>
#include <iostream>
#include <queue>
#include <vector>

template <typename Element>
void bfs(Element first) {
    std::queue<Element> queue;
    queue.push(first);
    while (!queue.empty()) {
        Element now = queue.front();
        queue.pop();
        if (now.terminate()) {
            now.process();
        }
        else {
            for (Element e: now.next()) {
                queue.push(e);
            }
        }
    }
}

template <typename Element>
class BFS {
public:
    virtual bool terminate() = 0;
    virtual void process() = 0;
    virtual std::vector<Element> next();
};

class Fib: public BFS<Fib> {
public:
    Fib(int _n) : n(_n) {}
    bool terminate() override {
        return n <= 1;
    }
    void process() override {
        sum += n;
    }
    std::vector<Fib> next() override {
        std::vector<Fib> ret;
        ret.push_back(Fib(n - 1));
        ret.push_back(Fib(n - 2));
        return ret;
    }
private:
    int n;
    static int sum;
};