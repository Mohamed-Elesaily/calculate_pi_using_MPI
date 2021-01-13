#include<stdio.h>
#include<time.h>
#include<math.h>
double pi(int limit){
    double sum = 0;
    for(int i=0;i<=limit;i++){
    sum += (pow(tgamma(i+1),2)*pow(2,i+1))/tgamma(2*i + 2);
    }
return sum;
}

int main(){
    int limit;
    printf("Please Enter i(0 -> 90):\n");
    scanf("%d",&limit);
    clock_t ts = clock();
    printf("PI = %.20lf \n",pi(limit));
    ts = clock() - ts;
    double time = ts;
    printf("time: %.9lf\n",time/CLOCKS_PER_SEC);
}
