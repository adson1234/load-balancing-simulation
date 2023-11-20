
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>    // std::random_shuffle

#include <sstream>
#include <string>
#include <fstream>  //處理檔案

#include <cstdlib>
#include <ctime>

#include <math.h>  //pow(,) sqrt()
using namespace std;

#define INF 2147483647

int m;  //num of machines
int n;  //num of jobs
double w[100][100]; //w[i][j]= weight of job i on machine j
double L[100]; //L[j]=sum of weight of machine j
double rho[100][100];  //rho[i][j]=w[i][j]/w[i][min]

int makespan_cnt[10000]; //makespan_cnt[i]= count of times of makespan=i

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double cal_P(double _rho, float _p, int _L){
    return pow(_rho, ((double)1)/_p)*_L;
}

int main()
{
      /* 固定亂數種子 */
    srand( time(NULL) );

    char buffer [50];
    sprintf (buffer, "out.txt");
    freopen(buffer,"w",stdout);

    int test=20;
    //int test=1;
    for(int run=1;run<=test;run++){


    sprintf (buffer, "in%d.txt", run);
    freopen(buffer,"r",stdin);


    float p=2560;
    //for(float p=2.09042;p<=2.09043;p=p+0.000001){
    scanf("%d %d", &m, &n);

    int i,j,k;

    for(i=0;i<10000;i++)   //init
    {
        makespan_cnt[i]=0;
    }

    for(i=1;i<=n;i++)   //input
        for(j=1;j<=m;j++){
            scanf("%lf", &w[i][j]);
        }

    double opt;
    scanf("%lf", &opt);

    for(i=1;i<=n;i++){   //calculate rho
        double w_min=INF;
        for(j=1;j<=m;j++){
            if (w_min>w[i][j]) w_min=w[i][j];
        }
        for(j=1;j<=m;j++){
            rho[i][j]= ((double)w[i][j])/w_min;
            //printf("%f ", rho[i][j]);
        }
        //printf("\n");
    }

    vector<int>ID; //ID[k]:  (the job with ID=k is "ID[k]"

    for (int i=0; i<=n; ++i) ID.push_back(i); // 1 2 3 4 5 6 7 8 9

  // using built-in random generator:
    //std::random_shuffle ( ID.begin()+1, ID.end() );
    double worst_NE=0,best_NE=INF;
    double sum=0,sum2=0;
    int order[1000];
    int order2[1000];
    do {
        for(j=1;j<=m;j++)   //init
            L[j]=0;

        for(k=1;k<=n;k++){
            double min_P=INF;
            int NE_machine;
            for(j=1;j<=m;j++){
                if (cal_P(rho[ID[k]][j],p,L[j]+w[ID[k]][j])<min_P){
                    min_P=cal_P(rho[ID[k]][j],p,L[j]+w[ID[k]][j]);
                    NE_machine=j;
                }
            }
            L[NE_machine]+=w[ID[k]][NE_machine];
            //printf("%lf ",w[ID[k]][NE_machine]);
        }
        //printf("\n");
        double makespan=0;
        for(j=1;j<=m;j++){
            if (L[j]>makespan){
                makespan=L[j];
            }
        }
        if (worst_NE<makespan){
            worst_NE=makespan;
            for(int k=1;k<=n;k++){
                order2[k]=ID[k];
            }
        }
        if (best_NE>makespan) {
            best_NE=makespan;
            for(int k=1;k<=n;k++){
                order[k]=ID[k];
            }
        }
        makespan_cnt[(int)round(makespan)]++;
        sum+=makespan;
        sum2+=makespan*makespan;
        //for (int i=0; i<=n; ++i) printf("%d ", ID[i]); // 1 2 3 4 5 6 7 8 9
        //printf("\n");
    } while ( std::next_permutation(ID.begin()+1,ID.end()) );


    printf("run=\n%d\n", run);
    printf("OPT=\n%f\n", opt);
    printf("best_NE=\n%f\n", best_NE);
    for(int k=1;k<=n;k++){
        printf("%d ", order[k]);
    }
    printf("\nworst_NE=\n%f\n", worst_NE);
    for(int k=1;k<=n;k++){
        printf("%d ", order2[k]);
    }
    printf("\nPOS=\n%f\n", (float)best_NE/opt);

    printf("\nPOA=\n%f\n", (float)worst_NE/opt);

    printf("AVG=\n%f\n", (float)sum/factorial(n));
    printf("VAR=\n%f\n", sum2/factorial(n)-pow((float)sum/factorial(n),2));

    for(i=0;i<10000;i++)   //init
    {
        if (makespan_cnt[i]>0){
            printf("makespan= %d %d times\n", i,makespan_cnt[i]);
        }
    }
    //printf("p= %f, best_NE= %f, worst_NE= %f\n", p, best_NE, worst_NE);
    //}
    }
    fclose (stdout);

    return 0;
}
