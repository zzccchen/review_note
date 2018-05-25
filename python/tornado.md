# Tornado

**Example: hello world**

``` python
from tornado.ioloop import IOLoop
from tornado import gen, web


class ExampleHandler(web.RequestHandler):

    # 装饰器，一个普通的函数变成一个返回 Future 对象的异步函数
    @gen.coroutine
    def get(self):
        delay = self.get_argument('delay', 5)

        yield gen.sleep(int(delay))
        # 得到两倍延时
        # times = yield self.delayTwice(int(delay)) 或
        # yield self.delayTwice(int(delay))
        self.write({"status": 200, "msg": "success"})

        # 正常结束的 HTTP 调用须以 self.finish() 结束
        # 但如果是 渲染模板 或者 跳转到其它网址 不应添加
        self.finish()

    @gen.coroutine
 　 def delayTwice(self, seconds):
    # 两倍延时
        yield gen.sleep(seconds)
        yield gen.sleep(seconds)
        # 生成器无法使用 return， 只能 raise gen.Return()
 　　   raise gen.Return(2)

    @gen.coroutine
    def get(self):
    # 跳转到其它网址
        self.redirect("/example2")


application = web.Application([
    (r"/example", ExampleHandler),
    #( r"/other", OtherHandler ),
], autoreload=True)  # autoreload 程序修改后，服务能够自动reload新的代码

application.listen(8080)
IOLoop.current().start()
```

启动多线程

```python
from tornado.httpserver import HTTPServer

server = HTTPServer(application)
server.bind(8080)  # 绑定8080端口
server.start(4)  # 启动4线程
```