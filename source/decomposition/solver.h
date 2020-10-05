#ifndef DECOMPOSITION_LIBRARY_SOLVER_H
#define DECOMPOSITION_LIBRARY_SOLVER_H

#include "problem.h"
#include "common.h"

namespace decompose {
    class solver {

        protected:
            criteria stop_, current_;
            options options_{};
            status m_status = status::NotStarted;
            stats m_stats;
            debug_level m_debug = debug_level::None;

        public:
            virtual ~solver() = default;

            solver();

            solver(criteria &current_criteria, criteria &stop_criteria, options &o);

            const status &get_status();

            stats &get_stats();

            static std::string get_status_string(const status &s);

            void set_debug(const debug_level &d);

            virtual void minimize(problem &problem_, std::vector<scalar> &x0) = 0;

            static status check_convergence(const criteria &stop, const criteria &current);
    };
}
#endif