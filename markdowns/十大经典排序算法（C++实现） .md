## 0、算法分类

**排序算法是《数据结构与算法》中最基本的算法之一。**

十种常见排序算法可以分为两大类：

- **比较类排序**：通过比较来决定元素间的相对次序，时间复杂度为 O(nlogn)～O(n²)。
- **非比较类排序**：不通过比较来决定元素间的相对次序，其时间复杂度可以突破 O(nlogn)，以线性时间运行。

![img](G:\Git\studyLinuxC\assets\849589-20190306165258970-1789860540.png)



![图片](G:\Git\studyLinuxC\assets\On.png)



**名次解释**：

- **时间/空间复杂度**：描述一个算法执行时间/占用空间与数据规模的增长关系。
- **n**：待排序列的个数。
- **k**：“桶”的个数（上面的三种非比较类排序都是基于“桶”的思想实现的）。
- **In-place**：原地算法，指的是占用常用内存，不占用额外内存。空间复杂度为 O(1) 的都可以认为是原地算法。
- **Out-place**：非原地算法，占用额外内存。
- **稳定性**：假设待排序列中两元素相等，排序前后这两个相等元素的相对位置不变，则认为是稳定的。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 1、冒泡排序（Bubble Sort）

冒泡排序（Bubble Sort），顾名思义，就是指越小的元素会经由交换慢慢“浮”到数列的顶端。

**1.1 算法描述**

- 从左到右，依次比较相邻的元素大小，更大的元素交换到右边；
- 从第一组相邻元素比较到最后一组相邻元素，这一步结束最后一个元素必然是参与比较的元素中最大的元素；
- 重复从左到后比较，而前一轮中得到的最后一个元素不参与比较，得出新一轮的最大元素；
- 按照上述规则，每一轮结束会减少一个元素参与比较，直到没有任何一组元素需要比较。

**1.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015223238449-2146169197.gif)

**1.3 代码实现**

```c++
// 交换宏
#define swap(x,y) x=x+y,y=x-y,x=x-y

void bubbleSort(int arr[], int n)
{
	bool bExchange = false; // 交换标志

	for (int i = 0; i < n - 1; i++) // 最多做n-1趟排序 
	{
		bExchange = false;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j + 1], arr[j]);
				bExchange = true; // 发生了交换，故将交换标志置为真
			}
		}

		if (!bExchange) // 考虑有一趟排序未发生交换的理想情况，可以提前终止算法
			return;
	}
}
```

**1.4 算法分析**

冒泡排序属于**交换排序**，是**稳定排序**，平均时间复杂度为 O(n²)，空间复杂度为 O(1)。

但是我们常看到冒泡排序的**最优时间复杂度是 O(n)**，那要如何优化呢？

上面就是优化后的代码，用了一个 bExchange 参数记录新一轮的排序中元素是否做过交换，如果没有，说明前面参与比较过的元素已经是正序，那就没必要再从头比较了，就可以优化到 O(n) 。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 2、选择排序（Selection Sort）

选择排序（Selection Sort）是一种简单直观的排序算法。它的基本思想就是，每一趟`n-i+1(i=1,2,…,n-1)`个记录中选取值最小的索引作为有序序列的第 i 个索引。

**2.1 算法描述**

- 在未排序序列中找到最小（大）元素，存放到排序序列的起始位置;
- 在剩余未排序元素中继续寻找最小（大）元素，放到已排序序列的末尾;
- 重复步骤 2，直到所有元素排序完毕。

**2.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015224719590-1433219824.gif)

**2.3 代码实现**

```c++
void selectSort(int* arr, int n)
{
	int minIndex = 0;
	int temp;

	for (int i = 0; i < n - 1; i++) // 排序n-1次
	{
		minIndex = i; // minIndex设置为每轮未排序序列的第一个位置

		for (int j = i + 1; j < n; j++)
		{
			// 每轮中最小的值索引，赋值给minIndex
			if (arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
		}

		// 将每轮中最小的值与每轮中第一个位置(i)的值进行交换
		if (minIndex != i) // 如果这轮中最小的值刚好在第一个位置，就不用交换了
		{
			temp = arr[minIndex];
			arr[minIndex] = arr[i];
			arr[i] = temp;
		}
	}
}
```

