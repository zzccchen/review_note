# JavaScript

## 输出

JavaScript 可以通过不同的方式来输出数据：

* 使用 `window.alert()` 弹出警告框。

* 使用 `document.write()` 方法将内容写到 HTML 文档中。

* 使用 `innerHTML` 写入到 HTML 元素。

* 使用 `console.log()` 写入到浏览器的控制台。

## 对代码行进行折行

可以在文本字符串中使用反斜杠对代码行进行换行。下面的例子会正确地显示：

```js
document.write("你好 \
世界!");
```

不能像这样折行：

```js
document.write \
("你好世界!");
```

## 变量

```js
var lastname="Doe", age=30, job="carpenter";

var lastname="Doe",
age=30,
job="carpenter";

var x,y,z=1;
// x,y 为 undefined， z 为 1
```

如果重新声明 JavaScript 变量，该变量的值不会丢失

### let 变量

```js
function varTest() {
    var x = 1;
    if (true) {
        var x = 2;       // 同样的变量!
        console.log(x);  // 2
    }
    console.log(x);  // 2
}

function letTest() {
    let x = 1;
    if (true) {
        let x = 2;       // 不同的变量
        console.log(x);  // 2  
    }
    console.log(x);  // 1
}
```

## 数组

```js
var cars=new Array();
cars[0]="Saab";
cars[1]="Volvo";
cars[2]="BMW";

var cars=new Array("Saab","Volvo","BMW");

var cars=["Saab","Volvo","BMW"];

// 判断对象是否为数组
// 1. 错
document.write(typeof cars); // object
// 2. 对
if(Array.isArray(cars)) {
    document.write("该对象是一个数组。") ;
}
// 3. 对
if (cars instanceof Array) {
    document.write("该对象是一个数组。") ;
}
```

## 对象

Undefined 这个值表示变量不含有值。

可以通过将变量的值设置为 `null` 来清空变量。

```js
var person={firstname:"John", lastname:"Doe", id:5566};

var person={
    firstname : "John",
    lastname  : "Doe",
    id        :  5566,
    fullName : function()
    {
        return this.firstName + " " + this.lastName;
    }
};

name=person.lastname;
name=person["lastname"];
person.fullName();
```

javaScript 对象中属性具有唯一性（这里的属性包括方法），如果有两个重复的属性，则以最后赋值为准。

## undefined 和 null

undefined 这个值表示变量不含有值。

可以通过将变量的值设置为 `null` 来清空变量。

```js
cars=null;
person=null;

var x,y;
if(x == null){
    document.write(x);
}
if(y == undefined){
    document.write(y);
}
// 二者都会输出 undefined
```

## 声明变量类型

```js
var carname=new String;
var x=      new Number;
var y=      new Boolean;
var cars=   new Array;
var person= new Object;
```

## 函数

```js
function myFunction(var1,var2)
{
    //代码
    // return var; (var 可选)
}
```

JavaScript 变量的生命期从它们被声明的时间开始。局部变量会在函数运行以后被删除。全局变量会在页面关闭后被删除。

如果您把值赋给尚未声明的变量，该变量将被自动作为 window 的一个属性。这条语句将声明 window 的一个属性 carname。

```js
carname="Volvo";
```

非严格模式下给未声明变量赋值创建的全局变量，是全局对象的可配置属性，可以删除。

如果变量在函数内没有声明（没有使用 `var` 关键字），该变量为全局变量。在 `func()` 被第一次调用之前， 该变量是不存在的即 `undefined`。`func()` 被调用过之后，该变量成为全局变量。

在 HTML 中, 全局变量是 window 对象: 所有数据变量都属于 window 对象。

### 自调用函数

自调用表达式会自动调用。

如果表达式后面紧跟 () ，则会自动调用。

通过添加括号，来说明它是一个函数表达式：

```js
(function () {
    var x = "Hello!!";      // 我将调用自己
})();
```

### arguments 对象

