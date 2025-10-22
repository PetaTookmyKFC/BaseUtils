//
// Created by PetaTookmyKFC on 22/10/2025.
//

#ifndef BASEUTILS_ARRAY_H
#define BASEUTILS_ARRAY_H

#include <cstddef>
#include <stdexcept>

namespace UT {
    // Like an array except you can only add or remove from the back, you can edit the middle just not remove
    template <typename T>
    class ArrayStack {
    private:
        T* data;
        size_t totalSize;
        size_t occupiedSpace;
        size_t incrementSize;

        void resize(size_t newSize) {
            if (newSize == 0) {
                newSize = incrementSize;
            }

            T* newData = new T[newSize];
            for ( size_t i = 0; i < occupiedSpace; ++i ) {
                newData[i] = std::move(data[i]);
            }
            delete[] data;
            data = newData;
            totalSize = newSize;
        };
    public:
        ArrayStack(size_t StartingSize = 0, size_t incrementAmount = 4) {
            data = new T[StartingSize];

            this->setIncrementSize(incrementAmount);
            totalSize = StartingSize;
            occupiedSpace = 0;
        };
        ~ArrayStack() {
            delete[] data;
        };
        // Only Adds to the end... Removed the remove feature.
        void pushBack(const T& value) {
            if (totalSize == occupiedSpace) {
                this->resize(totalSize + this->incrementSize);
            }
            data[occupiedSpace++] = value;
        };

        void setIncrementSize(size_t newIncrementSize) {
            if (newIncrementSize < 1) {
                throw std::out_of_range("Increment size must be possitive");
            }
            this->incrementSize = newIncrementSize;
        };

        // void popBack();

        T& operator[](size_t index) {
            if (index >= occupiedSpace) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        };

        const T& operator[](size_t index) const {
            if (index >= occupiedSpace) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        auto begin() {
            return data;
        };
        auto end() {
            return data + occupiedSpace;
        };

        auto begin() const {
            return data;
        };
        auto end() const {
            return data + occupiedSpace;
        };

        size_t size () const { return occupiedSpace; };
        size_t CurrentCapacity() const { return totalSize; };
        size_t AvailableSpace () const { return totalSize - occupiedSpace; };
    };
}

#endif //BASEUTILS_ARRAY_H