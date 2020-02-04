#include <utility>
#include <iostream>
#include <cassert>
#include <memory>

#include "fvector.h"

constexpr int32_t kSize = 10;

void TestInitialization() {
  std::cerr << "Run init test" << std::endl;
  f::vector<int32_t> v(kSize);
  for (int32_t i = 0; i < kSize; ++i) {
    assert(v[i] == 0);
  }

  f::vector<int32_t> v_second(kSize, 123);
  for (int32_t i = 0; i < kSize; ++i) {
    assert(v_second[i] == 123);
  }
}

void TestMemberAccess() {
  std::cerr << "Run access test" << std::endl;
  f::vector<int32_t> v(kSize);
  v[1] = 1;
  assert(v[1] == 1);
  v[1] = 2;
  assert(v[1] == 2);
}

void TestRangeBasedFor() {
  std::cerr << "Run range based for test" << std::endl;
  f::vector<int32_t> v(kSize);
  for (auto& val : v) {
    assert(val == 0);
    val = 1;
  }

  for (auto& val : v) {
    assert(val == 1);
  }
}

void TestConstIterator() {
  std::cerr << "Run const iterator test" << std::endl;
  const f::vector<int32_t> v(kSize, 1234);
  for (auto& val : v) {
    assert(val == 1234);
  }
  f::vector<int32_t>::const_iterator begin = v.begin();
}

void TestNontrivialType() {
  std::cerr << "Run non trivial type test" << std::endl;
  const f::vector<std::pair<int, int>> v2(kSize);
  const f::vector<std::string> v(kSize, "test_string");
  for (auto& val : v) {
    assert(val == "test_string");
  }
}

void TestPushBack() {
  constexpr int32_t kTestSize = 50;
  std::cerr << "Run push back type test" << std::endl;
  f::vector<std::pair<int, int>> v;
  for (int i = 0; i < kTestSize; ++i) {
    v.push_back({i, i});
  }

  for (int i = 0; i < kTestSize; ++i) {
    assert(v[i] == std::make_pair(i, i));
  }
}

void TestUniquePtr() {
  std::cerr << "Run test unique ptr" << std::endl;
  auto p = std::make_unique<f::vector<int32_t>>();
  p->push_back(1);
  assert(p->operator[](0) == 1);
}

void TestOutOfRange() {
  std::cerr << "Run test out of range" << std::endl;
  auto p = f::vector<int32_t>();
  bool catched = false;
  try {
    p[10];
  } catch (std::out_of_range& e) {
    catched = true;
  }
  assert(catched);
}

void TestOutput() {
  std::cerr << "Run test output" << std::endl;
  auto p = f::vector<int32_t>(5, 3);
  std::cout << p << std::endl;

}

int main() {
  TestInitialization();
  TestMemberAccess();
  TestRangeBasedFor();
  TestConstIterator();
  TestNontrivialType();
  TestPushBack();
  TestUniquePtr();
  TestOutOfRange();
  TestOutput();

  // How to call an function.
  void (*f)() = TestOutOfRange;
  f();
  return 0;
}

