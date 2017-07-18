#pragma once
#include <iostream>  
#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
#include <cmath>  
using namespace std;
const int maxn = 15;

struct T   //构造trie树每个节点的结构  
{
	int num;          //每个节点出现的次数  
	T* next[26];     //每个节点的下一个节点的字母  
	T()
	{
		num = 0;
		for (int i = 0; i<26; i++)
			next[i] = NULL;     //trie树初始化为空  
	}
}trie;

void Insert(char str[]) {   //trie树的插入建立  
	T* p = 0;
	for (int i = 0; i<len; ++i)   //插入单词str  
	{
		int len = strlen(str);
		int a = str[i] - 'a';
		if (p->next[a] == NULL)
			p->next[a] = new T;
		p = p->next[a];
		p->num++;         //每访问到一次该节点，节点个数加1   
	}
}

int find(char str[])     //查找含有前缀str的单词个数  
{
	T* p = 0;
	int len = strlen(str);
	for (int i = 0; i<len; i++)
	{
		int a = str[i] - 'a';      //把字母转换成数字  
		if (p->next[a] == NULL)     //如果没找到前缀和中匹配的字母，则查找不成功  
			return 0;
		p = p->next[a];       //指针指向下一个节点  
	}
	return p->num;        //返回该节点出现的次数，即单词个数  
}

int main2()
{
	int n, m;
	char str[maxn];
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", str);
		Insert(str);     //把一个单词插入到trie树中  
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s", str);     //输入前缀  
		printf("%d\n", find(str));    //查找含有此前缀的单词个数  
	}
	return 0;
}

