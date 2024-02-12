#include "ShowMeCash.h"

DynamicArray* createDynamicArray() 
{
    DynamicArray* dynArray = (DynamicArray*)malloc(sizeof(DynamicArray)); //Allocates memory for the DynamicArray structure
    if (dynArray == NULL) //Checks for memory allocation failure
    {
		#ifdef DEBUG //Checks for debug "setting"
		{
			printf("DEBUG: Failed to allocate memory for DynamicArray in createDynamicArray...\n");
		}
		#endif //Ends debugging exclusive code
		
        return NULL;
    }

    dynArray -> data = (int*)malloc(INITIAL_CAPACITY * sizeof(int)); //Allocates memory for the data array
    if (dynArray -> data == NULL) 
    {
        #ifdef DEBUG //Checks for debug "setting"
		{
			printf("DEBUG: Failed to allocate memory for data in createDynamicArray...\n");
		}
		#endif //Ends debugging exclusive code
		
        free(dynArray); //Frees previously allocated memory
		
        return NULL; //Returns error code of NULL
    }

    dynArray -> size = 0; //Initializes the size to 0
    dynArray -> capacity = INITIAL_CAPACITY; //Initializes the capacity to the initial value
	
    return dynArray; //Returns the dynamic array
}

void appendValue(DynamicArray* dynArray, int value) 
{
    if (dynArray -> size >= dynArray -> capacity) //Checks if the array is full
    {
        
        dynArray -> capacity *= 2; //If the array is full, the capacity is doubled
		
        dynArray -> data = (int*)realloc(dynArray -> data, dynArray -> capacity * sizeof(int)); //Reallocates memory
        if (dynArray -> data == NULL) //Checks for memory allocation failure
        {
			#ifdef DEBUG //Checks for debug "setting"
			{
				printf("DEBUG: Failed to reallocate memory for data in appendValue...\n");
			}
			#endif //Ends debugging exclusive code
			
            return;
        }
    }

    dynArray -> data[dynArray -> size] = value; //Adds the value to the end of the array
    dynArray -> size++; //Increments the size
}


int getValueAtIndex(DynamicArray* dynArray, int index) 
{
    if (index < dynArray -> size) //Checks if the provided index is within the bounds of the DynamicArray
    {
        return dynArray -> data[index]; //Returns the value at the specified index in the DynamicArray
    } 
	
    else 
    {
		#ifdef DEBUG //Checks for debug "setting"
		{
			printf("DEBUG: Index out of bounds in getValueAtIndex...\n"); 
		}
		#endif //Ends debugging exclusive code
		
        return -1; //Returns error code of -1
    }
}


void freeDynamicArray(DynamicArray* dynArray) 
{
    free(dynArray -> data); //Frees the data array
    free(dynArray); //Frees the DynamicArray structure
}


void countAndPrintValueProbabilities(DynamicArray* dynArray) 
{
    if (dynArray -> size == 0) //Checks for empty array
	{
		#ifdef DEBUG //Checks for debug "setting"
		{
			printf("DEBUG: DynamicArray is empty in countAndPrintValueProbabilities...\n");
		}
		#endif //Ends debugging exclusive code
		
        return;
    }

    //Creates an array to store value-probability pairs
    ValueProbability* probabilityArray = (ValueProbability*)malloc(dynArray -> size * sizeof(ValueProbability));
    if (probabilityArray == NULL) //Checks for memory allocation failure
	{
		#ifdef DEBUG //Checks for debug "setting"
		{
			printf("DEBUG: Failed to allocate memory for probabilityArray in countAndPrintValueProbabilities...\n");
		}
		#endif //Ends debugging exclusive code
		
        return;
    }

    int current = dynArray -> data[0]; //Initializes with the value of the first element in the 'data' array of 'dynArray'
	int count = 1; //Initializes to 1 to keep track of the number of consecutive occurrences of 'current'
	int index = 0; //Initializes to 0

    for (int i = 1; i < dynArray -> size; i++) //Iterates through the elements of the array
	{
        if (dynArray -> data[i] == current) //Checks if the current element is equal to the previous element
		{
            count++; //Increments the count
        }
		
		else 
		{
            probabilityArray[index].value = current; //Stores the current value in the probabilityArray
			
			//Calculates and store the probability of the current value
            probabilityArray[index].probability = calculateProbability(count, dynArray -> size); 
            index++;
            current = dynArray -> data[i];
            count = 1;
        }
    }

    //Calculates the probability for the last element
    probabilityArray[index].value = current;
    probabilityArray[index].probability = calculateProbability(count, dynArray -> size);

    index++; //Increments the index for the last value

    //Sorts the probabilityArray by probability
    qsort(probabilityArray, index, sizeof(ValueProbability), compareValueProbability);

    //Prints the table header
    printf("| Value | Probability |\n");
    printf("|-------|-------------|\n");

    //Prints the sorted values with probabilities in a table
    for (int i = 0; i < index; i++) 
	{
        printf("| %-5d | %-10.3f%% |\n", probabilityArray[i].value, probabilityArray[i].probability);
    }

    //Frees the allocated memory
    free(probabilityArray);
}


double calculateProbability(int valueCount, int totalCount)
{
    return (((double)valueCount / totalCount) * 100);
}


int compareValueProbability(const void* a, const void* b) 
{
    const ValueProbability* vp1 = (const ValueProbability*)a; //Cast 'a' to ValueProbability pointer and assign it to vp1
    const ValueProbability* vp2 = (const ValueProbability*)b; //Cast 'b' to ValueProbability pointer and assign it to vp2

    if (vp1 -> probability > vp2 -> probability) return -1; //If vp1's probability is greater than vp2's probability, return -1 
    if (vp1 -> probability < vp2 -> probability) return 1;  //If vp1's probability is less than vp2's probability, return 1 

    return 0; //If vp1 and vp2 have the same probability, return 0
}


int compareIntegers(const void* ptr1, const void* ptr2) 
{
    const int* intPtr1 = (const int*)ptr1; //Cast ptr1 to pointer to const int
    const int* intPtr2 = (const int*)ptr2; //Cast ptr2 to pointer to const int

    //If the first integer is less than the second, return negative.
    //If the first integer is greater than the second, return positive.
    //If they are equal, return zero.
    return *intPtr1 - *intPtr2;
}
