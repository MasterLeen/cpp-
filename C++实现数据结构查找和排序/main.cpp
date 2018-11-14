#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <algorithm>
#include <sstream>//stringstream must include the header
using namespace std;
void SeqFind(const int& tmp);
void BinarySearch(const int& tmp);
void LinerExploration(int & num,char *cp);
void SearchStu(const int &num);
int Hash(char* cp);
void BubbleSort(vector<int> m_vec);
void SelectSort(vector<int> m_vec);
void InsertSort(vector<int> m_vec);
void QuickSort(vector<int> m_vec);
void QSort(vector<int>& m_vec,int low,int high);
void MergeSort(vector<int> m_vec);
void Print(const int & tmp);
void MergePass(vector<int> &m_vec, int head1, int head2, int tail2);

vector<int> m_vec;
map<int,char*> hash_map;
int main()
{
    /*m_vec = {3,10,13,17,40,43,50,70};
    SeqFind(43);
    SeqFind(5);
    BinarySearch(43);
    BinarySearch(5);*/

    //只输入两个姓名测试
    /*char** cp = new char* [30];
    cp[0] = "李华";
    cp[1] = "周军";
    for(int i = 0;i < 2;i++){
    int location = Hash(cp[i]);
    LinerExploration(location,cp[i]);
    }
    SearchStu(1);
    SearchStu(27);
    for(int i = 0;i < 30;i++)
        delete [] cp[i];
    delete cp;*/

    //5种排序算法
    cout<<"please input out of order digital series:"<<endl;
    /*int tmp;
    do{
        cin>>tmp;
        m_vec.push_back(tmp);
    }while(cin.get() != '\n');*/
    /*string ss;
    getline(cin,ss,'\n');//使用string流读取一行
    stringstream s;
    s<<ss;
    int tmp;
    while(s>>tmp)
        m_vec.push_back(tmp);
    BubbleSort(m_vec);
    SelectSort(m_vec);
    InsertSort(m_vec);
    QuickSort(m_vec);
    MergeSort(m_vec);*/

    //利用归并排序合并两个顺序表
    /*m_vec = {1,5,10,44,66,2,4,7,11,55};
    int head2 = 0,len = m_vec.size();
    for(int i = 0;i < len - 1;i++)
    {
        if(m_vec[i] > m_vec[i + 1])
        {
            head2 = i + 1;
            break;
        }
    }
    head2 = head2 == 0?m_vec.size() - 1:head2;
    MergePass(m_vec,0,head2,len - 1);
    for_each(m_vec.begin(),m_vec.end(),Print);*/

    return 0;
}

void SeqFind(const int &tmp)
{
    //vector<int>::iterator iter = m_vec.begin();
    int i = 0;
    for(;i < m_vec.size();i++) {
        if(m_vec[i] == tmp)
        {
            cout<<"found it! it's location in m_vec :"<<i<<endl;
            return;
        }
    }
    if(i == m_vec.size())
        cout<<"can not find it!"<<endl;
}

void BinarySearch(const int &tmp)
{
    int low = 0,high = m_vec.size() - 1,middle;
    while(low <= high)
    {
        middle = (low + high)/2;
        if(m_vec[middle] == tmp){
            cout<<"found it! it's location in m_vec :"<<middle<<endl;
            return;
        }
        else if(m_vec[middle] > tmp){
            high = middle - 1;
        }
        else
            low = middle + 1;
    }
    cout<<"can not find it!"<<endl;
}

int Hash(char* cp)
{
    int sum = 0;
    int len = strlen(cp);
    for(int i = 0;i < len;i++){
        sum += (int)*cp;
        cp++;
    }
    return abs(sum%30);
}

void LinerExploration(int & num,char* cp)
{
    while (hash_map.find(num) != hash_map.end())    num++;
    hash_map.insert(pair<int,char*>(num,cp));
}

void SearchStu(const int &num)
{
    map<int,char*>::iterator iter = hash_map.find(num);
    if(iter == hash_map.end())
        cout<<"false! can not find the stu!"<<endl;
    else
        cout<<"num = "<<iter->first<<" the stu name is :"<<iter->second<<endl;
}

