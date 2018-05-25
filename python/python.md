# yield 生成器

**生成器只能遍历一次**

---

常规列表推导：`squares = [x**2 for x in range(5)]`

生成器表达式：`squares = (x**2 for x in range(5))`

DO: `sum(x ** 2 for x in xrange(4))`

DON'T: `sum([x ** 2 for x in xrange(4)])`

---

generator 对象具有 next() 方法，在 for 循环中会自动调用 next()

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

---

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

---

判断一个函数是否是 generator 函数

``` python
>>> from inspect import isgeneratorfunction
>>> isgeneratorfunction(fab)
True
```

每次调用 fab 函数都会生成一个新的 generator 实例，各实例互不影响

在一个 generator function 中，如果没有 return，则默认执行至函数完毕，如果在执行过程中 return，则直接抛出 StopIteration 终止迭代

# 迭代器

> 可迭代类：提供 \__iter__() 或 \__getitem__() 方法的类
>
> 迭代器类：同时提供 \__iter__() 和 \__next__() 这两个方法的类

\__iter__()使迭代器对象返回自己，就可以把自身变成可迭代对象，因此就可以像可迭代对象一样，用for或in方法来处理

---

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

---

迭代器像list那样按照下标取出元素或切片，需要实现__getitem__()方法：

\__getitem__()传入的参数可能是一个int，也可能是一个切片对象slice

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

# for循环

---

**不建议在for循环中修改列表**

例：`for i in range(5):`

在程序第一次运行到这句的时候，python会自动去调用range(5)对象的__iter__()方法，返回一个range_iterator对象再由这个range_iterator对象不断调用其__next__()方法，直到捕获异常StopIteration为止完成迭代。换句话说，当执行这个for语句的时候，迭代次数就已经被in后面的可迭代对象确定下来了

**但一旦在迭代过程中pop()或者append()元素后前者越界，后者漏值**

---