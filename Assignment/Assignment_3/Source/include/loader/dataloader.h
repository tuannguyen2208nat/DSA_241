
#ifndef DATALOADER_H
#define DATALOADER_H
#include "tensor/xtensor_lib.h"
#include "loader/dataset.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader
{
public:
    class Iterator;

private:
    Dataset<DType, LType> *ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int nbatch;
    ulong_tensor item_indices;
    int m_seed;
    xt::xarray<int> indices;
    int num_of_batch;

public:
    DataLoader(Dataset<DType, LType> *ptr_dataset,
               int batch_size, bool shuffle = true,
               bool drop_last = false, int seed = -1)
        : ptr_dataset(ptr_dataset),
          batch_size(batch_size),
          shuffle(shuffle),
          drop_last(drop_last),
          m_seed(seed)
    {
        nbatch = ptr_dataset->len() / batch_size;
        item_indices = xt::arange(0, ptr_dataset->len());
        int size = 0;
        this->indices = xt::arange<int>(0, int(ptr_dataset->len()));
        this->num_of_batch = int(ptr_dataset->len()) >= batch_size ? int(ptr_dataset->len()) / batch_size : 0;
        if (shuffle)
        {
            if (seed >= 0)
            {
                xt::random::seed(seed);
                xt::random::shuffle(indices);
            }
            else
            {
                xt::random::shuffle(indices);
            }
        }

        if (!drop_last)
        {
            size = int(ptr_dataset->len());
        }
        else
        {
            size = int(ptr_dataset->len()) >= batch_size ? int(num_of_batch * batch_size) : 0;
        }

        this->indices = xt::view(this->indices, xt::range(0, size));
    }
    virtual ~DataLoader() {}

    // New method: from V2: begin
    int get_batch_size() { return batch_size; }
    int get_sample_count() { return ptr_dataset->len(); }
    int get_total_batch() { return int(ptr_dataset->len() / batch_size); }

    // New method: from V2: end
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
public:
    Iterator begin()
    {
        // YOUR CODE IS HERE
        return Iterator(ptr_dataset, batch_size, indices, num_of_batch, true);
    }
    Iterator end()
    {
        // YOUR CODE IS HERE
        return Iterator(ptr_dataset, batch_size, indices, num_of_batch, false);
    }

    // BEGIN of Iterator

    // YOUR CODE IS HERE: to define iterator

    // END of Iterator

    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
    class Iterator
    {
    private:
        Dataset<DType, LType> *ptr_dataset;
        int batch_size;
        int current_index;
        xt::xarray<int> indices;
        int num_of_batch;

    public:
        // TODO implement contructor
        Iterator(Dataset<DType, LType> *ptr_dataset, int batch_size, const xt::xarray<int> &indices, int num_of_batch, bool begin = true)
            : ptr_dataset(ptr_dataset), batch_size(batch_size), num_of_batch(num_of_batch), indices(indices)
        {
            if (begin)
            {
                current_index = 0;
            }
            else
            {
                current_index = num_of_batch;
            }
        }

        Iterator &operator=(const Iterator &iterator)
        {
            // TODO implement
            this->ptr_dataset = iterator.ptr_dataset;
            this->batch_size = iterator.batch_size;
            this->current_index = iterator.current_index;
            this->indices = iterator.indices;
            this->num_of_batch = num_of_batch;
            return *this;
        }

        Iterator &operator++()
        {
            // TODO implement
            this->current_index++;
            return *this;
        }

        Iterator operator++(int)
        {
            // TODO implement
            Iterator iterator = *this;
            ++(*this);
            return iterator;
        }

        bool operator!=(const Iterator &other) const
        {
            // TODO implement
            return current_index != other.current_index;
        }

        Batch<DType, LType> operator*() const
        {
            // TODO implement
            if (indices.size() == 0)
            {
                return Batch<DType, LType>(xt::xarray<DType>(), xt::xarray<LType>());
            }

            TensorDataset<DType, LType> *tensor_dataset_ptr = dynamic_cast<TensorDataset<DType, LType> *>(ptr_dataset);

            xt::svector<unsigned long> data_shape = tensor_dataset_ptr->get_data_shape();
            xt::svector<unsigned long> label_shape = tensor_dataset_ptr->get_label_shape();

            int start = current_index * batch_size;
            int end = current_index == (num_of_batch)-1 ? indices.size() : start + batch_size;
            int size = current_index == (num_of_batch)-1 ? indices.size() - start : batch_size;

            data_shape[0] = label_shape[0] = size;

            xt::xarray<DType> data = xt::empty<DType>(data_shape);
            xt::xarray<LType> label = xt::empty<LType>(label_shape);

            for (int i = start; i < end; i++)
            {
                DataLabel<DType, LType> data_label = tensor_dataset_ptr->getitem(indices[i]);
                if (data_shape.size() > 0)
                {
                    xt::view(data, i - start) = data_label.getData();
                }
                else
                {
                    data = xt::empty<DType>({});
                }
                if (label_shape.size() > 0)
                {
                    xt::view(label, i - start) = data_label.getLabel();
                }
                else
                {
                    label = xt::empty<LType>({});
                }
            }
            return Batch<DType, LType>(data, label);
        }
    };
};

#endif /* DATALOADER_H */