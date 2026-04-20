#include<stdio.h>
#define v 3
#define inf 9999


void printMatrix(int dist[][v], int step){
  printf("A^%d :\n",step);
  for(int i = 0 ; i < v; i++){
    for(int j = 0; j < v; j++){
      if(dist[i][j] != inf){
        printf("%d\t",dist[i][j]);
      }
      else{
        printf("%s\t","INF");
      }
    }
    printf("\n");
  }
}
void floyedWarshall(int graph[][v]){
  int dist[v][v];
  int next[v][v];

  for(int i = 0; i < v; i++){
    for(int j = 0; j < v; j++){
      dist[i][j] = graph[i][j];
      if(graph[i][j] != inf && i != j){
        next[i][j] = j;
      }
      else{
        next[i][j] = -1;
      }
    }
  }

  for(int k = 0; k < v; k++){
    for(int i = 0; i < v; i++){
      for(int j = 0; j < v; j++){
        if(dist[i][k] != inf && dist[k][j] != inf && (dist[i][k] + dist[k][j] < dist[i][j])){
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = next[i][k];
        }
      }
    }

    printMatrix(dist,k+1);
  }

  for(int i = 0; i < v; i++){
    for(int j = 0; j < v; j++){
      if(i != j){
      int u = i;
      printf("%d ",u+1);
      while(u != j){
        u = next[u][j];
        printf("-> %d ",u+1);
      }
      printf(": %d\n",dist[i][j]);
    }
  }
}
}

int main() {
    int graph[v][v] = {
        {0,   4,  11},  // From node 1
        {6,   0,    2},  // From node 2
        {3,   inf,  0}   // From node 3
    };

    printf("Initial Graph (A^0):\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (graph[i][j] == inf) printf("%s\t", "INF");
            else printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }

    floyedWarshall(graph);

    return 0;
}
