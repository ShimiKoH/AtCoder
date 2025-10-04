## [AtCoder Beginner Contest009_D 漸化式](https://atcoder.jp/contests/abc009/tasks/abc009_4)

## 問題
数列 $A$ は全ての要素が $32$ ビットの符号なし整数で表現でき、その値は次のようにして決まる。
- 初めの $K$ 項 $A_1, A_2, \cdots , A_K$ は入力で与えられる。
- $A$ とは別に $K$ 項の数列 $C_1, C_2, \cdots , C_K$ (こちらもすべての要素が $32$ ビットの符号なし整数に収まる)が入力で与えられ、 $K + 1$ 項目以降の $A$ の値はこの $C$ を用いて次のように計算される。
    - $N \leqq 1$ に対し $A_{N + K} = (C_1 \ \mathrm{AND} \ A_{N + K - 1}) \ \mathrm{XOR} \ (C_2 \ \mathrm{AND} \ A_{N + K - 2}) \ \mathrm{XOR} \ \cdots \ \mathrm{XOR} \ (C_K \ \mathrm{AND} \ A_N)$
    - ただし、 $\mathrm{AND}$ はビットごとの論理積、 $\mathrm{XOR}$ はビットごとの排他的論理和を表す。

この数列 $A$ の $M$ 番目の値 $A_M$ を求めるプログラムを作成せよ。

## 入力
入力は以下の形式で標準入力から与えられる。

$$
\begin{matrix}
K & M &\\
A_1 & A_2 & \cdots & A_K & \\
C_1 & C_2 & \cdots & C_K & \\
\end{matrix}
$$

- $1$ 行目には、はじめに決まっている項の数を表す整数 $K(1 \leqq K \leqq 100)$ および数列の求める項の番号を表す整数 $M(1 \leqq M \leqq 10^9)$ が与えられる。
- $2$ 行目には、数列 $A$ の最初の $K$ 項が与えられる。 $A$ の値は全て $32$ ビット符号なし整数に収まる。
- $2$ 行目には、数列 $A$ の $K + 1$ 項目以降を計算するときに使う数列 $C$ の要素が順に与えられる。 $C$ の値は全て $32$ ビット符号なし整数に収まる。

## 出力
$A_M$ の値を $1$ 行に出力せよ。
出力の末尾にも改行を入れること。

## 解き方
長さ $K$ の数列 $A$ および 数列 $C$ をもとに $A_{K+1}$ を求める計算は、計算量 $\mathcal{O}(K)$ を必要とするので、愚直に求める方法は $\mathcal{O}(KM)$ で遅い。  

ここで、 $A_{N + K}$ を求めるプロセスを考えると、毎回末尾の $K$ 項のみ用いて、数列 $A$ のそれ以前の項は全く使わないことが分かる。

$$
\begin{align*}
& \begin{pmatrix}
    A_1 & A_2 & \cdots & A_K
\end{pmatrix} 
& \bigstar \mathbb{M} & =
\begin{pmatrix}
    A_2 & A_3 & \cdots & A_{K + 1}
\end{pmatrix}
\\
& \begin{pmatrix}
    A_2 & A_3 & \cdots & A_{K + 1}
\end{pmatrix}
& \bigstar \mathbb{M} & = 
\begin{pmatrix}
    A_3 & A_4 & \cdots & A_{K + 2}
\end{pmatrix} \\
& & \vdots \\
& \begin{pmatrix}
    A_N & A_{N + 1} & \cdots & A_{N + K - 1}
\end{pmatrix}
& \bigstar \mathbb{M} & = 
\begin{pmatrix}
    A_{N + 1} & A_{N + 2} & \cdots & A_{N + K}
\end{pmatrix} \\
\end{align*} \\
$$

上記の $\mathbb{M}$ を考える際に肝心なこととして、  
$\mathrm{AND}$ 演算や $\mathrm{XOR}$ 演算は
- 加法乗法のように交換法則や結合法則が成立する
- それぞれ単位元が存在する ( $\mathrm{AND}$ は $1(2^k-1)$ 、 $\mathrm{XOR}$ は $0$ )

仮に、 $\mathrm{AND}$ 演算子を乗法、 $\mathrm{XOR}$ 演算子を加法とみなすと、

$$
\mathbb{M} =
\begin{pmatrix}
    0 & 0 & \cdots & 0 & C_K \\
    1 & 0 & \cdots & 0 & C_{K - 1} \\
    0 & 1 & \cdots & 0 & C_{K - 2} \\
    \vdots & \vdots & \ddots & \vdots & \vdots \\
    0 & 0 & \cdots & 1 & C_1
\end{pmatrix}
$$

である。これをもとのビット演算子に戻すと、すべての値は $32$ ビットに収まることを考え、

$$
\mathbb{M} =
\begin{pmatrix}
    0 & 0 & \cdots & 0 & C_K \\
    e & 0 & \cdots & 0 & C_{K - 1} \\
    0 & e & \cdots & 0 & C_{K - 2} \\
    \vdots & \vdots & \ddots & \vdots & \vdots \\
    0 & 0 & \cdots & e & C_1
\end{pmatrix}
$$

ただし、 $e = 2^{32} - 1$ である。また、

$$
\begin{align*}
& \begin{pmatrix}
    A_1 & A_2 & \cdots & A_K
\end{pmatrix} 
& \bigstar \mathbb{M} \ \bigstar \mathbb{M} \bigstar \cdots \bigstar \mathbb{M} & =
\begin{pmatrix}
    A_{N + 1} & A_{N + 2} & \cdots & A_{N + K}
\end{pmatrix} \\
\end{align*}
$$

のように変換でき、先に $\mathbb{M}$ を $N$ 回掛けておくことで、計算量 $\mathcal{O}(K)$ で $A_{N + K}$ を求めることができる。この $N$ 回掛ける処理は、例えば $100 = 1100100_{(2)}$ を踏まえて、 

$$
\begin{align*}
2^{100} & = 2^{64 + 32 + 4} \\
& = 2^{64} \times 2^{32} \times 2^4
\end{align*}
$$

と、累乗のみを掛けることで、簡略化を図れる。