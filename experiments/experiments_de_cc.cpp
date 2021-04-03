#include "problems/f1_cec.h"
#include "problems/f2_cec.h"
#include "problems/f3_cec.h"
#include "problems/f4_cec.h"
#include "problems/f5_cec.h"
#include "problems/f6_cec.h"
#include "problems/f7_cec.h"
#include "problems/f8_cec.h"
#include "problems/f9_cec.h"
#include "problems/f10_cec.h"
#include "problems/f11_cec.h"
#include "problems/f12_cec.h"
#include "problems/f13_cec.h"
#include "problems/f14_cec.h"
#include "problems/f15_cec.h"
#include "differential_evolution_cooperative_coevolutive.h"
#include <iostream>
#include <string>
#include <climits>
#include <iomanip>

using namespace decompose;
using namespace std;

class read_files{
    public:
        string data_dir = "decomposition_solutions";

        void read_decomposition_solutions(const size_t id_function, const string &method, optimization_problem &problem, criteria &current_criteria) const{
            string name_file = "F" + to_string(id_function) + "_" + method + ".txt";

            stringstream ss;
            ss << data_dir <<"/" << method << "/" << name_file;
            ifstream file(ss.str());

            cout << "NAME FILE: " << ss.str() << endl;

            std::string tmp;
            // Function Description
            file >> tmp;
            cout << tmp << " ";
            file >> tmp;
            cout << tmp << endl;

            // Method Description
            file >> tmp;
            cout << tmp << " ";
            file >> tmp;
            cout << tmp << endl;

            // Function Evaluation Description
            file >> tmp;
            cout << tmp << " ";
            long fes;
            file >> fes;
            cout << fes << endl;
            current_criteria.evaluations = fes;

            // Subproblems Description
            file >> tmp;
            file >> tmp;

            string sub_problem_tmp;
            bool add;
            std::vector<std::set<size_t>> sub_problems;
            size_t id_sub_problem = -1;
            for(char & iter : tmp){
                if((char) iter == '['){
                    id_sub_problem++;
                    std::set<size_t> set_tmp;
                    add = false;
                    sub_problem_tmp = "";
                    sub_problems.push_back(set_tmp);
                }
                else if ((char) iter == ']' || (char) iter == ',') {
                    add = true;
                }
                else if ((char) iter != ' '){
                    add = false;
                    sub_problem_tmp += iter;
                }
                if(add){
                    scalar value = stoi(sub_problem_tmp);
                    sub_problems[id_sub_problem].insert(value);
                    sub_problem_tmp = "";
                }
            }

            // Setting subproblems
            problem.set_problem_structure(sub_problems);
            file.close();

            // Checking Subproblems
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
                        structure_method += ",";
                    }else{
                        print = false;
                    }
                }
                structure_method += "]";
            }
            structure_method += "]";
            cout << "SUBPROBLEMS SIZE: " << sub_problems.size() << endl;
            if(structure_method.find(tmp) != std::string::npos){
                cout << "CHECKING SUBPROBLEMS: OK" << endl;
            }
            else{
                cerr << "CHECKING SUBPROBLEMS: ERROR" << endl;
                exit(0);
            }
        }
};

void save_results(const string &id_version, size_t id_func, size_t id_rep, vector<scalar> &x, const scalar fx){
    ofstream file_results;
    ofstream file_solutions;
    file_results.open(id_version + ".txt", std::ofstream::app);
    file_results << id_version << "; " << id_func << "; " << id_rep << "; 3e6; " << setprecision(20) << fx << endl;
    file_results.close();
    file_solutions.open(id_version + "_solutions.txt", std::ofstream::app);
    file_solutions << id_version << "; " << "Func: " << id_func << "; Rep: " << id_rep << "; ";
    for(scalar i : x){
        file_solutions << i << "; ";
    }
    file_solutions << endl;
    file_solutions.close();
}

int main() {
    const size_t max_id_function = 15;
    const size_t max_rep = 30;
    string methods[] = {"DG", "DG2", "XDG", "FII", "GDG", "RDG", "RDG2", "RDG3"};

    for(size_t id_function = 1; id_function <= max_id_function; id_function++){
        for(const auto & method : methods){
            for(size_t i_rep = 1; i_rep <= max_rep; i_rep++) {

                string results_file = "results_" + method;
                size_t dimension;
                scalar lower_bound, upper_bound;
                if (id_function == 13 || id_function == 14) {
                    dimension = 905;
                } else {
                    dimension = 1000;
                }
                criteria current_, stop_;
                options options_ = options::defaults();
                stop_.evaluations = 3e6;
                stop_.iterations = LONG_MAX;
                stop_.fx_is_know = true;
                stop_.error_fx_best = 0.0;
                stop_.fx_best = 0.0;

                switch (id_function) {
                    case 1: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f1_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 2: {
                        lower_bound = -5.0;
                        upper_bound = 5.0;
                        f2_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 3: {
                        lower_bound = -32.0;
                        upper_bound = 32.0;
                        f3_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 4: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f4_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 5: {
                        lower_bound = -5.0;
                        upper_bound = 5.0;
                        f5_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 6: {
                        lower_bound = -32.0;
                        upper_bound = 32.0;
                        f6_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 7: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f7_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 8: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f8_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 9: {
                        lower_bound = -5.0;
                        upper_bound = 5.0;
                        f9_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 10: {
                        lower_bound = -32.0;
                        upper_bound = 32.0;
                        f10_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 11: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f11_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 12: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f12_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 13: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f13_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 14: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f14_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    case 15: {
                        lower_bound = -100.0;
                        upper_bound = 100.0;
                        f15_cec f(dimension, vector<scalar>(dimension, lower_bound),vector<scalar>(dimension, upper_bound));

                        read_files read_files_;
                        read_files_.read_decomposition_solutions(id_function, method, f, current_);
                        cout << endl << endl;

                        vector<scalar> x0(dimension, 0.0);
                        differential_evolution_cooperative_coevolutive solver(current_, stop_, options_);
                        solver.set_debug(debug_level::Low);
                        solver.minimize(f, x0);
                        x0 = solver.get_best_solution();
                        unsigned long i_last = solver.get_stats().get_history().size() - 1;
                        scalar fx_best = solver.get_stats().get_history()[i_last].fx;
                        save_results(results_file, id_function, i_rep, x0, fx_best);
                        break;
                    }
                    default: {
                        cerr << "Invalid id function." << endl;
                        exit(2);
                    }
                }
            }
        }
    }
    return 0;
}