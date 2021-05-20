#*我的leetcode 题解与测试函数*  

本项目包含一系列我的leetcode ~~解题算法~~以及测试函数 

包含两个文件, leetcode.cpp与leetcodeconcurrency.cpp  

leetcode.cpp:算法和测试函数

leetcodeconcurrency.cpp 多线程解题以及测试用相关部分

语言:~~C++~~

##_leetcode.cpp_

###~~普通题解~~

~~没啥新颖的,只有部分算法达到了100%,有兴趣就看吧~~

使用方法: solution[题目号]::leetcode一致的函数名,即可使用.

###测试函数

本文件包含一系列方便在提交前,能很方便的在初次调试自己算法之后,方便的构造测试用例提高ac率的函数.
包含在~~namespace testhelper~~里.
####testRvalue 

leetcode里很多题目输入值为vector<int> 每次我们构造测试用例需要类似:
	vector<int> v1;然后将v1传给函数,不是很方便.如果构造很多组的话,想名字想半天,复制名字还可能出错
所以用这个函数可以使用右值构造一个无名vector,传给我们编写的算法函数.
使用方法:testRvalue<RET, vector<int>>(leetcodefunction, {1, 2, 3, 4, 5});其中RET为测试函数的返回值.leetcodefunction 为我们编写的算法.

####printContainerResult与printVectorResult2d

leetcode很多算法结果为一元数组或者二元数组
当我们调通算法之后,测试数据可能会很多,观察结果就是重要的一环.
此时我们可以使用~~printContainerResult~~来打印vector/list,不管里面包含的是什么,只要该类有重载ostream opreator<<
就可以打印.
使用方法 testhelper::printContainerResult<vector>({1, 2, 3, 4, 5},/*", "*/)
注意.此函数有第二个参数选项:分隔符:默认元素使用","分割数组之间元素, 你可以使用任意字符串自己分隔,接受右值.
二元数组使用printVectorResult2d({{1}, {2}, {3}})进行打印.

####printTreeResultprefix

leetcode 有一少部分算法需要生成树把root保存到vector, 为了调试,我对上面的打印函数进行了改动.使用前序遍历
目前没有需要,所以中序遍历和后续遍历暂时不会加.
使用方法:testhelper::printContainerResult<vector>(function()) function必须返回vector/list<TreeNode*>
TODO,单独打印遍历树

####generateList

leetcode有很多算法是链表算法.
而我们调试的时候则需要自己创建链表,基于leetcode给定元素使用类似数组的格式提供.
所以此函数为基于vector生成一个链表.
使用方法:testhelper::generateList<ListNode, vector<int>>({ 1,1 }) 接受右值vector,返回链表头节点

####printListNode

打印链表看结果
使用方法:printListNode(testhelper::generateList<ListNode, vector<int>>({ 1,1 }))

####其他函数

generateVector/fillVector/print90degreeVector
不常用,不表


##__leetcodeconcurrency.cpp __

包含leetcode 多线程题目的题解
与leetcode同名的函数为题解
test为模拟测试环境
	
	