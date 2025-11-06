#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override {
        list.AddTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getHead() == nullptr) {
            throw std::out_of_range("LLQ is empty");
        }
        T item = list.getHead()->item;
        list.RemoveHead();
        return item;
    }

    // Access
    T peek() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("LLQ is empty");
        }
        return list.getHead()->item;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return static_cast<std::size_t>(list.getCount());
    }
    void PrintForward() {
        list.PrintForward();
    }
    void PrintReverse() {
        list.PrintReverse();
    }

};