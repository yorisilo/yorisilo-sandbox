# problem5 #
http://odz.sakura.ne.jp/projecteuler/index.php?cmd=read&page=Problem%205

## メモ ##
### 最大公約数の求め方 ###

    long int g(long int m, long int n){
      long int temp;
      if (n>m) {
        temp = m;
        m = n;
        n = temp;
      }//m>nが真になるようにする．

      long int gcm=1, N=m;
      int k;
      for (k=2; k<=N; k++){
        while(m%k==0 && n%k==0) {
          m = m/k, n = n/k;
          gcm = gcm*k;
        }
      }
      return gcm;
    }

最大公約数を求めるときに例えば，割る数iが3から3へいくパターンはあり得るが，割る数iが7から3へ減るパターン，はありえないのでこれで良い．つまりiは同じか増えるかでしかない．公約数の定義より証明可能．というか自明だなこれは．例えば，ある数を何で割るか調べるときに，割る数を2から順々に増やして調べて行って，7で初めて割りきれたとすると，ある数を7で割ったものが3で割り切れるとかはありえない．いやなんか直感的にはそういうことなんだけど，これは自明と片付けても良いのだろうか．ふむ．ある数の素因数分解を考えてやれば，分かりやすいか．もしありえるかもしれない！とか思ったら，割った数に対してiをもう一度2から順々に増やして割り切れるまで調べれば良い．そして，それを繰り返してやればおｋ．
こんな感じで．

    long int g(long int m, long int n) {
      long int temp;
      if (n>m) {
        temp = m;
        m = n;
        n = temp;
      }//m>nが真になるようにする．
      long int gcm=1, N=m;
      int k,i = 2;
      for(k=2;k<=N;k++){
        for (i = 2; i < N; i++){
          if (m%i==0 && n%i==0) {
            m = m/i, n = n/i;
            gcm = gcm*i;
          }
        }
      }
      return gcm;
    }

まあありえないんだけどもさ．．．

### 最小公倍数 ###
それから最小公倍数は

    lcm = gcm*m*n;

で求めることができる．

この最小公倍数の求め方は効率が悪いので，ユークリッドの互除法とやらを使うと良いっぽい．

[参照URL](http://bach.istc.kobe-u.ac.jp/lect/ProLang/org/euler-005.html#sec-2)

でもとりあえず，最初に思いついたもので解いた．
## 道筋 ##

1から20の最小公倍数を求めていく．

1と1の最小公倍数は？ 1

1と2の最小公倍数は？ 2

2と3の最小公倍数は？ 6

6と4の最小公倍数は？ 12

．．．みたいな感じでやっていけばおｋ．
