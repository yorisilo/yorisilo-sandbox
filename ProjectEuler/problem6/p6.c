#include <stdio.h>
#include <math.h>

long int sum_square (int N) {
  int i;
  long int SumSqu = 0;
  for (i = 1; i <= N; i++){
    SumSqu = SumSqu + i*i;
  }
  return SumSqu;
}

long int square_sum (int N) {
  int i;
  long int Sum = 0;
  for (i = 1; i <= N; i++){
    Sum = Sum + i;
  }
  return Sum*Sum;
}

long int square_sum_algo (int N) {
  long int temp = (1 + N)*N/2;
  return temp*temp;
}

int main()
{
  int n;
  printf ("input natural number\n");
  scanf ("%d", &n);
  long int temp;
  temp = sum_square(n) - square_sum_algo(n);
  if (temp<0) {
    temp = -temp;
  }

  printf ("%ld\n",temp);
  return 0;
}
