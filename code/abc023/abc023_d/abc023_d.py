from sys import stdin
from math import floor

class shooting:
    def __init__(self) -> None:
        items = [list(map(int, t.split())) for t in stdin.readlines()]
        self.N = items[0][0]
        self.target = items[1:self.N+1]

    def main(self):
        left = -1
        right = 1E15
        while right-left>1:
            middle = (left+right)//2
            print("[", left, middle, right, "]")
            result = self.judge(middle)
            if result:
                print(True)
                right = middle
            else:
                print(False)
                left = middle
            print("---------------")
        print(int(right))

    
    def judge(self, maximum)->bool:
        count = [0]*(self.N+1)
        for h,s in self.target:
            t = min(floor((maximum-h)/s), self.N)
            print("\th = ", h)
            print("\ts = ", s)
            print("\tt = ", t)
            if t<0:
              return False
            else:
              count[t]+=1

        i=0
        for ci,c in enumerate(count):
            i += c
            if i > ci + 1:
                return False
            # for _ in range(c):
            #     if i>ci:
            #         return False
            #     i+=1
        
        return True

if __name__ == "__main__":
    s = shooting()
    s.main()