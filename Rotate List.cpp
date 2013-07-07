// Rotate List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/**
 * Definition for singly-linked list.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (NULL == head)
        {
            return head;
        }
        
        ListNode* theOrigHead = head;
        ListNode* theOrigTail = NULL;
        int count = 0;
        while (head)
        {
            if (NULL == head->next)
            {
                theOrigTail = head;
            }
            
            head = head->next;
            ++count;
        }
        
        k %= count;
        if (0 == k)
        {
            return theOrigHead;
        }
        
        head = theOrigHead;
        ListNode* theNewTail = head;
        
        while (k--)
        {
            head = head->next;
        }
        
        while (head->next)
        {
            head = head->next;
            theNewTail = theNewTail->next;
        }
        
        theOrigTail->next = theOrigHead;
        ListNode* theNewHead = theNewTail->next;
        theNewTail->next = NULL;
        
        return theNewHead;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

