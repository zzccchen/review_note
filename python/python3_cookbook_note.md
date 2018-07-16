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

[关于 deque 双向队列](./python.md#deque-双向队列)

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
cheap = heapq.nsmallest(2, portfolio, key=lambda s: s['price'])
print(cheap)
# 输出 [{'name': 'YHOO', 'shares': 45, 'price': 16.35},
# {'name': 'FB', 'shares': 200, 'price': 21.09}]
expensive = heapq.nlargest(2, portfolio, key=lambda s: s['price'])
print(expensive)
# 输出 [{'name': 'AAPL', 'shares': 50, 'price': 543.22},
# {'name': 'ACME', 'shares': 75, 'price': 115.65}]
```

[关于 heapq 堆](./python.md#heapq-堆)

堆数据结构最重要的特征是 `heap[0]` 永远是最小的元素。并且剩余的元素可以很容易的通过调用 `heapq.heappop()` 弹出最小元素方法得到， 该方法会先将第一个（最小）元素弹出来，然后用下一个最小的元素来取代被弹出元素

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

[关于 heapq 堆](./python.md#heapq-堆)  
[关于 \_\_repr__](./python.md#__repr__-与-__str__)


### 1.6 字典中的键映射多个值

**将键映射到列表 `list` 或集合 `set` 中**

[关于 defaultdict](./python.md#defaultdict)

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

[关于 OrderedDict](./python.md#OrderedDict)

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
print(min(prices.items(), key=lambda k: k[1]))# Returns ('FB', 10.75)
max(prices, key=lambda k: prices[k]) # Returns 'AAPL'
```

### 1.9 查找两字典的相同点

[关于 集合](./python.md#集合)

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

### 1.10 删除序列相同元素并保持顺序

如果序列上的值都是 `hashable` 类型，利用集合或者生成器来解决这个问题

```python
def dedupe(items):
    seen = set()
    for item in items:
        if item not in seen:
            yield item
            seen.add(item)

a = [1, 5, 2, 1, 9, 1, 5, 10]
print(list(dedupe(a)))
# 输出 [1, 5, 2, 9, 10]
```

如果序列上的值不可哈希（比如 `dict` 类型）

```python
def dedupe(items, key=None):
    seen = set()
    for item in items:
        val = item if key is None else key(item)
        if val not in seen:
            yield item
            seen.add(val)

a = [{'x':1, 'y':2}, {'x':1, 'y':3}, {'x':1, 'y':2}, {'x':2, 'y':4}]
print(list(dedupe(a, key=lambda d: (d['x'],d['y']))))
# 输出 [{'x': 1, 'y': 2}, {'x': 1, 'y': 3}, {'x': 2, 'y': 4}]
print(list(dedupe(a, key=lambda d: d['x'])))
# 输出 [{'x': 1, 'y': 2}, {'x': 2, 'y': 4}]
```

如果仅想消除重复元素，不关心元素位置被打乱

```python
a = [1, 5, 2, 1, 9, 1, 5, 10]
print(set(a))
# 输出 {1, 2, 10, 5, 9}
```

读取一个文件，消除重复行

```python
with open(somefile,'r') as f:
    for line in dedupe(f):
        pass
```

### 1.11 命名切片

前：

```python
record = '....................100 .......513.25 ..........'
cost = int(record[20:23]) * float(record[31:37])
```

后：

```python
SHARES = slice(20, 23)
PRICE = slice(31, 37)
cost = int(record[SHARES]) * float(record[PRICE])
```

[关于 slice 切片](./python.md#slice-切片)

### 1.12 序列中出现次数最多的元素

[关于 Counter](./python.md#Counter)

```python
from collections import Counter

words = [
    'look', 'into', 'my', 'eyes', 'look', 'into', 'my', 'eyes',
    'the', 'eyes', 'the', 'eyes', 'the', 'eyes', 'not', 'around', 'the',
    'eyes', "don't", 'look', 'around', 'the', 'eyes', 'look', 'into',
    'my', 'eyes', "you're", 'under'
]

word_counts = Counter(words)
# 出现频率最高的3个单词
top_three = word_counts.most_common(3)
print(top_three)
# Outputs [('eyes', 8), ('the', 5), ('look', 4)]
```

如果想手动增加计数：

```python
morewords = ['why','are','you','not','looking','in','my','eyes']

# 通过update()
word_counts.update(morewords)

# 或通过dict
for word in morewords:
    word_counts[word] += 1

# 或通过数学运算操作
a = Counter(words)
b = Counter(morewords)
c = a + b
d = a - b
```

### 1.13 通过某个关键字排序一个字典列表

[关于 itemgetter](./python.md#itemgetter)

```python
rows = [
    {'fname': 'Brian', 'lname': 'Jones', 'uid': 1003},
    {'fname': 'David', 'lname': 'Beazley', 'uid': 1002},
    {'fname': 'John', 'lname': 'Cleese', 'uid': 1001},
    {'fname': 'Big', 'lname': 'Jones', 'uid': 1004}
]
```

通过使用 `operator` 模块的 `itemgetter` 函数：

```python
from operator import itemgetter


rows_by_fname = sorted(rows, key=itemgetter('fname'))
rows_by_uid = sorted(rows, key=itemgetter('uid'))
rows_by_lfname = sorted(rows, key=itemgetter('lname','fname'))

print(rows_by_fname)
print(rows_by_uid)
print(rows_by_lfname)
```

通过 `lambda` 表达式：

```python
from operator import itemgetter


rows_by_fname = sorted(rows, key=lambda r: r['fname'])
rows_by_lfname = sorted(rows, key=lambda r: (r['lname'],r['fname']))

print(rows_by_fname)
print(rows_by_lfname)
```

但使用 `itemgetter()` 方式会运行的稍微快点

同时上述方法对 `min()` 和 `max()` 等函数也同样适用

### 1.14 排序不支持原生比较的对象

[关于 itemgetter](./python.md#itemgetter)  
[关于 attrgetter](./python.md#attrgetter)

内置的 `sorted()` 函数有一个关键字参数 `key` ，可以传入一个 `callable` 对象给它。 这个 `callable` 对象对每个传入的对象返回一个值，这个值会被 `sorted` 用来排序这些对象

因此可以使用 `operator.attrgetter()`, `operator.itemgetter()`, `lambda` 来传入 `key`

`attrgetter()` 函数与 `itemgetter()` 类似，通常会比 `lambda` 运行的稍微快点

### 1.15 通过某个字段将记录分组

[关于 groupby](./python.md#groupby) 

通过 `groupby()` 函数：

```python
from itertools import groupby
from operator import itemgetter


rows = [
    {'address': '5412 N CLARK', 'date': '07/01/2012'},
    {'address': '5148 N CLARK', 'date': '07/04/2012'},
    {'address': '5800 E 58TH', 'date': '07/02/2012'},
    {'address': '2122 N CLARK', 'date': '07/03/2012'},
    {'address': '5645 N RAVENSWOOD', 'date': '07/02/2012'},
    {'address': '1060 W ADDISON', 'date': '07/02/2012'},
    {'address': '4801 N BROADWAY', 'date': '07/01/2012'},
    {'address': '1039 W GRANVILLE', 'date': '07/04/2012'},
]

# Sort by the desired field first
rows.sort(key=itemgetter('date'))
# Iterate in groups
for date, items in groupby(rows, key=itemgetter('date')):
    print(date)
    for i in items:
        print(' ', i)

# 输出
# 07/01/2012
#   {'date': '07/01/2012', 'address': '5412 N CLARK'}
#   {'date': '07/01/2012', 'address': '4801 N BROADWAY'}
# 07/02/2012
#   {'date': '07/02/2012', 'address': '5800 E 58TH'}
#   {'date': '07/02/2012', 'address': '5645 N RAVENSWOOD'}
#   {'date': '07/02/2012', 'address': '1060 W ADDISON'}
# 07/03/2012
#   {'date': '07/03/2012', 'address': '2122 N CLARK'}
# 07/04/2012
#   {'date': '07/04/2012', 'address': '5148 N CLARK'}
#   {'date': '07/04/2012', 'address': '1039 W GRANVILLE'}
```

或：

```python
from collections import defaultdict


rows_by_date = defaultdict(list)
for row in rows:
    rows_by_date[row['date']].append(row)
```

此方法没有对记录进行排序。因此，如果对内存占用不是很关心， 这种方式会比先排序然后再通过 `groupby()` 函数迭代的方式运行得快一些

### 1.16 过滤序列元素

最简单的方法就是使用列表推导，但一个潜在缺陷就是如果输入非常大的时候会产生一个非常大的结果集，占用大量内存：

```python
>>> mylist = [1, 4, -5, 10, -7, 2, 3, -1]
>>> [n for n in mylist if n > 0]
[1, 4, 10, 2, 3]
>>> [n for n in mylist if n < 0]
[-5, -7, -1]
```

使用生成器表达式迭代产生过滤的元素，可以减少内存占用：

```python
>>> pos = (n for n in mylist if n > 0)
>>> pos
<generator object <genexpr> at 0x1006a0eb0>
>>> for x in pos:
... print(x)
```

也可以使用内建的 `filter()` 函数，适用于过滤规则比较复杂的情况：

```python
values = ['1', '2', '-3', '-', '4', 'N/A', '5']
def is_int(val):
    try:
        x = int(val)
        return True
    except ValueError:
        return False
ivals = list(filter(is_int, values))
print(ivals)
# Outputs ['1', '2', '-3', '4', '5']
```

过滤操作的一个变种就是将不符合条件的值用新的值代替，而不是丢弃它们：

```python
>>> clip_neg = [n if n > 0 else 0 for n in mylist]
>>> clip_neg
[1, 4, 0, 10, 0, 2, 3, 0]
>>> counts = [ 0, 3, 10, 4, 1, 7, 6, 1]
>>> more5 = [n > 5 for n in counts]
>>> more5
[False, False, True, False, False, True, True, False]
```

使用 `itertools.compress()`：

```python
addresses = [
    '5412 N CLARK',
    '5148 N CLARK',
    '5800 E 58TH',
    '2122 N CLARK',
    '5645 N RAVENSWOOD',
    '1060 W ADDISON',
    '4801 N BROADWAY',
    '1039 W GRANVILLE',
]
counts = [ 0, 3, 10, 4, 1, 7, 6, 1]

>>> from itertools import compress
>>> more5 = [n > 5 for n in counts]
>>> more5
[False, False, True, False, False, True, True, False]
>>> list(compress(addresses, more5))
['5800 E 58TH', '1060 W ADDISON', '4801 N BROADWAY']
```

`itertools.compress()` 以一个 `iterable` 对象和一个相对应的 `Boolean` 选择器序列作为输入参数。然后输出 `iterable` 对象中对应选择器为 `True` 的元素。当需要用另外一个相关联的序列来过滤某个序列的时候，这个函数是非常有用的

和 `filter()` 函数类似，`compress()` 也是返回的一个迭代器。因此，如果需要得到一个列表，那么需要使用 `list()` 来将结果转换为列表类型

### 1.17 从字典中提取子集

使用字典推导:

```python
prices = {
    'ACME': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}
# Make a dictionary of all prices over 200
p1 = {key: value for key, value in prices.items() if value > 200}
# Make a dictionary of tech stocks
tech_names = {'AAPL', 'IBM', 'HPQ', 'MSFT'}
p2 = {key: value for key, value in prices.items() if key in tech_names}
```

或：

```python
p1 = dict((key, value) for key, value in prices.items() if value > 200)
p2 = { key:prices[key] for key in prices.keys() & tech_names }
```

但使用法一，即字典推导是最快的

### 1.18 映射名称到序列元素

```python
>>> from collections import namedtuple
>>> Subscriber = namedtuple('Subscriber', ['addr', 'joined'])
>>> sub = Subscriber('jonesy@example.com', '2012-10-19')
>>> sub
Subscriber(addr='jonesy@example.com', joined='2012-10-19')
>>> sub.addr
'jonesy@example.com'
>>> sub.joined
'2012-10-19'
```

尽管 `namedtuple` 的实例看起来像一个普通的类实例，但是它跟元组类型是可交换的，支持所有的普通元组操作，比如索引和解压

```python
>>> len(sub)
2
>>> addr, joined = sub
>>> addr
'jonesy@example.com'
>>> joined
'2012-10-19'
```

命名元组的一个主要用途是将你的代码从下标操作中解脱出来。因此，如果你从数据库调用中返回了一个很大的元组列表，通过下标去操作其中的元素，当你在表中添加了新的列的时候你的代码可能就会出错了。但是如果你使用了命名元组，那么就不会有这样的顾虑

命名元组另一个用途就是作为字典的替代，因为字典存储需要更多的内存空间。 如果你需要构建一个非常大的包含字典的数据结构，那么使用命名元组会更加高效。 但是需要注意的是，不像字典那样，一个命名元组是不可更改的。如果真的需要改变属性的值，那么可以使用命名元组实例的 `_replace()` 方法， 它会创建一个全新的命名元组并将对应的字段用新的值取代

```python
>>> sub = sub._replace(joined='2010-10-10')
>>> sub
Subscriber(addr='jonesy@example.com', joined='2010-10-10')
```

`_replace()` 方法还有一个很有用的特性就是当你的命名元组拥有可选或者缺失字段时候，它是一个非常方便的填充数据的方法。你可以先创建一个包含缺省值的原型元组，然后使用 `_replace()` 方法创建新的值被更新过的实例

```python
from collections import namedtuple


Stock = namedtuple('Stock', ['name', 'shares', 'price', 'date', 'time'])

# Create a prototype instance
stock_prototype = Stock('', 0, 0.0, None, None)

# Function to convert a dictionary to a Stock
def dict_to_stock(s):
    return stock_prototype._replace(**s)

>>> a = {'name': 'ACME', 'shares': 100, 'price': 123.45}
>>> dict_to_stock(a)
Stock(name='ACME', shares=100, price=123.45, date=None, time=None)
>>> b = {'name': 'ACME', 'shares': 100, 'price': 123.45, 'date': '12/17/2012'}
>>> dict_to_stock(b)
Stock(name='ACME', shares=100, price=123.45, date='12/17/2012', time=None)
```

### 1.19 转换并同时计算数据

使用一个生成器表达式参数

```python
s = sum((x * x for x in nums)) # 显示的传递一个生成器表达式对象
s = sum(x * x for x in nums) # 更加优雅的实现方式，省略了括号
```

而使用一个生成器表达式作为参数会比先创建一个临时列表更加高效和优雅

```python
nums = [1, 2, 3, 4, 5]
s = sum([x * x for x in nums])
```

### 1.20 合并多个字典或映射

使用 `collections` 模块中的 `ChainMap` 类

```python
from collections import ChainMap


a = {'x': 1, 'z': 3 }
b = {'y': 2, 'z': 4 }

c = ChainMap(a,b)
print(c['x'])  # 输出 1  # 来自 a
print(c['y'])  # 输出 2  # 来自 b
print(c['z'])  # 输出 3  # 来自 a
```

一个 `ChainMap` 接受多个字典并将它们在逻辑上变为一个字典。然后，这些字典并不是真的合并在一起了，`ChainMap` 类只是在内部创建了一个容纳这些字典的列表，并重新定义了一些常见的字典操作来遍历这个列表

大部分字典操作都是可以正常使用的，但如果出现重复键，那么第一次出现的映射值会被返回。对于字典的更新或删除操作总是影响的是列表中第一个字典

```python
>>> len(c)
3
>>> list(c.keys())
['x', 'y', 'z']
>>> list(c.values())
[1, 2, 3]

>>> c['z'] = 10
>>> c['w'] = 40
>>> del c['x']
>>> a
{'w': 40, 'z': 10}
>>> del c['y']
Traceback (most recent call last):
...
KeyError: "Key not found in the first mapping: 'y'"
```

注意：`ChainMap` 使用原来的字典，它自己不创建新的字典
