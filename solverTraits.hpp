#ifndef _SOLVER_TRIATS_HPP_
#define _SOLVER_TRIATS_HPP_

#include <type_traits>
#include <array>
#include <functional>


// The first concept 'Scalar' ensures that the input type is a floating point number
template<typename T>
concept Scalar = std::is_floating_point<std::decay_t<T>>::value;

// The second concept 'ScalarFunction' ensures that the input type is a function that can be converted to 
// std::function<double (double)> and the return type of this function is also double

template<class F>
concept ScalarFunction = std::convertible_to<F,std::function<std::decay_t<double> (std::decay_t<double>)>>;


#endif /* _SOLVER_TRIATS_HPP_ */
