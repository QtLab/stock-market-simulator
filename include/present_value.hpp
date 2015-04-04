/**
 * \file
 * The finance::PresentValue class provides methods to calculate the current value of a stream of
 * future payments.
 */

#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>



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
     * \brief Calculates the present value considering a continuously compounded interest.
     *
     * \param cflow_times   Instants of time.
     * \param cflow_amounts Cash flow at time \f$ t \f$.
     * \param r             Constant interest rate.
     * \return              The calculated present value
     *
     * \par Continuously compounded interest.
     *      The interest is added continuously. Given an interest rate \f$ r \f$, the current
     *      price of reciving one euro at a future date \f$ t \f$ is
     *
     *      \f$ d_{t} = e^{-rt} \f$
     * \par
     *      Appliying this to a set of cash flows at future dates \f$ t_{1},t_{2},...,t_{n} \f$ we
     *      get the following present value calculation:
     *
     *      \f$ PV = \sum_{i=1}^{n}e^{-rt_{i}}C_{t_{i}} \f$
     */
    T pv_continuous_cflow(const std::vector<T>& cflow_times,
                          const std::vector<T>& cflow_amounts,
                          const T r)
    {
        T present_value = 0.0;
        for (int t = 0; t < cflow_times.size(); t++) {
            present_value += cflow_amounts[t] * exp(-r * cflow_times[t]);
        }
        return present_value;
    }

    /**
     * \brief Calculates whether the combination of cash flows has a real solution.
     *
     * \param cflow_times   Instants of time.
     * \param cflow_amounts Cash flow at time \f$ t \f$
     * \return              True if there is a real solution,
     *                      Flalse if a complex solution is found or if there is no soluton at all.
     *
     * \par
     *      The polinomical equation solved in the calculus of IRR can give complex solutions.
     *      To see whether we are likely to have problems in identifying a single meaningful IRR.
     * \par
     *      The first test is just to count the number of sign changes in the cash flow.
     *      From Descartes rule we know that the number of real roots is one if there is only
     *      one sign change. If there is more than one change in the sign of cash flows, we can
     *      go further and check the aggregated cash flows for sign changes.
     *
     */
    bool unique_discrete_irr(const std::vector<T>& cflow_times,
                             const std::vector<T>& cflow_amounts)
    {
        int sign_changes = 0;
        for (int t = 1; t < cflow_times.size(); t++) {
            if (std::signbit(cflow_amounts[t-1]) xor std::signbit(cflow_amounts[t]))
                sign_changes++;
        }
        if (sign_changes == 0) return false;
        if (sign_changes == 1) return true;

        T A = cflow_amounts[0];
        T B = A;
        sign_changes = 0;
        for (int t = 1; t < cflow_times.size(); t++) {
            B += cflow_amounts[t];
            if (std::signbit(A) xor std::signbit(B))
                sign_changes++;
        }
        if (sign_changes <= 1) return true;
        return false;
    }

    /**
     * \brief Calculates the internal rate of return.
     *
     * \param cflow_times   Instants of time.
     * \param cflow_amounts Cash flow at time \f$ t \f$.
     * \exception std::invalid_argument if parameter sizes differ
     * \exception std::domain_error if an internall error occurrs.
     * \return              The calculated internal rate of return.
     *
     * \par Internal rate of return.
     *      The percentage return on an investment is a summary measure of the investment's profitability.
     *      The return is a relative measure of profitability. To estimate a return for a set of cash flows
     *      we calculate the <em>internal rate of return</em>. The internal rate of return for a set of
     *      cash flows is the interest rate that makes the present value of the cash flows equal to zero.
     * \par
     *      Suppose the cash flows are \f$ C_{0},C_{1},C_{2},...C_{T} \f$. Finding an internal rate of
     *      return is finding a solution \f$ y \f$ of the equation:
     *
     *      \f$ \sum_{t=1}^{T}\frac{C_{t}}{(1+y)^{t}}-C_{0} = 0 \f$
     *
     * \par
     *      This is a polinomical equation that we solve numerically. For well behaved cash flows, we
     *      know that there is one IRR, we find the IRR using an iterative bisection process.
     */
    T irr_discrete_cflow(const std::vector<T>& cflow_times,
                         const std::vector<T>& cflow_amounts)
    {
        if (cflow_times.size() != cflow_amounts.size())
            throw std::invalid_argument("sizes differ");

        const T ACCURACY = 1.0e-5;
        const int MAX_ITERATIONS = 50;
        T x1 = 0.0;
        T x2 = 0.2;

        T f1 = pv_discrete_cflow(cflow_times, cflow_amounts, x1);
        T f2 = pv_discrete_cflow(cflow_times, cflow_amounts, x2);
        for (int i = 0; i < MAX_ITERATIONS and (f1*f2) >= 0.0; i++) {
            if (fabs(f1) < fabs(f2))
                f1 = pv_discrete_cflow(cflow_times, cflow_amounts, x1+=1.6*(x1-x2));
            else
                f2 = pv_discrete_cflow(cflow_times, cflow_amounts, x2+=1.6*(x2-x1));
        }
        if (f1*f2 > 0.0)
            throw std::domain_error("f1 & f2 are wrong");

        T f = pv_discrete_cflow(cflow_times, cflow_amounts, x1);
        T rtb;
        T dx=0;
        if (f < 0.0) {
            rtb = x1;
            dx  = x2-x1;
        } else {
            rtb = x2;
            dx  = x1-x2;
        }
        for (int i = 0; i < MAX_ITERATIONS; i++) {
            dx *= 0.5;
            T x_mid = rtb + dx;
            T f_mid = pv_discrete_cflow(cflow_times, cflow_amounts, x_mid);
            if (f_mid <= 0.0)
                rtb = x_mid;
            if ((fabs(f_mid) < ACCURACY) or (fabs(dx) < ACCURACY))
                return x_mid;
        }
        throw std::domain_error("Solution not found");
    }

    /**
     * \brief Calculates the present value considering one interest rate with annual compounding.
     *
     * \param cflow_times   Instants of time.
     * \param cflow_amounts Cash flow at time \f$ t \f$.
     * \param r             Constant interest rate.
     * \return              The calculated present value
     *
     * \par One interest rate with annual compounding.
     *      The best known way to simplify the present value calculation is to rewrite the discount
     *      factors int terms of interest rates, or yields, througt the relationship:
     *
     *      \f$ d_{t} = \frac{1}{(1+r_{t})^{t}} \f$
     * \par
     *      where \f$ r_{t} \f$ is the interest rate (usually termed the spot rate) relevant for
     *      a t-period investment. To further simplify this calculation one can impose that this
     *      interest rate r is constant for all periods. This is termed a <em>flat</em> term
     *      structure. The prices for valuing the future payments \f$ d_{t} \f$ is calculated from
     *      this interest rate:
     *
     *      \f$ d_{t} = \frac{1}{(1+r)^{t}} \f$
     * \par
     *      Then the present value of a stream of cash flow paid at discrete dates \f$ t = 1,2,..N \f$ is:
     *
     *      \f$ PV = \sum_{t=1}^{N}\frac{C_{t}}{(1+r)^{t}} \f$
     */
    T pv_discrete_cflow(const std::vector<T>& cflow_times,
                        const std::vector<T>& cflow_amounts,
                        const T r)
    {
        T present_value = 0.0;
        for (int t = 0; t < cflow_times.size(); t++) {
            present_value += cflow_amounts[t] / pow(1.0 + r, cflow_times[t]);
        }
        return present_value;
    }


    /**
     * \brief Calculates the present value considering a perpetuity with a fix interest rate.
     *
     * \param cflow_amount  Payment in each period of time \f$ X \f$.
     * \param r             Constant interest rate.
     * \return              The calculated present value
     *
     * \par A perpetuity is
     *      a promise of a payment of a fixed amount \f$ X \f$ each period of time for
     *      the indefinite future. Supposing there is a fixed interest rate \f$ r \f$, the present
     *      value of this sequence of cash flows is calculated as
     *
     *      \f$ PV = \sum_{t=1}^{\infty}\frac{X}{(1+r)} = \frac{X}{r} \f$
     */
    T pv_perpetuity(const T cflow_amount,
                    const T r)
    {
        return cflow_amount / r;
    }

    /**
     * \brief Calculates the present value considering a growing perpetuity with a fix interest rate.
     *
     * \param initial_cflow_amount  Initial payment \f$ X_{1} \f$.
     * \param r                     Constant interest rate.
     * \param g                     Constant growing rate.
     * \return                      The calculated present value
     *
     * \par A growing perpetuity is
     *      an infinite sequence of cashflows, where the payment the first year is \f$ X \f$ and
     *      each consequent payment grows by a constant rate \f$ g \f$.
     *      Supposing there is a fixed interest rate \f$ r \f$, the present value of this sequence
     *      of cash flows is calculated as
     *
     *      \f$ PV = \sum_{t=1}^{\infty}\frac{X(1+g)^{t-1}}{(1+r)^{t}} = \frac{X_{1}}{r-g} \f$
     */
    T pv_growing_perpetuity(const T initial_cflow_amount,
                            const T r,
                            const T g)
    {
        return initial_cflow_amount / (r - g);
    }

    /**
     * \brief Calculates the present value considering a annuity with a fix interest rate.
     *
     * \param cflow_amount  Payment in each period of time \f$ X \f$.
     * \param num_periods   Number of of periods \f$ T \f$ into the future.
     * \param r             Constant interest rate.
     * \return              The calculated present value
     *
     * \par An annuity is
     *      a sequence of cashflows for a given number of years \f$ T \f$ periods into the future.
     *      Consider an annuity paying a fixed amount \f$ X \f$ each period at a fixed interest
     *      rate \f$ r \f$. The present value of this sequence of cash flows is calculated as
     *
     *      \f$ PV = \sum_{t=1}^{T}\frac{X}{(1+r)^{t}} = X \lbrack \frac{1}{r}-\frac{1}{r}\frac{1}{(1+r)^{T}} \rbrack \f$
     */
    T pv_annuity(const T cflow_amount,
                 const T num_periods,
                 const T r)
    {
        return cflow_amount * ( (1/r) - (1 / (r * pow(1+r, num_periods)) ));
    }

    /**
     * \brief Calculates the present value considering a growing annuity with a fix interest rate.
     *
     * \param initial_cflow_amount  Initial payment \f$ X_{1} \f$.
     * \param num_periods           Number of of periods \f$ T \f$ into the future.
     * \param r                     Constant interest rate.
     * \param g                     Constant growing rate.
     * \return                      The calculated present value
     *
     * \par A growing annuity is
     *      a sequence of cashflows for a given number of years \f$ T \f$ periods into the future,
     *      where each payment grows by a given factor each year. Consider a T-period annuity that
     *      pays \f$ X \f$ the first period. After that, the payments grows at a rate \f$ g \f$ per year
     *      with a fix interest rate \f$ r \f$. The present value of this sequence of cash flows is
     *      calculated as
     *
     *      \f$ PV = \sum_{t=1}^{T}\frac{X(1+g)^{t-1}}{(1+r)^{t}} = X_{1} \lbrack \frac{1}{r-g}-(\frac{1+g}{1+r})^{T}\frac{1}{r-g} \rbrack \f$
     */
    T pv_growing_annuity(const T initial_cflow_amount,
                         const T num_periods,
                         const T r,
                         const T g)
    {
        return initial_cflow_amount * ((1/(r-g) - pow((1+g)/(1+r), num_periods) * (1/(r-g)) ));
    }

private:
    T present_value;
};

}
