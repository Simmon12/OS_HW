#include<iostream>
using namespace std;

// �����ж����еĽ����Ƿ��Ѿ���������Դ 
bool isFinish(bool Finish[], int n)    
{
    for(int i = 0; i < n; i++)          //�������еĽ��̣��������һ������û�б�������Դ���ͷŻ�false 
      if(Finish[i] == false)     
        return false;
    return true;
}

int main()
{
    int t;                            // t��ʾ������������ 
    cin >> t;
    int n, m;                         // n��ʾ������Ŀ��m��ʾ��Դ��Ŀ 
    while(t--)
    {
        // ��ʼ�� 
        cin >> n >> m;
        int available[m];              // ��ʾһ��ʼϵͳ��ÿһ����Դ�ɷ�������� 
        int allocation[n][m];          // ��ʾ�����Ѿ��Ѿ��������Դ���� 
        int need[n][m];                // ��ʾ���̵��������� 
        bool Finish[n];                // ��ʾ�����Ƿ��Ѿ������䣬 
        int work[m];                   // ��ʾϵͳ����ʱ��ÿһ����Դ�ɷ��������
        int safe[n];                   // ��ʾ��ȫ���е�����
        for(int i = 0; i < m; i++)
           cin >> available[i]; 
        for(int i = 0; i < n; i++)     
          for(int j = 0; j < m; j++)
             cin >> allocation[i][j];
        for(int i = 0; i < n; i++)
          for(int j = 0; j < m; j++)
             cin >> need[i][j];
             
             
        // �ж��Ƿ�ȫ
        for(int i = 0; i < n; i++)              // δ�����κη������ǰ����finish�����ʼ��Ϊfalse
            Finish[i] = false; 
        
		for(int i = 0; i < m; i++)
		    work[i] = available[i];            // ���Ƚ�work�����ֵ��ʼ��Ϊavailable��ֵ  
        
        int k = 0;
        for(int i = 0; i < n; i++)     
        {
            int right = 0;                       // ���ڼ�¼ÿ���������㰲ȫ�����ĸ���
            if(Finish[i] == false)               // ���ȵ�һ�������ǽ���iû�б�������Դ
            {
                for(int j = 0; j < m; j++)
                {
//     
                   if(need[i][j] <= work[j])      // ����ÿһ����Դ���������Ƿ�����ϵͳ�ɷ��������
                     right = right+1;             // �������Ļ����ͽ�right��1
                }


                if(right == m)                                      // ��right = m����ʾ����i�������������ԴС��ϵͳ������Դ������i�ɵõ���Դ
                {
                    Finish[i] = true;                                //����i��finishֵ��Ϊtrue���Ѿ���������Դ
                    safe[k] = i;                                     //��i��¼��safe�����У���¼��ȫ����
                    k = k +1;                                       // �����ж��Ƿ��������еĽ��̶��ܱ���ȫ������Դ
                    for(int j = 0; j < m; j++)                      // ����i��ɺ�Ҫ�ͷŵ��ѷ������Դallocation
                       work[j] = work[j] + allocation[i][j];
                    i = -1;                                         //����Ҫ��ȫ�����ǰ�������ˣ���i = -1�� ��ͷ��ʼ�ٽ����ж� 
                }               
            }

        }
//    
        if(k == n)                                                 // k = n�� ��ʾ���еĽ��̶�����������������ڰ�ȫ״̬��
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

