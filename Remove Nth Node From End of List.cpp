// Remove Nth Node From End of List.cpp : Defines the entry point for the console application.
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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode* theReturnedHead = head;
        ListNode* nFromLast = head;
        
        while (n--)
        {
            head = head->next;
        }
        
        while (head && head->next)
        {
            head = head->next;
            nFromLast = nFromLast->next;
        }

        {
            if (head == NULL)
            {
                theReturnedHead = theReturnedHead->next;
                delete nFromLast;
            }
            else
            {
                ListNode* theN = nFromLast->next;
                nFromLast->next = theN->next;
            
                delete theN;
            }
        }

        return theReturnedHead;
    }
};
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

