#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        capacity_ = 0;
        curr_size_ = 0;
        array_ = new T[capacity_];
    }
    explicit ABS(const size_t capacity) {
        capacity_ = capacity;
        curr_size_ = 0;
        array_ = new T[capacity];
    }
    //copy constructor
    ABS(const ABS& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < capacity_; i++) {
            array_[i] = other.array_[i];
        }
    }
    //copy assignment constructor
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[capacity_];
        for (std::size_t i = 0; i < capacity_; i++) {
            array_[i] = rhs.array_[i];
        }
        return *this;
    }
    //move constructor
    ABS(ABS&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    //move assignment constructor
    ABS& operator=(ABS&& rhs) noexcept {
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
    ~ABS() noexcept override {
        delete[] array_;
        array_ = nullptr;
        capacity_ = 0;
        curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

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

    // Push item onto the stack
    void push(const T& data) override {
        if (capacity_ == 0) {
            resize(1);
        }
        if (curr_size_ == capacity_) {
            resize(capacity_ * scale_factor_);
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::out_of_range("empty ABS");
        }
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::out_of_range("empty ABS");
        }
        curr_size_--;
        if (capacity_/4 < curr_size_) {
            resize(capacity_/2);
        }
        return array_[curr_size_ -1];
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
