
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
        int size = 0;
        this->indices = xt::arange<int>(0, int(ptr_dataset->len()));
        if (shuffle)
        {
            xt::random::default_engine_type engine(0);
            xt::random::shuffle(indices, engine);
        }
        if (!drop_last)
        {
            size = int(ptr_dataset->len());
            this->num_of_batch = int(ptr_dataset->len()) >= batch_size ? int(ptr_dataset->len()) / batch_size : 1;
        }
        else
        {
            this->num_of_batch = int(ptr_dataset->len()) >= batch_size ? int(ptr_dataset->len()) / batch_size : 0;
            size = int(ptr_dataset->len()) >= batch_size ? int(num_of_batch * batch_size) : 0;
        }
        this->indices = xt::view(this->indices, xt::range(0, size));
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
            // TODO implement
            if (indices.size() == 0)
            {
                return Batch<DType, LType>(xt::xarray<DType>(), xt::xarray<LType>());
            }
            TensorDataset<DType, LType> *tensor_dataset_ptr = dynamic_cast<TensorDataset<DType, LType> *>(ptr_dataset);

            xt::svector<unsigned long> data_shape = tensor_dataset_ptr->get_data_shape();
            xt::svector<unsigned long> label_shape = tensor_dataset_ptr->get_label_shape();

            int start = current_index * batch_size;
            int end = (start + batch_size) > indices.size() ? indices.size() : start + batch_size;
            int size = (start + batch_size) > indices.size() ? indices.size() - start : batch_size;
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