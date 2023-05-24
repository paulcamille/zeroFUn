#ifndef __SOLVER_HPP__
#define __SOLVER_HPP__


#include "solverTraits.hpp"
#include "solverParam.hpp"



template <ScalarFunction FunctionType, Scalar xType>
class SolverBase{

    using Options = SolverOption<FunctionType, xType>;

    protected:
        Options m_options;

    public:
        SolverBase(Options);
        virtual SolverResult<xType> solve() const = 0;
        virtual ~SolverBase();
        
};


template <ScalarFunction FunctionType, Scalar xType>
SolverBase<FunctionType, xType>::SolverBase(Options options_) : m_options(options_) {}


template <ScalarFunction FunctionType, Scalar xType>
SolverBase<FunctionType, xType>::~SolverBase(){}



#endif /*__SOLVER_HPP__*/

