#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 动态内存函数
// 1. void* malloc(size_t size)
//  开辟 size 个字节的空间，开辟成功则返回这块空间的地址；开辟失败则返回空指针,因此malloc的返回值一定要做检查
//  如果size为0，malloc的行为是未定义的，取决于编译器
//  使用malloc 开辟的空间在未使用之前，里面是随机值
// 2. void free (void* memblack)
// free是专门用来做动态内存的释放和回收的，如果，free函数的参数指向的空间不是动态开辟的，那么free函数的行为是未定义的
// 
// 例如：int a=10;
//		 int* p =&a;
//		 free(p);
//		 p=NULL;
//  这样是错误的，因为 p不是动态开辟的空间
// 
// 如果free函数的参数是NULL空指针，那么free函数什么都不会做
// 释放 指针 memblack 指向的空间
//    通常用于释放malloc申请的内存空间，
// 注意：malloc、calloc 通常和free 成对使用，申请了空间用完就要释放，否则会造成内存泄露
// malloc 和 free函数都声明在 stdlib.h 和 molloc.h 头文件中
// 3.   void*   calloc(size_t num,size_t size)
//   表示开辟 num 个 size个字节大小的空间 ，并且初始化为 0，返回值是开辟空间的地址
//  比如 calloc(10,4); 表示开辟10个4个字节大小的空间，并且初始化值为0
// 开辟成功则返回扩充为之后的地址的值，扩充失败返回空指针NULL
// 4. realloc
// void* realloc(void* ptr, size_t size)
// 表示 把 ptr指向的空间扩充为  size个字节大小的空间，（并且保留原来的ptr指向的值），
// 扩充成功则返回扩充为之后的地址的值（并且主动释放原来的空间），扩充失败返回空指针NULL

// malloc:
#include <malloc.h>
#include <string.h>
#include <errno.h>
//int main()
//{
//	int* p = (int*)malloc(40);// 向内存申请40个字节的空间，并且把地址赋值给p
//	// 判断空间是否申请成功
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));//根据错误码打印错误信息
//		return 1;//程序一般来说，运行成功返回0，运行失败返回1
//	}
//	// 空间申请成功之后才能使用，否则不安全
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		*(p + i) = i;//p是int类型的指针，所以 p+i 一次跳过i个int 类型
//     //p[i]=i;
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", *(p + i));
//	}
////
////	// 释放申请的空间
////	free(p);//释放p指向的空间
////	//如果申请的空间使用完没有释放，那么只有在程序结束时才会释放
////	//如果程序一直不结束，那么就会形成内存泄露
////	p = NULL;//虽然 p指向的空间已经被释放了，但是在系统对这块空间重新分配之前，
////	//p里面还存放着这块空间的的地址，有潜在的危险，使用把 p 赋值为空指针，安全
//	return 0;
//}

//  calloc
//int main()
//{
//	// 开辟10个整型的空间
//	int*p=(int*)calloc(10, sizeof(int));
//	//判断返回值是否是空指针
//	if (p == NULL)
//	{
//		printf("%s\n",strerror(errno));
//		return 1;
//	}
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", *(p + i));
//	}
//	free(p);
//	p = NULL;
//
//	return 0;
//}
// 如果你想要初始化，那就要calloc;如果不想要初始化，那就用melloc
// 二者功能一样，至少区别在是否进行初始化


// 3.  realloc
//int main()
//{
//	int* p = (int*)malloc(40);//转化为int 类型的空间
//	if (p == NULL)//开辟空间失败
//	{
//		printf("%s\n", strerror(errno));
//		return 1;
//	}
//	// 空间开辟成功
//	int i = 0;
//	for (i = 0; i < 10; i++)//给开辟的空间赋值，1-10
//	{
//		*(p + i) = (i + 1);
//	}
//	// 扩展刚才开辟的空间
//	int* ptr = (int*)realloc(p,80);//把p指向的空间拓展为80个字节
//	if (ptr != NULL)//判断空间是否拓展成功，然后再赋值，否则如果扩展不成功，返回空指针，直接赋值会把原来的空间也丢失！！！
//	{
//		p = ptr;
//	}
//
//	for (i = 0; i < 20; i++)
//	{
//		printf("%d ", *(p + i));//前10个值还是1-10，后10个是随机值
//	}
//	//使用完开辟的空间，释放
//	free(p);
//	p = NULL;
//	return 0;
//}



// 常见的动态内存错误：
// 1.对空指针NULL的解引用操作
// 例如：
 //int main()
 //{
	// int* p = (int*)malloc(40);
	// *p = 20;//没有判断p是否是空指针，直接使用很危险

	//return 0;
 //}
// 2.对动态开辟空间的越界访问
// 例如：
//int main()
//{
//	int* p =(int*) malloc(40);
//	if (p == NULL)
//	{
//		printf("%s\n", strerror(errno));
//		return 1;
//	}
//	int i = 0;
//	for (i = 0; i <= 10; i++)//十一次循环，访问11个元素，越界了
//	{
//		p[i] = i;
//	}
//	free(p);
//  p=NULL;
//  }
//
//	return 0;
//}
//
// 3.对非动态开辟内存使用free释放
// 例如：
//int main()
//{
//	int a = 10;
//	int* p = &a;
//	free(p);//p 不是动态开辟的空间，无法通过free释放，错误！
//	p = NULL;
//	return 0;
//}

// 4.使用free释放动态开辟内存的一部分
// 例如 1:
//int main()
//{
//	int* p = (int*)malloc(40);
//	if (p != NULL)
//	{
//		return 1;
//	}
//	//使用
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		*p = i;
//		p++;
//	}
//	free(p);//此时，p已经变了，p已经不指向这块空间的起始位置了
//	p = NULL;
//	
//	return 0;
//}
// 例如 2：
//int main()
//{
//	int* p = (int*)malloc(40);
//	if (p != NULL)
//	{
//		return 1;
//	}
//	//使用
//	int i = 0;
//	for (i = 0; i < 5; i++)
//	{
//		*p = i;
//		p++;
//	}
//	free(p);//此时，p已经变了，p已经不指向这块空间的起始位置了
//	p = NULL;
//	
//	return 0;
//}
// 5.对同一块空间多次释放
//int main()
//{
//	int* p = (int*)malloc(40);
//	free(p);
//	free(p);// 错误!，前面已经对p指向的空间释放过了
//
//	return 0;
//}
// 6.动态开辟的内存忘记释放（内存泄露）
//int main()
//{
//	int* p = (int*)malloc(40);
//
//	//……
//	int flag = 0;
//	scanf("%d", &flag);
//	if (flag == 5)
//		return;
//	// 释放 有可能不会实行，有可能造成空间泄露
//	free(p);
//	p = NULL;
//
//	return 0;
//}
//  或者
//int* test()
//{
//	//在这个函数里面开辟的空间
//	// 但是并没有在这个函数里面释放
//	int* p = (int*)malloc(100);
//	if (p == NULL)
//	{
//		return p;
//	}
//	//……
//	return p;
//
//}
//int main()
//{
//	int* ret = test();
//	//在这里调用了开辟空间的函数，
//	// 但是没有在这里释放
//	return 0;
//}

// 切记！动态开辟的空间一定要释放，并且要正确释放！！！
