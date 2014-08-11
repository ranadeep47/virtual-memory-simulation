//frame , main memory , pageframedescriptors 

pageFrame* createFrame(int id,page *pAGE){
    pageFrame *pf = (pageFrame *)malloc(sizeof(pageFrame));
		   	 pf->list = NULL;
             pf->next = NULL;
			 pf->frameNo = id;
             if(pAGE) copyPageToFrame(pAGE,pf);
             return pf;
           }

pageFrameDes* createFrameDescriptor(int id,pageFrame *pf,page *pAGE){
   pageFrameDes *pfd = (pageFrameDes *)malloc(sizeof(pageFrameDes));
			 pfd->frame   = pf;
			 pfd->frameNo = id;
			 pfd->next = NULL;
			 pfd->pageId = pAGE ? pAGE->pageId : 999;
			 pfd->status = pAGE ? 1 : 0;
			 return pfd;
}

void initFrames(){
     int i;
     headPF = NULL , headPFD = NULL;
     for(i=0;i<NUM_OF_FRAMES;++i){
        if(headPF == NULL) {
                  headPF = createFrame(i,NULL);
                  headPFD = createFrameDescriptor(i,headPF,NULL);
                  }    
        else {
           pageFrame *tmp_PF = headPF;
           pageFrameDes *tmp_PFD = headPFD;
           while(tmp_PF->next != NULL) tmp_PF = tmp_PF->next;
           while(tmp_PFD->next != NULL) tmp_PFD = tmp_PFD->next;
           tmp_PF->next = createFrame(i,NULL);
           tmp_PFD->next = createFrameDescriptor(i,tmp_PF->next,NULL);
        }
     }

// Initialise first 25 frames with first 25 pages , rem 25 frames are free
  pageFrame *destFrame = headPF;
  for(i=0;i<NUM_OF_FRAMES/2;++i){
      page *pageToCopy = findPage(i);
      copyPageToFrame(pageToCopy,destFrame);
     // printf("% i page copied to %i frame \n",i,destFrame->frameNo);
      destFrame = destFrame->next;        
  }
}

void removePageFromFrame(pageFrame *pf){
     //Removing Nodes
     int pageNO,i;
     if(pf->list == NULL) return;
     else {
          node *arrayOfNodes[NUM_OF_NODES_PERPAGE];
          node *tmp_NODE = pf->list;
          for(i=0;i<NUM_OF_NODES_PERPAGE;++i){
                arrayOfNodes[i] = tmp_NODE;
                tmp_NODE = tmp_NODE->next;       
             } 
          for(i=0;i<NUM_OF_NODES_PERPAGE;++i) free(arrayOfNodes[i]);
          pf->list = NULL;
          }
     //Update Page Frame Descriptor
     pageFrameDes *tmp_PFD = headPFD;
     while(tmp_PFD->frameNo != pf->frameNo ) tmp_PFD = tmp_PFD->next;
     pageNO = tmp_PFD->pageId;
     tmp_PFD->pageId = 999;
     tmp_PFD->status = 0;
     //Updatge Page Table
     int PTid = pageNO/10;
     pageTable *tmp_PT = headPT;
     while(tmp_PT->id!= PTid) tmp_PT = tmp_PT->next;
     pageTableEntry *tmp_PTE = tmp_PT->list;
     while(tmp_PTE->pageID != pageNO) tmp_PTE = tmp_PTE->next;
     tmp_PTE->flag = 0;
     tmp_PTE->frame = NULL;    
}

void copyPageToFrame(page *pAGE,pageFrame *frame){
    //Update Page Frame Nodes
    if(frame && frame->list != NULL ) removePageFromFrame(frame);
    if(pAGE == NULL) return;
    node *tmp_NODE = pAGE->list;
    while(tmp_NODE != NULL ){
                   if(frame->list == NULL) {
                         node *n = (node *)malloc(sizeof(node));
                         n->next = NULL;
                         n->data = tmp_NODE->data;
                         frame->list = n;       
                                  }
                   else{
                        node *tmp = frame->list;
                        while(tmp->next != NULL) tmp = tmp->next;
                        node *n = (node *)malloc(sizeof(node));
                        n->next = NULL;
                        n->data = tmp_NODE->data;
                        tmp->next = n;
                        }
                   tmp_NODE = tmp_NODE->next;
                   }
   //Update Page Frame Descriptor
    pageFrameDes *tmp_PFD = headPFD;
    while(tmp_PFD->frameNo != frame->frameNo) tmp_PFD = tmp_PFD->next;
    tmp_PFD->pageId = pAGE->pageId;
    tmp_PFD->status = 1;
   //Update PageTable  
    int PTid  = pAGE->pageId/10;
    pageTable *tmp_PT = headPT;
    while(tmp_PT->id != PTid ) tmp_PT = tmp_PT->next;
    pageTableEntry *tmp_PTE = tmp_PT->list;
    while(tmp_PTE->pageID != pAGE->pageId ) tmp_PTE = tmp_PTE->next;
    tmp_PTE->frame = frame;
    tmp_PTE->flag = 1;
}

pageFrame* freeFrameAvlbl(void){
           pageFrameDes *tmp = headPFD;
           while(tmp != NULL && tmp->status != 0) tmp = tmp->next;
           if(tmp != NULL) return tmp->frame;
           else return NULL;
  }