```js
x = findMax(1, 123, 500, 115, 44, 88);

function findMax() {
    var i, max = arguments[0];

    if(arguments.length < 2) return max;

    for (i = 0; i < arguments.length; i++) {
        if (arguments[i] > max) {
            max = arguments[i];
        }
    }
    return max;
}
```

## 常见的HTML事件

事件 | 描述
--|--
onchange | HTML 元素改变
onclick | 用户点击 HTML 元素
onmouseover | 用户在一个HTML元素上移动鼠标
onmouseout | 用户从一个HTML元素上移开鼠标
onkeydown | 用户按下键盘按键
onload | 浏览器已完成页面的加载

## 字符串

可以在字符串添加转义字符来使用引号：

```js
var x = 'It\'s alright';
var y = "He is called \"Johnny\"";

var txt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
var sln = txt.length;  // 字符串长度
```

## if else / switch / for / while

和 c++ 一样

`switch` 语句会使用恒等计算符(`===`)进行比较

## for-in 循环

```js
var person={fname:"John",lname:"Doe",age:25};

for (x in person)  // x 为属性名
{
    txt=txt + person[x];
}
```

## for-of 循环

`for in` 是遍历对象属性，`for of` 是遍历对象元素

for–of 循环并不能直接使用在普通的对象上，但如果我们按对象所拥有的属性进行循环，可使用内置的Object.keys() 方法

```js
for (var value of myArray) {
  console.log(value);
}
```

循环一个数组:

```js
let iterable = [10, 20, 30];

for (let value of iterable) {
  console.log(value);
}
```

可以使用 `const` 来替代 `let` ，这样它就变成了在循环里的不可修改的静态变量

```js
let iterable = [10, 20, 30];

for (const value of iterable) {
  console.log(value);
}
```

循环一个字符串:

```js
let iterable = "boo";

for (let value of iterable) {
  console.log(value);
}
```

循环一个类型化的数组(TypedArray)：

```js
let iterable = new Uint8Array([0x00, 0xff]);

for (let value of iterable) {
  console.log(value);
}
// 0
// 255
```

循环一个Map:

```js
let iterable = new Map([["a", 1], ["b", 2], ["c", 3]]);

for (let [key, value] of iterable) {
  console.log(value);
}
// 1
// 2
// 3

for (let entry of iterable) {
  console.log(entry);
}
// [a, 1]
// [b, 2]
// [c, 3]
```

循环一个 Set:

```js
let iterable = new Set([1, 1, 2, 2, 3, 3]);

for (let value of iterable) {
  console.log(value);
}
// 1
// 2
// 3
```

## JavaScript 标签

```js
list:
{
    document.write(cars[0] + "<br>"); 
    document.write(cars[1] + "<br>"); 
    document.write(cars[2] + "<br>"); 
    break list;
    document.write(cars[3] + "<br>"); 
    document.write(cars[4] + "<br>"); 
    document.write(cars[5] + "<br>"); 
}

outerloop:
for (var i = 0; i < 10; i++)
{
    innerloop:
    for (var j = 0; j < 10; j++)
    {
        if (j > 3)
        {
            break;
        }
        if (i == 2)
        {
            break innerloop;
        }
        if (i == 4)
        {
            break outerloop;
        }
        document.write("i=" + i + " j=" + j + "");
    }
}
```

## typeof, null, undefined

```js
var person = null;           // 值为 null(空), 但类型为对象

var person = undefined;     // 值为 undefined, 类型为 undefined
```

* `NaN` 的数据类型是 `number`

* 数组(Array)的数据类型是 `object`

* 日期(Date)的数据类型为 `object`

* `null` 的数据类型是 `object`

* 未定义变量的数据类型为 `undefined`

`constructor` 属性返回所有 JavaScript 变量的构造函数。

