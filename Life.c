#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<stdio.h>
#include<stdbool.h>

int  main(int argc, char *args[]){
    
     int width;
     int height;
     time_t t;
    double probability;
    if(argc==4){
        width = atoi(args[1]);
        height = atoi(args[2]);
       probability = atof(args[3]);
      // printf("w = %d h = %d p= %f",width,height, probability);
    }
    bool map[width][height];
    srand((unsigned) time(&t));
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            
             map[i][j] = (double)rand()/RAND_MAX < probability;
           }
    }
    /*print matricx
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
             if(map[i][j]) printf("1\t");
             if(!map[i][j]) printf("0\t");
           }
           printf("\n");
    }
    */
    
   

}