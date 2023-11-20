
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>

#include <sstream>
#include <string>
#include <fstream>  //處理檔案

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <map>
#include <cmath>
#include <random>//std::normal_distribution
using namespace std;

#define INF 2147483647

int m;  //num of machines
int n;  //num of jobs
int w[100][100]; //w[i][j]= weight of job i on machine j
int L[100]; //L[j]=sum of weight of machine j
int opt_time;


void track(int v){
    for(int j=1;j<=m;j++){
        L[j]=L[j]+ w[v][j];
        if (v<n) track(v+1);
        else{
            int tmp=0;
            for(int p=1;p<=m;p++){
                if (tmp<L[p]) tmp=L[p];
            }
            if (opt_time > tmp) opt_time = tmp;
        }
        L[j]=L[j]- w[v][j];
    }
}

int main()
{
      /* 固定亂數種子 */
    srand( time(NULL) );

    // random device class instance, source of 'true' randomness for initializing random seed
    std::random_device rd;
    // Mersenne twister PRNG, initialized with seed from previous random device instance
    std::mt19937 gen(rd());
    float sample;

    int test=20;

    for(int run=1;run<=test;run++){

    char buffer [50];
    sprintf (buffer, "in%d.txt", run);
    freopen(buffer,"w",stdout);
    //freopen("out10_6.txt","w",stdout);
    m=5;
    n=8;
    printf("%d %d\n", m, n);
    int i,j;



    for(i = 1; i <= n; ++i)
    {
        // instance of class std::normal_distribution with specific mean and stddev
            std::normal_distribution<float> d(500, 240);

            // get random number with normal distribution using gen as random source
            sample = d(gen);

            // profit
            //do_something_with_this_value(sample);
            int tmp=max((int)round(sample),1);

        for(j=1;j<=m;j++){
             w[i][j]= tmp;
            //w[i][j]=500;
            printf("%d ", w[i][j]);
        }
        printf("\n");
    }

    /*for(i=1;i<=n;i++){   //input
        for(j=1;j<=m;j++){
            w[i][j]= rand() %100 +10;
            printf("%d ", w[i][j]);
        }
        printf("\n");
    }*/

    for(j=1;j<=m;j++)
        L[j]=0;

    //compute opt
    opt_time=INF;
    track(1);
    printf("%d\n", opt_time);

    fclose (stdout);
    }
    return 0;
}
