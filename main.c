#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//gdb fork test
#include <sys/types.h>
#include <unistd.h>

#include <dlfcn.h>

int sum(int *arr, int n);

int *getPrimes(int n);

int isPrime(int x);

//gdb 断点调试子进程
void forkexample()
{
  printf("enter forkexample!\n");
  int pid;
  if ((pid = fork()) == 0) //子进程断点调试需要设置-gdb-set follow-fork-mode child
  {
    printf("Hello from Child(pid=%d)!\n", getpid());

    //测试子进程加载so库gdb是否可以设置断点
    loadAndCallSoFile(100 , 120);
  }
  else
    printf("Hello from Parent(pid=%d)!\n", getpid());

  printf("leave forkexample!\n");
}

void loadAndCallSoFile(int x, int y)
{
  void *pHandler = NULL;
  char *pErr = NULL;
  int (*pSum)(int x, int y);

  pHandler = dlopen("./lib/libtest.so", RTLD_LAZY);

  pErr = dlerror();
  if (!pHandler || pErr != NULL)
  {
    printf("Failed load library!\n%s\n", pErr);
    return -1;
  }

  pSum = dlsym(pHandler, "so_func_sum");
  pErr = dlerror();
  if (!pSum || pErr != NULL)
  {
    printf("%s\n", pErr);
    return -1;
  }

  // 调用StrLen函数
  printf("%d + %d =%d\n", x, y, pSum(x, y));
}

int main(int argc, char **argv)
{

  int n = 10; //default to the first 10 primes
  if (argc == 2)
  {
    n = atoi(argv[1]);
  }
  int *primes = getPrimes(n);

  //主进程动态加载so文件,可以设置断点调试
  loadAndCallSoFile(5 , 7);

  //测试多进程gdb是否可以设置断点
  forkexample();
 

  int s = sum(primes, n);
  printf("The sum of the first %d primes is %d\n", n, s);

  return 0;
}

int sum(int *arr, int n)
{
  int i;
  int total = 0;
  for (i = 0; i < n; i++)
  {
    total += arr[i];
  }
  return total;
}

int *getPrimes(int n)
{
  int *result = (int *)malloc(sizeof(int) * n);
  result[0] = 2;
  int i = 1;
  int x = 3;
  while (i < n)
  {
    if (isPrime(x))
    {
      result[i] = x;
      i++;
    }
    x += 2;
  }
  return result;
}

int isPrime(int x)
{

  if (x < 2)
  {
    return 0;
  }
  else if (x == 2)
  {
    return 1;
  }
  else if (x % 2 == 0)
  {
    return 0;
  }
  for (int i = 3; i <= sqrt(x); i += 2)
  {
    if (x % i == 0)
    {
      return 0;
    }
  }
  return 1;
}
