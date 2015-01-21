#include <iostream>
#include <cassert>
#include <functional>
#include <climits>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x, ListNode *p=nullptr) : val(x), next(p) {}
};

ListNode *mkList(const char *str) {
    ListNode *head=nullptr, *p=nullptr;
    const char *begin = str;
    char *end;
    for(int val = strtol(begin, &end, 10); begin != end;
            val = strtol(begin, &end, 10)) {
        begin = end + 1;
        ListNode *node = new ListNode(val);
        if(!head) {
            p = head = node;
        } else {
            p->next = node;
            p = node;
        }

        if(*end == '\0') {
            break;
        }
    }

    return head;
}

void print(ListNode *head) {
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void destroy(ListNode *head) {
    while(head) {
        ListNode *p = head;
        head = head->next;
        delete p;
    }
}

//-------------------------remove node-------------------------
//O(1), but can't delete tail node
void removeRandomNode(ListNode *p) {
    assert(p && p->next); //p can't be tail node
    ListNode *next = p->next;
    *p = *p->next;
    delete next;
}

//can delete any node
ListNode *removeIf(ListNode *head, std::function<bool(int)> &functor) {
    cout << "use std::function&" << endl;
    ListNode **p = &head;
    while(*p) {
        if(functor((*p)->val)) {
            //remove *p
            ListNode *tmp = *p;
            *p = (*p)->next;
            delete tmp;
        } else {
            p = &((*p)->next);
        }
    }

    return head;
}

//priority lower than template version
ListNode *removeIf(ListNode *head, std::function<bool(int)> &&functor) {
    cout << "use std::function&&" << endl;
    ListNode **p = &head;
    while(*p) {
        if(functor((*p)->val)) {
            //remove *p
            ListNode *tmp = *p;
            *p = (*p)->next;
            delete tmp;
        } else {
            p = &((*p)->next);
        }
    }

    return head;
}

// same as std::function&& version, but has higher priority
template<typename Functor>
ListNode *removeIf(ListNode *head, Functor &&functor) {
    cout << "use template" << endl;
    ListNode **p = &head;
    while(*p) {
        if(functor((*p)->val)) {
            //remove *p
            ListNode *tmp = *p;
            *p = (*p)->next;
            delete tmp;
        } else {
            p = &((*p)->next);
        }
    }

    return head;
}

//-------------------------reverse list-------------------------
ListNode *reverseByLoop(ListNode *head) {
    if(!head || !head->next) {
        return head;
    }

    ListNode *pre = nullptr, *next = nullptr;
    while(head) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }

    return pre;
}

ListNode *reverseByRecursion(ListNode *head) {
    if(!head || !head->next) {
        return head;
    }

    ListNode *p = reverseByRecursion(head->next);
    head->next->next = head;
    head->next = nullptr;

    return p;
}

//-------------------------reverse nth node-------------------------
ListNode *getReverseNthNode(ListNode *head, int n) {
    assert(n>=0);
    ListNode *p = head;

    while(n) {
        if(!p) {
            return nullptr;
        } else {
            p = p->next;
            --n;
        }
    }

    while(p) {
        p = p->next;
        head = head->next;
    }

    return head;
}


//-------------------------the middle node-------------------------
ListNode *getMidNode(ListNode *head) {
    if(!head || !head->next) {
        return head;
    }

    ListNode *slow = head, *fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

//-------------------------circle-------------------------
ListNode *hasCircle(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) {
            return slow;
        }
    }

    return nullptr;

}

/*
 *                            &
 * |          a         |  b  |
 * @->@->@->@->@->@->@->@->@->@->@
 *                      \        |
 *                       @   L   @
 *                        \      |
 *                         @<-@<-@
 *
 *  slow: a+b=n
 *  fast: a+b+k*L=2*n
 *
 *  k*L = a+b = n
 */
ListNode *findCircleEntry(ListNode *head) {
    ListNode *slow = hasCircle(head);
    if(!slow) {
        return slow;
    }

    ListNode *fast = head;
    while(fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }

    return fast;
}


int main(int argc, char const* argv[]) {
    const char *str = "3, 1, 5, 4, 8, 4, 4, 8, 10";
    ListNode *head = mkList(str);
    print(head);

    // use template first, std::function&& as candidate
    head = removeIf(head, [](int val){return val == 8;});
    cout << "after remove node 8: ";
    print(head);

    // use template first, std::function&& as candidate
    auto lambda = [](int val){return val == 4;};
    head = removeIf(head, lambda);
    cout << "after remove node 4: ";
    print(head);

    // use std::function&
    std::function<bool(int)> functor = [](int val){return val == 1;};
    head = removeIf(head, functor);
    cout << "after remove node 1: ";
    print(head);

    head = reverseByLoop(head);
    cout << "after reverse list by loop: ";
    print(head);

    head = reverseByRecursion(head);
    cout << "after reverse list by recursion: ";
    print(head);

    ListNode *p = getReverseNthNode(head, 1);
    cout << "the reverse first node: " << (p ? p->val : INT_MAX) << endl;

    p = getReverseNthNode(head, 4);
    cout << "the reverse fourth node: " << (p ? p->val : INT_MAX) << endl;

    p = getMidNode(head);
    cout << "the middle node: " << (p ? p->val : INT_MAX) << endl;

    p = getMidNode(nullptr);
    cout << "the middle node: " << (p ? p->val : INT_MAX) << endl;

    p = hasCircle(head);
    cout << "has circle: " << (p ? p->val : INT_MAX) << endl;

    p = hasCircle(nullptr);
    cout << "has circle: " << (p ? p->val : INT_MAX) << endl;

    destroy(head);

    return 0;
}
