#include "Header.h"
#include <sys/time.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

double getrnd() {
    return (double)rand() / (double)RAND_MAX;
}

double explore_random(Benchmarks*  fp, int maxevals) {
    double fitness, best_fitness;
    const unsigned dim=1000;
    double X[1000];
    unsigned i;
    int evals;

    fp->nextRun();

    for (i=0; i<dim; i++){
        X[i]=getrnd()*200-100;
    }

    fitness = fp->compute(X);
    evals = 1;
    best_fitness = fitness;

    for (evals = 1; evals < maxevals; evals++) {
        for (i=0; i<dim; i++){
            X[i]=getrnd()*200-100;
        }

        fitness = fp->compute(X);

        if (fitness < best_fitness) {
            best_fitness = fitness;
            printf("%e\n", best_fitness);
        }
    }

    return best_fitness;
}

int main(){
    /*  Test the basic benchmark function */
    Benchmarks* fp=NULL;
    unsigned funToRun[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    // unsigned funToRun[] = {1};
    // unsigned funToRun[] = {15};
    unsigned funNum = 3;
    double best_fitness;

    vector<double> runTimeVec;
    struct timeval start, end;
    long seconds, useconds;
    double mtime;
    unsigned maxevals = 3000000;

    srand(time(NULL));

    for (unsigned i=1; i<funNum; i++){
        fp = generateFuncObj(funToRun[i]);
        gettimeofday(&start, NULL);
        best_fitness = explore_random(fp, maxevals);
        gettimeofday(&end, NULL);

        printf("F %d value = %1.20E\n", fp->getID(), best_fitness);
        seconds  = end.tv_sec  - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;

        mtime = (((seconds) * 1000 + useconds/1000.0) + 0.5)/1000;

        runTimeVec.push_back(mtime);
        printf ( "F %d, Running Time = %f s\n\n", fp->getID(), mtime);

        delete fp;
    }

    // for (unsigned i=0; i<runTimeVec.size(); i++){
    // 	printf ( "%f\n", runTimeVec[i] );
    // }

    return 0;
}

// create new object of class with default setting
Benchmarks* generateFuncObj(int funcID){
    Benchmarks *fp;
    // run each of specified function in "configure.ini"
    if (funcID==1){
        fp = new F1();
    }else if (funcID==2){
        fp = new F2();
    }else if (funcID==3){
        fp = new F3();
    }else if (funcID==4){
        fp = new F4();
    }else if (funcID==5){
        fp = new F5();
    }else if (funcID==6){
        fp = new F6();
    }else if (funcID==7){
        fp = new F7();
    }else if (funcID==8){
        fp = new F8();
    }else if (funcID==9){
        fp = new F9();
    }else if (funcID==10){
        fp = new F10();
    }else if (funcID==11){
        fp = new F11();
    }else if (funcID==12){
        fp = new F12();
    }else if (funcID==13){
        fp = new F13();
    }else if (funcID==14){
        fp = new F14();
    }else if (funcID==15){
        fp = new F15();
    }else{
        cerr<<"Fail to locate Specified Function Index"<<endl;
        exit(-1);
    }
    return fp;
}
