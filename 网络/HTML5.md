# HTML5

## [HTML字符实体]("https://www.runoob.com/tags/ref-entities.html")

显示结果 | 描述 | 实体名称 | 实体编号
--|--|--|--
 &nbsp; | 空格 | `&nbsp;` | `&#160;`
< | 小于号 | `&lt;` | `&#60;`
> | 大于号 | `&gt;` | `&#62;`
& | 和号 | `&amp;` | `&#38;`
" | 引号 | `&quot;` | `&#34;`
' | 撇号 | `&apos;` (IE不支持) | `&#39;`
￠ | 分 | `&cent;` | `&#162;`
£ | 镑 | `&pound;` | `&#163;`
¥ | 人民币/日元 | `&yen;` | `&#165;`
€ | 欧元 | `&euro;` | `&#8364;`
§ | 小节 | `&sect;` | `&#167;`
© | 版权 | `&copy;` | `&#169;`
® | 注册商标 | `&reg;` | `&#174;`
™ | 商标 | `&trade;` | `&#8482;`
× | 乘号 | `&times;` | `&#215;`
÷ | 除号 | `&divide;` | `&#247;`

## URL 字符编码

URL 只能使用 ASCII 字符集.

来通过因特网进行发送。由于 URL 常常会包含 ASCII 集合之外的字符，URL 必须转换为有效的 ASCII 格式。

URL 编码使用 "%" 其后跟随两位的十六进制数来替换非 ASCII 字符。

URL 不能包含空格。URL 编码通常使用 + 来替换空格。

## 标签

### 基本标签

```html
<h1>最大的标题</h1>
<h2> . . . </h2>
<h3> . . . </h3>
<h4> . . . </h4>
<h5> . . . </h5>
<h6>最小的标题</h6>

<p>这是一个段落。</p>
<br /> （换行）
<hr /> （水平线）
<!-- 这是注释 -->
```

### 文本格式化

```html
<b> 粗体文本 </b>
<code> 计算机代码 </code>
<em> 强调文本 </em>
<i> 斜体文本 </i>
<kbd> 键盘输入 </kbd>
<pre> 预格式化文本 </pre>
<!-- 被包围在 <pre> 标签 元素中的文本通常会保留空格和换行符。而文本也会呈现为等宽字体。 -->
<small> 更小的文本 </small>
<strong> 重要的文本 </strong>

<abbr> （缩写）</abbr>
<address> （联系信息）</address>
<bdo> （文字方向）</bdo>
<blockquote> （从另一个源引用的部分）</blockquote>
<cite> （工作的名称）</cite>
<del> （删除的文本）</del>
<ins> （插入的文本）</ins>
<sub> （下标文本）</sub>
<sup> （上标文本）</sup>
```

## 链接

```html
普通的链接：<a href="http://www.example.com/">链接文本</a>
图像链接： <a href="http://www.example.com/"><img src="URL" alt="替换文本"></a>
邮件链接： <a href="mailto:webmaster@example.com">发送e-mail</a>
书签：
<a id="tips">提示部分</a>
<a href="#tips">跳到提示部分</a>
```

## 图片

```html
<img src="URL" alt="替换文本" height="42" width="42">
```

## 样式/区块

```html
<style type="text/css">
h1 {color:red;}
p {color:blue;}
</style>
<div>文档中的块级元素</div>
<span>文档中的内联元素</span>
```

## [列表]("https://www.runoob.com/html/html-lists.html")

### 无序列表

```html
<ul>
    <li>项目</li>
    <li>项目</li>
</ul>
```

### 有序列表

```html
<ol>
    <li>第一项</li>
    <li>第二项</li>
</ol>
```

### 定义列表

```html
<dl>
  <dt>项目 1</dt>
    <dd>描述项目 1</dd>
  <dt>项目 2</dt>
    <dd>描述项目 2</dd>
</dl>
```

## [表格]("https://www.runoob.com/html/html-tables.html")

```html
<table border="1">
  <tr>
    <th>表格标题</th>
    <th>表格标题</th>
  </tr>
  <tr>
    <td>表格数据</td>
    <td>表格数据</td>
  </tr>
</table>
```

## 框架

```html
<iframe src="demo_iframe.htm"></iframe>
```

## [表单]("https://www.runoob.com/html/html-forms.html)

```html
<form action="demo_form.php" method="post/get">
<input type="text" name="email" size="40" maxlength="50">
<input type="password">
<input type="checkbox" checked="checked">
<input type="radio" checked="checked">
<input type="submit" value="Send">
<input type="reset">
<input type="hidden">
<select>
<option>苹果</option>
<option selected="selected">香蕉</option>
<option>樱桃</option>
</select>
<textarea name="comment" rows="60" cols="20"></textarea>

</form>
```

## logo

HTML`<title>` 元素不仅可以显示文本，也可以在左侧显示 logo 等图片。

显示时，要将 `<link>` 标签放入 `<head>` 里。

举例：

```html
<!doctype HTML>
<html>

<head>
    <link rel="shortcup icon" href="图片url">
    <title>这是一个带图片的标签</title>
</head>

<body>
    ……
    ……
    ……
</body>

</html>
```
