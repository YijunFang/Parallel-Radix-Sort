#include "BucketSort.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

#define PRINTTHING 0

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

unsigned long long power(unsigned long long base, int k){
	return k? power(base * base, k/2)  * ( k % 2 ? base : 1) : 1 ;
}
int getNum(unsigned long long x, int k){
	unsigned long long temp = power(10,k);
	if(x < temp) return -1;
	while(x / 10 >= temp) x/= 10;
	return x % 10;
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


//Single thread
void BucketSort::sort_singleThread(unsigned int numCores){
	std::vector<BucketSort> buckets;
	for(int i = 0; i < 11; ++i){
		buckets.push_back(new BucketSort);
	}
	for(auto e: numbersToSort){
		int d = getNum(e, digitIndex);
		buckets[(d == -1 ? 10: d)].add(e);
	}
	for(auto b: buckets){
		if(b.numbersToSort.size() <= 1) continue;
		b.digitIndex = digitIndex + 1;
		b.sort_singleThread();
	}
	numbersToSort.clear();
	numbersToSort.insert(numbersToSort.end, buckets[10].begin(),buckets[10].end());
	for(int i = 0; i < 10; ++i){
		numbersToSort.insert(numbersToSort.end, buckets[i].begin(),buckets[i].end());
	}
	
}

void BucketSort::add(unsigned int num){
	numbersToSort.push_back(num);
}

void BucketSort::sort(unsigned int numCores) {
}
