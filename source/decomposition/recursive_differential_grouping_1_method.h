#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_1_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_1_METHOD_H

#include "decomposition.h"

namespace decompose {
    class recursive_differential_grouping_1_method : public decomposition {
        protected:
            scalar y1;
            size_t dim;
            scalar epsilon;
            criteria current_criteria;

        public:
            recursive_differential_grouping_1_method();

            void analyze(problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            void generate_random_solution(problem &problem_, std::vector<scalar> &x) const;
            std::pair<std::set<size_t>, std::set<size_t>> interact(problem &problem_, std::set<size_t> sub_1, std::set<size_t> sub_2, std::set<size_t> x_remain);
    };
}

#endif