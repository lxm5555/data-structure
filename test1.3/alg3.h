#pragma once
#include<iostream>
#include"lk_queue.h"
#include"lk_stack.h"
using namespace std;

bool Palindrome(char *s)
{
    LinkStack<char> ls;
    LinkQueue<char> lq;
    for(int i=0;i<strlen(s);i++)
    {
        ls.Push(s[i]);
        lq.InQueue(s[i]);
    }
    for(int i=0;i<strlen(s);i++)
    {
        char a,b;
        ls.Pop(a);
        lq.OutQueue(b);
        if(a!=b)
        {
            return false;
        }
    }
    return true;
}

template <class ElemType>
void Reverse(LinkQueue<ElemType> &lq)
{
    LinkStack<int> ls;
    int a;
    int b=lq.Length();
    for(int i=0;i<b;i++)
    {
        lq.OutQueue(a);
        ls.Push(a);
    }
    int c=ls.Length();
    for(int i=0;i<c;i++)
    {
        ls.Pop(a);
        lq.InQueue(a);
    }
}
