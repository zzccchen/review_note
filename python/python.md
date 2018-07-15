# Python Note

## dict 字典

# TODO: https://www.cnblogs.com/wushuaishuai/p/7739441.html

## slice 切片

> `class slice(stop)`
> `class slice(start, stop[, step])`

```python
items = [0, 1, 2, 3, 4, 5, 6]
a = slice(2, 4)
items[a]  # 等效于 items[2:4]
          # 输出 [2, 3]

items[a] = [10,11]  # 等效于 items[2:4] = [10,11]
print(items)  # 输出 [0, 1, 10, 11, 4, 5, 6]

del items[a]
print(items)  # 输出 [0, 1, 4, 5, 6]
```

`slice` 的属性

```python
>>> a = slice(5, 50, 2)
>>> a.start
5
>>> a.stop
50
>>> a.step
2
```

**在 `[a:b]` 的情况下，必须保证 a 所在的索引位置在前，b 所在的索引位置在后，否则返回结果为空。在 `[a:b:step]` 的情况下，我们首先要根据 a，b 的位置来判断方向，a在前，b在后的话，step 应该为正，否则应该为负，不符合这些情况的话，则返回空的数组**

## 集合 

```python
a = t | s  # t 和 s的并集

b = t & s  # t 和 s的交集

c = t – s  # 求差集（项在t中，但不在s中）

d = t ^ s  # 对称差集（项在t或s中，但不会同时出现在二者中）
```

---

## tuple 元组

```python
len((1, 2, 3))  # 计算元素个数 3

(1, 2, 3) + (4, 5, 6)  # 连接 (1, 2, 3, 4, 5, 6)

('Hi!',) * 4  # 复制 ('Hi!', 'Hi!', 'Hi!', 'Hi!')
              # 仅元组内为单元素时需注意逗号
              # 没有逗号将变成 "Hi!Hi!Hi!Hi!"
```

**元组的比较** 类似于字符串的大小比较，先比较第一个元素，分不出大小的话，再比较下一个元素

元组可像列表一样 **截取** 或者 **迭代**

---

## for 循环

**不建议在 for 循环中修改列表**

例：`for i in range(5):`

在程序第一次运行到这句的时候，python 会自动去调用 `range(5)` 对象的 `__iter__` 方法，返回一个 range_iterator 对象再由这个 range_iterator 对象不断调用其 `__next__` 方法，直到捕获异常 `StopIteration` 为止完成迭代。换句话说，当执行这个 `for` 语句的时候，迭代次数就已经被 `in` 后面的可迭代对象确定下来了

**但一旦在迭代过程中 `pop()` 或者 `append()` 元素后前者越界，后者漏值**

---

## 转义字符

**`!` 只在fromat中有用**

e.g.

```python
print('hello, %s' % '123')
print('hello, {!s}'.format('123'))
# 只有这两种能输出 hello, 123
```

### %r 或 !r

`%r` 或 `!r` 用于直接反应对象本体，即调用对象的 `__repr()__` 方法

e.g.

```python
print('hello, %s' % '123')
# 输出 hello, 123
print('hello, {!r}'.format('123'))
# 输出 hello, '123'
# 注意 '123' 的引号
```

---

## [with 语句](https://www.ibm.com/developerworks/cn/opensource/os-cn-pythonwith/#icomments)

> **上下文管理协议（Context Management Protocol）**：包含方法 `__enter__` 和 `__exit__`，支持该协议的对象要实现这两个方法
>
> **上下文管理器（Context Manager）**：支持上下文管理协议的对象。上下文管理器定义执行 `with` 语句时要建立的运行时上下文，负责执行 `with` 语句块上下文中的进入与退出操作。通常使用 `with` 语句调用上下文管理器，也可以通过直接调用其方法来使用
>
> **运行时上下文（runtime context）**：由上下文管理器创建，通过上下文管理器的 `__enter__` 和 `__exit__` 方法实现，`__enter__` 方法在语句体执行之前进入运行时上下文，`__exit__` 在语句体执行完后从运行时上下文退出
>
> **上下文表达式（Context Expression）**：with 语句中跟在关键字 with 之后的表达式，该表达式返回一个上下文管理器对象
>
> **语句体（with-body）**：with 语句包裹起来的代码块，在执行语句体之前会调用上下文管理器的 `__enter__` 方法，执行完语句体之后会执行 `__exit__` 方法

