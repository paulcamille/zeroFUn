#include <iostream>
#include <functional>
#include <string>

#include "solverParam.hpp"
#include "solverBase.hpp"
#include "secant.hpp"
#include "bisection.hpp"
#include "newton.hpp"
#include "solverFactory.hpp"


int main(){

    // Defining a function type for the solver
    using Function = std::function<double(double)>;

    // Creating a solver factory with the specified options file
    SolverFactory<Function, double> sol("data.dat");

    // Solving using different methods and printing the results
    std::cout << "\tNewton ->\t" << sol("Newton")->solve() << std::endl;
    std::cout << "\tBisection ->\t" << sol("Bisection")->solve() << std::endl;
    std::cout << "\tSecant ->\t" << sol("Secant")->solve() << std::endl;

    return 0;
}
