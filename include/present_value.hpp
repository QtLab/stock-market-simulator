#pragma once

#include <cmath>
#include <vector>
#include <iostream>



template <class T>
class PresentValue
{
public:
    void cash_flow_pv_discrete(const std::vector<T>& cflow_times,
                               const std::vector<T>& cflow_amounts,
                               const T& r);
};

