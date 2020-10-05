#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_DIFFERENTIAL_GROUPING_2_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_DIFFERENTIAL_GROUPING_2_METHOD_H

#include "decomposition.h"
#include <unordered_set>

namespace decompose {
    class differential_grouping_2_method : public decomposition {
        protected:
            std::vector<std::vector<scalar>> matrix_f;
            std::vector<scalar> vec_f;
            std::vector<std::vector<scalar>> lambda;
            std::vector<std::vector<scalar>> theta;
        public:
            differential_grouping_2_method() = default;

            void analyze(problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            void ism(problem &problem_, size_t dim, scalar &fx_base, criteria &criteria_);
            void dsm(size_t dim, scalar &fx_base);
            static scalar gamma(double d);
            static scalar max_element(scalar x1, scalar x2, scalar x3, scalar x4);
            static scalar max_element(scalar x1, scalar x2);
    };
}

#endif