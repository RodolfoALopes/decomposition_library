---
layout: default
title: Executing an Decomposition Method:
nav_order: 2
has_children: false
parent: Examples
has_toc: false
---
# Executing an Decomposition Method:

The code below presents an example of the Differential Grouping for the optimization problem previously presented:

```cpp
#include <decomposition/differential_grouping.h>
#include <decomposition/optimization_problem.h>
#include <sstream>

using namespace decompose;
using namespace std;


int main(){
    const size_t dimension = 7;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;

    problem_example f(dimension, vector<scalar>(dimension, lower_bound), vector<scalar>(dimension, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    differential_grouping method;
    method.decompose(f, options_, criteria_);

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

    ostringstream s;
    s << "[";
    for(size_t i = 0; i < sub_problems.size(); i++){
        s << "[";
        auto it = sub_problems[i].begin();
        bool print = true;
        while(print && !sub_problems.empty()){
            s << (*it);
            it++;
            if(it != sub_problems[i].end()){
                s << ", ";
            }else{
                print = false;
            }
        }
        s << "]";
    }
    s << "]";

    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    cout << " - Problem Structure Found: " << s.str() << endl;
    cout << endl << endl;

    return 0;
}
```




<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
