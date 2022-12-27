#include <iostream>
#include <vector>
using namespace std;

template <typename T>           //Compatible with all datatypes

class queue
{
    private:
    vector<T> q;

    public:
    void push(T value)          //Pushing the new element at end
    {
        q.push_back(value);
        return;
    }
    T front()                   //Returning the front element
    {
        return q[0];
    }
    bool empty()                //If queue if empty
    {
        return q.size() == 0;
    }
    void pop()                  //Pops out front element
    {
        if (!q.empty())
        {
            q.erase(q.begin());
        }
        return;
    }
};

int timeimp (queue<int> &q1, queue<int> &q2)
{
    int cost = 0, temp;

    while (!q2.empty() and !q1.empty())
    {
        while (q1.front() != q2.front())
        {
            temp = q1.front();
            q1.pop();
            q1.push(temp);
            cost++;
        }
        if (q1.front() == q2.front())
        {
            q1.pop();
            q2.pop();
            cost++;
        }
    }
    return cost;
}

int main()
{

    return 0;
}