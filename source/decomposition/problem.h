#ifndef DECOMPOSITION_LIBRARY_PROBLEM_H
#define DECOMPOSITION_LIBRARY_PROBLEM_H

#include "common.h"
#include <iostream>
#include <set>
#include <utility>
#include <vector>

namespace decompose {
    class problem {

    protected:
        size_t dim;
        std::vector<scalar> lower_bound;
        std::vector<scalar> upper_bound;
        std::vector<std::set<size_t>> sub_problems;
        bool problem_structure_is_known;

    public:
        problem(size_t dim_, std::vector<scalar> lower_bound_, std::vector<scalar> upper_bound_);

        virtual ~problem() = default;

        virtual scalar value(const std::vector<scalar> &x) = 0;

        bool is_known_problem_structure() const;

        void set_problem_structure(std::vector<std::set<size_t>> sub_problems_);

        std::vector<std::set<size_t>> get_problem_structure();

        size_t get_dim() const;

        std::vector<scalar> get_lower_bound();

        std::vector<scalar> get_upper_bound();

        std::string print_sub_problem_structure();
    };
}
#endif