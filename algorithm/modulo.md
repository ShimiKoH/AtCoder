# 整数問題における剰余計算について
## 整数を巨大な素数で割るときの余り
競技プログラミングではしばしば、本来の数が大きすぎるために、素数で割った際の余りを代わりに扱うことがある。例えば「 $10^9+7$ で割ったあまりを出力せよ」といった具合である。高校数学(数A)では、「合同式」というものを学ぶが、この剰余計算でもこれをうまく使うことで、解を導ける。

## 合同式
軽く合同式について振り返る。ある数 $a$ を $p$ で割ったときの商を $q$ 、剰余を $r$ としたとき、以下の式が成り立つ。

$$
a = p \cdot q + r
$$

合同式はこの $r$ に焦点を当てた式で、以下のようにあらわす。

$$
a \equiv r \quad (\bmod \ p)
$$

このときの $p$ を「法」と呼び、「整数 $a$ と $r$ は法 $p$ に関して合同である」といったような使われ方をする。

### 数値演算
$2$ つの整数 $a_1, a_2$ が 整数 $p$ を法として合同であるとき、新たな整数 $k$ に対して、以下の式が成り立つ。

$$
a_1 \bigstar k \equiv a_2 \bigstar k
$$

演算記号 $\bigstar$ は $+, -, \cdot, \div,$ ^ である(その他の演算についてはここでは考えない)。ただし
- $\div$ の場合は、 $\dfrac{a_1}{k}$ および $\dfrac{a_2}{k}$ がともに整数

$$
\begin{align*}
\alpha \cdot (i \cdot p + j) & \equiv \alpha \cdot (i^{\prime} \cdot p + j^{\prime}) \\
\alpha j & \equiv \alpha j^{\prime} \\
\alpha (j - j^{\prime}) & \equiv 0 \\
\end{align*} \\
\alpha \equiv 0 \ \lor \ j -j^{\prime} \equiv 0 \\
$$

- ^ の場合は、 $k$ は $k \geqq 0$  

であるときのみ、上述の式はすべての $k$ で成り立つ。

ここで、減算は加算に置き換えられるが、除算は乗算に置き換えられるか考える。
つまり、ある数 $A$ に対して、

$$
\frac{A}{n} \equiv A \cdot f(n) \quad (\bmod \ p) \\
$$

を常に満たすような関数 $f(n)$ について考える。
ただし $\dfrac{A}{n}$ は整数、 $A$ と $p$ および $n$ と $p$ はそれぞれ互いに素(共通の素因数を持たない)、 $p$ は $p \gt n$ を満たす素数であるとする。

$$
\begin{align*}
\frac{A}{n} & \equiv A \cdot f(n) \quad \\
\frac{A}{n} \cdot n & \equiv A \cdot f(n) \cdot n \\
A & \equiv A \cdot f(n) \cdot n \\
1 & \equiv f(n) \cdot n \\
\therefore f(n) \cdot n & \equiv 1 \quad (\bmod \ p)\\
\end{align*}
$$

また、 $p = q \cdot n + r \quad (0 \lt r \lt n)$ とすると、

$$
\begin{align*}
p & \equiv 0 \quad (\bmod \ p) \\
q \cdot n + r & \equiv 0 \\
f(n) \cdot (q n + r) & \equiv 0 \\
q(f(n) \cdot n) + r \cdot f(n) & \equiv 0 \\
q + r \cdot f(n) & \equiv 0 \quad (\because f(n) \cdot n \equiv 1) \\
r \cdot f(n) & \equiv -q \\
\end{align*}
$$

ここで、 $0 \lt i \lt n$ を満たす $i$ について、 $f(i)$ が求められていると仮定すると、 $p$ を法とした合同式において、 $r$ で割ることは、 $f(r)$ を掛けることと同値であるから、

$$
\begin{align*}
r \cdot f(n) & \equiv -q \\
f(n) & \equiv -q \cdot f(r) \\
\end{align*}
$$

$f(n)$ は $-q \cdot f(r)$ を $p$ で割った剰余に等しいことが分かった。  
つまり、
1. $f(1)$ が求められる。
2. $1 \leqq i \lt k$ であるすべての $i$ について、 $f(i)$ が求められているならば、 $f(k)$ を求められる。

ので、任意の $f(n)$ は帰納的に求められる。
