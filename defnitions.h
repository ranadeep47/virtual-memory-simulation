#ifndef VirtualMemory_H

#define NUM_OF_NODES_PERPAGE 4
#define NUM_OF_NODES 400
#define NUM_OF_PAGES 100
#define NUM_OF_PAGETABLES 10
#define NUM_OF_PAGETABLEENTRIES 10
#define NUM_OF_FRAMES 50
#define NUM_OF_SEGMENTS 10
#define NUM_OF_SEGMENTNODES 40
#define NUM_OF_REFERENCES 100

//Structure defnitions and global variables
typedef struct segmentNode {
        int id;
        char pageDir[5];
        char pageTab[5];
        char pageOff[3];
        struct segmentNode *next;
        }segmentNode;

typedef struct segmentDes{
        int id;
        segmentNode *list;
        struct segmentDes *next;
        }segmentDes;

segmentDes *headSD = NULL;

typedef struct node{
	int data;
   	struct node* next;
	}node;
	
typedef struct page{
	int pageId;
    node *list;
   struct page *next;
	}page;	

page *headP = NULL;

typedef struct pageFrame{
    int frameNo;
    node *list;
    struct pageFrame *next;
}pageFrame;

pageFrame *headPF = NULL;

typedef struct pageFrameDes{
    pageFrame *frame;
	int frameNo;
	int pageId;
	int status;
	struct pageFrameDes *next;
}pageFrameDes;

pageFrameDes *headPFD = NULL;

typedef struct pageTableEntry{
	int pageID;
	int flag;
	pageFrame* frame;
	struct pageTableEntry* next;
	}pageTableEntry;
	
pageTableEntry *headPTE = NULL;

typedef struct pageTable{
	int id;
	pageTableEntry *list;
	struct pageTable *next;
	}pageTable;
	
pageTable *headPT = NULL;
	
typedef struct pageDirectory{
	pageTable *list;
	}pageDirectory;
	
pageDirectory *headPD = NULL;

typedef struct FIFONode{
        pageFrameDes *pfd;
        struct FIFONode *next;
        }FIFONode;

FIFONode *headFIFO = NULL;

typedef struct LRUNode{
        pageFrameDes *pfd;
        struct LRUNode *next;
        struct LRUNode *previous;
        }LRUNode;
LRUNode *headLRU=NULL,*tailLRU=NULL;

//Function Prototypes
           //Utility module's function prototypes
           char* decToBin(int n,int no);
           int binToDec(char *bin,int no);
           int ex2(int n);
           int random_400(void);
           
           //Segmentation module's function prototypes
           void createSegment(int id);
           char* getSegmentSelector(char *logicalAdd);
           char* getSegmentOffset(char *logicalAdd);
           void initSegments(void);
           
           //Paging module's function prototypes
           void createNodes(page* pAGE);
           page* createPage(int id);
           void createPageTableEntry(int pageID,pageFrame* pFrame,int flag);
           void createPageTable(int id);
           page* pageFromPageId(int id);
           void initPaging();
           int checkPageLoaded(page* pAGE);
           char* getPageTable(char *segmentOff);
           char* getPageOffset(char *segmentOff);
           page* findPage(int no);
           
           //Main Memory module's function prototypes
           pageFrame* createFrame(int id,page *pAGE);
           pageFrameDes* createFrameDescriptor(int id,pageFrame *pf,page *pAGE);
           void initFrames();
           void removePageFromFrame(pageFrame *pf);
           void copyPageToFrame(page *pAGE,pageFrame *frame);
           pageFrame* freeFrameAvlbl(void);
           
           //LRU module's function prototypes
           void updateLRUll(page *p);
           void LRUSimulate(int *mem_references,int *pageFaults);
           
           //FIFO module's function prototypes
           void FIFOSimulate(int *references,int *pageFault);
           void updateFIFOll(page *p);
           
#endif
