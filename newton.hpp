

#ifndef __NEWTON_HPP__
#define __NEWTON_HPP__


#include "solverBase.hpp"
#include "solverTraits.hpp"


template <ScalarFunction FunctionType, Scalar xType>
class Newton : public SolverBase<FunctionType, xType> {

    using Options = SolverOption<FunctionType, xType>;
  
    public:
        Newton(Options);
        SolverResult<xType> solve() const;
        ~Newton();
};


template <ScalarFunction FunctionType, Scalar xType>
Newton<FunctionType, xType>::Newton(Options options_) : SolverBase<FunctionType, xType>(options_) {}


template <ScalarFunction FunctionType, Scalar xType>
Newton<FunctionType, xType>::~Newton(){}

                                                

template <ScalarFunction FunctionType, Scalar xType>
  SolverResult<xType> Newton<FunctionType, xType>::solve() const{
    // Extract the options from the base class
    const auto& [lower_bound, upper_bound, tolerance, toler, n_max_iteration, m_f, m_df] = this->m_options;
    // Initializing variables.
    double a{lower_bound}, ya{m_f(a)}, resid{std::abs(ya)}, check{tolerance * resid + toler};
    bool goOn{resid > check};
    unsigned int iter{0u};
    // Initializing the result variable.
    SolverResult<xType> result;
    auto& [res, failed] = result;
    // Looping until the convergence criteria are met or until the maximum number of iterations is reached.
    while(goOn && iter < n_max_iteration){
        // Incrementing the iteration counter.
        ++iter;
        // Updating the approximation using Newton's method.
        a += - ya/m_df(a);
        // Evaluating the function at the updated approximation.
        ya = m_f(a);
        // Updating the residual and the goOn flag.
        resid = std::abs(ya);
        goOn = resid > check;
      }
      // Storing the result in the result variable.
      res = a;
      // Setting the failed flag to true if the maximum number of iterations is reached.
      failed = ( (iter >= n_max_iteration) );
    // Returning the result.
    return result;
}

#endif /*__NEWTON_HPP__*/




