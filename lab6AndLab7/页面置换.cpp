#include<bits/stdc++.h>
using namespace std;
int numf;
int num[51];
int pageFault;
int INF = 99999;
string input;

struct page
{
  int value;
  int latest_v_time;
  int future_used_t;
  page(int c, int t){value = c; latest_v_time = t; future_used_t = -1;}
};

bool isExist(deque<page> &frame, int v, int time)
{
   deque<page>::iterator pos;
   for(pos = frame.begin(); pos != frame.end(); pos++)
   {
     if((*pos).value == v)
     {
        (*pos).latest_v_time = time;                          
        return true; 
     }
   }
   pageFault++;
   return false;
}

void operate(deque<page> frame, string s, int b)
{
  if(s == "get")
    cout << isExist(frame, b, 0) << endl;
  else if(s == "pf")
    cout << pageFault << endl;
  else if(s == "seq")
  {
    deque<page>::iterator pos;
    for(pos = frame.begin(); pos != frame.end(); pos++)
       cout << (*pos).value;
    cout << endl;
  }
}

void FIF0(string s, int a, int b)
{
  deque<page> frame;
  for(int i = 0; i <= a-1; i++)
  {
    if(!isExist(frame, num[i], i))
    {
      if(frame.size() < numf)
        frame.push_back(page(num[i], i));
      else
      {
        frame.pop_front();
        frame.push_back(page(num[i], i));
      }
    }
  }
  operate(frame, s, b);
}

int LRU_victim(deque<page> &frame, int time)
{
   deque<page>::iterator pos;
   deque<page>::iterator victim = frame.begin();
   int min = INF;
   for(pos = frame.begin(); pos != frame.end(); pos++)
   {
    if((*pos).future_used_t == -1 &&(*pos).latest_v_time < min)
    {
      min = (*pos).latest_v_time;
      victim = pos;
    }
   }
   if(min != INF)
   {
   	 (*victim).value = num[time];
   	 (*victim).latest_v_time = time;
   	  return 1;
   }
   return 0;
}

void LRU(string s, int a, int b)
{
  deque<page> frame;
  deque<page>::iterator pos;
  for(int i = 0; i <= a-1; i++)
  {
    if(!isExist(frame, num[i], i))
    {
      if(frame.size() < numf)
          frame.push_back(page(num[i], i));
      else
      {
         LRU_victim(frame, i);
      }

    }
  }
  operate(frame, s, b);
}

void OPT(string s, int a, int b)
{
  deque<page> frame;
  deque<page>::iterator pos;
  for(int i = 0; i < a; i++)
  {
    if(!isExist(frame, num[i], i))
    {
      if(frame.size() < numf)
        frame.push_back(page(num[i], i));
      else
      {
         for(pos = frame.begin(); pos != frame.end(); pos++)
         {
             (*pos).future_used_t = -1;
             for(int j = i+1; j < input.length(); j++)
             {
                if((*pos).value == num[j])
                {
//                	cout << "Sd" ;
                  (*pos).future_used_t = j;
                  break;
                }
             }
         }
         deque<page>::iterator victim = frame.begin();
         int max = -1;
         int flag = 1;
         for(pos = frame.begin(); pos != frame.end(); pos++)
         {
            if(LRU_victim(frame, i))
              break;
            else
            {
               flag = 0;
               if((*pos).future_used_t > max)
               {
                  max = (*pos).future_used_t;
                  victim = pos;
               }
            }
         }
         if(!flag)
         {
           (*victim).value = num[i];
           (*victim).latest_v_time = i;        	
         }

      }
    }
  }
  operate(frame, s, b);
}

int main()
{
  while(cin >> numf)
  {
    cin >> input;
    for(int i = 0; i < input.length(); i++)
      num[i] = input[i] - '0';
    int k;
    cin >> k;
    while(k--)
    {
      int op;
      cin >> op;
      string s;
      cin >> s;
      int a = 0, b = 0;
      cin >> a;
      if(s == "get")
        cin >> b;
      pageFault = 0;
      if(op == 1)
        FIF0(s, a, b);
      else if(op == 2)
        LRU(s, a, b);
      else if( op == 3)
        OPT(s, a, b);
    }
  }
  return 0;
}

