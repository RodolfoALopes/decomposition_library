#include "solver.h"

using namespace decompose;
using namespace std;

solver::solver() {
    stop_criteria = criteria::defaults();
    solver_options = options::defaults();
    current_criteria.reset();
    m_stats.reset();
}

solver::solver(criteria &current_criteria_, criteria &stop_criteria_, options &options_) {
    stop_criteria = stop_criteria_;
    current_criteria = current_criteria_;
    solver_options = options_;
    m_stats.reset();
}

const status &solver::get_status() {
    return m_status;
}

stats &solver::get_stats(){
    return m_stats;
}

string solver::get_status_string(const status &s) {
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

void solver::set_debug(const debug_level &d) {
    m_debug = d;
}

status solver::check_convergence(const criteria &stop, const criteria &current) {
    if((stop.fx_is_know) && (current.fx_best - stop.fx_best <= stop.error_fx_best)) {
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