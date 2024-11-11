/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/*
 * File:   CrossEntropy.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"
#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction) : ILossLayer(reduction)
{
}

CrossEntropy::CrossEntropy(const CrossEntropy &orig) : ILossLayer(orig)
{
}

CrossEntropy::~CrossEntropy()
{
}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t)
{
    // YOUR CODE IS HERE
    m_aCached_Ypred = X;
    m_aYtarget = t;
    return cross_entropy(m_aCached_Ypred, m_aYtarget, this->m_eReduction == REDUCE_MEAN);
}
xt::xarray<double> CrossEntropy::backward()
{
    // YOUR CODE IS HERE
    double EPSILON = 1e-7;
    xt::xarray<double> grad = -(m_aYtarget / (m_aCached_Ypred + EPSILON));
    if (m_eReduction == REDUCE_MEAN)
    {
        grad /= m_aCached_Ypred.shape()[0];
    }
    return grad;
}