#include "differential_evolution_cooperative_coevolutive.h"
#include <vector>
#include <random>
#include <iomanip>


differential_evolution_cooperative_coevolutive::differential_evolution_cooperative_coevolutive(criteria &current_criteria, criteria &stop_criteria, options &o) : super(current_criteria, stop_criteria, o){}

void differential_evolution_cooperative_coevolutive::minimize(optimization_problem &problem, std::vector<scalar> &x0) {
    setting_method(problem.get_dimension());
    allocate_initial_population();
    generate_evaluate_init_population(problem);
    const long max_evaluation = this->stop_criteria.evaluations;
    bool is_known_problem_structure = problem.is_known_problem_structure();
    if(m_debug >= debug_level::Low){
        std::cout << "Solver Initialization ..." << std::endl;
        std::cout << "Iteration: " << current_criteria.iterations
                  << " - Evaluations: " << current_criteria.evaluations
                  << " - Fx Best: " << std::setprecision(20) << fx_best_solution << std::endl;
    }
    if(!is_known_problem_structure){
        std::cerr << "Problem Structure is not Available." << std::endl;
        return;
    }
    size_t index_sub_problem = 0;
    status status_ = check_convergence(stop_criteria, current_criteria);
    while(status_ == status::Continue){
        size_t max_eval_tmp = (this->current_criteria.evaluations + de_cycle <= max_evaluation ? this->current_criteria.evaluations + de_cycle : max_evaluation);
        this->stop_criteria.evaluations = max_eval_tmp;
        scalar gain = fx_best_solution;
        evolution(problem, index_sub_problem);
        gain = gain - fx_best_solution;
        this->stop_criteria.evaluations = max_evaluation;
        index_sub_problem = (index_sub_problem+1) % problem.get_problem_structure().size();
        if(m_debug >= debug_level::Low){
            std::cout << "Iteration: " << current_criteria.iterations
                      << " - Evaluations: " << current_criteria.evaluations
                      << " - Index Subproblem: " << index_sub_problem
                      << " - Fx: " << fx_best_solution
                      << " - Gain: " << gain  << std::endl;
        }
        status_ = check_convergence(stop_criteria, current_criteria);
    }
    std::cout << std::endl << std::endl << "Solver Status: " << std::endl << get_status_string(status_) << std::endl;
    std::cout << "Fx Best Solution: " << fx_best_solution << std::endl << std::endl;
}

void differential_evolution_cooperative_coevolutive::setting_method(size_t d){
    de_cr = this->solver_options.get_de_cr();
    de_size_pop = this->solver_options.get_de_size_pop();
    de_cycle = this->solver_options.get_de_cycle();
    dimension = d;
    best_solution = std::vector<scalar>(dimension, 1.0);
    fx_best_solution = max_limits();
}

void differential_evolution_cooperative_coevolutive::update_best_solution(std::vector<scalar> &x, scalar fx){
    if(fx < fx_best_solution){
        this->m_status = check_convergence(this->stop_criteria, this->current_criteria);
        if(this->m_status == status::Continue){
            best_solution = x;
            fx_best_solution = fx;
            this->m_stats.push(fx, this->current_criteria.evaluations);
        }
    }
}

void differential_evolution_cooperative_coevolutive::allocate_initial_population(){
    pop.reserve(de_size_pop);
    pop_aux.reserve(de_size_pop);
    for(size_t i = 0; i < de_size_pop; i++){
        std::vector<scalar> x(dimension, 0.0);
        pop.push_back(x);
        pop_aux.push_back(x);
    }
    fx_pop = std::vector<scalar>(de_size_pop, 1.0);
    fx_pop_aux = std::vector<scalar>(de_size_pop, 1.0);
}

void differential_evolution_cooperative_coevolutive::generate_evaluate_init_population(optimization_problem &problem){
    for(size_t i = 0; i < de_size_pop; i++){
        for (size_t j = 0; j < dimension; j++) {
            std::uniform_real_distribution<scalar> dist(problem.get_lower_bound()[j], problem.get_upper_bound()[j]);
                pop[i][j] = dist(default_generator());
                pop_aux[i][j] = pop[i][j];
        }
        scalar fx = problem.value(pop[i]);
        ++this->current_criteria.evaluations;
        fx_pop[i] = fx;
        fx_pop_aux[i] = fx;
        update_best_solution(pop[i], fx);
    }
}

