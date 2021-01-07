#include "differential_grouping_2.h"
#include "common.h"
#include "optimization_problem.h"

using namespace decompose;
using namespace std;

void differential_grouping_2::ism(optimization_problem &problem_, const size_t dim, scalar &fx_base, criteria &criteria_){
    matrix_f = vector<vector<scalar>>(dim, vector<scalar>(dim, std::nan("")));
    vec_f = vector<scalar>(dim, std::nan(""));
    lambda = vector<vector<scalar>>(dim, vector<scalar>(dim, 0.0));
    vector<scalar> x_1 = problem_.get_lower_bound();
    fx_base = problem_.value(x_1);
    criteria_.evaluations++;
    vector<scalar> middle_point(dim, 0.0);
    for(size_t i = 0; i < dim; i++){
        middle_point[i] = 0.5 * (problem_.get_upper_bound()[i] + problem_.get_lower_bound()[i]);
    }
    for(size_t i = 0; i < dim - 1; i++){
        if(isnan(vec_f[i])){
            vector<scalar> x_2 = x_1;
            x_2[i] = middle_point[i];
            vec_f[i] = problem_.value(x_2);
            criteria_.evaluations++;
        }
        for(size_t j = i+1; j < dim; j++){
            if(isnan(vec_f[j])){
                vector<scalar> x_3 = x_1;
                x_3[j] = middle_point[j];
                vec_f[j] = problem_.value(x_3);
                criteria_.evaluations++;
            }
            vector<scalar> x_4 = x_1;
            x_4[i] = middle_point[i];
            x_4[j] = middle_point[j];
            matrix_f[i][j] = problem_.value(x_4);
            criteria_.evaluations++;
            scalar delta_1 = vec_f[i] - fx_base;
            scalar delta_2 = matrix_f[i][j] - vec_f[j];
            lambda[i][j] = abs(delta_1 - delta_2);
            lambda[j][i] = abs(delta_1 - delta_2);
        }
    }
}

scalar differential_grouping_2::gamma(double d){
    scalar muM = (std::numeric_limits<scalar>::epsilon())/2.0;
    return (d * muM)/(1 - (d * muM));
}

scalar differential_grouping_2::max_element(scalar x1, scalar x2, scalar x3, scalar x4){
    if(x1 >= x2 && x1 >= x3 && x1 >= x4){
        return x1;
    } else if(x2 >= x1 && x2 >= x3 && x2 >= x4){
        return x2;
    } else if(x3 >= x1 && x3 >= x2 && x3 >= x4){
        return x3;
    }else{
        return x4;
    }
}

scalar differential_grouping_2::max_element(scalar x1, scalar x2){
    if(x1 >= x2){
        return x1;
    }
    else{
        return x2;
    }
}

void differential_grouping_2::dsm(const size_t dim, scalar &fx_base){
    theta = vector<vector<scalar>>(dim, vector<scalar>(dim, std::nan("")));
    size_t n_0 = 0;
    size_t n_1 = 0;
    for(size_t i = 0; i < dim-1; i++){
        for(size_t j = i+1; j < dim; j++){
            scalar fx_max = max_element(fx_base, matrix_f[i][j], vec_f[i], vec_f[j]);
            scalar e_inf = gamma(2) * max_element(fx_base + matrix_f[i][j], vec_f[i] + vec_f[j]);
            scalar e_sup = gamma(pow((scalar)dim, (scalar)0.5)) * fx_max;
            if(lambda[i][j] < e_inf){
                theta[i][j] = 0;
                theta[j][i] = 0;
                n_0++;
            }else if(lambda[i][j] > e_sup){
                theta[i][j] = 1;
                theta[j][i] = 1;
                n_1++;
            }
        }
    }
    for(size_t i = 0; i < dim-1; i++){
        for(size_t j = i+1; j < dim; j++){
            scalar fx_max = max_element(fx_base, matrix_f[i][j], vec_f[i], vec_f[j]);
            scalar e_inf = gamma(2) * max_element(fx_base + matrix_f[i][j], vec_f[i] + vec_f[j]);
            scalar e_sup = gamma(pow((scalar)dim, (scalar)0.5)) * fx_max;
            if(isnan(theta[i][j])){
                //scalar eps = (n_0 / (n_0 + n_1)) * e_inf + (n_1 / (n_0 + n_1)) * e_sup;
                scalar eps = (n_0 / (scalar)(n_0 + n_1)) * e_inf + (n_1 / (scalar)(n_0 + n_1)) * e_sup;
                if(lambda[i][j] > eps){
                    theta[i][j] = 1;
                    theta[j][i] = 1;
                }
                else{
                    theta[i][j] = (scalar) 0;
                    theta[j][i] = (scalar) 0;
                }
            }
        }
    }
}

void differential_grouping_2::decompose(optimization_problem &problem_, options &options_, criteria &criteria_) {
    criteria_.reset();
    vector<set<size_t>> sub_problems;
    const size_t dim = problem_.get_dimension();
    scalar fx_base = 0.0;
    ism(problem_, dim, fx_base, criteria_);
    dsm(dim, fx_base);

    set<size_t> dims;
    for(size_t i = 0; i < dim; i++){
        dims.insert(i);
    }
    for(size_t i = 0; i < dim; i++){
        set<size_t> sub_problem_tmp;
        if(dims.find(i) != dims.end()){
            sub_problem_tmp.insert(i);
            dims.erase(i);
            for(auto it = sub_problem_tmp.begin(); it != sub_problem_tmp.end(); it++){
                for(size_t j = 1+(*it); j < dim; j++){
                    if(theta[*it][j] == 1 && dims.find(j) != dims.end()){
                        theta[*it][j] = 0;
                        theta[*it][i] = 0;
                        sub_problem_tmp.insert(j);
                        dims.erase(j);
                    }
                }
            }
        }
        if(!sub_problem_tmp.empty()){
            sub_problems.push_back(sub_problem_tmp);
        }
    }
    problem_.set_problem_structure(sub_problems);
}