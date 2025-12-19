//
// Created by jacka on 06/12/2025.
//

#ifndef BASEUTILS_SEMIDYNAMICARRAY_H
#define BASEUTILS_SEMIDYNAMICARRAY_H

#include <cstdio>
#include <stdexcept>

namespace base_utils::types {

    template <typename T>
    class SemiDynamicArray {
    private:
        T* data;
        size_t totalSize;
        size_t occupiedSize;
        size_t incrementSize;

        void resize(std::size_t newSize) {
            if (newSize == 0) {
                newSize = incrementSize;
            }

            T* newData = new T[newSize];
            for (size_t i = 0; i < occupiedSize && i < newSize; i++) {
                newData[i] = std::move(data[i]);
            }

            delete[] data;
            data = newData;
            this->totalSize = newSize;
            // Reduced the occupiedSize to the total size, if the array is now smaller than the content
            if (occupiedSize > totalSize) {
                occupiedSize = totalSize;
            }


        }

    public:
        // Main Public Controls
        void setIncrementSize(size_t incrementSize) {
            if (incrementSize < 1) {
                throw std::out_of_range("Increment size must be greater than 0");
            }

            this->incrementSize = incrementSize;
        }
        // Adds an element to the end of the array - increasing the size if necessary
        void pushBack(const T& value) {
            // Increase the array size if required
            if (this->totalSize == this->occupiedSize) {
                this->resize(this->totalSize + incrementSize);
            }
            data[this->occupiedSize] = value;
			this->occupiedSize++;
        }


        // Implement basic array operations
        T& operator[](size_t index) {
            if (index >= this->occupiedSize) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }
        const T& operator[](size_t index) const {

            if (index >= occupiedSize) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        auto begin() {
            return data;
        }
        auto end() {
            return data + occupiedSize;
        }
        auto begin() const {
            return data;
        }
        auto end() const {
            return data + occupiedSize;
        }
        // Base Array Constants
        size_t size() const { return this->occupiedSize; };
        size_t CurrentCapacity() const {return this->totalSize;};
        size_t AvailableSpace() const {return this->totalSize - this->occupiedSize;};

        // Create and delete the dynamic Array
        ~SemiDynamicArray() {
            delete[] data;
        }
        SemiDynamicArray(size_t incrementSize, size_t defaultSize = 0): totalSize(defaultSize), occupiedSize(0) {
            this->setIncrementSize(incrementSize);
            this->data = new T[this->totalSize];
        };
		// DEEP COPY
		SemiDynamicArray(const SemiDynamicArray& other) : totalSize(other.totalSize), incrementSize(other.incrementSize), occupiedSize(other.occupiedSize)
		{
		    data = new T[totalSize];
		    for (size_t i = 0; i < other.occupiedSize; i++) {
		        data[i] = other.data[i];
		    }
		}

        // Copy Assignment Operator DEEP COPY
        SemiDynamicArray& operator=(const SemiDynamicArray& other)
		{
		    if (this != &other)
		    {
		        delete[] data;
		        totalSize = other.totalSize;
		        occupiedSize = other.occupiedSize;
		        incrementSize = other.incrementSize;
		        data = new T[totalSize];
		        for (size_t i = 0; i < other.occupiedSize; i++)
		        {
		            data[i] = other.data[i];
		        }
		    }
		    return *this;
		}

        // Move Constructor STEAL RESOURCES?
        SemiDynamicArray(SemiDynamicArray& other) noexcept:
            data(other.data), totalSize(other.totalSize), occupiedSize(other.occupiedSize), incrementSize(other.incrementSize)
		{
		    other.data = nullptr;
		    other.totalSize = 0;
		    other.occupiedSize = 0;
		}

        SemiDynamicArray& operator=(SemiDynamicArray&& other) noexcept
		{
		    if (this != &other)
		    {
		        delete[] data;

		        data = other.data;
		        totalSize = other.totalSize;
		        occupiedSize = other.occupiedSize;
		        incrementSize = other.incrementSize;

		        other.data = nullptr;
		        other.totalSize = 0;
		        other.occupiedSize = 0;
		    }
			return *this;
		}
    };
}


#endif //BASEUTILS_SEMIDYNAMICARRAY_H