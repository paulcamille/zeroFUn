#ifndef __SOLVER_PARM_HPP__
#define __SOLVER_PARM_HPP__

#include "solverTraits.hpp"
#include <GetPot>

#include "muparser_fun.hpp"



/// Struct holding the results of the solver.
template <Scalar xType = double>
struct SolverResult {

  xType x;   /// Solutions.
  bool failed = true;    /// Failure.
};


/// Solver option class.
template <ScalarFunction FunctionType, Scalar xType = double>
class SolverOption {
 public:

    //using Function = std::function<VariableType(TimeType, const VariableType&)>;
    //using Function = std::function<xType(xType)>;
  // Make the RKF class a friend for all its template combinations,
  // so they can access private members of this class.
  template <ScalarFunction, Scalar>
  friend class Bisection;

  template <ScalarFunction, Scalar>
  friend class Secant;

  template <ScalarFunction, Scalar>
  friend class Newton;


  SolverOption() = default;

  SolverOption(const std::string& filename) { parse_from_file(filename); }

  private:
    xType lower_bound;
    xType upper__bound;
    xType tolerance;
    xType toler;
    unsigned int n_max_iteration;
    FunctionType f;
    FunctionType df;

    void parse_from_file(const std::string& filename) {

      GetPot datafile(filename.c_str());

      lower_bound = datafile("lower_bound", 0.);
      upper__bound = datafile("upper_bound", 1.);
      tolerance = datafile("tolerance", 1e-6);
      toler = datafile("toler", 1e-6);
      n_max_iteration = datafile("n_max_iteration", 150);

      const std::string f_str = datafile("f", "x");
      const std::string df_str = datafile("df", "x");

      
      f = MuparserFun (f_str);
      df = MuparserFun (df_str);


  };
};

template <Scalar xType>
std::ostream& operator<<(std::ostream& out,
                         const SolverResult<xType> & res) {
  out << "Zero = " << res.x << "\tfailed = " << res.failed;
  return out;
}


#endif /*__SOLVER_PARM_HPP__*/
