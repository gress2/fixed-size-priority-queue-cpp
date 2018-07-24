#include <array>
#include <queue>
#include <iostream>

template<typename T, typename Cmp, int N>
class fixed_priority_queue {
  private:
    std::priority_queue<T, std::vector<T>, Cmp> priq_;
    Cmp cmp_;
  public:
    fixed_priority_queue(Cmp cmp) 
      : priq_(cmp), cmp_(cmp)
    {}

    void push(T t) {
      if (priq_.size() == N) {
        if (cmp_(t, priq_.top())) {
          priq_.pop();
          priq_.push(t);
        }
      } else {
        priq_.push(t);
      }
    }

    std::array<T, N> dump() {
      std::array<T, N> ary;
      int i = 0;
      while(!priq_.empty()) {
        ary[i] = priq_.top();
        priq_.pop();
        i++;
      }
      return ary;
    }
};

int main() {
  auto cmp = [](int a, int b) { return a > b; };

  fixed_priority_queue<int, decltype(cmp), 3> fixed(cmp);
  fixed.push(9);
  fixed.push(3);
  fixed.push(0);
  fixed.push(5);
  fixed.push(8);
  fixed.push(8);

  auto ary = fixed.dump();
  for (auto it = ary.begin(); it != ary.end(); ++it) {
    std::cout << *it << std::endl;
  }
}
