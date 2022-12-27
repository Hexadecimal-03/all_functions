#include <bits/stdc++.h>
using namespace std;

class node
{
	public:
	int value;
	node* next;

	node(int d)
	{
		value = d;
		next = NULL;
	}

};

void addatlast (int n, node* &head)
{
	if (head == NULL)
	{
		head = new node(n);
		return;
	}
	else
	{
		node* tail = head;

		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = new node(n);
	}
	return;
}

node* merge (node* &a, node* &b)
{
	node* c = NULL;
	if (a == NULL)
	{
		return b;
	}

	if (b == NULL)
	{
		return a;
	}

	if (a->value <= b-> value)
	{
		c = a;
		c->next = merge (a->next, b);
	}
	else
	{
		c = b;
		c->next = merge (a, b->next);
	}
	return c;
}

void print (node* head)
{
	while (head != NULL)
	{
		cout << head->value << " ";
		head = head->next;
	}
	cout << endl;
	return;
}

node* fromend (node* head, int k)
{
	node* slow = head;
	node* fast = head;
	int i;
	for (i = 1; i < k; ++i)
	{
		fast = fast->next;
	}

	while (fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next;
	}

	return slow;
}

void reverse (node* &head)
{
    node* prev = NULL;
    node* curr = head;
    node* next;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }

    head = prev;
}

void kreverse (node* &head, int k)
{
    int i;
    node* prev = NULL;
    node* curr1 = head;
    node* curr2 = head;
    node* next = curr1;

    while (curr1 != NULL)
    {
        for (i = 1; i < k; ++i)
        {
            curr2 = curr2->next;
        }
        next = curr2->next;
        curr2->next = prev;
        prev = curr1;
        curr1 = next;
        curr2 = next;
    }

    head = prev;

	reverse (head);
}

node* recrev (node* head)
{
    if (head->next == NULL or head == NULL)
    {
        return head;
    }

    node* shead = recrev(head->next);
    head->next->next = head;
    head->next = NULL;
    return shead;
}

void delathead (node* &head)
{
    if (head == NULL)
    {
        return;
    }

    node* temp = head->next;
    delete head;
    head = temp;

    return;
}

int main()
{
	node* head = NULL;

	for (int i = 0; i < 10; ++i)
	{
		addatlast (i, head);
	}

	node* iter = head;

	while (iter->next != NULL)
	{
		cout << iter->value << " ";
		iter = iter->next;
	}

	head = recrev (head);

	while (head != NULL)
	{
		cout << head->value << " ";
		head = head->next;
	}

	return 0;
}