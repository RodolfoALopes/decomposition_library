#include "optimization_problem.h"

#include <utility>

using namespace decompose;
using namespace std;

optimization_problem::optimization_problem(size_t dimension_, vector<scalar> lower_bound_, vector<scalar> upper_bound_) {
    dimension = dimension_;
    lower_bound = std::move(lower_bound_);
    upper_bound = std::move(upper_bound_);
    problem_structure_is_known = false;
}

bool optimization_problem::is_known_problem_structure() const{
    return problem_structure_is_known;
}

void optimization_problem::set_problem_structure(vector<set<size_t>> sub_problems_){
    sub_problems.clear();
    sub_problems = std::move(sub_problems_);
    problem_structure_is_known = true;
}

vector<set<size_t>> optimization_problem::get_problem_structure() const{
    return sub_problems;
}

size_t optimization_problem::get_dimension() const{
    return dimension;
}

vector<scalar> optimization_problem::get_lower_bound() const{
    return lower_bound;
}

vector<scalar> optimization_problem::get_upper_bound() const{
    return upper_bound;
}

//string optimization_problem::print_sub_problem_structure(){
//    string structure = "[";
//    for(size_t i = 0; i < sub_problems.size(); i++){
//        structure += "[";
//        auto it = sub_problems[i].begin();
//        bool print = true;
//        while(print && !sub_problems.empty()){
//            structure += to_string(*it);
//            it++;
//            if(it != sub_problems[i].end()){
//                structure += ", ";
//            }
//            else{
//                print = false;
//            }
//        }
//        structure += "]";
//    }
//    structure += "]";
//    return structure;
//}
