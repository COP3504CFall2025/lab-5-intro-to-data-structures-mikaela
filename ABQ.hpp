#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() {
        capacity_ = 1;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    explicit ABQ(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    //copy constructor
    ABQ(const ABQ& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    //copy assignment
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < curr_size_; i++) {
            array_[i] = rhs.array_[i];
        }
        return *this;
    }
    //move constructor
    ABQ(ABQ&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    //move assignment
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;
        return *this;

    }
    //destructor
    ~ABQ() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    //resizing
    void resize(size_t new_cap) {
        if (new_cap > curr_size_) {
            T* new_array = new T[new_cap];
            for (size_t i =0; i < curr_size_; i++) {
                new_array[i] = array_[i];
            }
            delete[] array_;
            array_ = new_array;
            capacity_ = new_cap;
        }
    }

    // Insertion
    void enqueue(const T& data) override {
        if (capacity_ == 0) {
            resize(1);
        }
        if (curr_size_ == capacity_) {
            resize(capacity_ * scale_factor_);
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::out_of_range("ABQ is empty");
        }
        return array_[curr_size_ - 1];
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::out_of_range("ABQ is empty");
        }
        T item = array_[0];
        T data = array_[curr_size_ - 1];
        for (size_t i = 1; i < curr_size_; i++) {
            data[i-1] = array_[i];
        }
        delete[] array_;
        array_ = data;
        curr_size_--;
        if (capacity_/4 < curr_size_) {
            resize(capacity_/2);
        }
        return item;

    }

    void PrintForward() {
        for (std::size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i];
        }
    }
    void PrintReverse() {
        for (std::size_t i = curr_size_ - 1; i > 0; i--) {
            std::cout << array_[i];
        }
    }
};