with 语句的语法格式

```python
with context_expression [as target(s)]:
    with-body
```

`context_expression` 返回一个上下文管理器对象。如果指定了 `as` 子句的话，会将上下文管理器的 `__enter__` 方法的返回值赋值给 `target(s)`。`target(s)` 可以是单个变量，或者由 `()` 括起来的元组 *不能是仅仅由 `,` 分隔的变量列表，必须加 `()`*

使用 with 语句操作文件对象

```python
with open(r'somefileName') as somefile:
    for line in somefile:
        print line
        # ...more code
```

with 语句执行过程

```python
# 执行 context_expression，生成上下文管理器 context_manager
context_manager = context_expression

# 调用上下文管理器的 __enter__() 方法
value = type(context_manager).__enter__(context_manager)

exit = type(context_manager).__exit__

exc = True   # True 表示正常执行，即便有异常也忽略；False 表示重新抛出异常，需要对异常进行处理
try:
    try:
        target = value  # 如果使用了 as 子句，则将 __enter__() 方法的返回值赋值给 as 子句中的 target(s)
        with-body     # 执行 with-body
    except:
        # 执行过程中有异常发生
        exc = False
        # 如果 __exit__ 返回 True，则异常被忽略；如果返回 False，则重新抛出异常
        # 由外层代码对异常进行处理
        if not exit(context_manager, *sys.exc_info()):
            raise
finally:
    # 正常退出，或者通过 statement-body 中的 break/continue/return 语句退出
    # 或者忽略异常退出
    if exc:
        exit(context_manager, None, None, None)
    # 缺省返回 None，None 在布尔上下文中看做是 False
```

`context_manager.__exit__(exc_type, exc_value, exc_traceback)` ：退出与上下文管理器相关的运行时上下文，返回一个布尔值表示是否对发生的异常进行处理。参数表示引起退出操作的异常，如果退出时没有发生异常，则3个参数都为 `None`。如果发生异常，返回 `True` 表示不处理异常，否则会在退出该方法后重新抛出异常以由 `with` 语句之外的代码逻辑进行处理。如果该方法内部产生异常，则会取代由 with-body 中语句产生的异常。要处理异常时，不要显示重新抛出异常，即不能重新抛出通过参数传递进来的异常，只需要将返回值设置为 `False` 就可以了。之后，上下文管理代码会检测是否 `__exit__()` 失败来处理异常

上下文管理器必须同时提供 `__enter__()` 和 `__exit__()` 方法的定义，缺少任何一个都会导致 `AttributeError`；`with` 语句会先检查是否提供了 `__exit__()` 方法，然后检查是否定义了 `__enter__()` 方法

# TODO: https://www.ibm.com/developerworks/cn/opensource/os-cn-pythonwith/#icomments

---

## yield 生成器

**生成器只能遍历一次**

常规列表推导：`squares = [x**2 for x in range(5)]`

生成器表达式：`squares = (x**2 for x in range(5))`

DO: `sum(x ** 2 for x in xrange(4))`

DON'T: `sum([x ** 2 for x in xrange(4)])`

generator 对象具有 `next` 方法，在 `for` 循环中会自动调用 `next` 方法

``` python
>>> def func(n):
...     yield n*2

>>> g = func(5)
... next(g)
10

>>> g = func(5)
... for i in g:
...     print(i)
10
```

用生成器实现斐波那契数列：

``` python
def fab(n):
    prev, curr = 0, 1
    while n > 0:
        n -= 1
        yield curr
        prev, curr = curr, curr + prev

print([i for i in fab(10)])
```

判断一个函数是否是 generator 函数