void differential_evolution_cooperative_coevolutive::generate_random_index(std::vector<size_t> &v, size_t n, size_t min, size_t max){
    std::uniform_int_distribution<int> dist_pop(min, max);
    for(size_t i = 1; i < n; i++){
        bool diff_index;
        do{
            diff_index = true;
            v[i] = dist_pop(default_generator());
            if(v[0] == v[i]){
                diff_index = false;
            }
            else{
                for(size_t j = 1; j < i; j++){
                    if(v[j] == v[i]) {
                        diff_index = false;
                        j += i;
                    }
                }
            }
        }while(!diff_index);
    }
}

scalar differential_evolution_cooperative_coevolutive::get_bounds(scalar x, scalar min_bound, scalar max_bound){
    if(x > max_bound){
        return max_bound;
    }else if(x < min_bound){
        return min_bound;
    } else {
        return x;
    }
}

void differential_evolution_cooperative_coevolutive::differential_mutation_operator(
    optimization_problem &problem, size_t i_ind, size_t i_x, std::vector<size_t> &index){
    std::uniform_real_distribution<scalar> dist(0.5, 1.0);
    scalar de_f = dist(default_generator());
    pop_aux[i_ind][i_x] = pop[index[1]][i_x] + de_f * (pop[index[2]][i_x] - pop[index[3]][i_x]);
    pop_aux[i_ind][i_x] = get_bounds(pop_aux[i_ind][i_x], problem.get_lower_bound()[i_x], problem.get_upper_bound()[i_x]);
}

void differential_evolution_cooperative_coevolutive::evolution(optimization_problem &problem, size_t index_sub_problem){
    std::set<size_t> sub_problem = problem.get_problem_structure()[index_sub_problem];
    std::uniform_int_distribution<int> dist_dim(0, dimension-1);
    std::uniform_real_distribution<scalar> dist_cr(0.0, 1.0);
    const size_t n_solutions = 4;
    std::vector<size_t> index(n_solutions);
    if(this->m_debug >= debug_level::High) {
        std::cout << "Current Iteration: " << this->current_criteria.iterations
                  << " - Evaluations: " << this->current_criteria.evaluations
                  << " - Fx: " << fx_best_solution << std::endl;
    }
    this->m_status = check_convergence(this->stop_criteria, this->current_criteria);
    while(this->m_status == status::Continue){
        for(size_t i = 0; i < de_size_pop; i++){
            index[0] = i;
            generate_random_index(index, n_solutions, 0, de_size_pop-1);
            size_t r = dist_dim(default_generator());
            pop_aux[i] = pop[i];
            for(unsigned long j : sub_problem){
                if(j == r || dist_cr(default_generator()) <= de_cr){
                    differential_mutation_operator(problem, i, j, index);
                }
            }
            scalar fx = problem.value(pop_aux[i]);
            ++this->current_criteria.evaluations;
            fx_pop_aux[i] = fx;
            update_best_solution(pop_aux[i], fx);
        }
        for(size_t i = 0; i < de_size_pop; i++){
            if(fx_pop_aux[i] < fx_pop[i]){
                pop[i] = pop_aux[i];
                fx_pop[i] = fx_pop_aux[i];
            }
        }
        ++this->current_criteria.iterations;
        this->current_criteria.fx_best = fx_best_solution;
        this->m_status = check_convergence(this->stop_criteria, this->current_criteria);
        if(this->m_debug >= debug_level::High) {
            std::cout << "Current Iteration: " << this->current_criteria.iterations
                      << " - Evaluations: " << this->current_criteria.evaluations
                      << " - Fx: " << fx_best_solution << std::endl;
        }
    }
}

std::vector<scalar> differential_evolution_cooperative_coevolutive::get_best_solution() const{
    return this->best_solution;
}