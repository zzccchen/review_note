# Tornado

**Example: hello world**

``` python
# -*- coding: utf-8 -*-
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

抓取网页内容

```python
from tornado.httpclient import AsyncHTTPClient


class GetPageHandler(web.RequestHandler):

    @gen.coroutine
    def get(self):
        # AsyncHTTPClient 的 fetch 方法返回远端网页的内容
        client = AsyncHTTPClient()
        url = 'http://hq.sinajs.cn/list=sz000001'
        response = yield client.fetch(url, method='GET')
        self.write(response.body.decode('gbk'))
        self.finish()
```

---

**Example: 身份验证**

```python
import tornado.web
import tornado.ioloop
import uuid  # uuid生成库

dict_sessions = {}  # 保存所有登陆的session


class BaseHandler(tornado.web.RequestHandler):

    # tornado和flask一样，在 RequestHandler 中 current_user 保存 get_current_user 返回值
    # get_current_user 默认返回值值时空，需要重载该函数实现
    def get_current_user(self):
        session_id = tornado.escape.native_str(
            self.get_secure_cookie('session_id'))
        return dict_sessions.get(session_id)


class MainHandler(BaseHandler):

    # authenticated 装饰器包裹get方法时，会调用 get_current_user() 方法获取 current_user 的值
    # 若值为None，则重定向到 self.settings['login_url']
    @tornado.web.authenticated
    def get(self):
        name = tornado.escape.xhtml_escape(self.current_user)  # 自动转义
        self.write('hello ' + name)


class LoginHandler(BaseHandler):
    def get(self):
        # 若已登录
        if self.get_current_user():
            self.redirect(self.get_argument('next', '/'))
        else:
            self.write(
                '<html><body><form action="/login" method = "post">Name:<input type = "text" name = "name">:<input type = "submit" value = "sign in"></form></body></html>')

    def post(self):
        if len(self.get_argument('name')) < 3:
            self.redirect('/login')
        session_id = str(uuid.uuid1())
        dict_sessions[session_id] = self.get_argument('name')
        self.set_secure_cookie('session_id', session_id)
        self.redirect('/')


class LogoutHandler(BaseHandler):
    def get(self):
        session_id = tornado.escape.native_str(
            self.get_secure_cookie('session_id'))
        self.clear_cookie("session_id")
        dict_sessions.pop(session_id)  # 删除字典内元素
        self.redirect("/")


application = tornado.web.Application([(r'/', MainHandler), (r'/login', LoginHandler), (r'/logout', LogoutHandler), ], cookie_secret='mimi',
                                      login_url='/login')  # authenticated 装饰器重定向位置 login_url


def main():
    application.listen(8888)
    tornado.ioloop.IOLoop.current().start()


if __name__ == '__main__':
    main()
```

---

**使用next重定向**

如url为"/login?next=%2Ftest"，处理方式如下：（没试过）

```python
self.redirect(self.get_argument("next", "/"))
```

---

###tornado.escape — 转义和字符串操作

[原文链接](http://tornado-zh.readthedocs.io/zh/latest/escape.html)

**Byte/unicode 转换**

转换一个byte 或unicode 字符串到 str 类型，解码成utf8

> 通用：`tornado.escape.native_str()`
> python2：`tornado.escape.utf8()`
> python3：`tornado.escape.to_unicode()`