``` python
>>> from inspect import isgeneratorfunction
>>> isgeneratorfunction(fab)
True
```

每次调用 `fab` 函数都会生成一个新的 generator 实例，各实例互不影响

在一个 generator function 中，如果没有 return，则默认执行至函数完毕，如果在执行过程中 return，则直接抛出 `StopIteration` 终止迭代

---

## 迭代器

> 可迭代类：提供 `__iter__` 或 `__getitem__` 方法的类
>
> 迭代器类：同时提供 `__iter__` 和 `__next__` 这两个方法的类

`__iter__` 使迭代器对象返回自己，就可以把自身变成可迭代对象，因此就可以像可迭代对象一样，用 `for` 或 `in` 方法来处理

例：斐波那契数列实现

``` python
class Fab(object):

    def __init__(self, n):
        self.n = n
        self.prev, self.cur = 0, 1

    def __iter__(self):
        return self

    def __next__(self):
        if self.n > 0:
            value = self.cur
            self.cur =self.cur + self.prev
            self.prev = value
            self.n -= 1
            return value
        else:
            raise StopIteration

for i in Fab(10):
    print(i)
```

迭代器像list那样按照下标取出元素或切片，需要实现 `__getitem__` 方法：

`__getitem__` 传入的参数可能是一个 int ，也可能是一个切片对象 slice

``` python
class Fib(object):
    def __getitem__(self, n):
        if isinstance(n, int):
            a, b = 1, 1
            for x in range(n):
                a, b = b, a + b
            return a
        if isinstance(n, slice):
            start = n.start
            stop = n.stop
            a, b = 1, 1
            L = []
            for x in range(stop):
                if x >= start:
                    L.append(a)
                a, b = b, a + b
            return L
```

## [装饰器]("http://python3-cookbook.readthedocs.io/zh_CN/latest/chapters/p09_meta_programming.html")

### 函数装饰器

```python
from functools import wraps
import logging

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger("main")


def logging(level):
    def decorator(func): 
        @wraps(func)
        # *args 用来代替参数， **kwargs 用来代替关键字函数
        def wrapper(*arg, **kwargs):
            if level == "info":
                logger.info('%s start' % func.__name__)
            elif level == "debug":
                logger.debug('%s start' % func.__name__)
            else:
                pass
            return func(*arg, **kwargs)
        return wrapper
    return decorator


@logging("info")
def foo():
    print('pass')


foo()
print(foo.__name__)
```

`logging` 函数最终返回的是 `wrapper`，`wrapper` 是一个函数对象。`@logging` 即将 `foo` 指向 `wrapper`

`@wraps` 装饰器把原函数的元信息拷贝到装饰器里面的 `func` 函数中。
使用时需 `from functools import wraps`

### 类装饰器

使用类装饰器时将自动调用类的 `__call__` 方法

```python
from functools import wraps


class Foo(object):
    def __init__(self, func):
        wraps(func)(self)
        self._func = func

    def __call__(self):
        print('class decorator runing')
        self._func()
        print('class decorator ending')


@Foo
def bar():
    print('bar00')


bar()
print(bar.__name__)
```

### 小细节

#### 调用方式的等效：

```python
class A:
    @classmethod
    def method(cls):
        pass

class B:
    def method(cls):
        pass
    method = classmethod(method)
```

一个装饰器就是一个函数，它接受一个函数作为参数并返回一个新的函数，上面两种调用方式是等效的。

#### 多个装饰器的顺序：

```python
@a
@b
@c
def foo():
    pass
```

等效于

`foo = a(b(c(foo)))`

#### \_\_wrapped__ 属性

假设装饰器是通过 `@wraps` 来实现的，那么可以通过访问 `__wrapped__` 属性来访问原始函数

```python
>>> @somedecorator
>>> def add(x, y):
...     return x + y
...
>>> orig_add = add.__wrapped__
>>> orig_add(3, 4)
7
```

