#include "ShowMeCash.h"


int main(void) 
{
    DynamicArray* dynArray = createDynamicArray(); //Creates a new DynamicArray

    FILE *file = fopen("WinningNumbersList.txt", "r"); //Opens the file for reading
    if (file == NULL) //Checks for failure in opening
	{
		#ifdef DEBUG //Checks for debug "setting"
		{
			printf("DEBUG: Failed to open file in main...\n");
		}
		#endif //Ends debugging exclusive code
		
        freeDynamicArray(dynArray); //Frees the DynamicArray if file opening fails
		
        return 1; //Returns an error code of 1
    }

    int tempInt;
    int tempCount = 0;
	
    while (fscanf(file, "%d", &tempInt) == 1) //Reads through the file
	{
        tempCount++;
        appendValue(dynArray, tempInt); //Adds each integer from the file to the DynamicArray
    }

    fclose(file); //Closes the file

    //Sort the array using Quick Sort
	qsort(dynArray -> data, dynArray -> size, sizeof(int), compareIntegers);

	
	printf("\nThe inception of this program can be traced back to the insightful work of Professor Sean Goggins \nat the University of Missouri.");
	printf(" Professor Goggins' Python-based program for calculating probabilities\nin the MegaMillions lottery served as a catalyst for the development of a similar tool customized\nfor the Show Me Cash lottery.");
	printf(" It is worth highlighting that a conscious decision was made to undertake\nthis project using the C programming language.");
	printf(" With great anticipation, I am pleased to share the\nresults with you:\n\n");

	
   
    countAndPrintValueProbabilities(dynArray); //Counts and prints the occurrences of each value

    printf("\nWithin this dataset, there are %d values that were used from the publicly available dataset that can\n", tempCount);
	printf("be found on the official website of the Missouri Lottery. The data used in this program begins on the\n");
	printf("date of January 1st, 2010 and is analyzed through September 12th, 2023.\n\n");
	
    freeDynamicArray(dynArray); //Frees the memory allocated for the DynamicArray

    return 0;
}