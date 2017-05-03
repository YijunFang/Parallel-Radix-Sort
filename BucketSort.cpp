#include "BucketSort.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

#define PRINTTHING 0
//this is faster than pow() because pow() is double percision
unsigned int pow_of_10(unsigned int x){
    unsigned int r = 1;
    while(x--)
        r *= 10;
    return r;
}

//recursion version for single sort
bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {
        // if the two numbers are the same then one is not less than the other
        if (x == y) return false;

        unsigned int a = x;
        unsigned int b = y;

        // work out the digit we are currently comparing on.
        if (pow == 0) {
                while (a / 10 > 0) {
                    a = a / 10;
                }
                while (b / 10 > 0) {
                    b = b / 10;
                }
        } else {     
            while (a / 10 >= (unsigned int)pow_of_10(pow)) {
                a = a / 10;
            }
            while (b / 10 >= (unsigned int) pow_of_10(pow)) {
                b = b / 10;
            }
        }

        if (a == b)
            return aLessB(x,y,pow + 1);  // recurse if this digit is the same using the original number
        else
            return a < b;
}


//my version of aLessB, twanty times faster than old version
bool myALessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {
    // if the two numbers are the same then one is not less than the other
    if (x == y) return false;
	
	//while loop is faster than recursion
    while (1){
        unsigned int a = x;
        unsigned int b = y;

        // work out the digit we are currently comparing on.
        if (pow == 0) {
            while (a / 10 > 0) a = a / 10;
            
            while (b / 10 > 0) b = b / 10;
            
        } else {     
            while (a / 10 >= (unsigned int)pow_of_10(pow)) a = a / 10;
            
            while (b / 10 >= (unsigned int) pow_of_10(pow)) b = b / 10;
        }

        if(a != b) {
            return a < b;
        }
        pow++;
    }
}

unsigned long long power(unsigned long long base, int k){
	return k? power(base * base, k/2)  * ( k % 2 ? base : 1) : 1 ;
}
int getNum(unsigned long long x, int k){
	unsigned long long temp = power(10,k);
	if(x < temp) return -1;
	while(x / 10 >= temp) x/= 10;
	return x % 10;
}

//Single thread
void BucketSort::sort_singleThread(unsigned int numCores){
    std::sort(numbersToSort.begin(),numbersToSort.end(), [](const unsigned int& x, const unsigned int& y){
            return aLessB(x,y,0);
    } );
}

//multithread
void BucketSort::sort(unsigned int numCores) {

    //store each vector into bucketsOfCore
    std::vector<std::vector<std::vector<unsigned int>>> buckets_all_core = std::vector<std::vector<std::vector<unsigned int>>>();
    std::vector<std::thread> thread_vector;
    std::mutex mutex_buckets;

    //seperate the whole vector into four parts
    unsigned int eachLength = numbersToSort.size()/numCores ;
    unsigned int nextIndex = 0;
    unsigned int endIndex = 0;

    /*
    lambda function put (numCores) number of vector (called buckets)
    onto buckets_all_core where each vector consist of 10 sub-vector.
    each sub-vector contain integers whose most-significant-bit == sub-vector's position in upper vector
    */
    auto seperateToCoreBucket = [this, &buckets_all_core, &mutex_buckets]
        (unsigned int start_index,unsigned int end_index) {

        std::vector<std::vector<unsigned int>> buckets;

        for (int j = 0; j <= 9; ++j) {
            buckets.push_back(std::vector<unsigned int>()); }

        for (unsigned int i = start_index; i <= end_index; ++i) {
            unsigned int a = numbersToSort[i];
            while (a / 10 > 0) {
                a /= 10;
            }
            buckets.at(a).push_back(numbersToSort[i]); 
        }
        std::lock_guard<std::mutex> lock(mutex_buckets);
        buckets_all_core.push_back(buckets);
    };

    //create a vector of thread which seperate the original
    //vector into numCores number vector (ordered by most significant bit)
    for (unsigned int i = 1; i <= numCores; ++i){
        if(i == numCores) endIndex = numbersToSort.size()-1;
        else endIndex = i*eachLength-1;

        thread_vector.push_back(std::thread(seperateToCoreBucket,nextIndex, endIndex));
        nextIndex = endIndex+1;
    }

    //start the thread
    for(auto &t: thread_vector)
        t.join();

    //clear thread vector and original input vector
    thread_vector.clear();
    numbersToSort.clear();

    //this vector contain sub-vector where each sub-vector contain integers
    //whose most-significant-bit == sub-vector's position in upper vector
    std::vector<std::vector<unsigned int>> msb_Bucket = std::vector<std::vector<unsigned int>>();;
    for (int j = 0; j <= 9; ++j)
        msb_Bucket.push_back(std::vector<unsigned int>());

    int msb = 10;
    //this lambda function put all intergers into prev-mentioned msb_Bucket
    std::function<void()> rearrange_with_msb;
    rearrange_with_msb = [this,numCores,  &msb,&rearrange_with_msb,
                        &buckets_all_core, &msb_Bucket, &mutex_buckets]() {
        int index = 0;
        {
            std::lock_guard<std::mutex> lock(mutex_buckets);
                index = --msb;
        }
        if (index < 0) return;

        //a reperence vector to avoid collision
        auto &vector_same_msb = msb_Bucket.at(index);
        for (auto fourCoreVector : buckets_all_core) {
            vector_same_msb.insert(vector_same_msb.end(), fourCoreVector.at(index).begin(), fourCoreVector.at(index).end());
        }

		//sort linear in each bucket
        if (index > 0)
            std::sort(msb_Bucket.at(index).begin(),msb_Bucket.at(index).end(), [](const unsigned int& x, const unsigned int& y){
            	return myALessB(x,y,1);});
            	
        rearrange_with_msb();
    };

    //create a vector of thread which rearranges accordng to most significant bit
    for (unsigned int i = 0; i < numCores; ++i){
        thread_vector.push_back(std::thread(rearrange_with_msb));
    }

    //start the thread
    for(auto &t: thread_vector)
        t.join();

    thread_vector.clear();

    //put all numbers into original vector
    for (auto v = msb_Bucket.begin(); v != msb_Bucket.end(); ++v)
        numbersToSort.insert(numbersToSort.end(), v->begin(), v->end());

    return;
}
