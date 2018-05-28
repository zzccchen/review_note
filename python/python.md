# yield 生成器

**生成器只能遍历一次**

---

常规列表推导：`squares = [x**2 for x in range(5)]`

生成器表达式：`squares = (x**2 for x in range(5))`

DO: `sum(x ** 2 for x in xrange(4))`

DON'T: `sum([x ** 2 for x in xrange(4)])`

---

generator 对象具有 next 方法，在 for 循环中会自动调用 next 方法

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

> 可迭代类：提供 \_\_iter__ 或 \_\_getitem__ 方法的类
>
> 迭代器类：同时提供 \_\_iter__ 和 \_\_next__ 这两个方法的类

\_\_iter__ 使迭代器对象返回自己，就可以把自身变成可迭代对象，因此就可以像可迭代对象一样，用 for 或 in 方法来处理

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

迭代器像list那样按照下标取出元素或切片，需要实现 \_\_getitem__ 方法：

\_\_getitem__ 传入的参数可能是一个 int ，也可能是一个切片对象 slice

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

在程序第一次运行到这句的时候，python会自动去调用 range(5) 对象的 \_\_iter__ 方法，返回一个range_iterator 对象再由这个 range_iterator 对象不断调用其 \_\_next__ 方法，直到捕获异常 StopIteration 为止完成迭代。换句话说，当执行这个for语句的时候，迭代次数就已经被in后面的可迭代对象确定下来了

**但一旦在迭代过程中pop()或者append()元素后前者越界，后者漏值**

---

# uuid

uuid是128位的全局唯一标识符，通常用32位的一个字符串的形式来表现

```python
import uuid


uuid.uuid1() # 基于MAC地址，时间戳，随机数来生成唯一的uuid，可以保证全球范围内的唯一性
```

---

# [装饰器]("http://python3-cookbook.readthedocs.io/zh_CN/latest/chapters/p09_meta_programming.html")

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

logging 函数最终返回的是 wrapper, wrapper 是一个函数对象。@logging 即将 foo 指向 wrapper

@wraps 装饰器把原函数的元信息拷贝到装饰器里面的 func 函数中。
使用时需 `from functools import wraps`

### 类装饰器

使用类装饰器时将自动调用类的 \_\_call__ 方法

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

假设装饰器是通过 @wraps 来实现的，那么可以通过访问 \_\_wrapped__ 属性来访问原始函数

```python
>>> @somedecorator
>>> def add(x, y):
...     return x + y
...
>>> orig_add = add.__wrapped__
>>> orig_add(3, 4)
7
```

如果有多个包装器，那么访问 \_\_wrapped__ 属性的行为是不可预知的。特别的，内置的装饰器 @staticmethod 和 @classmethod 就没有遵循这个约定 (它们把原始函数存储在属性 \_\_func__ 中)。

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

# 内置函数

### setattr / getattr 函数

**setattr 用于设置属性值，该属性可不存在**

`setattr(object, name, value)`

**getattr 用于返回一个对象属性值**

`getattr(object, name[, default])`
*default -- 默认返回值，如果不提供该参数，在没有对应属性时，将触发 AttributeError*

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