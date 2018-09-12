#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<stdio.h>
#include<stdbool.h>

int getNumNeighbours(int i, int j, int width, int height, bool *map){
    int nNeighbours = 0;
    //printf("middle: %d i: %d j: %d\n",map[i][j],i,j);
    if(map[i*height+(j+1)%width] == true){
        nNeighbours++; //rightside neighbour
    }
    //printf("right: %d\n", map[i][(j+1)%width]); //test
    if(map[((i+1)%height)*height+(j)] == true){
        nNeighbours++; //downside neighbour
    }
    //printf("down: %d\n", map[(i+1)%height][(j)]); //test
    if(j==0){
        if(map[i*height+width-1] == true){
            nNeighbours++; //leftside neighbour of edge case
        }
        //printf("leftedge: %d\n", map[i][width-1]); //test
    } else {
        if(map[i*height+j-1] == true){
            nNeighbours++; //leftside neighbour
        }
       // printf("left: %d\n", map[i][j-1]); //test
    }
    if(i==0){
        if(map[(height-1)*height+j] == true){
            nNeighbours++; //topside neighbour of edge case
        }
       // printf("upedge: %d\n", map[height-1][j]); //test
    } else {
        if(map[(i-1)*height+j] == true){
            nNeighbours++; //topside neighbour
        }
         //printf("up: %d\n", map[i-1][j]); //test
    }
    //printf("succucess"); 
    return nNeighbours;
}

int  main(int argc, char *args[]){
    
    int width;
    int height;
    time_t t,beginS,beginP,endS,endP; //for timing the sequential  and parallel program
    double probability;
    if(argc==4){
        width = atoi(args[1]);
        height = atoi(args[2]);
       probability = atof(args[3]);
      // printf("w = %d h = %d p= %f",width,height, probability);
    }
    //map initialisation
    bool *map= (bool *)malloc(width*height*sizeof(bool));
    bool *nextMap= (bool *)malloc(width*height*sizeof(bool));
    
    srand(0); 
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            
            map[i*height+j] = (double)rand()/RAND_MAX < probability;
           }
    }
   //print matrix
   /*
    for(int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
             if(map[i*height+j]) printf("1\t");
             if(!map[i*height+j]) printf("0\t");
           }
           printf("\n");
    }*/
    //sequential 
    beginS = clock();
    for(int l = 0; l < 100; l++){  //the main loop
    //next Generation
        for (int p = 0; p < width; p++){
            for (int q = 0; q < height; q++){
                    switch (getNumNeighbours(p,q,width,height,map))
                    {
                        case 2:  nextMap[p*height+q] = map[p*height+q]; break;
                        case 3:  nextMap[p*height+q] = true;      break;
                        default: nextMap[p*height+q] = false;
                    } 
            }
        }
   //swap the maps
   
        for(int x = 0;x<width;x++){
            for(int y=0;y<height;y++){ 
                bool temp = map[x*height+y];
                map[x*height+y] = nextMap[x*height+y];
                nextMap[x*height+y] = temp;
            }
        }

 
    //print matrix
    /*
        printf("Next generation\n");
        for (int z = 0; z < width; z++){
            for (int x = 0; x < height; x++){
                if(map[z*height+x]) printf("1\t");
                if(!map[z*height+x]) printf("0\t");
            }
            printf("\n");
        }*/
    }
    endS = clock();
    printf("time for sequential =%f\n",(double)(endS - beginS) / CLOCKS_PER_SEC);

    //parallazation using omp
    beginP = clock();
    for(int s = 0; s < 100; s++){
        //next Generation
        #pragma omp parallel
        {
            #pragma omp for
            for (int pp = 0; pp < width; pp++){
                 for (int qp = 0; qp < height; qp++){
                    switch (getNumNeighbours(pp,qp,width,height,map))
                    {
                        case 2:  nextMap[pp*height+qp] = map[pp*height+qp]; break;
                        case 3:  nextMap[pp*height+qp] = true;      break;
                        default: nextMap[pp*height+qp] = false;
                    } 
                }
             }
   //swap the maps
            #pragma omp for
            for(int xp = 0;xp<width;xp++){
                for(int yp=0;yp<height;yp++){ 
                    bool temp = map[xp*height+yp];
                    map[xp*height+yp] = nextMap[xp*height+yp];
                    nextMap[xp*height+yp] = temp;
                }
            }
        }
    }

    endP = clock();
    printf("time for parallel =%f\n",(double)(endP - beginP) / CLOCKS_PER_SEC);

}