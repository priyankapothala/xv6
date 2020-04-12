#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_hello(void){
  print_hello();
  return 0;
}

int sys_info(void){
  int param;
  argint(0, &param); //argint is used to retrieve system call's nth integer argument

  struct proc *curproc = myproc();
  if (param == 1)
  {
    cprintf("Number of processes: %d\n", info(param));
  }
  else if(param == 2)
  {
    cprintf("The total number of system calls that the current process has made so far: %d\n", curproc->num_sys_calls);
  }
  else if(param == 3)
  {
    cprintf("The number of memory pages the current process is using: %d\n", (int)(curproc->sz)/PGSIZE);
  }
  else
  {
    cprintf("Invalid parameter value\n");
    return -1;
  }
  return 0;
}
