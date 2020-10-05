#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_DIFFERENTIAL_GROUPING_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_DIFFERENTIAL_GROUPING_METHOD_H

#include <unordered_set>
#include <decomposition.h>

namespace decompose {
    class differential_grouping_method : public decomposition {
    public:
        differential_grouping_method() = default;

        void analyze(problem &problem_, options &options_, criteria &criteria_) override;
    };
}

#endif