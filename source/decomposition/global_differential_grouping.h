#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_GLOBAL_DIFFERENTIAL_GROUPING_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_GLOBAL_DIFFERENTIAL_GROUPING_METHOD_H

#include "decomposition_algorithm.h"

namespace decompose {
    class global_differential_grouping : public decomposition_algorithm {
        public:
          global_differential_grouping() = default;

            void decompose(optimization_problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            static void generate_random_solution(optimization_problem &problem_, std::vector<scalar> &x, size_t dim);
    };
}

#endif