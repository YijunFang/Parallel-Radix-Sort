#include <iostream>
#include <random>
#include <thread>
#include <chrono>

#include "BucketSort.h"
#include <iostream>
#include <random>
#include <thread>

#include "BucketSort.h"

// int main() {
	
// 	unsigned int totalNumbers =	500000;
// 	unsigned int printIndex =	259000;
	
// 	// use totalNumbers required as the seed for the random
// 	// number generator. 
// 	std::mt19937 mt(totalNumbers);
// 	std::uniform_int_distribution<unsigned int> dist(1, std::numeric_limits<unsigned int>::max());

// 	// create a sort object
// 	BucketSort pbs;

// 	// insert random numbers into the sort object
// 	for (unsigned int i=0; i < totalNumbers; ++i) {
// 		pbs.numbersToSort.push_back(dist(mt));
// 	} 
	
// 	// call sort giving the number of cores available.
//         const unsigned int numCores = std::thread::hardware_concurrency();
//         auto start = std::chrono::steady_clock::now();
// 		pbs.sort(numCores);
// 		auto end = std::chrono::steady_clock::now();
// 		std::cout << "Time to sort Parallel " << totalNumbers;
// 		std::cout<< " numbers = " << std::chrono::duration <double, std::milli> (end - start).count();
// 		std::cout<< " [ms]" << std::endl;

//         std::cout << "number of cores used: " << numCores << std::endl;
	
// 	// print certain values from the buckets
// 	std::cout << "Demonstrating that all the numbers that start with 1 come first" << std::endl;
// 	std::cout << pbs.numbersToSort[0] << " " << pbs.numbersToSort[printIndex - 10000]
// 		<< " " << pbs.numbersToSort[printIndex] << " " << pbs.numbersToSort[pbs.numbersToSort.size() - 1] 
// 		<< std::endl;
	
// }


//parallel version
// int main() {

//     unsigned int totalNumbers = 100000;//000000;

//     std::mt19937 mt(10);
//     std::uniform_int_distribution<unsigned int> dist(1, 10000);
    
//     BucketSort pbs;

//     for (unsigned int i=0; i < totalNumbers; ++i) {
//         pbs.numbersToSort.push_back(dist(mt));
//     }

//     pbs.sort(std::thread::hardware_concurrency());

//     for (auto num : pbs.numbersToSort) {
//         std::cout << num<< " ";
//     }
// }

 //single version
// int main() {

//     unsigned int totalNumbers = 100000;//000000;

//     std::mt19937 mt(10);
//     std::uniform_int_distribution<unsigned int> dist(1, 10000);
    
//     BucketSort pbs;

//     for (unsigned int i=0; i < totalNumbers; ++i) {
//         pbs.numbersToSort.push_back(dist(mt));
//     }

//     pbs.sort_singleThread(std::thread::hardware_concurrency());

