#include "global_differential_grouping.h"

using namespace decompose;
using namespace std;

void global_differential_grouping::generate_random_solution(
    optimization_problem &problem_, vector<scalar> &x, const size_t dim){
    for (size_t i = 0; i < dim; i++) {
        uniform_real_distribution<scalar> dist(problem_.get_lower_bound()[i], problem_.get_upper_bound()[i]);
        x[i] = dist(default_generator());
    }
}

void global_differential_grouping::decompose(optimization_problem &problem_, options &options_, criteria &criteria_) {
    criteria_.reset();
    vector<set<size_t>> sub_problems;
    const size_t dim = problem_.get_dimension();
    size_t k = options_.get_gdg_k();
    const scalar alpha = options_.get_gdg_alpha();
    scalar fx_min = max_limits();

    vector<vector<bool>> matrix_interaction(dim, vector<bool>(dim, false));
    vector<scalar> p_1(dim, 0.0);
    for(size_t i = 0; i < k; i++){
        generate_random_solution(problem_, p_1, dim);
        scalar fx = problem_.value(p_1);
        criteria_.evaluations++;
        if(abs(fx) < abs(fx_min)){
            fx_min = abs(fx);
        }
    }
    const scalar epsilon = alpha * fx_min;
    p_1 = problem_.get_lower_bound();
    scalar f_1 = problem_.value(p_1);
    criteria_.evaluations++;
    vector<scalar> f_2(dim, 0.0);
    vector<scalar> f_3(dim, 0.0);
    vector<vector<scalar>> f_4(dim, vector<scalar>(dim, 0.0));
    vector<scalar> p_2, p_3, p_4;
    for(size_t i = 0; i < dim; i++){
        scalar middle_x = problem_.get_lower_bound()[i] + (problem_.get_upper_bound()[i] - problem_.get_lower_bound()[i]) / 2.0;
        p_2 = p_1;
        p_3 = p_1;
        p_2[i] = problem_.get_upper_bound()[i];
        p_3[i] = middle_x;
        f_2[i] = problem_.value(p_2);
        criteria_.evaluations++;
        f_3[i] = problem_.value(p_3);
        criteria_.evaluations++;
    }
    for(size_t i = 0; i < dim-1; i++){
        for(size_t j = i+1; j < dim; j++){
            scalar middle_x = problem_.get_lower_bound()[j] + (problem_.get_upper_bound()[j] - problem_.get_lower_bound()[j]) / 2.0;
            p_4 = p_1;
            p_4[i] = problem_.get_upper_bound()[i];
            p_4[j] = middle_x;
            f_4[i][j] = problem_.value(p_4);
            f_4[j][i] = f_4[i][j];
            criteria_.evaluations++;
        }
    }
    for(size_t i = 0; i < dim-1; i++){
        for(size_t j = i+1; j < dim; j++){
            scalar delta_1 = f_1 - f_2[i];
            scalar delta_2 = f_3[j] - f_4[i][j];
            scalar lambda = abs(delta_1 - delta_2);
            if(lambda > epsilon){
                matrix_interaction[i][j] = true;
                matrix_interaction[j][i] = true;
            }
        }
    }
    set<size_t> dims;
    for(size_t i = 0; i < dim; i++){
        dims.insert(i);
    }
    for(size_t i = 0; i < dim; i++){
        set<size_t> sub_problem_tmp;
        if(dims.find(i) != dims.end()){
            sub_problem_tmp.insert(i);
            dims.erase(i);
            for(auto it = sub_problem_tmp.begin(); it != sub_problem_tmp.end(); it++){
                for(size_t j = 1+(*it); j < dim; j++){
                    if(matrix_interaction[*it][j] && dims.find(j) != dims.end()){
                        matrix_interaction[*it][j] = false;
                        matrix_interaction[*it][i] = false;
                        sub_problem_tmp.insert(j);
                        dims.erase(j);
                    }
                }
            }
        }
        if(!sub_problem_tmp.empty()){
            sub_problems.push_back(sub_problem_tmp);
        }
    }
    problem_.set_problem_structure(sub_problems);
}