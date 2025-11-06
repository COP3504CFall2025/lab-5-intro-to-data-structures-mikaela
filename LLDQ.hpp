#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getHead() == nullptr) {
            throw std::out_of_range("LLDQ is empty");
        }
        T item = list.getHead();
        list.RemoveHead();
        return item;
    }
    T popBack() override {
        if (list.getHead() == nullptr) {
            throw std::out_of_range("LLDQ is empty");
        }
        T item = list.getTail();
        list.RemoveTail();
        return item;
    }

    // Element Accessors
    const T& front() const override {
        return list.getHead();
    }
    const T& back() const override {
        return list.getTail();
    }

    // Getter
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return static_cast<std::size_t>(list.getCount());
    }
    void PrintForward() {
        list.PrintForward();
    }
    void PrintReverse() {
        list.PrintReverse();
    }
};