**2.4 算法分析**

选择排序是**不稳定排序**，时间复杂度固定为 O(n²)，因此它不适用于数据规模较大的序列。不过它也有优点，就是不占用额外的内存空间。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 3、插入排序（Insertion Sort）

插入排序（Insertion-Sort）的算法描述是一种简单直观的排序算法。它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。

**3.1 算法描述**

- 将第一待排序序列第一个元素看做一个有序序列，把第二个元素到最后一个元素当成是未排序序列。
- 从头到尾依次扫描未排序序列，将扫描到的每个元素与有序序列的每个元素进行比较，小于哪个有序序列的元素就进行交换，相当于插入到该元素索引位置。（如果待插入的元素与有序序列中的某个元素相等，则将待插入元素插入到相等元素的后面。）

**3.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015225645277-1151100000.gif)

**3.3 代码实现**

```c++
void insertSort(int arr[], int n) {
	int i, j, temp;
	for (i = 1; i < n; i++) {
		temp = arr[i];

		for (j = i; j > 0 && arr[j - 1] > temp; j--)
			arr[j] = arr[j - 1]; // 把已排序元素逐步向后挪位

		arr[j] = temp; // 插入
	}
}
```

**3.4 算法分析**

插入排序在实现上，通常采用 in-place 排序（即只需用到 O(1) 的额外空间的排序），因而在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 4、希尔排序（Shell Sort）

1959年Shell发明，第一个突破 O(n2) 的排序算法，是插入排序的改进版。它与插入排序的不同之处在于，它会优先比较距离较远的元素。希尔排序又叫**缩小增量排序**。

**4.1 算法描述**

先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，具体算法描述：

- 选择一个增量序列 t1，t2，…，tk，其中 ti>tj，tk=1；
- 按增量序列个数 k，对序列进行 k 趟排序；
- 每趟排序，根据对应的增量 ti，将待排序列分割成若干长度为 m 的子序列，分别对各子表进行直接插入排序。仅增量因子为 1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。

**4.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20180331170017421-364506073.gif)

**4.3 代码实现**

```c++
void shellSort(int *arr, int size)  
{  
    int i, j, tmp, increment;  
    for (increment = size/ 2; increment > 0; increment /= 2) {    
        for (i = increment; i < size; i++) {  
            tmp = arr[i];  
            for (j = i - increment; j >= 0 && tmp < arr[j]; j -= increment) {  
                arr[j + increment] = arr[j];  
            }  
            arr[j + increment] = tmp;
        }  
    }  
}  
```

**4.4 算法分析**

快速排序是**不稳定排序**，所比较快，因为相比冒泡排序，每次交换是跳跃式的。每次排序的时候设置一个基准点，将小于等于基准点的数全部放到基准点的左边，将大于等于基准点的数全部放到基准点的右边。这样在每次交换的时候就不会像冒泡排序一样每次只能在相邻的数之间进行交换，交换的距离就大的多了。因此总的比较和交换次数就少了，速度自然就提高了。当然在最坏的情况下，仍可能是相邻的两个数进行了交换。因此快速排序的最差时间复杂度和冒泡排序是一样的都是 O(n²)，它的平均时间复杂度为 O(n log n)。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 5、归并排序（Merge Sort）

归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为 2- 路归并。

**5.1 算法描述**

- 把长度为 n 的输入序列分成两个长度为 n/2 的子序列；
- 对这两个子序列分别采用归并排序；
- 将两个排序好的子序列合并成一个最终的排序序列。

**5.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015230557043-37375010.gif)

**5.3 代码实现**

