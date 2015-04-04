/**
 * \file
 * The finance::PresentValue class provides methods to calculate the current value of a stream of
 * future payments.
 */

#pragma once

#include <cmath>
#include <vector>
#include <iostream>




namespace finance {

/**
 * \brief The PresentValue class provides methods to calculate the current value of a stream of
 *        future payments.
 * \ingroup Finance
 *
 * \tparam T        The type of calculations (must be an floating point).
 *
 * \par The <em>present value</em> is the current value of a stream of future payments.
 *      Let \f$ C_{t} \f$ be the cash flow at time \f$ t \f$. Suppose we have \f$ N \f$ future cash
 *      flows that occur at times \f$ t_{1},t_{2},...,t_{N} \f$.
 *      To find the <em>present</em> value of these future cash flows one need a set of prices of
 *      future cash flows. Suppose \f$ d_{t} \f$ is the price one would pay today for the right to
 *      receive one dollar at a future date \f$ t \f$. Such a price is also called a
 *      <em>discount factor</em>. If one knows the set of prices for future claims of one dollar,
 *      \f$ d_{1},d_{2},..., \f$ one would calculate the present value as the sum of the present
 *      values of the differents elements.
 *
 *      \f$ PV = \sum_{i=0}^{N}d_{t_{i}}C_{t_{i}} \f$
 *
 */
template <class T>
class PresentValue
{
public:
    /**
     * \brief Calculates the present value considering one interest rate with annual compounding.
     *
     * \param cflow_times   Instants of time.
     * \param cflow_amounts Cash flow at time \f$ t \f$.
     * \param r             Constant interest rate.
     *
     * \par One interest rate with annual compounding.
     *      The best known way to simplify the present value calculation is to rewrite the discount
     *      factors int terms of interest rates, or yields, througt the relationship:
     *      \f$ d_{t} = \frac{1}{(1+r_{t})^{t}} \f$
     *      where \f$ r_{t} \f$ is the interest rate (usually termed the spot rate) relevant for
     *      a t-period investment. To further simplify this calculation one can impose that this
     *      interest rate r is constant for all periods. This is termed a <em>flat</em> term
     *      structure. The prices for valuing the future payments \f$ d_{t} \f$ is calculated from
     *      this interest rate:
     *      \f$ d_{t} = \frac{1}{(1+r)^{t}} \f$
     *      Then the present value of a stream of cash flow paid at discrete dates \f$ t = 1,2,..N \f$ is:
     *
     *      \f$ PV = \sum_{i=0}^{N}\frac{C_{t_{i}}}{(1+r)^{t}} \f$
     */
    void cash_flow_pv_discrete(const std::vector<T>& cflow_times,
                               const std::vector<T>& cflow_amounts,
                               T r)
    {
        this->present_value = 0.0;
        for (int t = 0; t < cflow_times.size(); t++) {
            this->present_value += cflow_amounts[t] / pow(1.0 + r, cflow_times[t]);
        }
    }
private:
    T present_value;
};

}
