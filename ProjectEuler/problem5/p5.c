#include <stdio.h>

long int lcm(long int m, long int n){
  long int temp;
  if (n>m) {
    temp = m;
    m = n;
    n = temp;
  }//m>nが真になるようにする．

  long int gcm=1, N=m;
  long int lcm;
  int k;
  for (k=2; k<=N; k++) {
    while(m%k==0 && n%k==0) {
      m = m/k, n = n/k;
      gcm = gcm*k;
    }
  }
  lcm = gcm*m*n;
  return lcm;
}

int main()
{
  long int n=1;
  int i;
  for (i = 1; i <= 20 ; i++){
    n = lcm(n,i);
  }
  printf ("%ld\n",n);
  return 0;
}
