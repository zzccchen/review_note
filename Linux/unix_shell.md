# Unix shell

## 通配符

 通配符  | 作用
--------|---- 
 \*      | 匹配 0 或多个字符 <br> 例 a*b：a 与 b 之间可以有任意长度的任意字符，也可以一个也没有，如 aabcb，a01b，ab 等
 ?      | 匹配任意一个字符 <br> 例 a?b：a 与 b 之间有且只有一个字符，可以是任意字符，如 aab，adb，a0b 等
 [list] | 匹配 list 中的任意单一字符 <br> 例 a[xyz]b：a 与 b 之间有且只有一个字符，且只能是 x 或 y 或 z，如 axb，ayb，azb 等
 [!list] | 匹配除 list 中的任意单一字符 <br> 例 a[!0-9]b：a 与 b 之间有且只有一个字符，但不能是数字，如 axb，aab，a-b 等
 [c1-c2] | 匹配 c1 - c2 中的任意单一字符 <br> 例 a[0-9]b：a 与 b 之间有且只有一个字符，该字符是 0 - 9 之间的数字，如 a0b, a1b，...，a9b 等
 {string1, string2, ...} | 匹配 sring1 或 string2 （或更多）其中一字符串 <br> 例 a{abc,xyz,123}b：a 与 b 之间只能是 abc 或 xyz 或 123 这三个字符串之一

## 元字符

*TODO: https://www.cnblogs.com/fengkui/p/6133896.html*

## 转义字符

*TODO: https://www.cnblogs.com/fengkui/p/6133896.html*