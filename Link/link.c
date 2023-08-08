#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


void shortestPath(int n , int cost[n][n],int src){

      int distance[n];
      int visited[n];
      int previous[n];
     int u;
      for(int i=0;i<n;i++){
          distance[i] =10000;
          visited[i] = 0;
          previous[i] = src;
      }

      distance[src] = 0;

      for(int i =0;i<n;i++){
        int min = 10000;
        for(int j =0;j<n;j++){
            if(visited[j] == 0 && distance[j] < min){
                min = distance[j];
                u=i;
            }
        }
        visited[u] = 1;
        for(int k=0;k<n;k++)
      }


}

int main(){
    
    int n;
    printf("enter the number of nodes");
    scanf("%d",&n);

    int cost[n][n];

    printf("enter the cost matrix\n");

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i == j){
                cost[i][j] = 0;
            }
            else{
                printf("enter the cost from %d to %d: ",i+1,j+1);
                scanf("%d",&cost[i][j]);
                if(cost[i][j] == 0){
                    cost[i][j] = 999;
                }
            }

        }

    }


    printf("enter the source node: ");
    int source;
    scanf("%d",&source);

    shortestPath(cost,n,source-1);
}