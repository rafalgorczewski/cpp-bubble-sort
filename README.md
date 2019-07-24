# cpp-bubble-sort
Bubble sort with templates shenanigans.

The function comes in two versions: `bubble_sort(ForwardIter begin, ForwardIter end)` when the `value_type` is comparable with `operator<`, and `bubble_sort(ForwardIter begin, ForwardIter end, Comp comparator)` when you want to provide your own comparator.

```cpp
std::vector<int> foo = { 2, 1, 3, 7 };
hqrp::bubble_sort(begin(foo), end(foo));
```
Will result in the vector elements  `1 2 3 7`.
