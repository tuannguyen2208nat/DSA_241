
#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/dataset.h"
#include "ann/xtensor_lib.h"

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
    xt::xarray<int> indices;
    int num_of_batch;

public:
    DataLoader(Dataset<DType, LType> *ptr_dataset, int batch_size,
               bool shuffle = true, bool drop_last = false)
    {
        // TODO implement
        this->ptr_dataset = ptr_dataset;
        this->batch_size = batch_size;
        this->shuffle = shuffle;
        this->drop_last = drop_last;

        indices = xt::arange<int>(0, int(ptr_dataset->len()));

        if (shuffle)
        {
            auto &engine = xt::random::get_default_random_engine();
            xt::random::shuffle(indices, engine);
        }
        if (int(ptr_dataset->len()) >= batch_size)
        {
            num_of_batch = int(ptr_dataset->len()) / batch_size;
            if ((int(ptr_dataset->len()) % batch_size != 0) && drop_last)
            {
                num_of_batch += 1;
            }
        }
        else
        {
            num_of_batch = 1;
        }
    }

    virtual ~DataLoader()
    {
        // TODO implement
    }

    Iterator begin()
    {
        // TODO implement
        return Iterator(ptr_dataset, batch_size, indices, num_of_batch, true);
    }

    Iterator end()
    {
        // TODO implement
        return Iterator(ptr_dataset, batch_size, indices, num_of_batch, false);
    }

    // TODO implement forech
    class Iterator
    {
    private:
        Dataset<DType, LType> *ptr_dataset;
        int batch_size;
        size_t current_index;
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
            TensorDataset<DType, LType> *tensor_dataset_ptr = dynamic_cast<TensorDataset<DType, LType> *>(ptr_dataset);

            auto data_shape = tensor_dataset_ptr->get_data_shape();
            auto label_shape = tensor_dataset_ptr->get_label_shape();

            int start, end;
            if ((current_index == (num_of_batch)-1))
            {
                start = current_index * batch_size;
                end = indices.size();
                int size = indices.size() - start;
                data_shape[0] = size;
                label_shape[0] = size;
            }
            else
            {
                start = current_index * batch_size;
                end = start + batch_size;
                data_shape[0] = batch_size;
                label_shape[0] = batch_size;
            }

            xt::xarray<DType> data = xt::empty<DType>(data_shape);
            xt::xarray<LType> label = xt::empty<LType>(label_shape);

            if (end > indices.size())
            {
                end = indices.size();
            }

            for (int i = start; i < end; i++)
            {
                auto data_label = tensor_dataset_ptr->getitem(indices[i]);
                if (data_label.getData().size() > 0)
                {
                    xt::view(data, i - start) = data_label.getData();
                }

                if (data_label.getLabel().size() > 0)
                {
                    xt::view(label, i - start) = data_label.getLabel();
                }
            }
            return Batch<DType, LType>(data, label);
        }
    };
};

#endif /* DATALOADER_H */
