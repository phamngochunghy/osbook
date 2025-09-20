#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <climits>

// Hàm tìm kiếm một phần tử trong một tập hợp
bool search(const std::unordered_set<int>& set, int key) {
    return set.find(key) != set.end();
}

// Hàm dự đoán trang sẽ được sử dụng xa nhất trong tương lai cho thuật toán OPT
int predict_optimal(const std::vector<int>& pages, const std::vector<int>& frame, int current_index) {
    int res = -1, farthest = current_index;
    for (int i = 0; i < frame.size(); i++) {
        int j;
        for (j = current_index; j < pages.size(); j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pages.size()) {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

// Thuật toán FIFO
void fifo_page_replacement(const std::vector<int>& pages, int capacity) {
    std::unordered_set<int> s;
    std::queue<int> indexes;
    int page_faults = 0;
    for (int i = 0; i < pages.size(); i++) {
        if (s.size() < capacity) {
            if (!search(s, pages[i])) {
                s.insert(pages[i]);
                page_faults++;
                indexes.push(pages[i]);
            }
        } else {
            if (!search(s, pages[i])) {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                page_faults++;
            }
        }
    }
    std::cout << "So loi trang (FIFO): " << page_faults << std::endl;
}

// Thuật toán Optimal
void optimal_page_replacement(const std::vector<int>& pages, int capacity) {
    std::vector<int> frame;
    int page_faults = 0;
    for (int i = 0; i < pages.size(); i++) {
        auto it = std::find(frame.begin(), frame.end(), pages[i]);
        if (it == frame.end()) {
            if (frame.size() < capacity) {
                frame.push_back(pages[i]);
            } else {
                int j = predict_optimal(pages, frame, i + 1);
                frame[j] = pages[i];
            }
            page_faults++;
        }
    }
    std::cout << "So loi trang (Optimal): " << page_faults << std::endl;
}

// Thuật toán LRU
void lru_page_replacement(const std::vector<int>& pages, int capacity) {
    std::unordered_set<int> s;
    std::unordered_map<int, int> indexes;
    int page_faults = 0;
    for (int i = 0; i < pages.size(); i++) {
        if (s.size() < capacity) {
            if (!search(s, pages[i])) {
                s.insert(pages[i]);
                page_faults++;
            }
            indexes[pages[i]] = i;
        } else {
            if (!search(s, pages[i])) {
                int lru = INT_MAX, val;
                for (auto it = s.begin(); it != s.end(); it++) {
                    if (indexes[*it] < lru) {
                        lru = indexes[*it];
                        val = *it;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
                page_faults++;
            }
            indexes[pages[i]] = i;
        }
    }
    std::cout << "So loi trang (LRU): " << page_faults << std::endl;
}

int main() {
    std::vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int capacity = 4;

    std::cout << "Chuoi tham chieu: 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5" << std::endl;
    std::cout << "So khung nho: " << capacity << std::endl;

    fifo_page_replacement(pages, capacity);
    optimal_page_replacement(pages, capacity);
    lru_page_replacement(pages, capacity);

    return 0;
}