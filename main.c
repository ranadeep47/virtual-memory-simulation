#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Custom Modules
#include<defnitions.h>
#include<utilities.c>
#include<segmentation.c>
#include<paging.c>
#include<mainmemory.c>
#include<LRU.c>
#include<FIFO.c>

main(){
     initSegments();
     srand(time(0)); // To Generate unique random numbers each time program starts
     int FIFO_pf=0,LRU_pf=0;
     int node_numbers[NUM_OF_REFERENCES],page_numbers[NUM_OF_REFERENCES],i;
     for(i=0;i<NUM_OF_REFERENCES;++i){
         node_numbers[i] = random_400();  
         page_numbers[i] = node_numbers[i]/4;            
         }
     //Nodes to page Numbers conversion 
     
     //Simulation
     FIFOSimulate(page_numbers,&FIFO_pf);
     LRUSimulate(page_numbers,&LRU_pf);
     printf("In FIFO %i\n", FIFO_pf);
     printf("IN LRU %i",LRU_pf); 
     getch();
     }


