#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>  // define time unit
#include <vector>
#include <fstream>
#include <condition_variable>    // std::condition_variabl
using namespace std;

int global;
mutex for_global;
int cnt = 0;

void test()
{

    while(1)
    {
    	for_global.lock();
    	if(global >= 100)
    	{
    		for_global.unlock();
    		 break;
    	}
    	 
    	cout << "thread " <<this_thread::get_id() <<" ";
    	for(int j = 1; j <= 5; j++)
    	cout << global++ << " " ;
    	cout << endl;
    	
    	//每输出4行，空一行
		cnt++;
		if(cnt % 4 == 0)
		  cout << endl;
		   
    	for_global.unlock();
    }
}

int main() {
    global = 1;
    cout << "Main thread begin " << endl;
    vector<thread> threadset;               //子线程容器
	for(int k = 1; k <= 4; k++)
	{
		threadset.push_back(thread(test));
	
	}

	for(auto& subthread : threadset)        //子线程执行完后， 
	   subthread.join();
      
	cout << "Main thread finish" << endl; 
    return 0;
}
