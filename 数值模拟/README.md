# LBM_pythonic

本仓库存放数值模拟课程作业

其主要内容为基于格子玻尔兹曼法的数值模拟及其后处理

具体包括：

* 基于格子玻尔兹曼法的 **温度场** 模拟
  * 一维温度传导（Q1-3）
  * 二维温度传导（Q4-6）
    * 对于结晶潜热处理方法为 **焓方法**（Q6)
* 基于格子玻尔兹曼法的 **二维流场** 模拟（Q7-8）
  * **卡门涡街** 现象模拟（Q8）

数据后处理绘制使用到了：`matplotlib`，`plotly`，`plotly_express` 库

代码语言：`Python3`

## 2. [在线访问](https://nbviewer.jupyter.org/github/zzccchen/review_note/tree/master/数值模拟)

* [Q1-6 题目](https://github.com/zzccchen/review_note/blob/master/%E6%95%B0%E5%80%BC%E6%A8%A1%E6%8B%9F/Q1-7%E7%9B%B8%E5%85%B3%E6%96%87%E6%A1%A3/2019.04.23%2B%E4%B8%8A%E6%9C%BA%E9%A2%98%E7%9B%AE%E5%8F%8A%E8%A6%81%E6%B1%82%2B-%2B%E6%B8%A9%E5%BA%A6%E5%9C%BA%E8%AE%A1%E7%AE%97.pdf)

* [Q1_OneDimDiffusion](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q1_OneDimDiffusion/Q1_Answer.ipynb)

  * **利用有限差分法模型对一维热传导问题进行模拟**
  * 仅对高温边界温度进行固定

* [Q2_OneDimDiffusion](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q2_OneDimDiffusion/Q2_Answer.ipynb)

  * 利用有限差分法模型对一维热传导问题进行模拟
  * **仅对高温边界温度进行固定**
  * **对边界处理进行更详细的论述**

* [Q3_OneDimDiffusion](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q3_OneDimDiffusion/Q3_Answer.ipynb)

  * 利用有限差分法模型对一维热传导问题进行模拟
  * 仅对高温边界温度进行固定
  * **对两子区域热传导的边界处理进行的论述**

* [Q4_Optimization](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q4_Optimization/Q4_Optimization.ipynb)

  * 利用有限差分法模型对二维热传导问题进行模拟
  * **针对传统 `for` 循环算法提出 `向量法`、`矩阵法` 及使用 `numba` 库进行代码优化加速**

* [Q4_TwoDimDiffusion](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q4_TwoDimDiffusion/Q4_Answer.ipynb)

  * **利用有限差分法模型对二维热传导问题进行模拟**
  * **对二维边界处理进行论述**
  * **对高温边界温度进行固定**

* [Q5_TwoDimDiffusion](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q5_TwoDimDiffusion/Q5_Answer.ipynb)

  * 利用有限差分法模型对二维热传导问题进行模拟
  * **对低温边界温度进行固定**
  * **对部分边界设置绝热条件**

* [Q6_TwoDimDiffusion](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q6_TwoDimDiffusion/Q6_Answer.ipynb)

  * **在 Q5 基础上增加结晶潜热计算**

* [Q7-8 题目](https://github.com/zzccchen/review_note/blob/master/%E6%95%B0%E5%80%BC%E6%A8%A1%E6%8B%9F/Q7-8%E7%9B%B8%E5%85%B3%E6%96%87%E6%A1%A3/2019%2B%E4%B8%8A%E6%9C%BA%E9%A2%98%E7%9B%AE%E5%8F%8A%E8%A6%81%E6%B1%82%2B-%2B%E6%B5%81%E5%9C%BA%E8%AE%A1%E7%AE%97.pdf)

* [Q7_LBflowsBGK](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q7_LBflowsBGK/Q7_LBflowsBGK.ipynb)

  * **基于 `LBGK` 和 `D2Q9` 模型对二维流场进行模拟**

* [Q8_KarmanVortexStreet](https://nbviewer.jupyter.org/github/zzccchen/review_note/blob/master/数值模拟/Q8_KarmanVortexStreet/Q8_KarmanVortexStreet.ipynb)

  * 基于 `LBGK` 和 `D2Q9` 模型对二维流场的 **卡门涡街现象进行模拟**
