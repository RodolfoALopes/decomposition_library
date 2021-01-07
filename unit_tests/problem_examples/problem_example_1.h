#ifndef DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_1_H
#define DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_1_H

#include <decomposition/optimization_problem.h>

/*
 * problem_example_1 class
 * Full Separable Problem
 */

using namespace decompose;

class problem_example_1 : public optimization_problem {
public:
    using super = optimization_problem;

public:
    explicit problem_example_1(size_t dimension, std::vector<scalar> lower_bound,
                               std::vector<scalar> upper_bound)
        : super(dimension, std::move(lower_bound), std::move(upper_bound)) {}

    scalar value(const std::vector<scalar> &x) override {
        scalar sum = 0.0;
        for(scalar x_i : x){
            sum += x_i * x_i;
        }
        return sum;
    }
};

#endif
