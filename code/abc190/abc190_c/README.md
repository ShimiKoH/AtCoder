## [AtCoder Beginner Contest 190_C Bowls and Dishes](https://atcoder.jp/contests/abc190/tasks/abc190_c)

<!-- <details> -->
<summary><b>問題を確認</b></summary>

## 問題
$1,2,\dots,N$ の番号が付いた $N$ 個の皿と、$1,2,\dots,M$の番号が付いた $M$ 個の条件がある。条件 $i$ は、皿$A_i$ と皿 $B_i$ の両方にボールが($1$個以上)置かれているときに満たされる。
$1,2,\dots,K$ の番号が付いた $K$ 人の人がいて、人 $i$ は皿 $C_i$ か皿 $D_i$ のどちらか一方にボールを置く。
満たされる条件の個数は最大でいくつか。

## 制約
- 入力はすべて整数
- $2 \leqq N \leqq 100$
- $1 \leqq M \leqq 100$
- $1 \leqq A_i \lt B_i \leqq 100$
- $1 \leqq K \leqq 16$
- $1 \leqq C_i \lt D_i \leqq N$

## 入力
入力は以下の形式で標準入力から与えられる
```math
\begin{array}{c c}
N & M & \\
A_1 & B_1 & \\
\vdots & & \\
A_M & B_M & \\
K & & \\
C_1 & D_1 & \\
\vdots & & \\
C_K & D_K & \\
\end{array}
```

## 出力
答えを出力せよ。