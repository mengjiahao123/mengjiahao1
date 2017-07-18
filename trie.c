#pragma once
#include <iostream>  
#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
#include <cmath>  
using namespace std;
const int maxn = 15;

struct T   //����trie��ÿ���ڵ�Ľṹ  
{
	int num;          //ÿ���ڵ���ֵĴ���  
	T* next[26];     //ÿ���ڵ����һ���ڵ����ĸ  
	T()
	{
		num = 0;
		for (int i = 0; i<26; i++)
			next[i] = NULL;     //trie����ʼ��Ϊ��  
	}
}trie;

void Insert(char str[]) {   //trie���Ĳ��뽨��  
	T* p = 0;
	for (int i = 0; i<len; ++i)   //���뵥��str  
	{
		int len = strlen(str);
		int a = str[i] - 'a';
		if (p->next[a] == NULL)
			p->next[a] = new T;
		p = p->next[a];
		p->num++;         //ÿ���ʵ�һ�θýڵ㣬�ڵ������1   
	}
}

int find(char str[])     //���Һ���ǰ׺str�ĵ��ʸ���  
{
	T* p = 0;
	int len = strlen(str);
	for (int i = 0; i<len; i++)
	{
		int a = str[i] - 'a';      //����ĸת��������  
		if (p->next[a] == NULL)     //���û�ҵ�ǰ׺����ƥ�����ĸ������Ҳ��ɹ�  
			return 0;
		p = p->next[a];       //ָ��ָ����һ���ڵ�  
	}
	return p->num;        //���ظýڵ���ֵĴ����������ʸ���  
}

int main2()
{
	int n, m;
	char str[maxn];
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", str);
		Insert(str);     //��һ�����ʲ��뵽trie����  
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf("%s", str);     //����ǰ׺  
		printf("%d\n", find(str));    //���Һ��д�ǰ׺�ĵ��ʸ���  
	}
	return 0;
}

