//Virtual Memory -> Segmentation (Logical to Linear Address ) 
char* getSegmentSelector(char *logicalAdd){
      static char segSel[5] = {'\0'};
      int i;
      for(i=0;i<4;++i){
                       segSel[i] = logicalAdd[i];
                       }
      return segSel;
      }

char* getSegmentOffset(char *logicalAdd){
      static char segOff[7] = {'\0'};
      int i;
      for(i=0;i<6;++i){
           segOff[i] = logicalAdd[4+i];
                       }
      return segOff;
      }
      
char* getPageTable(char *segmentOff){
       static char pageTO[5] = {'\0'};
       int i;
       for(i=0;i<4;++i){
                        pageTO[i] = segmentOff[i];
                        }
       return pageTO;
      }
      
char* getPageOffset(char *segmentOff){
      static char pageO[3] = {'\0'};
      int i;
      for(i=0;i<2;++i){
                       pageO[i] = segmentOff[4+i];
                       }
      return pageO;
      }


void createSegment(int id){
    segmentNode *head = NULL;
    int j;
           for(j=0;j<NUM_OF_SEGMENTNODES;++j){
                               if(head == NULL) {
                                 segmentNode *n = (segmentNode *)malloc(sizeof(segmentNode));
                                 n->id = NUM_OF_SEGMENTNODES*id+j;
                                 strcpy(n->pageDir,getSegmentSelector(decToBin(NUM_OF_SEGMENTNODES*id+j,10)));
                                 strcpy(n->pageTab,getPageTable(getSegmentOffset(decToBin(NUM_OF_SEGMENTNODES*id+j,10))));  
                                 strcpy(n->pageOff,getPageOffset(getSegmentOffset(decToBin(NUM_OF_SEGMENTNODES*id+j,10)))); 
                                 n->next = NULL; 
                                 head = n;
                                 }
                               else {
                                 segmentNode *tmp = head;
                                 while(tmp->next != NULL ) {tmp = tmp->next;}  
                                 segmentNode *n = (segmentNode *)malloc(sizeof(segmentNode));
                                 n->id = 40*id+j;
                                 strcpy(n->pageDir,getSegmentSelector(decToBin(NUM_OF_SEGMENTNODES*id+j,10)));
                                 strcpy(n->pageTab,getPageTable(getSegmentOffset(decToBin(NUM_OF_SEGMENTNODES*id+j,10))));  
                                 strcpy(n->pageOff,getPageOffset(getSegmentOffset(decToBin(NUM_OF_SEGMENTNODES*id+j,10)))); 
                                 n->next = NULL;
                                 tmp->next = n;
                                    }        
                          }
         if(headSD == NULL){
                   segmentDes *sd = (segmentDes *)malloc(sizeof(segmentDes));
                   sd->id = id;
                   sd->list = head;
                   sd->next = NULL;
                   headSD = sd;
                   }
         else {
               segmentDes *tmp = headSD;
               while(tmp->next != NULL) tmp = tmp->next;
               segmentDes *SD = (segmentDes *)malloc(sizeof(segmentDes));
               SD->id = id;
               SD->list = head;
               SD->next = NULL;
               tmp->next = SD;
              }
     }
     
void initSegments(void){
     int i;
     headSD = NULL;
     for(i=0;i<NUM_OF_SEGMENTS;++i){                  
             createSegment(i);                    
                             }    
     }




