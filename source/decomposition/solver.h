#ifndef DECOMPOSITION_LIBRARY_SOLVER_H
#define DECOMPOSITION_LIBRARY_SOLVER_H

#include "common.h"
#include "optimization_problem.h"

namespace decompose {
    class solver {

        protected:
            criteria stop_criteria, current_criteria;
            options solver_options{};
            status m_status = status::NotStarted;
            stats m_stats;
            debug_level m_debug = debug_level::None;

        public:
            virtual ~solver() = default;

            solver();

            solver(criteria &current_criteria_, criteria &stop_criteria_, options &options_);

            const status &get_status();

            stats &get_stats();

            static std::string get_status_string(const status &s);

            void set_debug(const debug_level &d);

            virtual void minimize(optimization_problem &problem_, std::vector<scalar> &x0) = 0;

            static status check_convergence(const criteria &stop, const criteria &current);
    };
}
#endif