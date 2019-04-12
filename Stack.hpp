#ifndef STACK_STACK_HPP
#define STACK_STACK_HPP

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <memory>
#include <iostream>

template <typename T>
class Stack {
    struct Node {
        T data;
        Node *before;
        Node *after;
    };
    Node *head;
    Node *tail;
    std::size_t _size;

public:
    Stack() : _size(0), head(new Node()), tail(new Node()) {
        head->before = nullptr;
        tail->after = nullptr;
        head->after = tail;
        tail->before = head;
    }

    ~Stack() {
        Node *ptr = tail;
        while(ptr != head) {
            ptr = ptr->before;
            delete ptr->after;
        }
        delete ptr;
    }

    void clear() {
        Node *node = tail->before;
        head->after=tail;
        tail->before=head;
        while(node->before != head) {
            node = node->before;
            delete node->after;
        }
        delete node;
    }

    constexpr bool empty() { return head->after == tail && tail->before == head; }

    void push(T const &element) {
        auto node = new Node();
        node->data = element;
        node->before = tail->before;
        node->before->after = node;
        node->after = tail;
        tail->before = node;
    }
    void push(T &&element) noexcept {
        auto node = new Node();
        node->data = std::move(element);
        node->before = tail->before;
        node->before->after = node;
        node->after = tail;
        tail->before = node;
    }

    void pop() {
        if (empty()) throw std::runtime_error("Empty stack!");
        Node *node = tail->before;
        tail->before = node->before;
        tail->before->after = tail;
        delete node;
    }

    constexpr std::size_t size() const {
        return _size;
    }

    void swap(Stack &stack) {
        std::swap(this->head, stack.head);
        std::swap(this->tail, stack.tail);
        std::swap(this->_size, stack._size);
    }

    T const &top() const {
        return tail->before->data;
    }
    T top() {
        return tail->before->data;
    }
};


#endif