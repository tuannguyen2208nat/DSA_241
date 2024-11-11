/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/*
 * File:   ReLU.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:44 PM
 */

#include "layer/ReLU.h"
#include "sformat/fmt_lib.h"
#include "ann/functions.h"

ReLU::ReLU(string name)
{
    if (trim(name).size() != 0)
        m_sName = name;
    else
        m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::ReLU(const ReLU &orig)
{
    m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::~ReLU()
{
}

xt::xarray<double> ReLU::forward(xt::xarray<double> X)
{
    // YOUR CODE IS HERE
    m_aMask = (X >= 0);
    return xt::where(m_aMask, X, 0.0);
}
xt::xarray<double> ReLU::backward(xt::xarray<double> DY)
{
    // YOUR CODE IS HERE
    return xt::where(m_aMask, DY, 0.0);
}

string ReLU::get_desc()
{
    string desc = fmt::format("{:<10s}, {:<15s}:",
                              "ReLU", this->getname());
    return desc;
}