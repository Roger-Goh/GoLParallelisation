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
    bool nextMap[width][height];
    srand((unsigned) time(&t));
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            
             map[i][j] = (double)rand()/RAND_MAX < probability;
           }
    }
   
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
             if(map[i][j]) printf("1\t");
             if(!map[i][j]) printf("0\t");
           }
           printf("\n");
    }
    

   //next Generation
   for (int p = 0; p < width; p++){
        for (int q = 0; q < height; q++){
                switch (0)
                {
                    case 2:  nextMap[p][q] = map[p][q]; break;
                    case 3:  nextMap[p][q] = true;      break;
                    default: nextMap[p][q] = false;
                } 
        }
   }
   //swap the maps
   
    for(int x = 0;x<width;x++){
        for(int y=0;y<height;y++){ 
           bool temp = map[x][y];
           map[x][y] = nextMap[x][y];
           nextMap[x][y] = temp;
    }
}

 

    printf("Next generation\n");
   for (int z = 0; z < width; z++){
        for (int x = 0; x < height; x++){
             if(nextMap[z][x]) printf("1\t");
             if(!nextMap[z][x]) printf("0\t");
           }
           printf("\n");
    }
}   