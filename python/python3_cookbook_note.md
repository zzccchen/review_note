# 《Python Cookbook》3rd Edition 读书笔记

Python Cookbook, 3rd edition, by David Beazley and Brian K. Jones (O’Reilly). Copyright 2013 David Beazley and Brian Jones, 978-1-449-34037-7.

[中文翻译](http://python3-cookbook.readthedocs.io/zh_CN/latest/index.html) 译者： 熊能

## 第一章

### 1.1 解压序列赋值给多个变量

e.g.

```python
p = (4, 5)
x, y = p
```

任何的**可迭代对象**（如：列表、元组、字符串、文件对象、迭代器和生成器）可以 **通过一个赋值语句解压并赋值给多个变量**。 唯一的前提就是变量的数量必须跟序列元素的数量是一样的。

如果变量个数和序列元素的个数不匹配，会产生一个异常 `ValueError` 。

如需丢弃其他的值，可以使用任意变量名如：`_` 或 `ign` (ignore) 去占位。

### 1.2 解压可迭代对象赋值给多个变量

**用星号表达式解决个数不匹配问题**。`*` 提取的变量永远都是 **列表类型**。

e.g.

分离首位值和末位值：`first, *middle, last = grades`
分离首位值和第二位值：`first, second, *last = grades`
在 `for` 中的使用：

```python
records = [
    ('foo', 1, 2),
    ('bar', 'hello'),
    ('foo', 3, 4),
]

def do_foo(x, y):
    print('foo', x, y)

def do_bar(s):
    print('bar', s)

for tag, *args in records:
    if tag == 'foo':
        do_foo(*args)
    elif tag == 'bar':
        do_bar(*args)
```

### 1.3 保留最后 N 个元素

e.g.

```python
from collections import deque


def search(lines, pattern, history=5):
    previous_lines = deque(maxlen=history)
    for line in lines:
        if pattern in line:
            yield line, previous_lines
        previous_lines.append(line)

# Example use on a file
if __name__ == '__main__':
    with open(r'../../cookbook/somefile.txt') as f:
        for line, prevlines in search(f, 'python', 5):
            for pline in prevlines:
                print(pline, end='')
            print(line, end='')
            print('-' * 20)
```

### 1.4 查找最大或最小的 N 个元素

e.g.

```python
import heapq

nums = [1, 8, 2, 23, 7, -4, 18, 23, 42, 37, 2]
print(heapq.nlargest(3, nums))  # 输出 nums 中最大3个数 [42, 37, 23]
print(heapq.nsmallest(3, nums))  # 输出 nums 中最小3个数 [-4, 1, 2]

portfolio = [
    {'name': 'IBM', 'shares': 100, 'price': 91.1},
    {'name': 'AAPL', 'shares': 50, 'price': 543.22},
    {'name': 'FB', 'shares': 200, 'price': 21.09},
    {'name': 'HPQ', 'shares': 35, 'price': 31.75},
    {'name': 'YHOO', 'shares': 45, 'price': 16.35},
    {'name': 'ACME', 'shares': 75, 'price': 115.65}
]
cheap = heapq.nsmallest(3, portfolio, key=lambda s: s['price'])
expensive = heapq.nlargest(3, portfolio, key=lambda s: s['price'])
```

堆数据结构最重要的特征是 `heap[0]` 永远是最小的元素。并且剩余的元素可以很容易的通过调用 `heapq.heappop()` 方法得到， 该方法会先将第一个元素弹出来，然后用下一个最小的元素来取代被弹出元素

如果你仅仅想查找唯一的最小或最大（N=1）的元素的话，那么使用 `min()` 和 `max()` 函数会更快些。 类似的，如果 N 的大小和集合大小接近的时候，通常先排序这个集合然后再使用切片操作会更快点（`sorted(items)[:N]` 或者是 `sorted(items)[-N:]`）

### 1.5 实现一个优先级队列

```python
import heapq


class PriorityQueue:
    def __init__(self):
        self._queue = []
        self._index = 0

    def push(self, item, priority):
        # 引入 self._index 避免 priority 相同时，两个元组比较 item 导致的报错（item 不可比较）
        # 同时为 priority 相同时的排序提供依据
        heapq.heappush(self._queue, (-priority, self._index, item))
        self._index += 1

    def pop(self):
        return heapq.heappop(self._queue)[-1]


class Item:
    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return 'Item({!r})'.format(self.name)


q = PriorityQueue()
q.push(Item('foo'), 1)
q.pop()
```