如果有多个包装器，那么访问 `__wrapped__` 属性的行为是不可预知的。特别的，内置的装饰器 `@staticmethod` 和 `@classmethod` 就没有遵循这个约定 (它们把原始函数存储在属性 `__func__` 中)。

#### 接受参数的装饰器间的等效：

```python
@decorator(x, y, z)
def func(a, b):
    pass
```

上下等效

```python
def func(a, b):
    pass
func = decorator(x, y, z)(func)
```

---

## 内置函数

### min 与 max

关于 `key` 属性的使用

```python
a = [-9, -8, 1, 3, -4, 6]
tmp = max(a, key=lambda x: abs(x))
# 或 tmp = max(a, key=abs)
print(tmp)  # 输出 -9
            # 即判断是按 key 中的 abs(x) 但是返回的是原对象

min(1, 2, '3')  # 数值和字符串不能取最小值
min(1, 2, '3', key=int)  # 指定key为转换函数后，可以取最小值
```

空可迭代对象不能取最小值，需指定 default 参数为默认值，且默认值必须使用命名参数进行传参，否则将被认为是一个比较的元素

```python
min(())  # 报错 ValueError: min() arg is an empty sequence
min((), default=0)  # 输出 0
min((), 0)  # 报错 TypeError: unorderable types: int() < tuple()
```

### defaultdict

`defaultdict` 类的初始化函数接受一个类型作为参数，当所访问的键不存在的时候，可以实例化一个值作为默认值

这种形式的默认值只有在通过 `dict[key]` 或者 `dict.__getitem__(key)` 访问的时候才有效，

通过 `dict.get(key)` 得到的默认值仍为 `dict.get(key)` 方法的默认值，即 `None`

```python
from collections import defaultdict

d1 = defaultdict(int)  # 默认为 0
d2 = defaultdict(list)  # 默认为 []
d3 = defaultdict(lambda: "xxx")  # 默认为 'xxx'
```

### OrderedDict

python 中的字典是无序的，因为它是按照 hash 来存储的，`OrderedDict` 实现了对字典对象中元素 **按插入顺序排序**，大小也是普通字典的两倍，且两个 `OrderedDict` 的字典对象仅顺序不同也会被认为是两个不同对象

除以下方法，其余方法与 dict 类似

```python
from collections import OrderedDict


dd = {'banana': 3, 'apple': 4, 'pear': 1, 'orange': 2}

# 按key排序
kd = OrderedDict(sorted(dd.items(), key=lambda t: t[0]))
print(kd)

# 按照value排序
vd = OrderedDict(sorted(dd.items(), key=lambda t: t[1]))
print(vd)

# move_to_end （指定一个key，把对应的key-value移到最后）
vd.move_to_end('banana')
```

### Counter

`Counter` 对象可以接受任意的由可哈希( `hashable` )元素构成的序列对象。 在底层实现上，一个 `Counter` 对象就是一个字典，将元素映射到它出现的次数上

创建一个 `Counter`

```python
from collections import Counter


a = Counter('abcasdf')
b = Counter({'red': 4, 'yello': 2})
c = Counter(cats=2, dogs=5)
c1 = Counter(c)

print(a)  # Counter({'a': 2, 'b': 1, 'c': 1, 's': 1, 'd': 1, 'f': 1})
print(b)  # Counter({'red': 4, 'yello': 2})
print(c)  # Counter({'dogs': 5, 'cats': 2})
print(c1)  # Counter({'dogs': 5, 'cats': 2})
```

因为 Counter 实现了字典的 `__missing__` 方法， 所以当访问不存在的 key 的时候，返回值为 0

