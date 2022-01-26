# Commodities-information

## 前言

- 这是电子科技大学软件工程大一期末的程序项目实践，是一个商品信息管理系统。

- 代码由纯粹的C语言编写，无用户界面设计。

- 由于作者本人仅仅是初学者水平，有诸多方面不能顾全，可能出现bug或者设计不合理之处。

- 作者的开发工具为Visual Studio 2019，如果开发工具不相同，**可能会出现不兼容的问题**。

## 功能介绍

1. 注册，登录与注销（很简陋，但是聊胜于无）
2. 查看所有商品的信息，并可以打开文本文件查看**（此处需要修改源代码）**
3. 利用商品ID修改指定的商品信息
4. 利用商品ID查询指定的商品信息
5. 利用商品ID删除指定的商品信息
6. 删除所有的商品信息
7. 给商品价格进行排序（没什么用）

## 注意

- 关于打开文本文件查看的部分，需要根据实际情况修改代码，源代码为：

```c
system("C:/Users/33914/source/repos/软件界面/软件界面/商品信息.txt");
```

​       此处需要根据实际情况修改文件路径才可正常发挥作用。

- 代码中带有多个后缀为**”_s"**的函数，这可能是Visual Studio 2019 特有的函数，如果使用其它开发工具，可能会出现无法调试的情况，此时需要修改代码。部分修改如下：

```c
scanf_s() -> scanf()
fopen_s(&fp,filename,"a+") -> fp=fopen(filename,"a+")//返回值不一样了
strcpy_s(str1,MAX,str2) -> strcpy(str1,str2)    
```

