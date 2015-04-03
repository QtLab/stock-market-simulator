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
                               const T& r)
    {
        this->present_value = 0.0;
        for (int t = 0; t < cflow_times.size(); t++) {
            this->present_value += cflow_amounts[t] / pow(1.0 + r, cflow_times[t]);
        }
    }
private:
    T present_value;
};

