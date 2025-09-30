## [abc203_D Pond](https://atcoder.jp/contests/abc203/tasks/abc203_d)

## 問題
AtCoder公園の敷地は東西南北に広がる $N \times N$ のマス目からなっており、北から $i$ 番目かつ西から $j$ 番目のマスの高さは $A_{i,j}$ で与えられる。
公園の管理者である高橋君はここに $K \times K$ の区画の池を作ることにした。
池を作るにあたって、高橋君はAtCoder公園の敷地内に完全にふくまれる $K \times K$ の区画であってその区画に含まれるマスの高さの**中央値**が最も低いようなものを選ぼうと考えた。そのような区画のマスの高さの中央値を求めなさい。
ここで、 $K \times K$ の区画に含まれるマスの高さの中央値とはその区画に含まれる $K^2$ 個のマスのうち	​ $\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ 番目に高いマスの高さを指す。また、$\lfloor x \rfloor$ は $x$ 以下の最大の整数を表す。

## 制約
- $1 \leqq K \leqq N \leqq 800$
- $0 \leqq A_{i,j} \leqq 10^9$
- 入力はすべて整数である

## 入力
入力は以下の形式で標準入力から与えられる
```math
\begin{array}{cccc}
N & K \\
A_{1,1} & A_{1,2} & \cdots & A_{1,N} \\
A_{2,1} & A_{2,2} & \cdots & A_{2,N} \\
\vdots \\
A_{N,1} & A_{N,2} & \cdots & A_{N,N} \\
\end{array}
```

## 出力
答えを出力せよ

***

## 解き方
解の二分探索
すべての $K \times K$ の区画で、高さが任意の数値 $V$ 以上であるマスの数が、$\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ である $V$ のうち、最小のものを探す。
実際の高さが、ボーダー以上の場合は$1$ それ以外は $0$ で $N \times N$ のマスを埋めた配列について考える。
ある $K \times K$ 区画において、
- 中央値が $V$ 以上である
$=$ $V$ 以上の高さの数が $\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ 以上である
$=$ 区画内の数値の総和が $\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ 以上である
- 中央値が $V$ より小さい
$=$ $V$ 以上の高さの数が $\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ 未満である
$=$ 区画内の数値の総和が $\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ 未満である

ことがわかる。$N \times N$ の範囲の探索の結果、
- すべての $K \times K$ 区画で、総和が $\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ 以上の場合、解となる $V_{\mathrm{answer}}$ は、与えられた $V$ 以上である
$\Rightarrow \mathrm{true}$ を返し、より大きい範囲を探す。
- ある $K \times K$ 区画で総和が $\Big\lfloor \frac{K^2}{2} \Big\rfloor + 1$ 未満の場合、解となる $V_{\mathrm{answer}}$ は、与えられた $V$ よりも小さい
$\Rightarrow \mathrm{false}$ を返し、より小さい範囲を探す。

とし、二分探索で、$[\mathrm{judge}(V),\ \mathrm{judge}(V + 1)) \ = \ [\mathrm{true},\ \mathrm{false})$ となる区間を探す。このときの $V$ が $V_{\mathrm{answer}}$ である。

## 計算量
- 二分探索で $\mathcal{O}(\log 1\mathrm{e}9)$ $:$ 定数量
- 累積和配列の生成で $\mathcal{O}(N^2)$
- 累積和配列の走査で $\mathcal{O}((N-K)^2)$
#### 総計算量 
$\mathcal{O}(N^2 + (N-K)^2)$

## コード
### [C++](abc203_d.cpp)
