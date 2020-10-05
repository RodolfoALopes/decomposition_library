#include <decomposition/differential_grouping_method.h>
#include <decomposition/problem.h>

using namespace decompose;
using namespace std;

class problem_example : public problem {
    public:
        using super = problem;

        explicit problem_example(size_t dim, vector<scalar> lower_bound,
                                 vector<scalar> upper_bound)
            : super(dim, std::move(lower_bound), std::move(upper_bound)) {}

        scalar value(const vector<scalar> &x) override {
            scalar sum = 0.0;
            for(size_t i = 0; i < dim; i++){
                if(i % 3 == 0){
                    sum += pow(x[i], 2) * pow(x[(i+1) % dim], 2);
                } else{
                    sum += pow(x[i], 2);
                }
            }
            return sum;
        }
};


int main(){
    const size_t dim = 7;
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

    return 0;
}