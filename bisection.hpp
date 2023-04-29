// Header guards to prevent multiple includes of this file
#ifndef __BISSECTION_HPP__
#define __BISSECTION_HPP__

// Include the required headers
#include "solverBase.hpp"
#include "solverTraits.hpp"

// Template class for the bisection method, inherits from SolverBase class
template <ScalarFunction FunctionType, Scalar xType>
class Bisection : public SolverBase<FunctionType, xType> {
    // Alias for the SolverOption struct, used for readability
    using Options = SolverOption<FunctionType, xType>;

public:
    // Constructor takes an instance of the Options struct as an argument
    Bisection(Options);

    // Method that performs the bisection algorithm and returns a SolverResult struct
    SolverResult<xType> solve() const;

    // Destructor
    ~Bisection();
};

// Constructor implementation
template <ScalarFunction FunctionType, Scalar xType>
Bisection<FunctionType, xType>::Bisection(Options options_) : SolverBase<FunctionType, xType>(options_) {}

// Destructor implementation
template <ScalarFunction FunctionType, Scalar xType>
Bisection<FunctionType, xType>::~Bisection(){}

// Method implementation
template <ScalarFunction FunctionType, Scalar xType>
SolverResult<xType> Bisection<FunctionType, xType>::solve() const{
    // Extract the options from the base class
    const auto& [lower_bound, upper_bound, tolerance, toler, n_max_iteration, m_f, df] = this->m_options;
    // Initialize variables for the algorithm
    double a{lower_bound}, b{upper_bound}, ya{m_f(a)}, yb{m_f(b)}, delta{b-a}, yc{ya}, c{a};
    // Create a SolverResult struct to store the result of the algorithm
    SolverResult<xType> result;
    // Extract the result and failed fields from the SolverResult struct
    auto& [res, failed] = result;

    // Check if the function changes sign at the two end values
    if ( !(ya * yb <= 0) ){
        // Output an error message if the signs are not correct
        std::cerr << "Function must change sign at the two end values" << std::endl;
    }
    else{
        // Enter the main loop of the bisection algorithm
        while( (std::abs(delta) > 2 * tolerance)){
            // Compute the midpoint of the interval
            c = (a + b) / 2.;
            // Evaluate the function at the midpoint
            yc = m_f(c);
            // Check if the function value at one of the end points is zero
            if (ya == 0){
                // Set the result to the endpoint with zero function value
                res = a;
                // Update the interval so that it contains only the endpoint with zero function value
                b = a;
                // Break out of the loop
                break;
            }
            else if (yb == 0){
                // Set the result to the endpoint with zero function value
                res = b;
                // Update the interval so that it contains only the endpoint with zero function value
                a = b;
                // Break out of the loop
                break;
            }
            // Check if the function changes sign at the midpoint
            if(yc * ya < 0.0){
                // Update the interval to the left half
                yb = yc;
                b = c;
            }
            else{
                // Update the interval to the right half
                ya = yc;
                a = c;
            }
            delta = b - a; // update the difference between the two end points
        }
        failed = false;

        res = (a + b) / 2.; // final value of res if delta < 2*tolerance
    }
    return result;
}
#endif /*__BISSECTION_HPP__*/