void BubbleSort(vector<int> m_vec)
{
    for(int i = 0;i < m_vec.size();i++)
    {
        for(int j = 0;j < m_vec.size() - i - 1;j++)
        {
            if(m_vec[j] > m_vec[j + 1]){
                swap(m_vec[j],m_vec[j + 1]);
            }
        }
    }
    cout<<"the result of bubble sort algorithm is :"<<endl;
    for_each(m_vec.begin(),m_vec.end(),Print);//for_each需包含<algorithm>头文件
    cout<<endl;
}

void SelectSort(vector<int> m_vec)
{
    for(int i = 0;i < m_vec.size();i++)
    {
        int min = i;
        for(int j = i + 1;j < m_vec.size();j++){
            if(m_vec[j] < m_vec[min])
                min = j;
        }
        if(min != i)
            swap(m_vec[i],m_vec[min]);
    }
    cout<<"the result of select sort algorithm is :"<<endl;
    for_each(m_vec.begin(),m_vec.end(),&Print);
    cout<<endl;
}

void InsertSort(vector<int> m_vec)
{
    for(int i = 1;i < m_vec.size();i++)
    {
        if(m_vec[i] < m_vec[i - 1]){
            int temp = m_vec[i];
            int j = i - 1;
            for(;j >= 0 && m_vec[j] > temp;j--)
                m_vec[j + 1] = m_vec[j];
            m_vec[j + 1] = temp;
        }
    }
    cout<<"the result of insertion sort algorithm is :"<<endl;
    for_each(m_vec.begin(),m_vec.end(),&Print);
    cout<<endl;
}

void QuickSort(vector<int> m_vec)
{
    QSort(m_vec,0,m_vec.size() - 1);
    cout<<"the result of quick sort algorithm is :"<<endl;
    for_each(m_vec.begin(),m_vec.end(),&Print);
    cout<<endl;
}

//快排的思路是选取一个枢轴（比较值），将序列分成大于和小于枢轴的两部分再通过递归，直到序列不可分，因此每次递归都会确定枢轴的正确放置位置
void QSort(vector<int> &m_vec, int low, int high)
{
    int pivort;
    if(low < high)
    {
        {
            int temp = m_vec[low];
            int low1 = low;
            int high1 = high;
            while (low1 < high1) {
               while(low1 < high1 && m_vec[high1] >= temp) high1--;
               swap(m_vec[low1],m_vec[high1]);
               while(low1 < high1 && m_vec[low1] <= temp) low1++;
               swap(m_vec[low1],m_vec[high1]);
            }
            pivort = low1;
            QSort(m_vec,low,pivort - 1);
            QSort(m_vec,pivort + 1,high);
        }
    }
    else
        return;
}

void MergePass(vector<int>& m_vec,int head1,int head2,int tail2)
{
    int tail1 = head2 - 1,start = head1;
    vector<int> tmp;
    tmp.reserve(tail2 - head1 + 1);
    while (head1 <= tail1 && head2 <= tail2) {
        if(m_vec[head1] <= m_vec[head2])
            tmp.push_back(m_vec[head1++]);
        else
            tmp.push_back(m_vec[head2++]);
    }
    while(head1 <= tail1)
        tmp.push_back(m_vec[head1++]);
    while(head2 <= tail2)
        tmp.push_back(m_vec[head2++]);
    for(int i = 0;i < tmp.size();i++){
        m_vec[start + i] = tmp[i];
    }
    tmp.clear();
}

//用迭代法实现归并排序
void MergeSort(vector<int> m_vec)
{
    //步长每次都倍增
    int len = m_vec.size();
    for(int step = 1;step <= len;step <<= 1){
        int offset = step << 1;
        for(int index = 0;index < len;index += offset)
            MergePass(m_vec,index,min(index + step,len -1),min(index + offset - 1,len - 1));
    }
    cout<<"the result of merge sort algorithm is :"<<endl;
    for_each(m_vec.begin(),m_vec.end(),&Print);
    cout<<endl;
}

void Print(const int & tmp)
{
    cout<<tmp<<" ";
}
