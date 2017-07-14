#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <random>
#include <fstream>

using namespace std;

/************************
Following code is only one kind of implementation template.
Solve the problem in any way you want.
*************************/

void merge_array(int a[], int first, int mid, int last, int temp[])
{
    int  i = first;                       // ��j�ĳ�ʼֵ��Ϊ��ʼλ�� 
    int  j = mid + 1;                     // ��j�ĳ�ʼֵ��Ϊ�м�λ�õĺ�һ�� 
    int  k = 0;
    while(i <= mid && j <= last)          // �Ƚ������ֶ�Ӧ�Ĵ�С
    {                                     // ����ط���tmep������ 
    	if(a[i] < a[j])
    	   temp[k++] = a[i++];           // iҪ����һλ 
    	else
    	   temp[k++] = a[j++];           // jҪ����һλ 
    }
    
    //��ǰ�벿��ʣ�µ�Ԫ��ֱ�ӷ���temp������ 
    while(i <= mid)                     
        temp[k++] = a[i++];     
		
	//����벿��ʣ�µ�Ԫ��ֱ�ӷ���temp������ 
    while(j <= last)              
        temp[k++] = a[j++];    
		    
    //���Ѿ��ź���temp���鸳ֵ������a 
    for(int t = 0; t < k; t++)     
        a[first + t] = temp[t];    
}

void merge_sort(int array[], int first, int last, int temp[])
{
    if(first >= last) return;
    int mid = (first + last) / 2;
    merge_sort(array, first, mid, temp);             //��� 
    merge_sort(array, mid + 1, last, temp);          //��� 
    merge_array(array, first, mid, last, temp);      //�ϲ� 
    
}

void merge_start(int array[],int size)
{
   int* temp = new int[size+1];
   int first = 0;
   int last = size-1;
   merge_sort(array, first, size, temp);
   delete []temp;
}

void merge_two_thread(int array1[], int size1, int array2[], int size2, int total[])
{
   int* temp = new int[size1+size2+1];
   int mid = (size1+size2-1)/2;
   for(int i = 0; i < size1; i++)
   {
   	  total[i] = array1[i];
   	  total[size1+i] = array2[i];
   }
   merge_array(total, 0, mid , size1 + size2 -1, temp);
   delete []temp;   
}

bool isSorted(int array[], int size)
{
	for(int i = 0; i < size-1; i++)
	{
		if(array[i] > array[i+1])
		 return false;
	}
	return true;
}

int main()
{
    int n = 100000;
    int* number = new int[n+1];
    int* temp = new int[n+1];
    int* a = new int[n/2+1]; 
    int* b = new int[n/2+1];
    int k = 0, t = 0;
    for(int i=0;i<n;i++)
    {
        number[i] = rand() % 100000;
    }
    
    //������number��Ϊ�����֣�ǰ���ָ�����a���󲿷ָ�����b 
    for(int i = 0; i < n/2; i++)
    {
    	a[k] = number[i];
    	b[t] = number[n/2 + i];
    	k++;
    	t++;
    }
    
    int time3 = clock();
//    void merge_sort(int array[], int first, int last, int temp[])
    merge_sort(number, 0, n-1, temp); 
    int time4 = clock();
    cout << "���߳�: "  << time4 - time3 << endl;
//    ����˫�߳�
    int time1 = clock(); 
	thread t1(merge_start, a, n/2);
	thread t2(merge_start, b, n/2);
	
	t1.join();
	t2.join();
	
//	�鲢��������
	merge_two_thread(a, n/2, b, n/2, number) ;
	int time2 = clock();
	cout << "˫�߳�: " << time2 - time1 << endl;
//	���ź���Ľ�������result.txt�ļ��� 
    ofstream out("result.txt");
    for(int i = 0; i < n; i++)
       out << number[i] << endl;
       
    if(isSorted(number, n))
       cout << "Successful: isSorted" << endl;
    else
       cout << "Failed" << endl;
    delete []number;
    delete []temp;
    return 0;
}
