//FIFO for paging
void updateFIFOll(page *p){
     if(headFIFO == NULL ) {
                FIFONode *n = (FIFONode *)malloc(sizeof(FIFONode));
                n->next = NULL;
                pageFrameDes *tmp = headPFD;
                while(tmp->pageId != p->pageId) tmp = tmp->next;
                n->pfd = tmp;
                headFIFO = n;
                }
     else {
                FIFONode *TMP = headFIFO;
                while(TMP->next != NULL ) TMP = TMP->next;
                FIFONode *n = (FIFONode *)malloc(sizeof(FIFONode));
                n->next = NULL;
                pageFrameDes *tmp = headPFD;
                while(tmp->pageId != p->pageId){
                                  tmp = tmp->next;
                                  }
                n->pfd = tmp;
                TMP->next = n;
          }
     }
     
//The Simulator with FIFO Algorithm
void FIFOSimulate(int *references,int *pageFault){
         initPaging(); 
         initFrames();           // Initialise Frame , Basically resets all the frames
         int pageNo,i;
         for(i=0;i<100;++i){
           pageNo = references[i];
           page *p = findPage(pageNo);
           int present = checkPageLoaded(p);
           if(!present) {
                ++(*pageFault);
                //check free frame
                if(freeFrameAvlbl()){
                                     copyPageToFrame(p,freeFrameAvlbl());
                                     }
                else {
                      if(headFIFO ==  NULL ) {
                              copyPageToFrame(p,headPFD->frame);   
                                 }
                      else {
                            FIFONode *tmp = headFIFO;
                            if(headFIFO->next == NULL) {
                                copyPageToFrame(p,headFIFO->pfd->frame);
                                free(headFIFO);
                                headFIFO = NULL;
                                   }
                            else {
                            tmp = tmp->next;
                            pageFrame *frame = headFIFO->pfd->frame;
                            copyPageToFrame(p,frame);
                            free(headFIFO);
                            headFIFO = tmp;
                                }
                      }
              }
           }
         updateFIFOll(p);
     }
 }
