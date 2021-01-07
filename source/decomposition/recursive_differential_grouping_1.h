#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_1_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_1_METHOD_H

#include "decomposition_algorithm.h"

namespace decompose {
    class recursive_differential_grouping_1 : public decomposition_algorithm {
        protected:
            scalar y1;
            size_t dim;
            scalar epsilon;
            criteria current_criteria;

        public:
          recursive_differential_grouping_1();

            void decompose(optimization_problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            void generate_random_solution(optimization_problem &problem_, std::vector<scalar> &x) const;
            std::pair<std::set<size_t>, std::set<size_t>> interact(optimization_problem &problem_, std::set<size_t> sub_1, std::set<size_t> sub_2, std::set<size_t> x_remain);
    };
}

#endif