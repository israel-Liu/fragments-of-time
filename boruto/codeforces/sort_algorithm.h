#pragma once
#include <algorithm>
#include <vector>
#include <type_traits>
#include <iterator>

template <class RandomAccessIterator>
void BubbleSort(RandomAccessIterator first, RandomAccessIterator last)
{
  //typedef decltype(*first) value_type;
  //value_type temp = *first;
  //for (RandomAccessIterator iter_i = first; iter_i != last; ++iter_i) {
  //  for (RandomAccessIterator iter_j = first; iter_i != last; ++iter_j) {
  //    if (*iter_j > * (iter_j + 1)) {
  //      temp = *(iter_j + 1);
  //      *(iter_j + 1) = *iter_j;
  //      *iter_j = temp;
  //    }
  //  }
  //}

  //RandomAccessIterator i = first, j = first, k = --last;
  //for (; i < --last; ++i) {
  //  k -= i;
  //  for (; j < k; ++j) {
  //    if (*j > * (j + 1))
  //      std::swap(j, j + 1);
  //  }
  //}

  //typedef typename remove_reference<decltype(*first)>::type value_type;
  //value_type temp;
  typedef typename std::iterator_traits<RandomAccessIterator>::difference_type index_type;
  index_type len = std::distance(first, last);
  for (index_type i = 0; i < len - 1; ++i)
    for (index_type j = 0; j < len - 1 - i; ++j) {
      if (*(first + j) > * (first + j + 1))
        std::swap(*(first + j), *(first + j + 1));
    }
}
//
//template <typename T>
//void quick_sort_recursive(T arr[], int start, int end) {
//  if (start >= end)
//    return;
//  T mid = arr[end];
//  int left = start, right = end - 1;
//  while (left < right) { //��������Χ����Ѱ����ŦԪֵС����Ԫ�أ�Ȼ�����Ԫ�����Ҳ�Ԫ�ؽ���
//    while (arr[left] < mid && left < right) //��ͼ������ҵ�һ������ŦԪ�����Ԫ��
//      left++;
//    while (arr[right] >= mid && left < right) //��ͼ���Ҳ��ҵ�һ������ŦԪ��С��Ԫ��
//      right--;
//    std::swap(arr[left], arr[right]); //����Ԫ��
//  }
//  if (arr[left] >= arr[end])
//    std::swap(arr[left], arr[end]);
//  else
//    left++;
//
//  for (int i = start; i < end; ++i)
//    cout << arr[i] << " ";
//  cout << endl;
//
//  quick_sort_recursive(arr, start, left - 1);
//  quick_sort_recursive(arr, left + 1, end);
//}
//template <typename T> //�������c���Կ�ʹ��,��Ҫʹ�����(class)�r����O��"С�"(<)��"���"(>)��"��С�"(>=)���\���ӹ���
//void quick_sort(T arr[], int len) {
//  quick_sort_recursive(arr, 0, len - 1);
//  for (int i = 0; i < len; ++i)
//    cout << arr[i] << " ";
//  cout << endl;
//}

//int QuickSortPartition(int arr[], int s, int e)
//{
//  int p = arr[e];
//  int l = s;
//  int r = e;
//  vector<int> vl, vr;
//
//  for (int i = l; i < r; ++i) {
//    if (arr[i] < p) vl.push_back(arr[i]);
//    if (arr[i] > p) vr.push_back(arr[i]);
//  }
//
//  for (auto e : vl)
//    cout << e << " ";
//  cout << endl;
//
//  for (auto e : vr)
//    cout << e << " ";
//  cout << endl;
//}
//
//void QuickSortRecursive(int arr[], int start, int end)
//{
//  QuickSortPartition(arr, start, end);
//}
//
//void QuickSort(int arr[], int len)
//{
//  QuickSortRecursive(arr, 0, len - 1);
//}