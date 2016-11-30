#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

struct ListNode {
    int val;
    std::shared_ptr<ListNode> next;
    ListNode(int v, const std::shared_ptr<ListNode> & nx = nullptr)
        : val(v), next(nx) {}
};

using pNode = std::shared_ptr<ListNode>;

pNode createList(const std::vector<int> & nums) {
    pNode head = nullptr;
    std::for_each(nums.rbegin(), nums.rend(), [&](int i){
        head = std::make_shared<ListNode>(i, head);
    });
    return head;
}

void printList(const pNode & head, int n) {
    if (head != nullptr && n > 0) {
        std::cout << head->val << " -> ";
        printList(head->next, n-1);
    }
    else if (head == nullptr)
        std::cout << "null\n";
}

class solution {
  public:
    pNode detectCycle(const pNode & head) {
        pNode slow = head, fast = head->next;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next->next;
        }

        int cycleLen = 1;
        pNode next = fast->next;
        while (next != fast) {
            cycleLen++;
            next = next->next;
        }

        pNode first = head;
        while (cycleLen > 0) {
            first = first->next;
            cycleLen--;
        }
        pNode second = head;
        while (first != second) {
            first = first->next;
            second = second->next;
        }
        return first;
    }
};

int main() {
    std::vector<int> nums{1,2,3,4,5,6,7,8,9,10};
    pNode head = createList(nums);
    pNode last = head;
    while (last->next != nullptr)
        last = last->next;
    last->next = head->next->next->next->next;
    printList(head, 11);

    solution soln;
    pNode start = soln.detectCycle(head);
    std::cout << "\nThe start of the cycle is:\n"
              << start->val << std::endl;
}