```c++
/* 将 arr[L..M] 和 arr[M+1..R] 归并 */
void merge(int arr[], int L, int M, int R) {
    int LEFT_SIZE = M - L + 1;
    int RIGHT_SIZE = R - M;
    int left[LEFT_SIZE];
    int right[RIGHT_SIZE];
    int i, j, k;
    // 以 M 为分割线，把原数组分成左右子数组
    for (i = L; i <= M; i++) left[i - L] = arr[i];
    for (i = M + 1; i <= R; i++) right[i - M - 1] = arr[i];
    // 再合并成一个有序数组（从两个序列中选出最小值依次插入）
    i = 0; j = 0; k = L;
    while (i < LEFT_SIZE && j < RIGHT_SIZE) arr[k++] = left[i] < right[j] ? left[i++] : right[j++];
    while (i < LEFT_SIZE) arr[k++] = left[i++];
    while (j < RIGHT_SIZE) arr[k++] = right[j++];
}

void merge_sort(int arr[], int L, int R) {
    if (L == R) return;
    // 将 arr[L..R] 平分为 arr[L..M] 和 arr[M+1..R]
    int M = (L + R) / 2;
    // 分别递归地将子序列排序为有序数列
    merge_sort(arr, L, M);
    merge_sort(arr, M + 1, R);
    // 将两个排序后的子序列再归并到 arr
    merge(arr, L, M, R);
}
```

**5.4 算法分析**

快速排序是**不稳定排序**，所比较快，因为相比冒泡排序，每次交换是跳跃式的。每次排序的时候设置一个基准点，将小于等于基准点的数全部放到基准点的左边，将大于等于基准点的数全部放到基准点的右边。这样在每次交换的时候就不会像冒泡排序一样每次只能在相邻的数之间进行交换，交换的距离就大的多了。因此总的比较和交换次数就少了，速度自然就提高了。当然在最坏的情况下，仍可能是相邻的两个数进行了交换。因此快速排序的最差时间复杂度和冒泡排序是一样的都是 O(n²)，它的平均时间复杂度为 O(n log n)。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 6、快速排序（Quick Sort）

快速排序（Quick Sort），是冒泡排序的改进版，之所以“快速”，是因为使用了**分治法**。它也属于**交换排序**，通过元素之间的位置交换来达到排序的目的。

基本思想：通过一趟排序将待排记录分隔成独立的两部分，其中一部分记录的关键字均比另一部分的关键字小，则可分别对这两部分记录继续进行排序，以达到整个序列有序。

**6.1 算法描述**

- 从数列中挑出一个元素，称为 “基准”（pivot）；
- 重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作；
- 递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序。

**6.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015230936371-1413523412.gif)

**6.3 代码实现**

```c++
void quickSort(int arr[], int begin, int end)
{
	int i, j, t, pivot;
	if (begin > end) // 递归，直到start = end为止
		return;

	pivot = arr[begin]; // 基准数
	i = begin;
	j = end;
	while (i != j)
	{
		// 从右向左找比基准数小的数 （要先从右边开始找）
		while (arr[j] >= pivot && i < j)
			j--;
		// 从左向右找比基准数大的数
		while (arr[i] <= pivot && i < j)
			i++;
		if (i < j)
		{
			// 交换两个数在数组中的位置
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}

	// 最终将基准数归位
	arr[begin] = arr[i];
	arr[i] = pivot;
	quickSort(arr, begin, i - 1); // 继续处理左边的，这里是一个递归的过程
	quickSort(arr, i + 1, end); // 继续处理右边的 ，这里是一个递归的过程
}
```

**6.4 算法分析**

快速排序是**不稳定排序**，所比较快，因为相比冒泡排序，每次交换是跳跃式的。每次排序的时候设置一个基准点，将小于等于基准点的数全部放到基准点的左边，将大于等于基准点的数全部放到基准点的右边。这样在每次交换的时候就不会像冒泡排序一样每次只能在相邻的数之间进行交换，交换的距离就大的多了。因此总的比较和交换次数就少了，速度自然就提高了。当然在最坏的情况下，仍可能是相邻的两个数进行了交换。因此快速排序的最差时间复杂度和冒泡排序是一样的都是 O(n²)，它的平均时间复杂度为 O(n log n)。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 7、堆排序（Heap Sort）

堆排序（Heapsort）是指利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：即子结点的键值或索引总是小于（或者大于）它的父节点。

**7.1 算法描述**

