#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_GLOBAL_DIFFERENTIAL_GROUPING_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_GLOBAL_DIFFERENTIAL_GROUPING_METHOD_H

#include "decomposition.h"

namespace decompose {
    class global_differential_grouping_method : public decomposition {
        public:
            global_differential_grouping_method() = default;

            void analyze(problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            static void generate_random_solution(problem &problem_, std::vector<scalar> &x, size_t dim);
    };
}

#endif