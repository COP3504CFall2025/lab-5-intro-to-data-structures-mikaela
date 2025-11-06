#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override {
        list.AddTail(item);
    }

    // Deletion
    T pop() override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("LLS: Empty list");
        }
        T item = list.getTail()->data;
        list.RemoveTail();
        return item;
    }

    // Access
    T peek() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("LLS: Empty list");
        }
        return list.getHead()->data;
    }

    //Getters
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