```js
"John".constructor                 // function String()  { [native code] }
(3.14).constructor                 // function Number()  { [native code] }
false.constructor                  // function Boolean() { [native code] }
[1,2,3,4].constructor              // function Array()   { [native code] }
{name:'John', age:34}.constructor  // function Object()  { [native code] }
new Date().constructor             // function Date()    { [native code] }
function () {}.constructor         // function Function(){ [native code] }
```

可通过 `instanceof` 操作符来判断对象的具体类型

```js
arr = [1,2,3];
if(arr instanceof Array){
    document.write("arr 是一个数组");
} else {
    document.write("arr 不是一个数组");
}
```

可以使用 `constructor` 属性来查看对象是否为数组 (包含字符串 "Array"):

```js
function isArray(myArray) {
    return myArray.constructor.toString().indexOf("Array") > -1;
}
```

可以使用 `constructor` 属性来查看对象是否为日期 (包含字符串 "Date"):

```js
function isDate(myDate) {
    return myDate.constructor.toString().indexOf("Date") > -1;
}
```

可以使用 `typeof` 来获取一个变量是否存在，如 `if(typeof a!="undefined"){}`，而不要去使用 `if(a)` 因为如果 a 不存在（未声明）则会出错。

## 类型转换

全局方法 `String(x)` 可以将数字转换为字符串。

Number 方法 `x.toString()` 或 `(x).toString()` 也是有同样的效果。

`Date()` 返回字符串。

全局方法 `Number(x)` 可以将字符串转换为数字。

全局方法 `Number(x)` 可将日期转换为数字。

```js
d = new Date();
Number(d)          // 返回 1404568027739
```

日期方法 `x.getTime()` 也有相同的效果。

```js
d = new Date();
d.getTime()        // 返回 1404568027739
```

## 正则

`search()` 方法 用于检索字符串中指定的子字符串，或检索与正则表达式相匹配的子字符串，并返回子串的起始位置。

`replace()` 方法 用于在字符串中用一些字符替换另一些字符，或替换一个与正则表达式匹配的子串。

`test()` 方法用于检测一个字符串是否匹配某个模式，如果字符串中含有匹配的文本，则返回 true，否则返回 false。

`exec()` 方法用于检索字符串中的正则表达式的匹配。该函数返回一个数组，其中存放匹配的结果。如果未找到匹配，则返回值为 null。

```js
var str = "Visit Runoob!";
var n = str.search(/Runoob/i);

// /Runoob/i  是一个正则表达式。
// Runoob  是一个正则表达式主体 (用于检索)。
// i  是一个修饰符 (搜索不区分大小写)。

var str = "Visit Runoob!";
var txt = str.replace(/microsoft/i,"Runoob");

var patt = /e/;
patt.test("The best things in life are free!");
// true
/e/.test("The best things in life are free!")

/e/.exec("The best things in life are free!");
// e
```

### 正则表达式修饰符

修饰符 | 描述
--|--
i | 执行对大小写不敏感的匹配
g | 执行全局匹配（查找所有匹配而非在找到第一个匹配后停止）
m | 执行多行匹配

### 正则表达式模式

表达式 | 描述
------|-----
[abc] | 查找方括号之间的任何字符。
[0-9] | 查找任何从 0 至 9 的数字。
(x\|y) | 查找任何以 \| 分隔的选项。

元字符 | 描述
---|---
\d | 查找数字。
\s | 查找空白字符。
\b | 匹配单词边界。
\uxxxx | 查找以十六进制数 xxxx 规定的 Unicode 字符。

量词 | 描述
---|---
n+ | 匹配任何包含至少一个 n 的字符串。
n* | 匹配任何包含零个或多个 n 的字符串。
n? | 匹配任何包含零个或一个 n 的字符串。

## throw、try 和 catch

```js
try {
  //在这里运行代码
} catch(err) {
  //在这里处理错误
}
```

`throw exception` 异常可以是 JavaScript 字符串、数字、逻辑值或对象。

