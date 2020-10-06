#include "problem_examples/problem_example_1.h"
#include "problem_examples/problem_example_2.h"
#include "problem_examples/problem_example_3.h"
#include "problem_examples/problem_example_4.h"
#include <catch2/catch.hpp>
#include <decomposition/recursive_differential_grouping_2_method.h>
#include <iostream>

using namespace decompose;
using namespace std;

TEST_CASE("Recursive Differential Grouping 2 - Separable Problem - Unit Test") {
    const string problem_structure = "[[0][1][2][3][4][5][6][7][8][9]]";
    const size_t dim = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dim; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;
    string structure;

    problem_example_1 f(dim, vector<scalar>(dim, lower_bound), vector<scalar>(dim, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    recursive_differential_grouping_2_method method;
    method.analyze(f, options_, criteria_);


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

    string structure_method = f.print_sub_problem_structure();

    bool equal_structure = false;
    cout << "Problem Example 1 - Full separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    structure = f.print_sub_problem_structure();
    cout << " - Problem Structure Found:    " << structure << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 0 && number_seps == 10){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}


TEST_CASE("Recursive Differential Grouping 2 - Partially Separable Problem - Unit Test") {
    const string problem_structure = "[[0, 1, 2, 3, 4][5, 6, 7, 8, 9]]";
    const size_t dim = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dim; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;
    string structure;

    problem_example_2 f(dim, vector<scalar>(dim, lower_bound), vector<scalar>(dim, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    recursive_differential_grouping_2_method method;
    method.analyze(f, options_, criteria_);


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

    string structure_method = f.print_sub_problem_structure();

    bool equal_structure = false;
    cout << "Problem Example 2 - Partially separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    structure = f.print_sub_problem_structure();
    cout << " - Problem Structure Found:    " << structure << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 10 && number_seps == 0){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}


TEST_CASE("Recursive Differential Grouping 2 - NonSeparable Problem Example 1 - Unit Test") {
    const string problem_structure = "[[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]]";
    const size_t dim = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dim; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;
    string structure;

    problem_example_3 f(dim, vector<scalar>(dim, lower_bound), vector<scalar>(dim, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    recursive_differential_grouping_2_method method;
    method.analyze(f, options_, criteria_);


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

    string structure_method = f.print_sub_problem_structure();

    bool equal_structure = false;
    cout << "Problem Example 3 - Non-separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    structure = f.print_sub_problem_structure();
    cout << " - Problem Structure Found:    " << structure << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 10 && number_seps == 0){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}


TEST_CASE("Recursive Differential Grouping 2 - NonSeparable Problem Example 2 - Unit Test") {
    const string problem_structure = "[[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]]";
    const size_t dim = 10;
    const scalar lower_bound = -5.0;
    const scalar upper_bound = 10.0;

    vector<set<size_t>> sub_problems_original;
    for(size_t i = 0; i < dim; i++){
        set<size_t> x_tmp;
        x_tmp.insert(i);
        sub_problems_original.push_back(x_tmp);
    }

    vector<set<size_t>> sub_problems;
    size_t number_seps, number_non_seps;
    string structure;

    problem_example_4 f(dim, vector<scalar>(dim, lower_bound), vector<scalar>(dim, upper_bound));

    criteria criteria_;
    options options_ = options::defaults();
    recursive_differential_grouping_2_method method;
    method.analyze(f, options_, criteria_);


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

    string structure_method = f.print_sub_problem_structure();

    bool equal_structure = false;
    cout << "Problem Example 4 - Non-separable problem" << endl;
    cout << " - Number of sub-problems found: " << sub_problems.size() << endl;
    cout << " - Number of separable decision variables: " << number_seps  << endl;
    cout << " - Number of non-separable decision variables: " << number_non_seps  << endl;
    structure = f.print_sub_problem_structure();
    cout << " - Problem Structure Found:    " << structure << endl;
    cout << " - Problem Structure Original: " << problem_structure << endl;
    cout << endl << endl;
    if(structure_method == problem_structure && number_non_seps == 10 && number_seps == 0){
        equal_structure = true;
    }

    REQUIRE(equal_structure);
}