## [AtCoder Beginner Contest 167_C Skill Up](https://atcoder.jp/contests/abc167/tasks/abc167_c)

<!-- <details> -->
<summary><b>問題を確認</b></summary>

## 問題
競技プログラミングを始めた高橋君は、学びたいアルゴリズムが $M$ 個ある。最初、各アルゴリズムの理解度は $0$ である。
高橋君が書店に行くと、 $N$ 冊の参考書が売っていた。$i$ 番目の参考書 $(1 \leqq i \leqq N)$ は$C_i$ 円で売られていて、購入して読むことで、各 $j(1 \leqq j \leqq M)$ について $j$ 番目のアルゴリズムの理解度が $A_{i,j}$ 上がる。また、それ以外の方法で理解度を上げることはできない。
高橋君の目標は  $M$ 個すべてのアルゴリズムの理解度を $X$ 以上にすることである。高橋君が目標を達成することが可能化を判定し、可能な場合は目標を達成するのに必要な金額の最小値を計算しなさい。

## 制約
- 入力はすべて整数
- $1 \leqq N, M \leqq 12$
- $1 \leqq X \leqq 10^5$
- $1 \leqq C_i \leqq 10^5$
- $0 \leqq A_{i,j} \leqq 10^5$

## 入力
入力は以下の形式で標準入力から与えられる。
```math
\begin{array}{ccccc}
N & M & X & & & \\
C_1 & A_{1,1} & A_{1,2} & \cdots & A_{1,M} & \\
C_2 & A_{2,1} & A_{2,2} & \cdots & A_{2,M} & \\
\vdots & & & & & \\
C_N & A_{N,1} & A_{N,2} & \cdots & A_{N,M} & \\
\end{array}
```

## 出力
高橋君が目標を達成できないならば $-1$ を、そうでなければ目標を達成するのに必要な金額の最小値を出力せよ。

## 解き方
$N$ はそこまで大きくないため、$\text{bit}$ 全探索によって求める。

## 計算量
- $\text{bit}$ 全探索に $\mathcal{O}(2^N)$
- ある $\text{bit}$ について、対応する参考書のスキル計算および判定に $\mathcal{O}(N \times M)$
    #### 総計算量
    $\mathcal{O}(2^N \times (N \times M))$
    最大で $2^{12} \times 12 \times 12 \simeq 6.0 \times 10^6 $ 
    これは十分高速である


## コード
### [C++](abc167_c.cpp)