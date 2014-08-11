// LRU Algorithm for paging 

void updateLRUll(page *p){
     if(headLRU == NULL){
                LRUNode *n = (LRUNode *)malloc(sizeof(LRUNode));
                n->previous = NULL;
                n->next = NULL;
                pageFrameDes *tmp = headPFD;
                while(tmp->pageId != p->pageId) tmp = tmp->next;
                n->pfd = tmp; 
                headLRU = n;
                tailLRU = n;
                }
  else{
     // if p in ll , move to head
     // if not put it in head
     pageFrameDes *TMP = headPFD;
     while(TMP->pageId != p->pageId ) TMP = TMP->next;
     LRUNode *tmpLRU = headLRU;
     while(tmpLRU != NULL && tmpLRU->pfd != TMP) tmpLRU = tmpLRU->next;
     if(tmpLRU == NULL ) {
            // p not in ll , so put it in head
            LRUNode *N = (LRUNode *)malloc(sizeof(LRUNode));
            N->next = headLRU;
            N->previous = NULL;
            N->pfd = TMP;
            headLRU->previous = N;
            headLRU = N;
            }
     else{
          // present in ll , so put it to head
          LRUNode *prev = tmpLRU->previous;
          if(prev == NULL) return;
          else  prev->next = tmpLRU->next;
         if(tmpLRU->next == NULL )  { 
               prev->previous = tmpLRU;
               tmpLRU->next = headLRU;
               tmpLRU->previous = NULL;
               headLRU = tmpLRU;
              }
         else{
         // printf("%i put to head\n",tmpLRU->pfd->pageId);
          tmpLRU->next->previous  = prev;
          tmpLRU->next = headLRU;
          tmpLRU->previous = NULL;
          headLRU = tmpLRU;
            }
    }
  }
}

void LRUSimulate(int *mem_references,int *pageFaults){
     initPaging();
     initFrames();
     int pageNo,i;
     for(i=0;i<100;++i){
                        pageNo = mem_references[i];
                        page *p = findPage(pageNo);
                        int present = checkPageLoaded(p);
                        if(!present){
                                    ++(*pageFaults);  //Update PageFault , since !present            
                           if(freeFrameAvlbl()){
                                     copyPageToFrame(p,freeFrameAvlbl()); // if free free avlbl , use it
                                     }
                           else {
                                 if(headLRU ==  NULL ) {
                                     copyPageToFrame(p,headPFD->frame);    //if LRU List is empty, copy to first avbl frame
                                  }
                                 else {
                                pageFrame *frame = tailLRU->pfd->frame;   // Copy page to Least Recently used ie tail of LRU List
                                copyPageToFrame(p,frame);
                                LRUNode *newTail = NULL;
                                if(tailLRU->previous == NULL) headLRU = NULL;                                                         
                                else {
                                     newTail = tailLRU->previous;
                                     newTail->next = NULL;
                                }
                             //   printf("Removing %i page from frame\n",tailLRU->pfd->pageNo);
                                free(tailLRU);
                                tailLRU = newTail;
                                      }
                             }
                       }
            updateLRUll(p);
         }
}
