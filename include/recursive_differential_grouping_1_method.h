#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_1_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_RECURSIVE_DIFFERENTIAL_GROUPING_1_METHOD_H

#include <decomposition.h>

namespace decompose {
    class recursive_differential_grouping_1_method : public decomposition {
    protected:
        scalar y1;
        size_t dim;
        scalar epsilon;
        criteria current_criteria;

    public:
        recursive_differential_grouping_1_method() {
            y1 = 0;
            dim = 0;
            epsilon = 0;
        };

        void analyze(problem &problem_, options &options_, criteria &criteria_) override;

    protected:
        void generate_random_solution(problem &problem_, vector<scalar> &x) const;
        pair<set<size_t>, set<size_t>> interact(problem &problem_, set<size_t> sub_1, set<size_t> sub_2, set<size_t> x_remain);
    };
}

#endif