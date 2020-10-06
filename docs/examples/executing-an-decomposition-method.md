---
layout: default
title: Executing an Decomposition Method:
nav_order: 2
has_children: false
parent: Examples
grand_parent: 
has_toc: false
---
# Executing an Decomposition Method:

The code below presents an example of the Differential Grouping for the optimization problem previously presented:

```cpp
#include "problem.h"
#include "differential_grouping_method.h"

using namespace decompose;

int main(){
    const size_t dim = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;
    string structure;

    problem_example f(dim, vector<scalar>(dim, lower_bound), vector<scalar>(dim, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    differential_grouping_method method;
    method.analyze(f, options_, criteria_);

    cout << "Differential Grouping Method Example - Default Parameter" << endl;

    sub_problems = f.get_problem_structure();
    cout << " - Number of Function Evaluations: " << criteria_.evaluations << endl;
    number_seps = 0;
    number_non_seps = 0;
    for(auto & sub_problem : sub_problems){
        if(sub_problem.size() > 1){
            number_non_seps += sub_problem.size();
        }
        else{
            number_seps++;
        }
    }
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    structure = f.print_sub_problem_structure();
    cout << " - Problem Structure Found: " << structure << endl;
    cout << endl << endl;

    return 0.0;
}
```




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
