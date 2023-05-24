#ifndef __SECANT_HPP__
#define __SECANT_HPP__


#include "solverBase.hpp"
#include "solverTraits.hpp"


template <ScalarFunction FunctionType, Scalar xType>
class Secant : public SolverBase<FunctionType, xType> {

    using Options = SolverOption<FunctionType, xType>;

    public:
        Secant(Options);
        SolverResult<xType> solve() const;
        ~Secant();
};



template <ScalarFunction FunctionType, Scalar xType>
Secant<FunctionType, xType>::Secant(Options options_) : SolverBase<FunctionType, xType>(options_) {}




template <ScalarFunction FunctionType, Scalar xType>
Secant<FunctionType, xType>::~Secant(){}

                                                

template <ScalarFunction FunctionType, Scalar xType>
SolverResult<xType> Secant<FunctionType, xType>::solve() const{

    // Retrieve solver options
    const auto& [lower_bound, upper_bound, tolerance, toler, n_max_iteration, m_f, df] = this->m_options;
    
    // Initialize variables and result object
    double a{lower_bound}, b{upper_bound}, ya{m_f(a)}, resid{std::abs(ya)}, check{tolerance * resid + toler};
    bool goOn{resid > check};
    unsigned int iter{0u};
    SolverResult<xType> result;
    auto& [c, failed] = result;
    c = a;
    
    // Iterate until convergence or maximum number of iterations is reached
    while(goOn && iter < n_max_iteration){
        ++iter;
        double yb = m_f(b);
        c = a - ya * (b - a) / (yb - ya);
        double yc = m_f(c);
        resid = std::abs(yc);
        goOn = resid > check;
        ya = yc;
        a = c;
    }

    // Check if solver failed to converge
    failed = ( (iter >= n_max_iteration) );
    
    // Return the result object
    return result;
}



#endif /*__SECANT_HPP__*/


