#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    //copy constructor
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }
    //move assignment
    ABDQ(ABDQ&& other) noexcept {
        //steal all stuff
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        //set others to nothing
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    //copy assignment
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    //move assignment
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        //clear out current data
        delete[] data_;
        //steal stuff
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        // delete other
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    //destructor
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        capacity_ = 0;
    }

    void resize(size_t new_cap) {
        if (new_cap > size_) {
            T* new_array = new T[new_cap];
            for (size_t i =0; i < size_; i++) {
                new_array[i] = data_[i];
            }
            delete[] data_;
            data_ = new_array;
            capacity_ = new_cap;
        }
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            resize(capacity_ * SCALE_FACTOR);
        }
        if (size_ == 0) {
            resize(1);
        }
        T newData = new T[capacity_+1];
        newData[0] = item;
        for (std::size_t i = 1; i < size_+1; i++) {
            newData[i] = data_[i-1];
        }
        delete[] data_;
        data_ = newData;
        size_++;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            resize(capacity_ * SCALE_FACTOR);
        }
        if (size_ == 0) {
            resize(1);
        }
        data_[size_] = item;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABDQ");
        }
        size_--;
        return data_[front_];
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABDQ");
        }
        size_--;
        return data_[back_];
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABDQ");
        }
        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) {
            throw std::runtime_error("empty ABDQ");
        }
        return data_[back_ - 1];
    }

    // Getters
    [[nodiscard]] std::size_t getSize() const noexcept override {
        return size_;
    }
    void PrintForward() {
        for (std::size_t i = 0; i < size_; i++) {
            std::cout << data_[i];
        }
        std::cout << std::endl;
    }
    void PrintReverse() {
        for (std::size_t i = size_ - 1; i > 0; i--) {
            std::cout << data_[i];
        }
        std::cout << std::endl;
    }

};
