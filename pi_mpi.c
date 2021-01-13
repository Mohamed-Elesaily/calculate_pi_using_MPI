#include<stdio.h>
#include"mpi.h"
#include<time.h>
#include<math.h>
double pi( int begin, int limit){
    double sum = 0;
    for(int i=begin;i<limit;i++){
    sum += (pow(tgamma(i+1),2)*pow(2,i+1))/tgamma(2*i + 2);
    }
return sum;
}
int main(int argc, char **argv){
int size, node;
int limit,start, end,time;

double sum = 0;
double buf;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &node);
MPI_Comm_size(MPI_COMM_WORLD, &size);
time = MPI_Wtime();
if(node == 0){
printf("Please Enter i(0 -> 90):\n");
scanf("%d",&limit);
for(int i=1;i<size;i++){
MPI_Send(&limit, 1,MPI_INT, i,0, MPI_COMM_WORLD);
}
}
else{
MPI_Recv( &limit, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
}
//  for all process
int part = limit/size;
// each process

start = part * (node -1);
end = start + part;

buf = pi(start,end);

if(node != 0){

MPI_Send(&buf, 1,MPI_DOUBLE, 0,0, MPI_COMM_WORLD);
}
else{


for(int i=1;i<size;i++){


MPI_Recv( &buf, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
sum += buf;
}
 
}
if(node == 0){
printf("time using MPI: %0.9lf \n",(MPI_Wtime()-time)/CLOCKS_PER_SEC);
printf("PI = %.20lf \n",sum);
   
}

MPI_Finalize();
return 0;
}


