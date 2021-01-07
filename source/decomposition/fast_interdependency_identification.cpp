#include "fast_interdependency_identification.h"
#include "common.h"
#include "optimization_problem.h"

using namespace decompose;
using namespace std;

void fast_interdependency_identification::diff(optimization_problem &problem_, vector<scalar> &x, scalar delta, const set<size_t>& indices, vector<scalar> &v, criteria &criteria_){
    scalar value_1 = problem_.value(x);
    criteria_.evaluations++;
    for(unsigned long i : indices){
        vector<scalar> xd = x;
        xd[i] += delta;
        xd[i] = (xd[i] > problem_.get_upper_bound()[i] ? problem_.get_upper_bound()[i] : xd[i]);
        scalar value_2 = problem_.value(xd);
        criteria_.evaluations++;
        v[i] = value_2 - value_1;
    }
}

void fast_interdependency_identification::decompose(optimization_problem &problem_, options &options_, criteria &criteria_) {
    criteria_.reset();
    vector<set<size_t>> sub_problems;
    const size_t dim = problem_.get_dimension();
    const scalar epsilon_1 = options_.get_fii_epsilon_1();
    const scalar epsilon_2 = options_.get_fii_epsilon_2();
    const scalar sigma = options_.get_fii_sigma();
    const scalar delta = options_.get_fii_delta();
    vector<scalar> x(dim);
    vector<scalar> dv(dim, 0.0);
    set<size_t> indices;
    set<size_t> non_seps;
    for(size_t i = 0; i < dim; i++){
        scalar middle_x = problem_.get_lower_bound()[i] + (problem_.get_upper_bound()[i] - problem_.get_lower_bound()[i]) / 2.0;
        x[i] = middle_x;
        indices.insert(i);
    }
    diff(problem_, x, delta, indices, dv, criteria_);
    indices.clear();
    for(size_t i = 0; i < dim; i++){
        vector<scalar> x_line(dim);
        vector<scalar> pv(dim, 0.0);
        for(size_t j = 0; j < dim; j++){
            x_line[j] = x[i] + sigma;
            x_line[j] = (x_line[j] > problem_.get_upper_bound()[j] ? problem_.get_upper_bound()[j] : x_line[j]);
        }
        x_line[i] = x[i];
        indices.insert(i);
        diff(problem_, x_line, delta, indices, pv, criteria_);
        indices.clear();
        if(abs(pv[i] - dv[i]) <= epsilon_1){
            set<size_t> sub_problem_tmp;
            sub_problem_tmp.insert(i);
            sub_problems.push_back(sub_problem_tmp);
        }
        else{
            non_seps.insert(i);
        }
    }
    set<size_t> group;
    while(!non_seps.empty()){
        set<size_t> p_dim;
        size_t k = *non_seps.begin();
        p_dim.insert(k);
        group.insert(k);
        non_seps.erase(k);
        while(!p_dim.empty() && !non_seps.empty()){
            vector<scalar> x_line = x;
            size_t i_tmp = *p_dim.begin();
            x_line[i_tmp] = x_line[i_tmp] + sigma;
            vector<scalar> pv(dim, 0.0);
            diff(problem_, x_line, delta, non_seps, pv, criteria_);
            p_dim.clear();
            for(unsigned long non_sep : non_seps){
                if(abs(pv[non_sep] - dv[non_sep]) > epsilon_2){
                    group.insert(non_sep);
                    p_dim.insert(non_sep);
                }
            }
            for(unsigned long it : group){
                non_seps.erase(it);
            }
        }
        sub_problems.push_back(group);
        group.clear();
    }
    problem_.set_problem_structure(sub_problems);
}