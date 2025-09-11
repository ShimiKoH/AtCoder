<script async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.0/MathJax.js?config=TeX-AMS_CHTML"></script>
<!--<script src="https://cdnjs.cloudflare.com/ajax/libs/flowchart/1.18.0/flowchart.js" integrity="sha512-JR6IBB/IsR4q1zQjkrGqJsxF3e+C6iMitbWi4kh8x8Fr5L60c6WOWEiDfpDd6cBHMjjwt/oUotfjmlEvFApXsg==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>-->
<script src = "C:\Users\user\Downloads\flowchart.js"></script>


# 解き方
愚直にやるのであれば、すべての的を $1$ 秒ずつ進めて、毎時刻に次の $1$ 秒で高さが最も高くなる的を撃つ。
この方法では、的を進めるのに $O(N)$ 、撃ち切るまで $O(N)$ で最低 $O(N^2)$ の計算量となる。
<br>
問われているのは、ある順番で打った時のペナルティの最大値を、できるだけ小さくする方法である。
言い換えれば、ある点数 $P$ に対して、どんな順番で撃っても、そのペナルティが $P$ 以下となる$P$の中で、もっとも小さいものを探す、**判定問題**である。
<br>
また、この $P$ の存在し得る区間は限定されている(特定の開区間または閉区間の中にある)ので、**二分探索法**が使える。
<br>
<br>
では、この判定方法はどうすればよいか。
<br>
ある的 $Target_i$ について、初期高度 $H_i$ 、上昇度 $S_i$ が与えられている。
この的を撃つ時刻を $t$ としたとき、そのペナルティ $p_i(t)$ は、 
```math 
p_i(t) = H_i + S_i \times t 
```
で表される。 $p_i(t)$ が条件「 $p_i(t)$ は $P$ 以下である 」 を満たすためには、
<br>
```math
\begin{align*}
p_i(t) & \le P \\
H_i + S_i \times t & \le P \\
S_i \times t & \le P - H_i \\
t & \le \frac{P - H_i}{S_i} \\
\end{align*}
```
であることが必要十分条件である。これはいかなる $i$ でも成立する。
<br>
ガウス記号 $[ a ]$ を、「 $a$ を超えない最大の整数 」と定義し、
```math
t_i = \frac{P - H_i}{S_i}
```
とおく。
すべての $Target_i$ は $t_i{\sec}$以内に撃つ必要がある。
<br>
これで判定の基準が、
<br>
「すべての的が **毎秒かぶることなく** かつ **$t_i{\sec}$以内に撃つ** ことができるか」
<br>
に定まった。この「**毎秒かぶることなく**」という部分が、ややこしい。
<br>
例えば、$t_i = 0$ なるような $t$ が2個以上ある場合は解として不適である。
「**毎秒かぶることなく**」とは言い換えれば、 「 $j\sec$ 以内に撃つべき的の総数が $j+1$ を超えない」ということである。
<br>
そこで、配列 $array$ を用意する。この配列の要素 $array[j]$ は、$j\sec$ 以内に撃つ必要のある的の数である。これをすべての的において集計し、 $array$ の累積和を考えることで、与えられた $P$ が諸々の条件を満たすか判定することができるのである。

<br>

