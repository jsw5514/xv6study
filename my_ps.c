//my_ps.c
#include "types.h"
#include "defs.h"
#include "param.h"
/*
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
*/
//#include "proc.c"
enum procstate {UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE};
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  int pid;                     // Process ID
  struct proc *parent;         // Parent process
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)
};
extern struct proc* find_running_proc(int);

int my_ps(void){
  struct proc* p;
  int i;
  const char* state;
  cprintf("    PID    NAME     STATE\n");
  for(i=0;i<NPROC;i++){
    p=find_running_proc(i);
    switch(p->state){
    case UNUSED:
      state="UNUSED";
      break;
    case EMBRYO:
      state="EMBRYO";
      break;
    case SLEEPING:
      state="SLEEPING";
      break;
    case RUNNABLE:
      state="RUNNABLE";
      break;
    case RUNNING:
      state="RUNNING";
      break;
    case ZOMBIE:
      state="ZOMBIE";
      break;
    default:
      state="INVALID";
    }
    if(p!=0 && p->state!=UNUSED)//found process
      cprintf("    %d    %s      %s\n",p->pid,p->name,state);
    else if(p->state==UNUSED)  //found unused space
      continue;
    else                      //searched all
      break;
  }
  //cprintf("\ntest output\n");
  return 0;
}

int sys_my_ps(void){
  return my_ps();
}