```python
# elements() 按照counter的计数，重复返回元素
>>> c = Counter(a=4, b=2, c=0, d=-2)
>>> list(c.elements())
['a', 'a', 'a', 'a', 'b', 'b']

# most_common(n) 按照counter的计数，按照降序，返回前n项组成的list; n忽略时返回全部
>>> Counter('abracadabra').most_common(3)
[('a', 5), ('r', 2), ('b', 2)]

# subtract([iterable-or-mapping]) counter按照相应的元素，计数相减，，此方法保留任意值的value
>>> c = Counter(a=4, b=2, c=0, d=-2)
>>> d = Counter(a=1, b=2, c=3, d=4)
>>> c.subtract(d)  
>>> c
Counter({'a': 3, 'b': 0, 'c': -3, 'd': -6})
# 等同于 c - d，但此方法只保留正值(>0)的value
>>> c - d
Counter({'a': 3})

# update([iterable-or-mapping]) 不同于字典的update方法，这里更新counter时，相同的key的value值相加而不是覆盖
# 实例化 Counter 时， 实际也是调用这个方法，此方法保留任意值的value
# 等同于 c + d，但此方法只保留正值(>0)的value


# Counter 间的数学集合操作
>>> c = Counter(a=3, b=1, c=5)
>>> d = Counter(a=1, b=2, d=4)
>>> c + d                       # counter相加, 相同的key的value相加，只保留正值(>0)的value
Counter({'c': 5, 'a': 4, 'd': 4, 'b': 3})
>>> c - d                       # counter相减, 相同的key的value相减，只保留正值(>0)的value
Counter({'c': 5, 'a': 2})
>>> c & d                       # 交集:  取两者都有的key,value取小的那一个
Counter({'a': 1, 'b': 1})
>>> c | d                       # 并集:  汇聚所有的key, key相同的情况下，取大的value
Counter({'c': 5, 'd': 4, 'a': 3, 'b': 2})

常见做法:
sum(c.values())                 # 继承自字典的.values()方法返回values的列表，再求和
c.clear()                       # 继承自字典的.clear()方法，清空counter
list(c)                         # 返回key组成的list
set(c)                          # 返回key组成的set
dict(c)                         # 转化成字典
c.items()                       # 转化成(元素，计数值)组成的列表
Counter(dict(list_of_pairs))    # 从(元素，计数值)组成的列表转化成Counter
c.most_common()[:-n-1:-1]       # 最小n个计数的(元素，计数值)组成的列表
c += Counter()                  # 利用counter的相加来去除负值和0的值
```

### \_\_repr__ 与 \_\_str__

重构 `__repr__` 方法后，不管直接输出对象还是通过 `print` 打印的信息都按 `__repr__` 方法中定义的格式进行显示了
而重构 `__str__` 方法后，直接输出对象时并没有按我们 `__str__` 方法中定义的格式进行输出，输出：`<object at 0x7fa91c314e50>`，而用 `print` 输出的信息按 `__str__` 方法中定义的格式进行显示了

#### repr() 函数

```repr(object)```

`repr` 函数将对象转化为供解释器读取的形式，返回一个对象的 string 格式

### uuid

uuid 是128位的全局唯一标识符，通常用32位的一个字符串的形式来表现

```python

import uuid

uuid.uuid1() # 基于MAC地址，时间戳，随机数来生成唯一的uuid，可以保证全球范围内的唯一性

```

---

### setattr / getattr 函数

**setattr 用于设置属性值，该属性可不存在**

`setattr(object, name, value)`

**getattr 用于返回一个对象属性值**

`getattr(object, name[, default])`
*default -- 默认返回值，如果不提供该参数，在没有对应属性时，将触发 `AttributeError`*

```python

>>> class A(object):
...     bar = 1
...
>>> a = A()
···
>>> setattr(a, 'bar', 5)  # 设置属性 bar 值
>>> a.bar
5
>>> setattr(a, 'bar1', 5)  # 设置属性 bar1 值
>>> a.bar1
5
···
>>> getattr(a, 'bar')  # 获取属性 bar 值
5
>>> getattr(a, 'bar2', 3)  # 获取属性 bar2 值
3

```

---

### deque 双向队列

*线程安全*

