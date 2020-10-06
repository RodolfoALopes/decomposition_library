#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_FAST_INTERDEPENDECY_IDENTIFICATION_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_FAST_INTERDEPENDECY_IDENTIFICATION_METHOD_H

#include "decomposition.h"

namespace decompose {
    class fast_interdependency_identification_method : public decomposition {
        public:
            fast_interdependency_identification_method() = default;

            void analyze(problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            static void diff(problem &problem_, std::vector<scalar> &x, scalar delta, const std::set<size_t>& indices, std::vector<scalar> &v, criteria &criteria_);
    };
}

#endif