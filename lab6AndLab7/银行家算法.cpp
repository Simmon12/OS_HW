#include<iostream>
using namespace std;

// 用于判断所有的进程是否都已经被分配资源 
bool isFinish(bool Finish[], int n)    
{
    for(int i = 0; i < n; i++)          //遍历所有的进程，如果存在一个进程没有被分配资源，就放回false 
      if(Finish[i] == false)     
        return false;
    return true;
}

int main()
{
    int t;                            // t表示测试样例次数 
    cin >> t;
    int n, m;                         // n表示进程数目，m表示资源数目 
    while(t--)
    {
        // 初始化 
        cin >> n >> m;
        int available[m];              // 表示一开始系统中每一个资源可分配的数量 
        int allocation[n][m];          // 表示进程已经已经分配的资源数组 
        int need[n][m];                // 表示进程的需求数组 
        bool Finish[n];                // 表示进程是否已经被分配， 
        int work[m];                   // 表示系统任意时刻每一个资源可分配的数量
        int safe[n];                   // 表示安全序列的数组
        for(int i = 0; i < m; i++)
           cin >> available[i]; 
        for(int i = 0; i < n; i++)     
          for(int j = 0; j < m; j++)
             cin >> allocation[i][j];
        for(int i = 0; i < n; i++)
          for(int j = 0; j < m; j++)
             cin >> need[i][j];
             
             
        // 判断是否安全
        for(int i = 0; i < n; i++)              // 未进行任何分配操作前，将finish数组初始化为false
            Finish[i] = false; 
        
		for(int i = 0; i < m; i++)
		    work[i] = available[i];            // 首先将work数组的值初始化为available的值  
        
        int k = 0;
        for(int i = 0; i < n; i++)     
        {
            int right = 0;                       // 用于记录每个进程满足安全条件的个数
            if(Finish[i] == false)               // 首先第一个条件是进程i没有被分配资源
            {
                for(int j = 0; j < m; j++)
                {
//     
                   if(need[i][j] <= work[j])      // 遍历每一个资源的需求量是否满足系统可分配的数量
                     right = right+1;             // 如果满足的话，就将right加1
                }


                if(right == m)                                      // 当right = m，表示进程i所申请的所有资源小于系统现有资源，进程i可得到资源
                {
                    Finish[i] = true;                                //进程i的finish值变为true，已经被分配资源
                    safe[k] = i;                                     //将i记录到safe数组中，记录安全序列
                    k = k +1;                                       // 用于判断是否满足所有的进程都能被安全分配资源
                    for(int j = 0; j < m; j++)                      // 进程i完成后，要释放掉已分配的资源allocation
                       work[j] = work[j] + allocation[i][j];
                    i = -1;                                         //由于要求安全序列是按升序，因此，另i = -1， 从头开始再进行判断 
                }               
            }

        }
//    
        if(k == n)                                                 // k = n， 表示所有的进程都满足分配条件，处于安全状态。
        {
           cout << "Yes ";
           for(int i = 0; i < n-1; i++)     
             cout << safe[i] << " ";
           cout << safe[n-1] << endl;
        }
        else
        cout << "No" << endl;
    }
}

