#ifndef DECOMPOSITION_LIBRARY_OPTIMIZATION_PROBLEM_H
#define DECOMPOSITION_LIBRARY_OPTIMIZATION_PROBLEM_H

#include "common.h"
#include <iostream>
#include <set>
#include <utility>
#include <vector>

namespace decompose {
    class optimization_problem {

    protected:
        size_t dimension;
        std::vector<scalar> lower_bound;
        std::vector<scalar> upper_bound;
        std::vector<std::set<size_t>> sub_problems;
        bool problem_structure_is_known;

    public:
          optimization_problem(size_t dimension_, std::vector<scalar> lower_bound_, std::vector<scalar> upper_bound_);

            virtual ~optimization_problem() = default;

            virtual scalar value(const std::vector<scalar> &x) = 0;

            bool is_known_problem_structure() const;

            void set_problem_structure(std::vector<std::set<size_t>> sub_problems_);

            std::vector<std::set<size_t>> get_problem_structure() const;

            size_t get_dimension() const;

            std::vector<scalar> get_lower_bound() const;

            std::vector<scalar> get_upper_bound() const;
    };
}
#endif