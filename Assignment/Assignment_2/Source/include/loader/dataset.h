#ifndef DATASET_H
#define DATASET_H
#include "ann/xtensor_lib.h"
using namespace std;

template <typename DType, typename LType>
class DataLabel
{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;

public:
    DataLabel(xt::xarray<DType> data, xt::xarray<LType> label)
        : data(data), label(label) {}
    xt::xarray<DType> getData() const { return data; }
    xt::xarray<LType> getLabel() const { return label; }
};

template <typename DType, typename LType>
class Batch
{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;

public:
    Batch(xt::xarray<DType> data, xt::xarray<LType> label)
        : data(data), label(label) {}
    virtual ~Batch() {}
    xt::xarray<DType> &getData() { return data; }
    xt::xarray<LType> &getLabel() { return label; }
};

template <typename DType, typename LType>
class Dataset
{
private:
public:
    Dataset() {};
    virtual ~Dataset() {};

    virtual int len() = 0;
    virtual DataLabel<DType, LType> getitem(int index) = 0;
    virtual xt::svector<unsigned long> get_data_shape() = 0;
    virtual xt::svector<unsigned long> get_label_shape() = 0;
};

//////////////////////////////////////////////////////////////////////
template <typename DType, typename LType>
class TensorDataset : public Dataset<DType, LType>
{
private:
    xt::xarray<DType> data;
    xt::xarray<LType> label;
    xt::svector<unsigned long> data_shape, label_shape;

public:
    TensorDataset(xt::xarray<DType> data, xt::xarray<LType> label)
    {
        // TODO implement
        this->data = data;
        data_shape = data.shape();
        this->label = label;
        this->label_shape = label.shape();
    }

    int len()
    {
        // TODO implement
        return data.shape()[0];
    }

    DataLabel<DType, LType> getitem(int index)
    {
        // TODO implement
        if (index < 0 || index >= len())
        {
            throw std::out_of_range("Index is out of range!");
        }
        xt::xarray<DType> data_1 = xt::view(data, index, xt::all());
        xt::xarray<LType> label_1;
        if (label.shape().size() == 0)
        {
            label_1 = label;
        }
        else
        {
            label_1 = xt::view(label, index, xt::all());
        }
        return DataLabel<DType, LType>(data_1, label_1);
    }

    xt::svector<unsigned long> get_data_shape() { return data_shape; }

    xt::svector<unsigned long> get_label_shape() { return label_shape; }
};

#endif /* DATASET_H */