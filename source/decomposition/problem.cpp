#include "problem.h"

using namespace decompose;
using namespace std;

problem::problem(size_t dim_, vector<scalar> lower_bound_, vector<scalar> upper_bound_) {
    dim = dim_;
    lower_bound = std::move(lower_bound_);
    upper_bound = std::move(upper_bound_);
    problem_structure_is_known = false;
}


bool problem::is_known_problem_structure() const{
    return problem_structure_is_known;
}

void problem::set_problem_structure(vector<set<size_t>> sub_problems_){
    sub_problems.clear();
    sub_problems = sub_problems_;
    problem_structure_is_known = true;
}

vector<set<size_t>> problem::get_problem_structure(){
    return sub_problems;
}

size_t problem::get_dim() const{
    return dim;
}

vector<scalar> problem::get_lower_bound(){
    return lower_bound;
}

vector<scalar> problem::get_upper_bound(){
    return upper_bound;
}

string problem::print_sub_problem_structure(){
    string structure = "[";
    for(size_t i = 0; i < sub_problems.size(); i++){
        structure += "[";
        auto it = sub_problems[i].begin();
        bool print = true;
        while(print && !sub_problems.empty()){
            structure += to_string(*it);
            it++;
            if(it != sub_problems[i].end()){
                structure += ", ";
            }
            else{
                print = false;
            }
        }
        structure += "]";
    }
    structure += "]";
    return structure;
}