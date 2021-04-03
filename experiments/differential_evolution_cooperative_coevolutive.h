#ifndef DECOMPOSITION_LIBRARY_DIFFERENTIAL_EVOLUTION_COOPERATIVE_COEVOLUTIVE_H
#define DECOMPOSITION_LIBRARY_DIFFERENTIAL_EVOLUTION_COOPERATIVE_COEVOLUTIVE_H

#include <decomposition/solver.h>
#include <decomposition/optimization_problem.h>
#include <vector>

using namespace decompose;

class differential_evolution_cooperative_coevolutive : public solver {
    public:
        using super = solver;

        differential_evolution_cooperative_coevolutive(criteria &current_criteria, criteria &stop_criteria, options &o);

    protected:
        std::vector<std::vector<scalar>> pop;
        std::vector<std::vector<scalar>> pop_aux;
        std::vector<scalar> best_solution;
        scalar fx_best_solution{};
        std::vector<scalar> fx_pop;
        std::vector<scalar> fx_pop_aux;
        scalar de_cr{};
        size_t de_size_pop{};
        size_t de_cycle{};
        size_t dimension{};

    public:
        differential_evolution_cooperative_coevolutive() = default;
        void minimize(optimization_problem &problem_, std::vector<scalar> &x0) override;
        std::vector<scalar> get_best_solution() const;
        void setting_method(size_t d);
        void update_best_solution(std::vector<scalar> &x, scalar fx);
        void allocate_initial_population();
        void generate_evaluate_init_population(optimization_problem &problem);
        static void generate_random_index(std::vector<size_t> &v, size_t n, size_t min, size_t max);
        static scalar get_bounds(scalar x, scalar min_bound, scalar max_bound);
        void differential_mutation_operator(optimization_problem &problem, size_t i_ind, size_t i_x, std::vector<size_t> &index);
        void evolution(optimization_problem &problem, size_t index_sub_problem);

};

#endif // DECOMPOSITION_LIBRARY_DIFFERENTIAL_EVOLUTION_COOPERATIVE_COEVOLUTIVE_H
