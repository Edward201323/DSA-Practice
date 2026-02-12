#pragma once

template <typename T>
class List {
    protected:
        // the current number of elements in the list
        unsigned length;

    public:
        // default constructor
        List() : length(0) { }

        // destructor
        virtual ~List() { }

        // add the argument to the end of the list
        virtual void append(const T&) = 0;

        // remove all elements in the list, resetting to the initial state
        virtual void clear() = 0;

        // return the element at the given position (argument)
        virtual T getElement(unsigned) const = 0;

        // return the current length of the list
        virtual unsigned getLength() const = 0;

        // insert the given element (argument 2) at
        // the given position (argument 1)
        virtual void insert(unsigned, const T&) = 0;

        // determine if the list currently empty
        virtual bool isEmpty() const = 0;

        // remove the element at the given position (argument)
        virtual void remove(unsigned) = 0;

        // replace the element at the given position (argument 1) with
        // the value given (argument 2)
        virtual void replace(unsigned, const T&) = 0;
};