```python

from collections import deque

d = deque()  # 创建双向队列

d1 = deque(maxlen=5)  # 创建固定大小5的双向队列，当新的元素加入并且这个队列已满的时候，最老的元素会自动被移除掉

d.append(1)  # 往右边添加一个元素，如：[2] -> [2, 1]

d.appendleft(2)  # 往左边添加一个元素，如：[1] -> [2, 1]

d.clear()  # 清空队列

new_d = d.copy()  # 浅拷贝

d.count(1)  # 返回指定元素的出现次数

d.extend([3, 4, 5])  # 从队列右边扩展一个列表的元素

d.extendleft([3, 4, 5])  # 从队列左边扩展一个列表的元素

print(d.index(1))  # 查找某个元素的索引位置

print(d.index('c', 0, 3))  # 指定查找区间

d.insert(2, 'z')  # 在指定位置2插入元素'z'

d.pop()  # 弹出最右边一个元素

d.popleft()  # 弹出最左边一个元素

d.remove('c')  # 删除指定元素

d.reverse()  # 队列反转

d.rotate(2)  # 把右边元素放到左边，默认1次
             # 如：['a','b','c','d','e'] -> ['d', 'e', 'a', 'b', 'c']

```

---

### heapq 堆

```python

import heapq

heapq.heappush(heap,item)  # heap 为定义堆，item 为增加的元素

heapq.heapify(list)  # 将列表转换为堆

heapq.heappop(heap)  # 弹出最小元素

heapq.heapreplace(heap, item)   # 弹出最小元素，添加新的元素

heapq.heappushpop(heap, item)   # 添加元素与堆的第一个元素（即最小元素）对比，
                                # 如果大于则弹出最小元素，然后添加新的元素值，否则不更改堆
                                # 此函数返回值为两元素中的较小元素

heapq.merge(...)  # 将多个堆合并

heapq.nlargest(n, heap)  # 查询堆中的最大 n 个元素

heapq.nsmallest(n, heap)  # 查询堆中的最小 n 个元素

```

---

## 作用域

### LEGB 原则

* 说明：

    > L-Local(function): 函数内的名字空间
    >
    > E-Enclosing function locals: 外部嵌套函数的名字空间（例如 closure）
    >
    > G-Global(module): 函数定义所在模块（文件）的全局名字空间
    >
    > B-Builtin(Python)： Python 内置模块的名字空间

* 当在函数中使用未认证的变量名时，Python 依次搜索4个作用域：

    > 本地作用域(L)
    >
    > 上一层结构中 def 或 lambda 的本地作用域(E)
    >
    > 全局作用域(G)
    >
    > 内置作用域(B)

    并且在第一处能够找到这个变量名的地方停下来。如果变量名在这次搜索中没有找到，会报错

* **当在函数中给一个变量名赋值时（而不是在一个表达式中对其进行引用），Python 总是创建或改变本地作用域的变量名，除非它已经在那个函数中声明为全局变量**

* 当在函数之外给一个变量名赋值时（也就是说，在一个模块文件顶层，或者是在交互提示模式下），本地作用域和全局作用域是相同的

### global 语句

* 全局变量是位于模块文件内部的顶层的变量名

* 全局变量如果是在函数内被 **赋值** 的话，**必须** 经过声明

* 全局变量如果是在函数内被 **引用** 的话，**不必** 经过声明

> 函数 `func` 内 `global x` 语句用于告诉 Python 在 `func` 的本地作用域内，要使用全局作用域中的变量 x，因此 Python 不会再在本地作用域中新建一个变量，而是直接引用全局作用域中的变量 x

Example_1:

```python

x = 99
def func():
    x = 88
func()
print(x)  # 输出 99

```

Example_2:

```python

x = 99
def func():
    global x = 88
func()
print(x)  # 输出 88

```

### nonlocal 语句

> nonlocal 的作用与关键字 global 类似，关键字可以在一个嵌套的函数中修改嵌套作用域中的变量

Example_3:

```python

def func():
    count = 1
    def foo():
        count = 12
    foo()
    print(count)
func()  # 输出1

```

Example_4:

```python

def func():
    count = 1
    def foo():
        nonlocal count
        count = 12
    foo()
    print(count)
func()  # 输出12

```

---