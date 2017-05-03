#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <vector>
#include <thread>
#include <mutex>

struct BucketSort {
    // vector of numbers
    std::vector<unsigned int> numbersToSort;
    void sort(unsigned int numCores);
    void sort_singleThread(unsigned int numCores);
};


#endif /* BUCKET_SORT_H */
