#ifndef DECOMPOSITION_LIBRARY_PROBLEM_H
#define DECOMPOSITION_LIBRARY_PROBLEM_H

#include "common.h"
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace decompose {
    class problem {

    protected:
        size_t dim;
        vector<scalar> lower_bound;
        vector<scalar> upper_bound;
        vector<set<size_t>> sub_problems;
        bool problem_structure_is_known;

    public:
        problem(size_t dim_, vector<scalar> lower_bound_, vector<scalar> upper_bound_) {
            dim = dim_;
            lower_bound = std::move(lower_bound_);
            upper_bound = std::move(upper_bound_);
            problem_structure_is_known = false;
        }

        virtual ~problem() = default;

        virtual scalar value(const vector<scalar> &x) = 0;

        bool is_known_problem_structure() const{
            return problem_structure_is_known;
        }

        void set_problem_structure(vector<set<size_t>> sub_problems_){
            sub_problems.clear();
            sub_problems = std::move(sub_problems_);
            problem_structure_is_known = true;
        }

        vector<set<size_t>> get_problem_structure(){
            return sub_problems;
        }

        size_t get_dim() const{
            return dim;
        }

        vector<scalar> get_lower_bound(){
            return lower_bound;
        }

        vector<scalar> get_upper_bound(){
            return upper_bound;
        }

        string print_sub_problem_structure(){
            string structure = "[";
            for(auto & sub_problem : sub_problems){
                structure += "[";
                auto it = sub_problem.begin();
                bool print = true;
                while(print && !sub_problems.empty()){
                    structure += to_string(*it);
                    it++;
                    if(it != sub_problem.end()){
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
    };
}
#endif