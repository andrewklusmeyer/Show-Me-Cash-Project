#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

//Struct to represent a dynamic array
typedef struct 
{
    int* data;        
    int size;
    int capacity;  
} DynamicArray;

//Struct to store value-probability pairs
typedef struct 
{
    int value;
    double probability;
} ValueProbability;

DynamicArray* createDynamicArray();
void appendValue(DynamicArray* dynArray, int value);
int getValueAtIndex(DynamicArray* dynArray, int index);
void freeDynamicArray(DynamicArray* dynArray);
void countAndPrintValueProbabilities(DynamicArray* dynArray);
double calculateProbability(int valueCount, int totalCount);
int compareValueProbability(const void* a, const void* b);
int compareIntegers(const void* ptr1, const void* ptr2); 
