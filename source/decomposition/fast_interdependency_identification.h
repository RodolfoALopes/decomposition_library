#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_FAST_INTERDEPENDECY_IDENTIFICATION_METHOD_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_FAST_INTERDEPENDECY_IDENTIFICATION_METHOD_H

#include "decomposition_algorithm.h"

namespace decompose {
    class fast_interdependency_identification : public decomposition_algorithm {
        public:
          fast_interdependency_identification() = default;

            void decompose(optimization_problem &problem_, options &options_, criteria &criteria_) override;

        protected:
            static void diff(optimization_problem &problem_, std::vector<scalar> &x, scalar delta, const std::set<size_t>& indices, std::vector<scalar> &v, criteria &criteria_);
    };
}

#endif