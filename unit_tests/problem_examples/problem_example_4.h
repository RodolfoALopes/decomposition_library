#ifndef DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_4_H
#define DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_4_H

#include <decomposition/optimization_problem.h>

/*
 * problem_example_4 class
 * NonSeparable Problem
 */

using namespace decompose;

class problem_example_4 : public optimization_problem {
public:
    using super = optimization_problem;

public:
    explicit problem_example_4(size_t dimension, std::vector<scalar> lower_bound,
                               std::vector<scalar> upper_bound)
        : super(dimension, std::move(lower_bound), std::move(upper_bound)) {}

    scalar value(const std::vector<scalar> &x) override {
        scalar result = 1.0;
        for(scalar x_i : x){
            result = result * pow(x_i, 2);
        }
        return result;
    }
};

#endif
