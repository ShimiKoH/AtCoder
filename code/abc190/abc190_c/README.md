## [AtCoder Beginner Contest 190_C Bowls and Dishes](https://atcoder.jp/contests/abc190/tasks/abc190_c)

<details>
<summary><b>問題を確認</b></summary>

## 問題
$1,2,\dots,N$ の番号が付いた $N$ 個の皿と、$1,2,\dots,M$の番号が付いた $M$ 個の条件がある。条件 $i$ は、皿$A_i$ と皿 $B_i$ の両方にボールが($1$個以上)置かれているときに満たされる。
$1,2,\dots,K$ の番号が付いた $K$ 人の人がいて、人 $i$ は皿 $C_i$ か皿 $D_i$ のどちらか一方にボールを置く。
満たされる条件の個数は最大でいくつか。

## 制約
- 入力はすべて整数
- $2 \leqq N \leqq 100$
- $1 \leqq M \leqq 100$
- $1 \leqq A_i \lt B_i \leqq N$
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

</details>

## 解き方
この問題では、$K$ の最大値が $16$ と大きくないので、$\mathrm{bit}$ 全探索が可能である。
$16$ 桁の 二進数と、$K$ 人の人が球を置く皿を対応させる。
- $t$ 桁目が $0$ のとき、皿 $C_i$ に置く
- $t$ 桁目が $1$ のとき、皿 $D_i$ に置く
また皿に球が置いてある状態を $1$ 、置いていない状態を $0$ とし、ビット和によって求める。

## 計算量
- $\mathrm{bit}$ 全探索で $\mathcal{O}(2^K) \leqq \mathcal{O}(2^{16})$
- ある $16$ 桁の二進数に基づいて、
    - ボールの配置に $\mathcal{O}(16)$ で定数
    - 条件の精査に $\mathcal{O}(M)$

より、全体の計算量オーダーは $\mathcal{O}(2^K \cdot M)$


## コード
### [C++](abc190_c.cpp)