- 将初始待排序关键字序列(R1,R2….Rn)构建成大顶堆，此堆为初始的无序区；
- 将堆顶元素R[1]与最后一个元素R[n]交换，此时得到新的无序区(R1,R2,……Rn-1)和新的有序区(Rn),且满足R[1,2…n-1]<=R[n]；
- 由于交换后新的堆顶R[1]可能违反堆的性质，因此需要对当前无序区(R1,R2,……Rn-1)调整为新堆，然后再次将R[1]与无序区最后一个元素交换，得到新的无序区(R1,R2….Rn-2)和新的有序区(Rn-1,Rn)。不断重复此过程直到有序区的元素个数为n-1，则整个排序过程完成。

**7.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015231308699-356134237.gif)

**7.3 代码实现**

```c++
void heapify(int tree[], int n, int i) {
    // n 表示序列长度，i 表示父节点下标
    if (i >= n) return;
    // 左侧子节点下标
    int left = 2 * i + 1;
    // 右侧子节点下标
    int right = 2 * i + 2;
    int max = i;
    if (left < n && tree[left] > tree[max]) max = left;
    if (right < n && tree[right] > tree[max]) max = right;
    if (max != i) {
        swap(tree, max, i);
        heapify(tree, n, max);
    }
}

void build_heap(int tree[], int n) {
    // 树最后一个节点的下标
    int last_node = n - 1;
    // 最后一个节点对应的父节点下标
    int parent = (last_node - 1) / 2;
    int i;
    for (i = parent; i >= 0; i--) {
        heapify(tree, n, i);
    }
}

void heap_sort(int tree[], int n) {
    build_heap(tree, n);
    int i;
    for (i = n - 1; i >= 0; i--) {
        // 将堆顶元素与最后一个元素交换
        swap(tree, i, 0);
        // 调整成大顶堆
        heapify(tree, i, 0);
    }
}
```

**7.4 算法分析**

堆排序是**不稳定排序**，适合数据量较大的序列，它的平均时间复杂度为 Ο(n log n)，空间复杂度为 O(1)。
此外，堆排序仅需一个记录大小供交换用的辅助存储空间。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 8、计数排序（Heap Sort）

计数排序（Heap Sort）不是基于比较的排序算法，其核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。 作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。

**8.1 算法描述**

- 找出待排序的数组中最大和最小的元素；
- 统计数组中每个值为 i 的元素出现的次数，存入数组 C 的第 i 项；
- 对所有的计数累加（从 C 中的第一个元素开始，每一项和前一项相加）；
- 反向填充目标数组：将每个元素i放在新数组的第 C(i) 项，每放一个元素就将 C(i) 减去 1。

**8.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015231740840-6968181.gif)

**8.3 代码实现**

```c++
void counting_sort(int arr[], int n) {
    if (arr == NULL) return;
    // 定义辅助空间并初始化
    int max = arr[0], min = arr[0];
    int i;
    for (i = 1; i < n; i++) {
        if (max < arr[i]) max = arr[i];
        if (min > arr[i]) min = arr[i];
    }
    int r = max - min + 1;
    int C[r];
    memset(C, 0, sizeof(C));
    // 定义目标数组
    int R[n];
    // 统计每个元素出现的次数
    for (i = 0; i < n; i++) C[arr[i] - min]++;
    // 对辅助空间内数据进行计算
    for (i = 1; i < r; i++) C[i] += C[i - 1];
    // 反向填充目标数组
    for (i = n - 1; i >= 0; i--) R[--C[arr[i] - min]] = arr[i];
    // 目标数组里的结果重新赋值给 arr
    for (i = 0; i < n; i++) arr[i] = R[i];
}
```

**8.4 算法分析**

计数排序属于**非交换排序**，是**稳定排序**，适合数据范围不显著大于数据数量的序列。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 9、桶排序（Bucket Sort）

桶排序 （Bucket sort）是计数排序的升级版。它利用了函数的映射关系，高效与否的关键就在于这个映射函数的确定。桶排序的工作的原理：假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排）。

**9.1 算法描述**

- 设置一个定量的数组当作空桶；
- 遍历输入数据，并且把数据一个一个放到对应的桶里去；
- 对每个不是空的桶进行排序；
- 从不是空的桶里把排好序的数据拼接起来。

