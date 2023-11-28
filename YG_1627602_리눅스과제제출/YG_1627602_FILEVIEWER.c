#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SEM_KEY 7000
#define NUM_SEM 1
#define MAX_BUF 128
#define SEMA_KEY 7000

static int init_semaphore(void)
{
	key_t key = SEMA_KEY;
	int semid;
	semid = semget(key, NUM_SEM, IPC_CREAT | 0666);
	if (semid == -1) {
		perror("semget()");
		return -1;
	}

	return semid;
}
static int sem_sysv_init(int sem_id)
{
  int ret;
	ret = semctl(sem_id, 0, SETVAL, 1);	/* binary semaphore */
  if (ret == -1)
  {
    perror("semctl");
    return -1;
  }
	return 0;
}
static int sem_sysv_get(int sem_id)
{
	struct sembuf buf;
  printf("잘잠겼나?\n");
	memset(&buf, 0, sizeof(buf));
	buf.sem_op = -1;
	semop(sem_id, &buf, 1);

	return 0;
}
static int sem_sysv_release(int sem_id)
{
	struct sembuf buf;
  printf("잘풀렸나?\n");
	memset(&buf, 0, sizeof(buf));
	buf.sem_op = 1;
	semop(sem_id, &buf, 1);

	return 0;
}

int main(int argc, char *argv[]) {
  int sem_id, file_fd;

  sem_id = init_semaphore();

  sem_sysv_init(sem_id);

  // 세마포어 락
  sem_sysv_get(sem_id);

  // 파일 열기
  if ((file_fd = open("log.txt", O_RDONLY)) == -1) {
    perror("open");
    return -1;
  }

  // 파일 읽기 및 출력
  char imsi[MAX_BUF];
  int n;
  while ((n = read(file_fd, imsi, sizeof(imsi))) > 0) {
      write(STDOUT_FILENO, imsi, n);
  }

  // 파일 삭제
  if (unlink("log.txt") == -1) {
      perror("unlink");
      return -1;
  }

  // 세마포어 언락
  sem_sysv_release(sem_id);

  // 파일과 세마포어 닫기
  close(file_fd);
  semctl(sem_id, 0, IPC_RMID);

  return 0;
}