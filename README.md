###  Pintos 系统
Pintos is simple operating system framework for the 80x86 architecture. It supports kernel threads, loading and running user programs, and a file system. but it implements all of these in a very simple way.  In the Pintos projects, you and your project team will strengthen its support in all three of these areas. You will also add a virtual memory implementation.

#### HW1 
  * 通过修改pintos的线程休眠函数来保证pintos不会再一个线程休眠时忙等待
  * 通过修改pintos排队的方式来使得所有线程按优先级正确地被唤醒

#### HW2
*    在某个正在CPU中运行的线程发生优先级变化时，操作系统需要判断这个线程修改后的优先级是不是当前最大的优先级。如果不是，则要调度当前最高优先级的线程进入CPU中运行，也就是抢占调度。
*  同时，考虑刚刚创建的新线程的优先级，若一个线程创建了一个子线程，若子线程优先级较高，子线程需优先调度。

####  HW3
* 解决优先级反转的问题，实现优先级捐赠

####  HW4
* 理解条件变量的含义并通过priority-cond测试。
* 实现多级反馈队列的调度并通过所有的mlfqs-*测试

#### HW5
*  多线程编程 C++11

#### HW6/ HW7
* 银行家算法
* 页面置换算法
