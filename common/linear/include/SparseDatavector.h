// SparseDatavector.h

#pragma once

#include "IDataVector.h"
#include "CompressedIntegerList.h"
#include "IndexValue.h"

namespace linear
{
    typedef uint64_t uint;

    /// Implements a sparse binary vector as an increasing list of the coordinates where the value is 1.0
    ///
    template<typename ValueType, typename IntegerListType>
    class SparseDatavector : public IDataVector
    {
    public:

        /// A read-only forward iterator for the sparse binary vector.
        ///
        class Iterator
        {
        public:

            /// Default copy ctor
            ///
            Iterator(const Iterator&) = default;

            /// Default move ctor
            ///
            Iterator(Iterator&&) = default;

            /// \returns True if the iterator is currently pointing to a valid iterate
            ///
            bool IsValid() const;

            /// Proceeds to the Next iterate
            ///
            void Next();

            /// \returns The current index-value pair
            ///
            IndexValue GetValue() const;

        private:
            
            // define typenames to improve readability
            using IndexIteratorType = typename IntegerListType::Iterator;
            using ValueIteratorType = typename vector<ValueType>::const_iterator;

            /// private ctor, can only be called from SparseDatavector class
            Iterator(const IndexIteratorType& list_iterator, const ValueIteratorType& value_iterator);
            friend SparseDatavector<ValueType, IntegerListType>;

            // members
            IndexIteratorType _index_iterator;
            ValueIteratorType _value_iterator;
        };

        /// Constructs an empty sparse binary vector
        ///
        SparseDatavector();

        /// Converting constructor
        ///
        explicit SparseDatavector(const IDataVector& other);

        /// Move constructor
        ///
        SparseDatavector(SparseDatavector<ValueType, IntegerListType>&& other) = default;

        /// Deleted copy constructor
        ///
        SparseDatavector(const SparseDatavector<ValueType, IntegerListType>& other) = delete;

        /// Sets the element at the given index to 1.0. Calls to this function must have a monotonically increasing argument. 
        /// The value argument must equal 1.0
        virtual void PushBack(uint index, double value) override;

        /// Deletes all of the vector content and sets its Size to zero, but does not deallocate its memory
        ///
        virtual void Reset() override;

        /// Calls a callback function for each non-zero entry in the vector, in order of increasing index
        ///
        //virtual    void foreach_nonzero(function<void(uint, double)> func, uint index_offset = 0) const override;

        /// \returns The largest index of a non-zero entry plus one
        ///
        virtual uint Size() const override;

        /// \returns The number of non-zeros
        ///
        virtual uint NumNonzeros() const override;

        /// Computes the vector squared 2-norm
        ///
        virtual double Norm2() const override;

        /// Performs (*p_other) += scalar * (*this), where other a dense vector
        ///
        virtual void AddTo(double* p_other, double scalar = 1.0) const override;

        /// Computes the Dot product
        ///
        virtual double Dot(const double* p_other) const override;

        /// \Returns a Iterator that traverses the non-zero entries of the sparse vector
        ///
        Iterator GetIterator() const;

        /// Prints the datavector to an output stream
        ///
        virtual void Print(ostream& os) const override;

    private:
        IntegerListType _indices;
        vector<ValueType> _values;
    };

    class SparseDoubleDatavector : public SparseDatavector<double, CompressedIntegerList>
    {
    public:
        using SparseDatavector<double, CompressedIntegerList>::SparseDatavector;

        /// \returns The type of the vector
        ///
        virtual type GetType() const override;
    };

    class SparseFloatDatavector : public SparseDatavector<float, CompressedIntegerList>
    {
    public:
        using SparseDatavector<float, CompressedIntegerList>::SparseDatavector;

        /// \returns The type of the vector
        ///
        virtual type GetType() const override;
    };

    class SparseShortDatavector : public SparseDatavector<short, CompressedIntegerList>
    {
    public:
        using SparseDatavector<short, CompressedIntegerList>::SparseDatavector;

        /// \returns The type of the vector
        ///
        virtual type GetType() const override;
    };
}

