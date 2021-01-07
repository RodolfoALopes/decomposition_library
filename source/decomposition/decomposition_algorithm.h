#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_ALGORITHM_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_ALGORITHM_H

#include "common.h"
#include "optimization_problem.h"
#include <functional>
#include <set>

namespace decompose {
    class decomposition_algorithm {
        protected:
            debug_level m_debug = debug_level::None;

        public:
            virtual ~decomposition_algorithm() = default;

            decomposition_algorithm() = default;

            virtual void decompose(optimization_problem &problem_, options &options_, criteria &criteria_) = 0;
    };
}
#endif