//     for (auto num : pbs.numbersToSort) {
//         std::cout << num<< " ";
//     }
// }
/*
int main() {

    unsigned int totalNumbers = 5000000;
    
    std::mt19937 mt(10);
    std::uniform_int_distribution<unsigned int> dist(1, 10000);
    int i =0;
    BucketSort pbs;

    for (unsigned int i=0; i < totalNumbers; ++i) {
        pbs.numbersToSort.push_back(dist(mt));
    }

    std::cout << "<======= Single  Version =======>" << std::endl;
    auto start = std::chrono::steady_clock::now();
    pbs.sort_singleThread(std::thread::hardware_concurrency());
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time to sort Single " << totalNumbers;
    std::cout<< " numbers = " << std::chrono::duration <double, std::milli> (end - start).count();
    std::cout<< " [ms]" << std::endl;
    
    for (auto num : pbs.numbersToSort) {
        i++;
        if ( i % (totalNumbers/100) == 0){
           std::cout << num<< " ";
        }

        
        if ( i % (totalNumbers/10) == 0 && totalNumbers != 100){
            std::cout<< std::endl;
        }else if (totalNumbers == 100 && i %10 == 0){
            std::cout<< std::endl;
        }
    }
     std::cout<< std::endl;
     std::cout <<std::endl;
    pbs.numbersToSort.clear();
    std::mt19937 mt1(10);

    for (unsigned int i=0; i < totalNumbers; ++i) {
        pbs.numbersToSort.push_back(dist(mt1));
    }


    std::cout << "<======= Parallel Version =======>" << std::endl;
    auto start1 = std::chrono::steady_clock::now();
    pbs.sort(std::thread::hardware_concurrency());
    auto end1 = std::chrono::steady_clock::now();
    std::cout << "Time to sort Parallel " << totalNumbers;
    std::cout<< " numbers = " << std::chrono::duration <double, std::milli> (end1 - start1).count();
    std::cout<< " [ms]" << std::endl;
    i = 0;
    for (auto num : pbs.numbersToSort) {
        i++;
        if ( i % (totalNumbers/100) == 0){
           std::cout << num<< " ";
        }

        
        if ( i % (totalNumbers/10) == 0 && totalNumbers != 100){
            std::cout<< std::endl;
        }else if (totalNumbers == 100 && i %10 == 0){
            std::cout<< std::endl;
        }
    }
    std::cout<< std::endl;
    std::cout <<std::endl;
	
}
*/

int main() {

    unsigned int totalNumbers = 500000;
    unsigned int printIndex =   259000;

    // use totalNumbers required as the seed for the random
    // number generator.
    std::mt19937 mt(totalNumbers);
    std::uniform_int_distribution<unsigned int> dist(1, std::numeric_limits<unsigned int>::max());
    std::cout << "UniformDistro between 1 and " << std::numeric_limits<unsigned int>::max() << std::endl;
    // create a sort object
    BucketSort pbs;
    BucketSort pbs1;

    // insert random numbers into the sort object
    for (unsigned int i=0; i < totalNumbers; ++i) {
        auto num = dist(mt);
        pbs.numbersToSort.push_back(num);
        pbs1.numbersToSort.push_back(num);
    }

    // call sort giving the number of cores available.
    std::cout << "<======= Parallel Version =======>" << std::endl;
    auto start = std::chrono::steady_clock::now();
    auto numcore = std::thread::hardware_concurrency();
    std::cout << "Use: "<< numcore<<std::endl;
    pbs.sort(numcore);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time to sort " << totalNumbers << " numbers = " << std::chrono::duration <double, std::milli> (end - start).count() << " [ms]" << std::endl;

    // print certain values from the buckets
    std::cout << "Demonstrating that all the numbers that start with 1 come first" << std::endl;
    std::cout << pbs.numbersToSort[0] << " " << pbs.numbersToSort[printIndex - 10000]
        << " " << pbs.numbersToSort[printIndex] << " " << pbs.numbersToSort[pbs.numbersToSort.size() - 1]
        << std::endl;
    // for(auto num : pbs.numbersToSort)
    //     std::cout << num << std::endl;


    std::cout << "<======= Single  Version =======>" << std::endl;
    auto start1 = std::chrono::steady_clock::now();
    pbs1.sort_singleThread(std::thread::hardware_concurrency());
    auto end1 = std::chrono::steady_clock::now();
    std::cout << "Time to sort Single " << totalNumbers << " numbers = " << std::chrono::duration <double, std::milli> (end1 - start1).count() << " [ms]" << std::endl;

    // print certain values from the buckets
    std::cout << "Demonstrating that all the numbers that start with 1 come first" << std::endl;
    std::cout << pbs1.numbersToSort[0] << " " << pbs1.numbersToSort[printIndex - 10000]
        << " " << pbs.numbersToSort[printIndex] << " " << pbs1.numbersToSort[pbs.numbersToSort.size() - 1]
        << std::endl;
    // for(auto num : pbs1.numbersToSort)
    //     std::cout << num << std::endl;

}
