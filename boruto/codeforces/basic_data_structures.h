#pragma once

#include <vector>

class stack
{
public:
  using S = std::vector<int>;
  static const int MAX_N = 1000;

public:
  stack() = default;

  virtual ~stack()
  { }

  void Push(int e) // insert element at end
  {
    if (t_ + 1 > MAX_N) return;
    t_ += 1;
    s_.push_back(e);
  }

  int Pop() // erase last element
  {
    if (t_ < 0) return -1;
    int e = s_[t_];
    s_[t_] = -1;
    t_ -= 1;
    return e;
  }

private:
  S s_;
  int t_ = -1;
};

class queue
{
public:
  using Q = std::vector<int>;
  static const int MAX_N = 10;

public:
  queue()
  {
    q_.resize(MAX_N);
  }

  virtual ~queue()
  { }

  int dequeue()
  { 
    if (f_ == r_) return -1;
    int ret = q_[f_];
    q_[f_] = -1;
    f_ = (f_ + 1) % MAX_N;
    return ret;
  }

  void enqueue(int e)
  {
    if ((MAX_N - f_ + r_) % MAX_N == MAX_N - 1) return;
    q_[r_] = e;
    r_ = (r_ + 1) % MAX_N;
  }

private:
  Q q_;
  int f_ = 0;
  int r_ = 0;
};

class list
{
public:
  using L = std::vector<int>;
  static const int MAX_N = 10;

public:
  list()
  {
    l_.resize(MAX_N);
  }

  virtual ~list()
  { }

  void add(int r, int e)
  { 
    if (n_ == MAX_N) return;
    if (r < n_)
      for (int i = n_ - 1; i < r; --i)
        l_[i + 1] = l_[i];
    l_[r] = e;
    n_ += 1;
  }

  int remove(int r)
  {
    int e = l_[r];
    if (r < n_ - 1)
      for (int i = r; i < n_ - 2; ++i)
        l_[i] = l_[i + 1];

    n_ -= 1;
    return e;
  }

private:
  L l_;
  int n_ = 0;
};