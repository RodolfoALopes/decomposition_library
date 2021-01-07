#include "differential_grouping.h"
#include "common.h"
#include "optimization_problem.h"

using namespace decompose;
using namespace std;

void differential_grouping::decompose(optimization_problem &problem_, options &options_, criteria &criteria_) {
    criteria_.reset();
    vector<set<size_t>> sub_problems;
    const size_t dim = problem_.get_dimension();
    const scalar epsilon = options_.get_dg_epsilon();
    set<size_t> dims;
    for(size_t i = 0; i < dim; i++){
        dims.insert(i);
    }
    while (!dims.empty()){
        set<size_t> group;
        size_t i = *dims.begin();
        group.insert(i);
        for(unsigned long j : dims){
            if(j != i){
                vector<scalar> p1 = problem_.get_lower_bound();
                vector<scalar> p2 = problem_.get_lower_bound();
                p2[i] = problem_.get_upper_bound()[i];
                scalar delta_1 = problem_.value(p1) - problem_.value(p2);
                criteria_.evaluations += 2;
                scalar middle_x = problem_.get_lower_bound()[j] + (problem_.get_upper_bound()[j] - problem_.get_lower_bound()[j]) / 2.0;
                p1[j] = middle_x;
                p2[j] = middle_x;
                scalar delta_2 = problem_.value(p1) - problem_.value(p2);
                criteria_.evaluations += 2;
                if(abs(delta_1 - delta_2) > epsilon){
                    group.insert(j);
                }
            }
        }
        for(unsigned long it : group){
            dims.erase(it);
        }
        sub_problems.push_back(group);
    }
    problem_.set_problem_structure(sub_problems);
}