#ifndef DECOMPOSITION_LIBRARY_DECOMPOSITION_H
#define DECOMPOSITION_LIBRARY_DECOMPOSITION_H

#include "common.h"
#include "problem.h"
#include <functional>
#include <set>

using namespace std;

namespace decompose {
    class decomposition {
      protected:
        debug_level m_debug = debug_level::None;

      public:
        virtual ~decomposition() = default;

        decomposition() = default;

        virtual void analyze(problem &problem_, options &options_, criteria &criteria_) = 0;

    };
}
#endif