## 二分探索についてちょっと一言
二分探索では昇順または降順に並んだ、ある区間内に求めたい解があることがわかっているとき、探索範囲を半分に絞ったとき、その中にあるのか、もう一つの方にあるのか判定し、それを繰り返すことによって範囲を狭めていき解を得る方法である。
<br>
例えば、以下の昇順の数列において、最初に $10$ を超える数を求めることを考える。
```math
\begin{array}{c|cccccccccccc}
index & 0 & 1 & 2 & 3 & 4 & 5 &  6 &  7 &  8 &  9 & 10 &  11 & \\
\hline
value & 1 & 1 & 2 & 3 & 5 & 8 & 13 & 21 & 34 & 55 & 89 & 144 & \\
\end{array}
```
ここではインデックス値について範囲を狭めていく。
<br>
まず、両端の平均値である $5.5$ を切り捨てたインデックス $5$ を判定する。
<br>
$8 < 10$ であり、 $8$ は絶対に解にはならないため、解はインデックス $6$ 以降に存在するといえる。
```math
\begin{array}{c|cccccccccccc}
index & \sout{0} & \sout{1} & \sout{2} & \sout{3} & \sout{4} & \sout{5} &  6 &  7 &  8 &  9 & 10 &  11 & \\
\hline
value & \sout{1} & \sout{1} & \sout{2} & \sout{3} & \sout{5} & \sout{8} & 13 & 21 & 34 & 55 & 89 & 144 & \\
\end{array}
```
同様に両端の平均値 $8.5$ の切り捨てインデックス $8$ を判定する。
$34 > 10$ ではあるが、もし $11,12,\cdots,33$ が存在しないのであれば、解になりうるので、今回はインデックス $8$ を含め、 $8$ 以前に存在するといえる。
```math
\begin{array}{c|cccccccccccc}
index & \sout{0} & \sout{1} & \sout{2} & \sout{3} & \sout{4} & \sout{5} &  6 &  7 &  8 &  \sout{9} & \sout{10} &  \sout{11} & \\
\hline
value & \sout{1} & \sout{1} & \sout{2} & \sout{3} & \sout{5} & \sout{8} & 13 & 21 & 34 & \sout{55} & \sout{89} & \sout{144} & \\
\end{array}
```
残る配列幅は $3$ である。インデックス平均値は $7$ であり、その値 $21$ は $ 21 > 10 $ を満たすので、解はインデックス $7$ 以下にある。
```math
\begin{array}{c|cccccccccccc}
index & \sout{0} & \sout{1} & \sout{2} & \sout{3} & \sout{4} & \sout{5} &  6 &  7 &  \sout{8} &  \sout{9} & \sout{10} &  \sout{11} & \\
\hline
value & \sout{1} & \sout{1} & \sout{2} & \sout{3} & \sout{5} & \sout{8} & 13 & 21 & \sout{34} & \sout{55} & \sout{89} & \sout{144} & \\
\end{array}
```
配列幅 $2$ になった。同様にするとインデックス $7$ が消える。
```math
\begin{array}{c|cccccccccccc}
index & \sout{0} & \sout{1} & \sout{2} & \sout{3} & \sout{4} & \sout{5} &  6 &  \sout{7} &  \sout{8} &  \sout{9} & \sout{10} &  \sout{11} & \\
\hline
value & \sout{1} & \sout{1} & \sout{2} & \sout{3} & \sout{5} & \sout{8} & 13 & \sout{21} & \sout{34} & \sout{55} & \sout{89} & \sout{144} & \\
\end{array}
```
ここで **半開区間** について考える。
<br>
半開区間とは一方が開区間でもう一方が閉区間であるような区間のことで、
```math
(a, b] \\ [a, b)
```
のようにあらわされる。$[ \ ]$ は閉区間、$( \ )$ は開区間である。先ほどの例では、falseを返すようなインデックスには$ +1 $ または $-1$ をすることで、範囲を狭めていたが、この方法は直観的ではない。しかし、半開区間であれば、
```math
\begin{array}{c c c c c}
[0, 11] & [6, 11] & [6, 8] & [6, 7] & [6, 6] & \\
\hline
(-1, 11] & (5, 11] & (5, 8] & (5, 7] & (5, 6] & \\ 
\end{array}
```
このように平均値(切り捨て)をそのまま区間の端に設定できるのが強み。最終的に幅 $2$ に見えるが、左開区間は $5$ を含まない範囲なので、実質 $6$ のみである。開区間は解になり得ない端なので、初期設定で配列の外側を設定する必要があるが、代入は直観的になる。

<br>

# 実装


```flow
st=>start: 処理開始
e=>end: 処理終了
io1=>inputoutput: データ入力
cond=>condition: 入力値が空
でない？
io2=>inputoutput: エラー出力
（※1）:>#footnote
sub1=>subroutine: 入力値の検証
（※2）:>http://www.google.com[blank]
op1=>operation: セッション開始

st->io1->cond
cond(yes)->sub1->op1->e
cond(no)->io2(right)->io1
```