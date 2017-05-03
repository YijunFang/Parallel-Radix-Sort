#include<stdio.h>
/*
unsigned int power(int base, int k){
	unsigned int result = 1;
	unsigned int pivot = base;
	while(k > 0){
		result *= result;
		if(k % 2){
			printf("mod: %d %d\n", result, k);
			result *= base;
		}
		printf("result: %d %d\n", result, k);
		k /= 2;
	}
	return result;
}*/
int getNum(unsigned long long x, int k);
unsigned long long power(unsigned long long base, int k){
	return k? power(base * base, k/2)  * ( k % 2 ? base : 1) : 1 ;
}
int getNum(unsigned long long x, int k){
	unsigned long long temp = power(10,k);
	if(x < temp) return -1;
	while(x / 10 >= temp) x/= 10;
	return x % 10;
}

int main(){
	int a,b;
	scanf("%d",&a);
	scanf("%d",&b);
	
	printf("%d\n", getNum(a,b));
	return 0;
}

