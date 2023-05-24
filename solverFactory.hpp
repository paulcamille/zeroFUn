

#ifndef __SOLVER_FACTORY_HPP__
#define __SOLVER_FACTORY_HPP__

#include <string>
#include "solverParam.hpp"


template <ScalarFunction FunctionType, Scalar xType>
class SolverFactory{

    private: 
        std::string m_option_filename;

    public:
        SolverFactory(std::string);
        ~SolverFactory();
        void set_filename(std::string);
        std::unique_ptr<SolverBase<FunctionType, xType>> operator()(const std::string & type_solver) const; 

};

template <ScalarFunction FunctionType, Scalar xType>
SolverFactory<FunctionType, xType>::SolverFactory(std::string opt_filename) : m_option_filename(opt_filename) {}


// Setter for option filename
template <ScalarFunction FunctionType, Scalar xType>
void SolverFactory<FunctionType, xType>::set_filename(std::string new_option_filename){
    m_option_filename = new_option_filename;
}


template <ScalarFunction FunctionType, Scalar xType>
SolverFactory<FunctionType, xType>::~SolverFactory() {}


// Factory method to create solvers
template <ScalarFunction FunctionType, Scalar xType>
std::unique_ptr<SolverBase<FunctionType, xType>> SolverFactory<FunctionType, xType>::operator()(const std::string & type_solver) const{
    if (type_solver == "Bisection")
        return std::unique_ptr<SolverBase<FunctionType, xType>>( new Bisection<FunctionType, xType>(SolverOption<FunctionType, xType>(m_option_filename)));
    else if (type_solver == "Secant")
        return std::unique_ptr<SolverBase<FunctionType, xType>>( new Secant<FunctionType, xType>(SolverOption<FunctionType, xType>(m_option_filename)));
    else if (type_solver == "Newton")
        return std::unique_ptr<SolverBase<FunctionType, xType>>( new Newton<FunctionType, xType>(SolverOption<FunctionType, xType>(m_option_filename)));
    else
        throw std::invalid_argument("Invalid argument: wrong solver \"" + type_solver + "\" specified.");
}

#endif /*__SOLVER_FACTORY_HPP__*/