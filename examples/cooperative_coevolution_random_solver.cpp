#include "problem.h"
#include "fast_interdependency_identification_method.h"
#include "solver.h"

using namespace decompose;

class problem_example : public problem {
public:
    using super = problem;

    explicit problem_example(size_t dim, vector<scalar> lower_bound, vector<scalar> upper_bound) : super(dim, std::move(lower_bound), std::move(upper_bound)) {}

    scalar value(const vector<scalar> &x) override {
        scalar sum = 0.0;
        for(int i = 0; i < dim; i++){
            sum += pow(x[i], 2);
        }
        return sum;
    }
};

class cooperative_co_evolution_random_solver : public solver {
public:
    using super = solver;

    cooperative_co_evolution_random_solver() : super() {}

    cooperative_co_evolution_random_solver(criteria &current_criteria, criteria &stop_criteria, options &o) : super(current_criteria, stop_criteria, o) {}

    void generate_random_solutions(problem &problem_, size_t index_sub_problem, vector<scalar> &x, scalar &fx, size_t number_samples){
        vector<scalar> x_tmp = x;
        set<size_t> sub_problem = problem_.get_problem_structure()[index_sub_problem];
        for(size_t i = 1; i <= number_samples; i++){
            for(unsigned long index_var : sub_problem){
                uniform_real_distribution<scalar> dist(problem_.get_lower_bound()[index_var], problem_.get_upper_bound()[index_var]);
                x_tmp[index_var] = dist(default_generator());
            }
            status status_ = check_convergence(stop_, current_);
            if(status_ == status::Continue){
                scalar fx_tmp = problem_.value(x_tmp);
                current_.evaluations++;
                m_stats.push(fx_tmp, current_.evaluations);
                if(fx_tmp < fx){
                    fx = fx_tmp;
                    x = x_tmp;
                }
            }
            else{
                return;
            }
        }
    }

    void minimize(problem &problem_, vector<scalar> &x0) override{
        const size_t number_samples = 100;
        scalar best_fx = problem_.value(x0);
        current_.evaluations++;
        m_stats.push(best_fx, current_.evaluations);
        bool is_known_problem_structure = problem_.is_known_problem_structure();
        if(m_debug >= debug_level::Low){
            cout << "Solver Initialization ..." << endl;
            cout << "Iteration: " << current_.iterations << " - Evaluations: " << current_.evaluations << " - f(x0): " << best_fx << endl;
        }
        if(!is_known_problem_structure){
            cerr << "Problem Structure is not Available." << endl;
            return;
        }
        size_t index_sub_problem = 0;
        status status_ = check_convergence(stop_, current_);
        while(status_ == status::Continue){
            generate_random_solutions(problem_, index_sub_problem, x0, best_fx, number_samples);
            index_sub_problem = (index_sub_problem+1) % problem_.get_problem_structure().size();
            current_.iterations++;
            if(m_debug >= debug_level::Low){
                cout << "Iteration: " << current_.iterations << " - Evaluations: " << current_.evaluations << " - f(x0): " << best_fx << endl;
            }
            status_ = check_convergence(stop_, current_);
        }
        cout << endl << endl << "Solver Status: " << endl << get_status_string(status_) << endl;
        cout << "F(x) of Best Solution: " << best_fx << endl << endl;
    }
};

int main() {
    const size_t dim = 1000;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    criteria current_, stop_;
    options options_ = options::defaults();
    stop_.evaluations = dim * 1000;
    stop_.iterations = 1000;
    stop_.fx_is_know = true;
    stop_.error_fx_best = 0.001;
    stop_.fx_best = 0.0;

    problem_example f(dim, vector<scalar>(dim, lower_bound), vector<scalar>(dim, upper_bound));

    fast_interdependency_identification_method method;
    method.analyze(f, options_, current_);

    cooperative_co_evolution_random_solver solver(current_, stop_, options_);
    solver.set_debug(debug_level::None);

    vector<scalar> x0(dim);

    for(size_t i = 0; i < dim; i++){
        uniform_real_distribution<scalar> dist(f.get_lower_bound()[i], f.get_upper_bound()[i]);
        x0[i] = dist(default_generator());
    }

    solver.minimize(f, x0);

    for(size_t i = 0; i < solver.get_stats().get_history().size(); i++){
        cout << "Evaluation: " << solver.get_stats().get_history()[i].evaluation
             << " - F(x): " << solver.get_stats().get_history()[i].fx
             << " - Time: " << solver.get_stats().get_history()[i].time.count() << endl;
    }
    return 0;
}