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

### 1.6 字典中的键映射多个值

**将键映射到列表 `list` 或集合 `set` 中**

可以使用 `collections` 模块中的 `defaultdict` 自动初始化字典，并自动为将要访问的键（就算目前字典中并不存在这样的键）创建映射实体

e.g.

```python
from collections import defaultdict

d = defaultdict(list)
d['a'].append(1)
d['a'].append(2)
d['b'].append(4)

d = defaultdict(set)
d['a'].add(1)
d['a'].add(2)
d['b'].add(4)
```

也可通过 `d.setdefault('a', []).append(1)` 实现默认创建键所映射的实体，此处 `d` 为一个普通的字典

### 1.7 字典排序

`OrderedDict` 会保持元素被插入时的顺序，可精确控制以 JSON 编码后字段的顺序，或对字典排序

e.g.

```python
from collections import OrderedDict


dd = {'banana': 3, 'apple': 4, 'pear': 1, 'orange': 2}

# 按key排序
kd = OrderedDict(sorted(dd.items(), key=lambda t: t[0]))
print(kd)

# 按照value排序
vd = OrderedDict(sorted(dd.items(), key=lambda t: t[1]))
print(vd)
```

### 1.8 字典的运算

使用 `zip` 将键与值压缩成 `[(),(),...]`，需要注意的是 `zip` 函数创建的是一个只能访问一次的迭代器

e.g.

```python
prices = {
    'ACME': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}

# 找最大最小值
min_price = min(zip(prices.values(), prices.keys()))
# min_price is (10.75, 'FB')
max_price = max(zip(prices.values(), prices.keys()))
# max_price is (612.78, 'AAPL')

# 字典排序
prices_sorted = sorted(zip(prices.values(), prices.keys()))
# prices_sorted is [(10.75, 'FB'), (37.2, 'HPQ'),
#                   (45.23, 'ACME'), (205.55, 'IBM'),
#                   (612.78, 'AAPL')]

# 获取最小值或最大值对应的键的信息
min(prices, key=lambda k: prices[k]) # Returns 'FB'
max(prices, key=lambda k: prices[k]) # Returns 'AAPL'
```

### 1.9 查找两字典的相同点

两字典的 `keys()` 或者 `items()` 方法返回结果上执行集合操作，`values()` 方法不支持集合操作

```python
a = {
    'x' : 1,
    'y' : 2,
    'z' : 3
}

b = {
    'w' : 10,
    'x' : 11,
    'y' : 2
}

# Find keys in common
a.keys() & b.keys() # { 'x', 'y' }
# Find keys in a that are not in b
a.keys() - b.keys() # { 'z' }
# Find (key,value) pairs in common
a.items() & b.items() # { ('y', 2) }
```

也可以用于修改或者过滤字典元素

```python
# Make a new dictionary with certain keys removed
c = {key:a[key] for key in a.keys() - {'z', 'w'}}
# c is {'x': 1, 'y': 2}
```