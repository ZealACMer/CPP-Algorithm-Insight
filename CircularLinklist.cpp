#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr){}
    int data_;
    Node* next_;
};

class CircularLinklist
{
public:
    CircularLinklist()
    {
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CircularLinklist()
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }
        delete head_;
    }

    //尾部插入元素 O(1)
    void insertTail(int val)
    {
        Node* node = new Node(val);
        node->next_ = tail_->next_;
        tail_->next_ = node;
        tail_ = node;
    }

    //头部插入元素 O(1)
    void insertHead(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        if(node->next_ == head_)
        {
            tail_ = node;
        }
    }

    //删除节点 O(1)
    void remove(int val)
    {
        Node* q = head_;
        Node* p = head_->next_;
        while(p != head_)
        {
            if(p->data_ == val)
            {
                q->next_ = p->next_;
                delete p;
                if(q->next_ == head_)
                {
                    tail_ = q;
                    return;
                }
                p = q->next_;
            }
            else
            {
                q = p;
                p = p->next_;
            }
        }
    }

    //查询元素 O(n)
    bool find(int val) const
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            if(p->data_ == val)
            {
                return true;
            }
        }
        return false;
    }

    //打印链表
    void show() const
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    Node* head_;
    Node* tail_;
};

int main(int argc, char* argv[])
{
    CircularLinklist circularLinklist;
    srand(time(0));
    for(int i = 0; i < 10; ++i)
    {
        circularLinklist.insertTail(rand() % 100);
    }
    circularLinklist.show();

    circularLinklist.insertHead(100);
    circularLinklist.show();

    cout << boolalpha << circularLinklist.find(100) << endl;

    circularLinklist.remove(100);
    circularLinklist.show();

    return 0;
}