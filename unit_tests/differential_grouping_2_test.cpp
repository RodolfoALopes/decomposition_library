#include "problem_examples/problem_example_1.h"
#include "problem_examples/problem_example_2.h"
#include "problem_examples/problem_example_3.h"
#include "problem_examples/problem_example_4.h"
#include <catch2/catch.hpp>
#include <decomposition/differential_grouping_2.h>
#include <iostream>

using namespace decompose;
using namespace std;

TEST_CASE("Differential Grouping - Separable Problem - Unit Test") {
    const string problem_structure = "[[0][1][2][3][4][5][6][7][8][9]]";
    const size_t dimension = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dimension; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;

    problem_example_1 f(dimension, vector<scalar>(dimension, lower_bound), vector<scalar>(dimension, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    differential_grouping_2 method;
    method.decompose(f, options_, criteria_);

    sub_problems = f.get_problem_structure();
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

    string structure_method;
    structure_method += "[";
    for(size_t i = 0; i < sub_problems.size(); i++){
        structure_method += "[";
        auto it = sub_problems[i].begin();
        bool print = true;
        while(print && !sub_problems.empty()){
            structure_method += (std::to_string(*it));
            it++;
            if(it != sub_problems[i].end()){
                structure_method += ", ";
            }else{
                print = false;
            }
        }
        structure_method += "]";
    }
    structure_method += "]";

    bool equal_structure = false;
    cout << "Problem Example 1 - Full Separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    cout << " - Problem Structure Found:    " << structure_method << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 0 && number_seps == 10){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}


TEST_CASE("Differential Grouping - Partially Separable Problem - Unit Test") {
    const string problem_structure = "[[0, 1, 2, 3, 4][5, 6, 7, 8, 9]]";
    const size_t dimension = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dimension; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;

    problem_example_2 f(dimension, vector<scalar>(dimension, lower_bound), vector<scalar>(dimension, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    differential_grouping_2 method;
    method.decompose(f, options_, criteria_);


    sub_problems = f.get_problem_structure();
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

    string structure_method;
    structure_method += "[";
    for(size_t i = 0; i < sub_problems.size(); i++){
        structure_method += "[";
        auto it = sub_problems[i].begin();
        bool print = true;
        while(print && !sub_problems.empty()){
            structure_method += (std::to_string(*it));
            it++;
            if(it != sub_problems[i].end()){
                structure_method += ", ";
            }else{
                print = false;
            }
        }
        structure_method += "]";
    }
    structure_method += "]";

    bool equal_structure = false;
    cout << "Problem Example 2 - Partially Separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    cout << " - Problem Structure Found:    " << structure_method << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 10 && number_seps == 0){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}


TEST_CASE("Differential Grouping - NonSeparable Problem Example 1 - Unit Test") {
    const string problem_structure = "[[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]]";
    const size_t dimension = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dimension; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;

    problem_example_3 f(dimension, vector<scalar>(dimension, lower_bound), vector<scalar>(dimension, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    differential_grouping_2 method;
    method.decompose(f, options_, criteria_);

    sub_problems = f.get_problem_structure();
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

    string structure_method;
    structure_method += "[";
    for(size_t i = 0; i < sub_problems.size(); i++){
        structure_method += "[";
        auto it = sub_problems[i].begin();
        bool print = true;
        while(print && !sub_problems.empty()){
            structure_method += (std::to_string(*it));
            it++;
            if(it != sub_problems[i].end()){
                structure_method += ", ";
            }else{
                print = false;
            }
        }
        structure_method += "]";
    }
    structure_method += "]";

    bool equal_structure = false;
    cout << "Problem Example 3 - Non-separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    cout << " - Problem Structure Found:    " << structure_method << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 10 && number_seps == 0){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}


TEST_CASE("Differential Grouping - NonSeparable Problem Example 2 - Unit Test") {
    const string problem_structure = "[[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]]";
    const size_t dimension = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dimension; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;

    problem_example_4 f(dimension, vector<scalar>(dimension, lower_bound), vector<scalar>(dimension, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    differential_grouping_2 method;
    method.decompose(f, options_, criteria_);

    sub_problems = f.get_problem_structure();
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

    string structure_method;
    structure_method += "[";
    for(size_t i = 0; i < sub_problems.size(); i++){
        structure_method += "[";
        auto it = sub_problems[i].begin();
        bool print = true;
        while(print && !sub_problems.empty()){
            structure_method += (std::to_string(*it));
            it++;
            if(it != sub_problems[i].end()){
                structure_method += ", ";
            }else{
                print = false;
            }
        }
        structure_method += "]";
    }
    structure_method += "]";

    bool equal_structure = false;
    cout << "Problem Example 4 - Non-separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    cout << " - Problem Structure Found:    " << structure_method << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 10 && number_seps == 0){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}