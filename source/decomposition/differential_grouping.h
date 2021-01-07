#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_DIFFERENTIAL_GROUPING_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_DIFFERENTIAL_GROUPING_METHOD_H

#include "decomposition_algorithm.h"
#include <unordered_set>

namespace decompose {
    class differential_grouping : public decomposition_algorithm {
        public:
          differential_grouping() = default;

            void decompose(optimization_problem &problem_, options &options_, criteria &criteria_) override;
    };
}

#endif