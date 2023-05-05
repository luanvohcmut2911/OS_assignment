#ifndef OSMM_H
#define OSMM_H

#define MM_PAGING
#define PAGING_MAX_MMSWP 4 /* max number of supported swapped space */
#define PAGING_MAX_SYMTBL_SZ 30

typedef char BYTE;
typedef uint32_t addr_t;
//typedef unsigned int uint32_t;

struct pgn_t{     //
   int pgn;
   struct pgn_t *pg_next; 
};

/*
 *  Memory region struct
 MEMORY_MANAGEMENT ---> VIRTUAL_MEM_AREA + LIST_OF_REGIONS + LIST_OF_FREE_PAGES
 */
struct vm_rg_struct {   //virtual memory region
   unsigned long rg_start;
   unsigned long rg_end;

   struct vm_rg_struct *rg_next;
};

/*
 *  Memory area struct
 virtual memory space is organized as a memory mapping for each process PCB. 
 From the process point of view: 
 * the virtual address includes multiple vm areas (contiguously)
 * vm areas consist of many virtual memory region
 */
struct vm_area_struct {
   unsigned long vm_id;
   unsigned long vm_start; //Memory Area: Each memory area ranges continuously in [vm start,vm end]
   unsigned long vm_end;

   unsigned long sbrk;  //The actual usable area
/*
 * Derived field
 * unsigned long vm_limit = vm_end - vm_start
 */
   struct mm_struct *vm_mm;
   struct vm_rg_struct *vm_freerg_list;   //virtual FREE memory region (free slots tracking)
   struct vm_area_struct *vm_next;     //Pointer to the next vm_area, for future set tracking
};

/* 
 * Memory management struct
 */
struct mm_struct {
   uint32_t *pgd; //Page table directory, contains all page table entries
   //* Each entry is a map between page number and the frame number in the paging mem management system.


   struct vm_area_struct *mmap;  

   /* Currently we support a fixed number of symbol 
   !We temporarily imagine these regions as a set of limit number of region. We manage them by using an array of symrgtbl[PAGING MAX SYMTBL SZ].
   */
   struct vm_rg_struct symrgtbl[PAGING_MAX_SYMTBL_SZ];   
   //?PAGING_MAX_SYMTBL_SZ: Paging Max Symbol Table Size (i'm so tired of this type of abbreviation)
   //?symrgtbl = symbol region table

   /* list of free page */
   struct pgn_t *fifo_pgn; //![JUST LEFT IT THERE] mainly used to keep track of a specific user operation (caller, fifo page...) [jor refs]
};

/*
 * FRAME/MEM PHY struct
 */
struct framephy_struct { 
   int fpn;
   struct framephy_struct *fp_next;

   /* Resereed for tracking allocated framed */
   struct mm_struct* owner;
};

struct memphy_struct {
   /* Basic field of data and size */
   BYTE *storage;
   int maxsz;
   
   /* Sequential device fields */ 
   int rdmflg;
   int cursor;

   /* Management structure */
   struct framephy_struct *free_fp_list;
   struct framephy_struct *used_fp_list;
};

#endif
