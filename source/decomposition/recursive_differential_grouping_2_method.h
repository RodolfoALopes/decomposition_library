#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_2_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_2_METHOD_H

#include "decomposition.h"

namespace decompose {
    class recursive_differential_grouping_2_method : public decomposition {
    protected:
        scalar y1;
        size_t dim;
        criteria current_criteria;

    public:
        recursive_differential_grouping_2_method() {
            y1 = 0;
            dim = 0;
        };

        void analyze(problem &problem_, options &options_, criteria &criteria_) override;

    protected:
        static scalar gamma(double d);
        pair<set<size_t>, set<size_t>> interact(problem &problem_, set<size_t> sub_1, set<size_t> sub_2, set<size_t> x_remain);
    };
}

#endif