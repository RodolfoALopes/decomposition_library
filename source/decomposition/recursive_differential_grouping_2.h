#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_2_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_2_METHOD_H

#include "decomposition_algorithm.h"

namespace decompose {
    class recursive_differential_grouping_2 : public decomposition_algorithm {
        protected:
            scalar y1;
            size_t dim;
            criteria current_criteria;

        public:
          recursive_differential_grouping_2();

            void decompose(optimization_problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            static scalar gamma(double d);
            std::pair<std::set<size_t>, std::set<size_t>> interact(optimization_problem &problem_, std::set<size_t> sub_1, std::set<size_t> sub_2, std::set<size_t> x_remain);
    };
}

#endif