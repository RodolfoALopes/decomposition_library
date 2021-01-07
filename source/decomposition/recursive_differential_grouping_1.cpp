#include "recursive_differential_grouping_1.h"

using namespace decompose;
using namespace std;

recursive_differential_grouping_1::recursive_differential_grouping_1() {
    y1 = 0;
    dim = 0;
    epsilon = 0;
}

void recursive_differential_grouping_1::generate_random_solution(
    optimization_problem &problem_, vector<scalar> &x) const {
    for (size_t i = 0; i < dim; i++) {
        uniform_real_distribution<scalar> dist(problem_.get_lower_bound()[i], problem_.get_upper_bound()[i]);
        x[i] = dist(default_generator());
    }
}

pair<set<size_t>, set<size_t>> recursive_differential_grouping_1::interact(optimization_problem &problem_, set<size_t> sub_1, set<size_t> sub_2, set<size_t> x_remain){
    vector<scalar> p2 = problem_.get_lower_bound();
    for(unsigned long it : sub_1){
        p2[it] = problem_.get_upper_bound()[it];
    }
    scalar y2 = problem_.value(p2);
    current_criteria.evaluations++;
    scalar delta_1 = y1 - y2;
    vector<scalar> p3 = problem_.get_lower_bound();
    vector<scalar> p4 = p2;
    for(unsigned long it : sub_2){
        scalar middle_var = (problem_.get_upper_bound()[it] + problem_.get_lower_bound()[it]) / 2.0;
        p3[it] = middle_var;
        p4[it] = middle_var;
    }
    scalar y3 = problem_.value(p3);
    scalar y4 = problem_.value(p4);
    current_criteria.evaluations += 2;
    scalar delta_2 = y3 - y4;
    if(abs(delta_1 - delta_2) > epsilon){
        if(sub_2.size() == 1){
            sub_1.insert(*sub_2.begin());
            sub_2.clear();
        }else{
            auto k = (size_t)floor((scalar)sub_2.size() / 2);
            size_t k_max = sub_2.size();
            set<size_t> sub_2_1, sub_2_2;
            size_t cont = 1;
            auto it = sub_2.begin();
            while(cont <= k){
                sub_2_1.insert(*it);
                cont++;
                it++;
            }
            while(cont <= k_max){
                sub_2_2.insert(*it);
                cont++;
                it++;
            }
            set<size_t> sub_1_1, sub_1_2;
            pair<set<size_t>, set<size_t>> result_1 = interact(problem_, sub_1, sub_2_1, x_remain);
            sub_1_1 = result_1.first;
            x_remain = result_1.second;
            pair<set<size_t>, set<size_t>> result_2 = interact(problem_, sub_1, sub_2_2, x_remain);
            sub_1_2 = result_2.first;
            x_remain = result_2.second;
            sub_1.clear();
            for(unsigned long s : sub_1_1){
                sub_1.insert(s);
            }
            for(unsigned long s : sub_1_2){
                sub_1.insert(s);
            }
        }
    }
    else{
        for(unsigned long it : sub_2){
            x_remain.insert(it);
        }
    }
    pair<set<size_t>, set<size_t>> result(sub_1, x_remain);
    return result;
}

void recursive_differential_grouping_1::decompose(optimization_problem &problem_, options &options_, criteria &criteria_) {
    current_criteria.reset();
    vector<set<size_t>> sub_problems;
    dim = problem_.get_dimension();
    size_t k = options_.get_rdg_1_k();
    const scalar alpha = options_.get_rdg_1_alpha();
    scalar fx_min = max_limits();
    vector<scalar> x_random(dim, 0.0);
    for(size_t i = 0; i < k; i++){
        generate_random_solution(problem_, x_random);
        scalar fx = problem_.value(x_random);
        current_criteria.evaluations++;
        if(abs(fx) < abs(fx_min)){
            fx_min = abs(fx);
        }
    }
    epsilon = alpha * fx_min;
    y1 = problem_.value(problem_.get_lower_bound());
    current_criteria.evaluations++;
    set<size_t> sub_1, sub_2, x_remain;
    sub_1.insert(0);
    x_remain.insert(0);
    for(size_t i = 1; i < dim; i++){
        sub_2.insert(i);
        x_remain.insert(i);
    }
    while(!x_remain.empty()){
        x_remain.clear();
        pair<set<size_t>, set<size_t>> result = interact(problem_, sub_1, sub_2, x_remain);
        set<size_t> sub_1_a = result.first;
        x_remain = result.second;
        if(sub_1_a == sub_1){
            sub_problems.push_back(sub_1);
            if(x_remain.size() > 1){
                sub_1.clear();
                size_t key = *x_remain.begin();
                sub_1.insert(key);
                x_remain.erase(key);
                sub_2.clear();
                for(unsigned long it : x_remain){
                    sub_2.insert(it);
                }
            }
            else{
                sub_problems.push_back(x_remain);
                break;
            }
        }
        else{
            sub_1 = sub_1_a;
            sub_2 = x_remain;
            if(x_remain.empty()){
                sub_problems.push_back(sub_1);
                break;
            }
        }
    }
    criteria_ = current_criteria;
    problem_.set_problem_structure(sub_problems);
}