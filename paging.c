
//paging and pagetable generation , initialisation of 100 pages , 10 page tables 
void createNodes(page* pAGE){
     int j;
      for(j=0;j<4;++j){
			if(pAGE->list == NULL ){
				node *n = (node *)malloc(sizeof(node));
				n->data = 1000 + 4*pAGE->pageId + j;
				n->next = NULL;
				pAGE->list = n;
				}
			else {
				node *tmp = pAGE->list;
				while(tmp->next != NULL ) {
					tmp = tmp->next;
					}
				node *n = (node *)malloc(sizeof(node));
				tmp->next = n;
				n->data = 1000 + 4*pAGE->pageId +j;
				n->next = NULL;
				}
			}
      }
//create page
page* createPage(int id){
     page *pAGE = (page *)malloc(sizeof(page));
     pAGE->pageId = id;
     pAGE->list   = NULL;
     createNodes(pAGE);
     pAGE->next = NULL;
     return pAGE;
 }
// Page Table Entry -> page NO , Frame , Flag   
void createPageTableEntry(int pageID,pageFrame* pFrame,int flag){
      if(headPTE == NULL ){
			 pageTableEntry *pte = (pageTableEntry *)malloc(sizeof(pageTableEntry));
			 pte->next = NULL;
			 pte->flag = flag;
			 pte->frame = pFrame;
			 pte->pageID = pageID;
			 headPTE = pte;
			 }
		else {
			 pageTableEntry *tmp = headPTE;
			 while(tmp->next != NULL) tmp = tmp->next;
			 pageTableEntry *PTE = (pageTableEntry *)malloc(sizeof(pageTableEntry));
			 PTE->flag = flag;
			 PTE->frame = pFrame;
			 PTE->next = NULL;
			 PTE->pageID = pageID;
			 tmp->next = PTE;
			}                      
 } 
 // pageTable with 10 pageTableEntries
void createPageTable(int id){
   int i;
   for(i=0;i<NUM_OF_PAGETABLEENTRIES;++i) createPageTableEntry(10*id+i,NULL,0);
          if(headPT == NULL ) {
				 pageTable *pt = (pageTable *)malloc(sizeof(pageTable));
				 pt->id  = id;
				 pt->list = headPTE;
				 pt->next = NULL;
				 headPT=pt;
				 headPTE = NULL;
				 }
			 else{
				 pageTable *tmp = headPT;
				 while(tmp->next != NULL) {
					 tmp = tmp->next;
					 }
				 pageTable *PT = (pageTable *)malloc(sizeof(pageTable));
				 PT->id = id;
				 PT->list = headPTE;
				 PT->next = NULL;
				 tmp->next = PT;
				 headPTE = NULL;
				 }
}

void initPaging(){
     int i;
     headP = NULL;
     headPT = NULL;
     headPD = NULL;
//creating pages .
     for(i=0;i<NUM_OF_PAGES;++i){
          if(headP == NULL ) headP = createPage(i);
		  else {
			 page *tmp_p = headP;
			 while(tmp_p->next != NULL ) tmp_p = tmp_p->next;
			 tmp_p->next = createPage(i);
			 }
    }
//creating pageTables
     for(i=0;i<NUM_OF_PAGETABLES;++i){
       createPageTable(i);
     }
//creating pageDirectory
   pageDirectory *PD = (pageDirectory *)malloc(sizeof(pageDirectory));
   PD->list = headPT;
   headPD = PD;
}

page* pageFromPageId(int id){
     page *found = NULL;
	 page *tmp = headP;
	 while(tmp != NULL ){
		 if(tmp->pageId == id ){
			 found = tmp;
			 break;
			 }
		 else {
			 tmp = tmp->next;
			 }
	  }
	 return found;
      }

int checkPageLoaded(page* pAGE){
    int PTid = pAGE->pageId/10;
    pageTable *tmp_PT = headPT;
    while(tmp_PT->id != PTid) tmp_PT = tmp_PT->next;
    pageTableEntry *tmp_PTE = tmp_PT->list;
    while(tmp_PTE->pageID != pAGE->pageId ) tmp_PTE = tmp_PTE->next;
    return tmp_PTE->flag;
    }

page* findPage(int no){
	 page *found = NULL;
	 page *tmp = headP;
	 while(tmp != NULL ){
		 if(tmp->pageId == no ){
			 found = tmp;
			 break;
			 }
		 else {
			 tmp = tmp->next;
			 }
	  }
	 return found;
  }
