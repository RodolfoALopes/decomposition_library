#include "extended_differential_grouping.h"
#include "common.h"
#include "optimization_problem.h"

using namespace decompose;
using namespace std;

void extended_differential_grouping::decompose(optimization_problem &problem_, options &options_, criteria &criteria_) {
    criteria_.reset();
    vector<set<size_t>> sub_problems;
    const size_t dim = problem_.get_dimension();
    const scalar epsilon = options_.get_xdg_epsilon();
    vector<vector<bool>> matrix_interaction(dim, vector<bool>(dim, false));
    vector<scalar> x_1(dim, 0.0);
    vector<scalar> x_2(dim, 0.0);
    for(size_t i = 0; i < dim; i++){
        x_1 = problem_.get_lower_bound();
        x_2 = problem_.get_lower_bound();
        x_2[i] = problem_.get_upper_bound()[i];
        scalar delta_1 = problem_.value(x_1) - problem_.value(x_2);
        criteria_.evaluations += 2;
        for(size_t j = i+1; j < dim; j++){
            if(!matrix_interaction[i][j]){
                vector<scalar> x_line_1 = x_1;
                vector<scalar> x_line_2 = x_2;
                scalar middle_x = problem_.get_lower_bound()[j] + (problem_.get_upper_bound()[j] - problem_.get_lower_bound()[j]) / 2.0;
                x_line_1[j] = middle_x;
                x_line_2[j] = middle_x;
                scalar delta_2 = problem_.value(x_line_1) - problem_.value(x_line_2);
                criteria_.evaluations += 2;
                if(abs(delta_1 - delta_2) > epsilon){
                    matrix_interaction[i][j] = true;
                }
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