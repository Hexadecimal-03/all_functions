#include <iostream>
#include <vector>
using namespace std;

template <typename T>

class stack
{
    private:
    vector <T> s;

    public:
    void push (T val)
    {
        s.push_back(val);
    }
    T top()
    {
        return s[s.size()-1];
    }
    bool empty()
    {
        return s.size() == 0;
    }
    void pop()
    {
        if (!s.empty())
        {
            s.pop_back();
        }
    }
    int size()
    {
        return s.size();
    }
};

void nextGreater (int arr[], int n)
{
    int result[n];
    int i;
    for (i = 0; i < n; ++i)
    {
        result[i] = -1;
    }

    stack <int> s;

    for (i = 0; i < n; ++i)
    {
        while (!s.empty() and arr[s.top()] < arr[i])
        {
            result[s.top()] = arr[i];
            s.pop();
        }

        s.push(i);
    }

    for (i = 0; i < n; ++i)
    {
        cout << arr[i] << "," << result[i] << endl;
    }
    return;
}

void stocks (int arr[], int n)
{
    stack<int> stk;
    int i, k = 1;


    for (i = 0; i < n; ++i)
    {
        if (arr[i-1] <= arr[i])
        {
            stk.push(k);
            k++;
        }
        else
        {
            while (!stk.empty())
            {
                stk.pop();
                k--;
            }
        }
        if (stk.empty())
        {
            stk.push(k);
            k++;
        }
        
        cout << stk.top() << " ";
    }
    return;
}

void insertAtBottom (stack<int> &s, int x)
{
    int data;
    if (s.empty())
    {
        s.push(x);
        return;
    }

    data = s.top();
    s.pop();
    insertAtBottom(s, x);
    s.push(data);
    return;
}

void reverseStack (stack<int> &s)
{
    int x;
    if (s.empty())
    {
        return;
    }

    x = s.top();
    s.pop();

    reverseStack(s);
    insertAtBottom (s, x);
    return;
}

bool balanced (string str)
{
    stack<char> stk1;
    stack<char> stk2;
    stack<char> stk3;
    int i;
    for (i = 0; i < str.length(); ++i)
    {
        if(str[i] == '(')
        {
            stk1.push(str[i]);
        }
        else if (str[i] == ')')
        {
            if (stk1.empty() or stk1.top() != '(')
            {
                return false;
            }
            stk1.pop();
        }
        else if(str[i] == '{')
        {
            stk2.push(str[i]);
        }
        else if (str[i] == '}')
        {
            if (stk2.empty() or stk2.top() != '{')
            {
                return false;
            }
            stk2.pop();
        }
        else if(str[i] == '[')
        {
            stk3.push(str[i]);
        }
        else if (str[i] == ']')
        {
            if (stk3.empty() or stk3.top() != '[')
            {
                return false;
            }
            stk3.pop();
        }
    }
    return stk1.empty() and stk2.empty() and stk3.empty();
}

int celebrity (bool** arr, int n)
{
    stack<int> stk;
    int C, a, b, i;

    for (i = 0; i < n; ++i)
    {
        stk.push(i);
    }

    while (stk.size() > 1)
    {
        a = stk.top();
        stk.pop();
        b = stk.top();
        stk.pop();

        if (arr[a][b])
        {
            stk.push(b);
        }
        else
        {
            stk.push(a);
        }
    }

    C = stk.top();
    stk.pop();

    for (i = 0; i < n; ++i)
    {
        if ((i != C) && ((arr[C][i]) || (!arr[i][C])))
        {
            return -1;
        }
    }

    return C;
}

int main()
{
    
    return 0;
}