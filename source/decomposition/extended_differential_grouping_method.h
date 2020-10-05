#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_EXTENDED_DIFFERENTIAL_GROUPING_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_EXTENDED_DIFFERENTIAL_GROUPING_METHOD_H

#include "decomposition.h"
#include <random>

namespace decompose {
    class extended_differential_grouping_method : public decomposition {
    public:
        extended_differential_grouping_method() = default;

        void analyze(problem &problem_, options &options_, criteria &criteria_) override;
    };
}

#endif