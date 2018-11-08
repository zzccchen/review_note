# Vue.js

CDN: 

* unpkg: [https://unpkg.com/vue/dist/vue.min.js](https://unpkg.com/vue/dist/vue.min.js)保持和 npm 发布的最新的版本一致

* Staticfile CDN（国内）: [https://cdn.staticfile.org/vue/2.2.2/vue.min.js](https://cdn.staticfile.org/vue/2.2.2/vue.min.js)

```html
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>title</title>
<script src="https://unpkg.com/vue/dist/vue.js"></script>
</head>
<body>
</body>
</html>
```

## 起步

每个 Vue 应用都需要通过实例化 Vue 来实现。

```js
var vm = new Vue({})
```

```html
<div id="vue_det">
    <h1>site : {{site}}</h1>  <!-- {{ }} 用于输出对象属性和函数返回值 -->
    <h1>url : {{url}}</h1>
    <h1>{{details()}}</h1>
</div>
<script type="text/javascript">
    var data = { site: "菜鸟教程", url: "www.runoob.com", alexa: 10000}
    var vm = new Vue({
        el: '#vue_det',  // 对应 DOM 元素中的 id
        data: data,  // 用于定义属性，此处 data 为引用
        methods: {  // 用于定义的函数，可以通过 return 来返回函数值
            details: function() {
                return  this.site + " - 学的不仅是技术，更是梦想！";
            }
        }
    })
</script>
```

```js
document.write(vm.$data） // 访问默认属性需要前缀 $
document.write(vm.site）  // 访问用户定义属性
```

## 模板

### 插值

#### 文本

```html
<div id="app">
  <p>{{ message }}</p>
</div>
```

#### Html

```html
<div id="app">
    <div v-html="message"></div>
</div>
    
<script>
new Vue({
  el: '#app',
  data: {
    message: '<h1>菜鸟教程</h1>'
  }
})
</script>
```

#### Html 属性

```html
<div id="app">
  <label for="r1">修改颜色</label><input type="checkbox" v-model="class1" id="r1">
  <br><br>
  <div v-bind:class="{'class1': class1}">
    v-bind:class 指令
  </div>
</div>
    
<script>
new Vue({
    el: '#app',
  data:{
      class1: false
  }
});
</script>
```

#### 表达式

```html
<div id="app">
    {{5+5}}<br>
    {{ ok ? 'YES' : 'NO' }}<br>
    {{ message.split('').reverse().join('') }}
    <div v-bind:id="'list-' + id">菜鸟教程</div>
</div>
    
<script>
new Vue({
  el: '#app',
  data: {
    ok: true,
    message: 'RUNOOB',
    id : 1
  }
})
</script>
```

### 指令

指令是带有 `v-` 前缀的特殊属性。

指令用于在表达式的值改变时，将某些行为应用到 DOM 上。

```html
<div id="app">
    {{5+5}}<br>
    {{ ok ? 'YES' : 'NO' }}<br>
    {{ message.split('').reverse().join('') }}
    <div v-bind:id="'list-' + id">菜鸟教程</div>
</div>
    
<script>
<div id="app">
    <p v-if="seen">现在你看到我了</p>
    <p v-if="ok">现在你看不到我了</p>
</div>
    
<script>
new Vue({
  el: '#app',
  data: {
    seen: true,
    ok: false
  }
})
</script>
```

#### 参数

参数在指令后以冒号指明。例如， `v-bind` 指令被用来响应地更新 HTML 属性

```html
<div id="app">
    <pre><a v-bind:href="url">菜鸟教程</a></pre>
</div>
    
<script>
new Vue({
  el: '#app',
  data: {
    url: 'http://www.runoob.com'，
    target:'_blank' // 绑一个target，新窗口打开页面。
  }
})
</script>
```

#### 参数

修饰符是以半角句号 `.` 指明的特殊后缀，用于指出一个指令应该以特殊方式绑定。例如，`.prevent` 修饰符告诉 `v-on` 指令对于触发的事件调用 `event.preventDefault()`

```html
<form v-on:submit.prevent="onSubmit"></form>
```

### 用户输入

`v-model` 指令用来在 input、select、text、checkbox、radio 等表单控件元素上创建双向数据绑定，根据表单上的值，自动更新绑定的元素的值。

```html
<div id="app">
    <p>{{ message }}</p>
    <input v-model="message">
</div>
    
<script>
new Vue({
  el: '#app',
  data: {
    message: 'Runoob!'
  }
})
</script>
```

按钮的事件我们可以使用 `v-on` 监听事件，并对用户的输入进行响应。

```html
<div id="app">
    <p>{{ message }}</p>
    <button v-on:click="reverseMessage">反转字符串</button>
</div>
    
<script>
new Vue({
  el: '#app',
  data: {
    message: 'Runoob!'
  },
  methods: {
    reverseMessage: function () {
      this.message = this.message.split('').reverse().join('')
    }
  }
})
</script>
```

### 过滤器

过滤器函数接受表达式的值作为第一个参数。

```html
<div id="app">
  {{ message | capitalize }}
</div>
    
<script>
new Vue({
  el: '#app',
  data: {
    message: 'runoob'
  },
  filters: {
    capitalize: function (value) {
      if (!value) return ''
      value = value.toString()
      return value.charAt(0).toUpperCase() + value.slice(1)
    }
  }
})
</script>
```

过滤器可以串联：

```js
{{ message | filterA('arg1', arg2) }}
```

过滤器是 JavaScript 函数，因此可以接受参数。这里，message 是第一个参数，字符串 'arg1' 将传给过滤器作为第二个参数， arg2 表达式的值将被求值然后传给过滤器作为第三个参数。

```js
{{ message | filterA('arg1', arg2) }}
```

### 缩写

Vue.js 为两个最为常用的指令提供了特别的缩写：

v-bind 缩写：

```html
<!-- 完整语法 -->
<a v-bind:href="url"></a>
<!-- 缩写 -->
<a :href="url"></a>
```

v-on 缩写：

```html
<!-- 完整语法 -->
<a v-on:click="doSomething"></a>
<!-- 缩写 -->
<a @click="doSomething"></a>
```

