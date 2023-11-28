#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// 쓰레드 함수
int n_do_proc = 0;
void *t_function(void *data)
{    
  int id, i = 0;    
  id = *((int *)data);   
  while(1) {   
    if(n_do_proc == 0) { continue; }
    printf("%d : %d\n", id, i);   
    i++; 
    if(i > 1000) { break; }
  }
  return NULL;
}

int main() {    
  pthread_t p_thread[2];    
   int thr_id;    
  int status;   
  int a = 1;    
  int b = 2;    
  // 쓰레드 생성 시 인수 1 을 넘긴다.      
  thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);    
  if (thr_id < 0) {        
    perror("thread create error : ");  exit(0);    
  }    
  // 쓰레드 생성 시 인수 2 를 넘긴다.     
  thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&b);    
  if (thr_id < 0) {        
    perror("thread create error : ");  exit(0);    
  }    
  sleep(1);
  n_do_proc = 1;
  // 쓰레드 종료를 기다린다.     
  pthread_join(p_thread[0], (void **)&status); 
  pthread_join(p_thread[1], (void **)&status);    
  return 0;
}
