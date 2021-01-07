#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_EXTENDED_DIFFERENTIAL_GROUPING_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_EXTENDED_DIFFERENTIAL_GROUPING_METHOD_H

#include "decomposition_algorithm.h"
#include <random>

namespace decompose {
    class extended_differential_grouping : public decomposition_algorithm {
        public:
          extended_differential_grouping() = default;

            void decompose(optimization_problem &problem_, options &options_, criteria &criteria_) override;
    };
}

#endif