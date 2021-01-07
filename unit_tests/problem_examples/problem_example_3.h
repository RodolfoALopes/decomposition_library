#ifndef DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_3_H
#define DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_3_H

#include <decomposition/optimization_problem.h>

/*
 * problem_example_3 class
 * NonSeparable Problem
 */

using namespace decompose;

class problem_example_3 : public optimization_problem {
public:
    using super = optimization_problem;

public:
    explicit problem_example_3(size_t dimension, std::vector<scalar> lower_bound,
                             std::vector<scalar> upper_bound)
        : super(dimension, std::move(lower_bound), std::move(upper_bound)) {}

    scalar value(const std::vector<scalar> &x) override {
        scalar sum = 0.0;
        for(size_t i = 0; i < dimension-1; i++){
            sum += ((100*pow(x[i+1] - pow(x[i],2),2)) + pow(x[i]-1,2));
        }
        return sum;
    }
};

#endif
