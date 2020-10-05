#ifndef DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_2_H
#define DECOMPOSITION_LIBRARY_PROBLEM_EXAMPLE_2_H

#include "problem.h"

/*
 * problem_example_2 class
 * Partially Separable Problem
 */

using namespace decompose;

class problem_example_2 : public problem {
public:
    using super = problem;

public:
    explicit problem_example_2(size_t dim, vector<scalar> lower_bound, vector<scalar> upper_bound) : super(dim, std::move(lower_bound), std::move(upper_bound)) {}

    scalar value(const vector<scalar> &x) override {
        size_t n_sub_problem = 2;
        size_t size_sub_problem = floor(dim/n_sub_problem);
        vector<pair<size_t,size_t>> sub_problems_tmp;
        size_t k = 0;
        for(size_t i = 1; i < n_sub_problem; i++){
            pair<size_t,size_t> tmp(k, k + size_sub_problem);
            sub_problems_tmp.push_back(tmp);
            k += size_sub_problem;
        }
        pair<size_t,size_t> tmp(k, dim);
        sub_problems_tmp.push_back(tmp);
        scalar sum = 0.0;
        for(auto p : sub_problems_tmp){
            scalar result = 1.0;
            for(size_t j = p.first; j < p.second; j++){
                result = result * pow(x[j], 2);
            }
            sum += result;
        }
        return sum;
    }
};

#endif
