#pragma once

#include <iostream>
#include <stack>

#include "basic_data_structures.h"

#include "logging.h"

static const int MAX_N = 10;

void TestStack()
{
  using std::cout;
  using std::endl;

  stack s;
  s.Push(1);
  cout << s.Pop() << endl;

  s.Push(2);
  cout << s.Pop() << endl;
  cout << s.Pop() << endl;

  //for (int i = 0; i < 1001; ++i)
  //  s.Push(i);

  //for (int i = 0; i < 1001; ++i)
  //  cout << s.Pop() << endl;
}

void TestQueue()
{
  queue q;
  std::cout << q.dequeue() << std::endl;

  q.enqueue(1);
  std::cout << q.dequeue() << std::endl;

  for (int i = 0; i < 10; ++i) {
    q.enqueue(i);
  }

  for (int i = 0; i < 10; ++i) {
    std::cout << q.dequeue() << std::endl;
  }

  q.enqueue(100);
  std::cout << q.dequeue() << std::endl;
}

using namespace tlog;
class LogSeverity;

void TestList()
{
  LOG(INFO) << "logging on INFO level";

  list l;

  l.add(2, 1);
  std::cout << l.remove(2) << std::endl;

  for (int i = 0; i < MAX_N; ++i)
    l.add(i, i * i);

  for (int i = 0; i < MAX_N; ++i)
    std::cout << l.remove(i) << std::endl;
}