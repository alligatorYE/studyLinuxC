## C++中数组作为函数参数的注意问题
1 问题引入
从《剑指Offer》上的相关问题，下面的输出是什么？

```c++
#include<iostream>
using namespace std;

int GetSize(int data[]) {
    return sizeof(data);
}
int main() {
    int data1[] = {1,2,3,4,5};
    int size1 = sizeof(data1);

    int *data2 = data1;
    int size2 = sizeof(data2);
    
    int size3 = GetSize(data1);
    
    cout<<size1<<" "<<size2<<" "<<size3<<endl;
    return 0;
}
```

![image-20230212220644250](G:\Git\studyLinuxC\assets\image-20230212220644250.png)

1. data1是一个数组，sizeof(data1)是求数组的大小。这个数组包含5个整数，每个整数占4个字节，因为总共是20个字节。
2. data2声明为指针，尽管它指向了数组data1，对认真指针求sizeof，得到的结果都是4。
3. 在C/C++中，当数组作为函数的参数进行传递时，数组就自动退化为同类型的指针。因此尽管函数GetSize的参数data被声明为数组，但它会退化为指针，size3的结果仍然是4
