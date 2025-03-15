#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>
using namespace std;

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

//Stack();
template <typename T>
Stack<T>::Stack(){}

//~Stack();
template <typename T>
Stack<T>::~Stack(){}

//bool empty() const;
template <typename T>
bool Stack<T>::empty() const{
    return vector<T>::size() == 0;
}

//size_t size() const;
template <typename T>
size_t Stack<T>::size() const{
    return vector<T>::size();
}

//void push(const T& item);
template <typename T>
void Stack<T>::push(const T& item){
    vector<T>::push_back(item);
}

//void pop()
template <typename T>
void Stack<T>::pop(){
    if(Stack<T>::empty()){
        throw underflow_error("Pop From Empty Stack");
    }
    vector<T>::pop_back();
}

//const T& top() const; 
template <typename T>
const T& Stack<T>::top() const{
    if(Stack<T>::empty()){
        throw underflow_error("Top From Empty Stack");
    }
    return vector<T>::back();
}

#endif