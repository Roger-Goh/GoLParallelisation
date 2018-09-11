#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<stdio.h>
#include<stdbool.h>

int getNumNeighbours(int i, int j, int width, int height, bool map[width][height]){
    int nNeighbours = 0;
    printf("middle: %d i: %d j: %d\n",map[i][j],i,j);
    if(map[i][(j+1)%width] == true){
        nNeighbours++; //rightside neighbour
    }
    printf("right: %d\n", map[i][(j+1)%width]); //test
    if(map[(i+1)%height][(j)] == true){
        nNeighbours++; //downside neighbour
    }
    printf("down: %d\n", map[(i+1)%height][(j)]); //test
    if(j==0){
        if(map[i][width-1] == true){
            nNeighbours++; //leftside neighbour of edge case
        }
        printf("leftedge: %d\n", map[i][width-1]); //test
    } else {
        if(map[i][j-1] == true){
            nNeighbours++; //leftside neighbour
        }
        printf("left: %d\n", map[i][j-1]); //test
    }
    if(i==0){
        if(map[height-1][j] == true){
            nNeighbours++; //topside neighbour of edge case
        }
        printf("upedge: %d\n", map[height-1][j]); //test
    } else {
        if(map[i-1][j] == true){
            nNeighbours++; //topside neighbour
        }
         printf("up: %d\n", map[i-1][j]); //test
    }
    return nNeighbours;
}

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
    srand(0);
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

    int test = getNumNeighbours(1,7,width,height,map);
    printf("NumNeightbours: %d", test);
}
