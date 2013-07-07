// Add Two Numbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
Add Two Numbers
You are given two linked lists representing two non-negative numbers.
The digits are stored in reverse order and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int carrage = 0;
        ListNode* preNode = NULL;
        ListNode* headNode = NULL;
        while (l1 && l2)
        {
            int sum = l1->val + l2->val + carrage;
            int bit = sum % 10;

            ListNode* newNode = new ListNode(bit);
            if (preNode)
            {
                preNode->next = newNode;
            }
            preNode = newNode;
            if (NULL == headNode)
            {
                headNode = newNode;
            }

            carrage = sum / 10;
            
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1)
        {
            int sum = l1->val + carrage;
            int bit = sum % 10;

            ListNode* newNode = new ListNode(bit);
            
            if (preNode)
            {
                preNode->next = newNode;
            }
            preNode = newNode;
            if (NULL == headNode)
            {
                headNode = newNode;
            }
            
            carrage = sum / 10;
            
            l1 = l1->next;
        }

        while (l2)
        {
            int sum = l2->val + carrage;
            int bit = sum % 10;

            ListNode* newNode = new ListNode(bit);
            
            if (preNode)
            {
                preNode->next = newNode;
            }
            preNode = newNode;
            if (NULL == headNode)
            {
                headNode = newNode;
            }

            carrage = sum / 10;
            
            l2 = l2->next;
        }
        
        if (carrage)
        {
            ListNode* newNode = new ListNode(carrage);
            
            if (preNode)
            {
                preNode->next = newNode;
            }
            preNode = newNode;
            if (NULL == headNode)
            {
                headNode = newNode;
            }
        }

        return headNode;
    }
};
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

