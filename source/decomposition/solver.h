#ifndef DECOMPOSITION_LIBRARY_SOLVER_H
#define DECOMPOSITION_LIBRARY_SOLVER_H

#include "problem.h"
#include "common.h"

namespace decompose {
    class solver {
    public:

    protected:
        criteria stop_, current_;
        options options_{};
        status m_status = status::NotStarted;
        stats m_stats;
        debug_level m_debug = debug_level::None;

    public:
        virtual ~solver() = default;

        solver() {
            stop_ = criteria::defaults();
            options_ = options::defaults();
            current_.reset();
            m_stats.reset();
        }

        solver(criteria &current_criteria, criteria &stop_criteria, options &o) {
            stop_ = stop_criteria;
            current_ = current_criteria;
            options_ = o;
            m_stats.reset();
        }

        const status &get_status() { return m_status; }

        stats &get_stats() { return m_stats; }

        static string get_status_string(const status &s) {
            string os;
            switch (s) {
                case status::IterationLimit: os += "Iteration limit reached."; break;
                case status::EvaluationLimit: os += "Function evaluation limit reached."; break;
                case status::FOptimum:   os += "f(x*) criteria reached."; break;
                case status::NotStarted: os += "Solver not started."; break;
                case status::Continue:   os += "Convergence criteria not reached."; break;
            }
            return os;
        }

        void set_debug(const debug_level &d) { m_debug = d; }

        virtual void minimize(problem &problem_, vector<scalar> &x0) = 0;

        static status check_convergence(const criteria &stop, const criteria &current) {
            if ((stop.fx_is_know) && (current.fx_best - stop.fx_best <= stop.error_fx_best)) {
                return status::FOptimum;
            }
            if ((stop.iterations > 0) && (current.iterations >= stop.iterations)) {
                return status::IterationLimit;
            }
            if ((stop.evaluations > 0) && (current.evaluations >= stop.evaluations)) {
                return status::EvaluationLimit;
            }
            return status::Continue;
        }

    };
}
#endif