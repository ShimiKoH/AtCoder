## [AtCoder Begginer Contest 197_C ORXOR](https://atcoder.jp/contests/abc197/tasks/abc197_c)

<details>
<summary><b>問題を確認</b></summary>

## 問題
長さ $N$ の数列 $A$ が与えられる。
この数列を、$1$ つ以上の空でない連続した区分に分ける。
その後、分けた各区間で、区間内の数のビット単位 $\mathrm{OR}$ を計算する。
こうして得られたすべての値のビット単位 $\mathrm{XOR}$ として考えらえる最小値を求めなさい。

<details>
<summary>

ビット単位 $\mathrm{OR}$ 演算とは
</summary>

整数 $A,B$ のビット単位 $\mathrm{OR}$ 、$A \ \mathrm{OR} \ B$ は以下のように定義される。
- $A \ \mathrm{OR} \ B$ を二進表記した際の $2^k(k \geqq 0)$ の位の数は、 $A,B$ を二進表記した際の $2^k$ の位の数のうち少なくとも片方が $1$ であれば $1$、そうでなければ $0$ である。
</details>

<details>
<summary>

ビット単位 $\mathrm{XOR}$ 演算とは</summary>

整数 $A,B$ のビット単位 $\mathrm{XOR}$ 、$A \ \mathrm{XOR} \ B$ は以下のように定義される。
- $A \ \mathrm{XOR} \ B$ を二進表記した際の $2^k(k \geqq 0)$ の位の数は、 $A,B$ を二進表記した際の $2^k$ の位の数のうち一方のみが $1$ であれば $1$、そうでなければ $0$ である。
</details>

## 制約
- $1 \leqq N \leqq 20$
- $0 \leqq A_i \leqq 2^{30}$
- 入力に含まれる値はすべて整数である

## 入力
入力は以下の形式で標準入力から与えられる。
```math
\begin{array}{ccccc}
N & & & & & \\
A_1 & A_2 & A_3 & \cdots & A_N &\\
\end{array}
```

## 出力
答えを出力せよ。
</details>

## 解き方
入力される数列の長さは最大で $N = 20$ であり、そこまで多くはない。
$\mathrm{bit}$ 全探索により、数列と $N$ 桁二進数を対応させ、部分数列を作り出す。
$\mathrm{bit}$ の連続する $0$ とそのあとの $1$ を一括りにして考える。
```math
\begin{array}{c|ccccccccc}
A & A_1 & A_2 & A_3 & A_4 & A_5 & A_6 & A_7 & A_8 & A_9 & \\
binary & 1 & 0 & 0 & 0 & 1 & 1 & 0 & 0 & (1) & \\
\end{array} \\
\Downarrow \\
\begin{array}{c|c|cccc|c|ccc|}
A & A_1 & A_2 & A_3 & A_4 & A_5 & A_6 & A_7 & A_8 & A_9 & \\
binary & 1 & 0 & 0 & 0 & 1 & 1 & 0 & 0 & (1) & \\

\end{array} \\
\Downarrow \\
(A_1) \mathrm{XOR} (A_2 \mathrm{OR} A_3 \mathrm{OR} A_4 \mathrm{XOR} A_5) \mathrm{XOR} (A_6) \mathrm{XOR} (A_7 \mathrm{OR} A_8 \mathrm{OR} A_9)
```
