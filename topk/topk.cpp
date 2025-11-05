#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <cstdlib>
#include <ctime>
using namespace std;
void AdjustDown(vector<int>& arr, int size, int parent)
{
    int child = parent * 2 + 1;
    while (child < size)
    {
        if (child + 1 < size && arr[child + 1] < arr[child])
        {
            child++;
        }
        if (arr[child] < arr[parent])
        {
            swap(arr[parent], arr[child]);
            parent = child;
        }
        else
        {
            break;
        }
    }
}
void AdjustUp(vector<int>& arr, int child)
{
    int parent = (child - 1) / 2;
    while (child > 0)
    {
        if (arr[parent] < arr[child])
        {
            swap(arr[parent], arr[child]);
            child = parent;
            parent = (child - 1) / 2;
        }
        else
        {
            break;
        }
    }
}
void CreateNDate()
{
	// 造数据
	int n = 10000;
	srand(time(0));
	const char* file = "data.txt";
	FILE* fin = fopen(file, "w");
	if (fin == NULL)
	{
		perror("fopen error");
		return;
	}

	for (size_t i = 0; i < n; ++i)
	{
		int x = rand() % 1000000;
		fprintf(fin, "%d\n", x);
	}

	fclose(fin);
}

void PrintTopK(vector<int>& arr,int k)
{
    int n = 10000;
    const char* file = "data.txt";
	FILE* fout = fopen(file, "r");
    if (fout == NULL)
	{
		perror("fopen error");
		return;
	}
    
    for(size_t i = 0; i < k; ++i)
    {
        int tmp=0;
        fscanf(fout,"%d",&tmp);
        arr.push_back(tmp);
        AdjustUp(arr,i);
    }
    int x=0;
    while(fscanf(fout,"%d",&x)!=EOF)
    {
        if(x>arr[0])
        {
            arr[0]=x;
            AdjustDown(arr,k,0);
        }
    }
}
// void PrintTopK(const char* file, int k)
// {
// 	FILE* fout = fopen(file, "r");
// 	if (fout == NULL)
// 	{
// 		perror("fopen error");
// 		return;
// 	}

// 	// 建一个k个数小堆
// 	int* minheap = (int*)malloc(sizeof(int) * k);
// 	if (minheap == NULL)
// 	{
// 		perror("malloc error");
// 		return;
// 	}

// 	// 读取前k个，建小堆
// 	for (int i = 0; i < k; i++)
// 	{
// 		fscanf(fout, "%d", &minheap[i]);
// 		AdjustUp(minheap, i);
// 	}

// 	int x = 0;
// 	while (fscanf(fout, "%d", &x) != EOF)
// 	{
// 		if (x > minheap[0])
// 		{
// 			minheap[0] = x;
// 			AdjustDown(minheap, k, 0);
// 		}
// 	}

// 	for (int i = 0; i < k; i++)
// 	{
// 		printf("%d ", minheap[i]);
// 	}
// 	printf("\n");

// 	free(minheap);
// 	fclose(fout);
// }
// void topk(vector<int> &arr, int k)
// {
//     // 对前k个数建小堆
//     for (int i = k / 2 - 1; i >= 0; i--)
//     {
//         AdjustDown(arr, k, i);
//     }
//     // 依次读取后面的值，如果比堆顶大，则向下调整，此时最大的元素被换到堆底，当前堆最小的元素在堆顶
//     // 因为如果是大根堆的话，如果此时堆顶的元素是整个数组中最大的元素，将无法跟任何元素交换，导致只有该元素找到，其余元素无法找到
//     // 当循环结束时，堆顶的元素大于堆外的任何元素
//     for (int i = k + 1; i < arr.size(); i++)
//     {
//         if (arr[i] > arr[0])
//         {
//             swap(arr[0], arr[i]);
//             AdjustDown(arr, 5, 0);
//         }
//     }
//     for (int i = 0; i < 5; i++)
//     {
//         cout << arr[i] << " ";
//     }
// }

int main()
{
    // vector<int> arr;
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<> dis(1, 1000); // 生成范围为 [1, 1000]

    // for (int i = 0; i < 100; i++)
    // {
    //     arr.push_back(dis(gen));
    // }
    // for (auto e : arr)
    // {
    //     cout << e << " ";
    // }
    // cout << endl;
    // topk(arr, 5);
    // return 0;
    vector<int> arr;
    //CreateNDate();
    PrintTopK(arr,10);
    for(auto e:arr)
    {
        cout<<e<<' '<<endl;
    }
}