```js
function myFunction() {
    var message, x;
    message = document.getElementById("message");
    message.innerHTML = "";
    x = document.getElementById("demo").value;
    try {
        if(x == "")  throw "值为空";
        if(isNaN(x)) throw "不是数字";
        x = Number(x);
        if(x < 5)    throw "太小";
        if(x > 10)   throw "太大";
    }
    catch(err) {
        message.innerHTML = "错误: " + err;
    }
}
```

## 变量提升

JavaScript 中，函数及变量的声明都将被提升到函数的最顶部

JavaScript 只有声明的变量会提升，初始化的不会。

```js
var x = 5; // 初始化 x

elem = document.getElementById("demo"); // 查找元素
elem.innerHTML = x + " " + y;           // 显示 x 和 y
                                        // y 输出了 undefined

var y = 7; // 初始化 y
```

## 严格模式

`"use strict"` 严格模式下

* 不能使用未声明的变量

* 不允许删除变量或对象

* 不允许删除函数

* 不允许变量重名

* 不允许使用八进制

* 不允许使用转义字符

* 不允许对只读属性赋值

* 不允许对一个使用getter方法读取的属性进行赋值

* 不允许删除一个不允许删除的属性

* 变量名不能使用 "eval"

* 变量名不能使用 "arguments"

* 由于一些安全原因，在作用域 `eval()` 创建的变量不能被调用

  ```js
  "use strict";
  eval ("var x = 2");
  alert (x);               // 报错
  ```

* 禁止 `this` 关键字指向全局对象

## 精度问题

```js
var x = 0.1;
var y = 0.2;
var z = x + y            // z 的结果为 0.3
if (z == 0.3)            // 返回 false

// 用整数的乘除法来解决：
var z = (x * 10 + y * 10) / 10;       // z 的结果为 0.3
```

## 程序块作用域

在每个代码块中 JavaScript 不会创建一个新的作用域，一般各个代码块的作用域都是全局的。

以下代码的的变量 i 返回 10，而不是 `undefined`：

```js
for (var i = 0; i < 10; i++) {
    // some code
}
return i;
```

## 表单验证

```js
function validateForm() {
    var x = document.forms["myForm"]["fname"].value;
    if (x == null || x == "") {
        alert("需要输入名字。");
        return false;
    }
}
```

```html
<form name="myForm" action="demo_form.php" onsubmit="return validateForm()" method="post">
名字: <input type="text" name="fname">
<input type="submit" value="提交">
</form>
```

`onsubmit="validateForm()"` 能够调用 `validateForm()` 对表单进行验证，但是在验证不通过的情况下，并不能阻止表单提交。

`onsubmit="return validateForm()"` 当验证不通过时，返回 `false`，可以阻止表单提交。

HTML 表单自动验证。如果表单字段 (fname) 的值为空，`required` 属性会阻止表单提交：

```html
<form action="demo_form.php" method="post">
  <input type="text" name="fname" required="required">
  <input type="submit" value="提交">
</form>
```

## JSON

`JSON.parse()` 将字符串转换为 JavaScript 对象
`JSON.stringify()` 用于将 JavaScript 值转换为 JSON 字符串

## void

```js
void func()
javascript:void func()
void(func())
javascript:void(func())
```

### 死链接

推荐：

```html
<a href="javascript:void(0)">单击此处什么也不会发生</a>
```

不推荐：

```html
<a href="#">单击此处什么也不会发生</a>
```

## DOM

### 查找

```js
// 查找 id="main" 的元素，然后查找 id="main" 元素中的所有 <p> 元素：
var x=document.getElementById("main");
var y=x.getElementsByTagName("p");

var x=document.getElementsByClassName("intro");
```

### 改变 HTML 内容

```js
document.getElementById(id).innerHTML="新的 HTML";
document.getElementById("p1").innerHTML="新文本!";
```

### 改变 HTML 属性

```js
document.getElementById(id).attribute="新属性值";
document.getElementById("image").src="landscape.jpg";
```

### 改变 HTML 样式

```js
document.getElementById(id).style.property="新样式";
document.getElementById("p2").style.color="blue";
```