**9.2 动图演示**

![img](G:\Git\studyLinuxC\assets\16899013-5d25f17192c66b70.gif?imageMogr2/auto-orient/strip%7CimageView2/2/w/600/format/webp)

**9.3 代码实现**

```c++
void bucket_sort(int arr[], int n, int r) {
    if (arr == NULL || r < 1) return;

    // 根据最大/最小元素和桶数量，计算出每个桶对应的元素范围
    int max = arr[0], min = arr[0];
    int i, j;
    for (i = 1; i < n; i++) {
        if (max < arr[i]) max = arr[i];
        if (min > arr[i]) min = arr[i];
    }
    int range = (max - min + 1) / r + 1;

    // 建立桶对应的二维数组，一个桶里最多可能出现 n 个元素
    int buckets[r][n];
    memset(buckets, 0, sizeof(buckets));
    int counts[r];
    memset(counts, 0, sizeof(counts));
    for (i = 0; i < n; i++) {
        int k = (arr[i] - min) / range;
        buckets[k][counts[k]++] = arr[i];
    }

    int index = 0;
    for (i = 0; i < r; i++) {
        // 分别对每个非空桶内数据进行排序，比如计数排序
        if (counts[i] == 0) continue;
        counting_sort(buckets[i], counts[i]);
        // 拼接非空的桶内数据，得到最终的结果
        for (j = 0; j < counts[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }
}
```

**9.4 算法分析**

桶排序是**稳定排序**，但仅限于桶排序本身，假如桶内排序采用了快速排序之类的非稳定排序，那么就是不稳定的。

[回到顶部](https://www.cnblogs.com/linuxAndMcu/p/10201215.html#_labelTop)

## 10、基数排序（Radix Sort）

基数排序（Radix Sort）是按照低位先排序，然后收集；再按照高位排序，然后再收集；依次类推，直到最高位。有时候有些属性是有优先级顺序的，先按低优先级排序，再按高优先级排序。最后的次序就是高优先级高的在前，高优先级相同的低优先级高的在前。

**10.1 算法描述**

- 取得数组中的最大数，并取得位数；
- arr 为原始数组，从最低位开始取每个位组成 radix 数组；
- 对 radix 进行计数排序（利用计数排序适用于小范围数的特点）。

**10.2 动图演示**

![img](G:\Git\studyLinuxC\assets\849589-20171015232453668-1397662527.gif)

**10.3 代码实现**

```c++
// 基数，范围0~9
#define RADIX 10

void radix_sort(int arr[], int n) {
    // 获取最大值和最小值
    int max = arr[0], min = arr[0];
    int i, j, l;
    for (i = 1; i < n; i++) {
        if (max < arr[i]) max = arr[i];
        if (min > arr[i]) min = arr[i];
    }
    // 假如序列中有负数，所有数加上一个常数，使序列中所有值变成正数
    if (min < 0) {
        for (i = 0; i < n; i++) arr[i] -= min;
        max -= min;
    }
    // 获取最大值位数
    int d = 0;
    while (max > 0) {
        max /= RADIX;
        d ++;
    }
    int queue[RADIX][n];
    memset(queue, 0, sizeof(queue));
    int count[RADIX] = {0};
    for (i = 0; i < d; i++) {
        // 分配数据
        for (j = 0; j < n; j++) {
            int key = arr[j] % (int)pow(RADIX, i + 1) / (int)pow(RADIX, i);
            queue[key][count[key]++] = arr[j];
        }
        // 收集数据
        int c = 0;
        for (j = 0; j < RADIX; j++) {
            for (l = 0; l < count[j]; l++) {
                arr[c++] = queue[j][l];
                queue[j][l] = 0;
            }
            count[j] = 0;
        }
    }
    // 假如序列中有负数，收集排序结果时再减去前面加上的常数
    if (min < 0) {
        for (i = 0; i < n; i++) arr[i] += min;
    }
}
```

**10.4 算法分析**

基数排序是**稳定排序**，适用于关键字取值范围固定的排序。