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
//lab1

  int status;
  if(argint(0,&status)<0){
	return -1;
  }
  exit(status);
  return 0;  // not reached
}
//lab1
int
sys_wait(void)
{
  char* status;
  if(argptr(0,&status,4)< 0){
    return -1;
  }
  return wait((int*)status);
}

//lab1
int
sys_waitpid(void){
  int pid;
  char* temp;
  int options;
  if(argint(0,&pid)< 0 || argptr(1,&temp,4) < 0 || argint(0, &options) < 0){
     return -1;
  }
  return waitpid(pid,(int*)temp,options);	
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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

//I added this part
int 
sys_switch_priority(void){
  int n;
  if(argint(0, &n)<0){
    return -1;
  }
 switch_priority(n);
 return 0;
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
    if(proc->killed){
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
