#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Each decryptor has these values. Initializer is below
typedef struct decryptor {

    char name[60];
    float decryptProb;
    int decryptRuns;
    float decryptCost;

} Decryptor;

void printDecryptorStats(Decryptor,int,int);
int initializeData(int);
void printTableHeader();
void clear();

//BASE VALUES
int baseRunsPerCopy;
float baseInventionProbability;
int numDecryptors;
/////////////

//PRICES AND PROFITS
int numDatacore1;
float datacore1cost;
int numDatacore2;
float datacore2cost;
Decryptor *decryptorArray;
/////////////

int main(){

	srand(time(NULL));

	if(initializeData(0) == 0){
	
		printf("Exiting....\n");
		return 1;
		
	}

	int inventionRuns;
	printf("Enter number of invention runs:");
    	scanf(" %d", &inventionRuns);
	printf("\n");
	
	int finished;

	do{

		clear();

		printf("Choose a decryptor -\n");
		
		int i;
		for(i = 0; i < numDecryptors; i++){
			
			printf("%d - %s\n", i, decryptorArray[i].name);
			
		}
		
		printf("a - Display Stats For All\n");
		printf("q - Quit\n> ");

		char decryptorType;
		scanf(" %c", &decryptorType);	//Read user input

		clear();

		Decryptor decryptorUsed;
	
		if(decryptorType == 'q' || decryptorType == 'Q'){	//User wants to quit
			printf("Byebye!");
			return 0;
		}

		if(decryptorType == 'a' || decryptorType == 'A'){	//User wants to see info for all the decryptors

	
			printTableHeader();
					
			for(i = 0; i < numDecryptors; i++){	//Cycle through all the decryptors

				decryptorUsed = decryptorArray[i];
				printDecryptorStats(decryptorUsed, inventionRuns,0);

			}
			
			printf("\n\nAgain? [0/1]:");
			scanf(" %d", &finished);
			continue;

		}
		
		decryptorUsed = decryptorArray[decryptorType-'0'];	// Get the decryptor the user wants
		
		printDecryptorStats(decryptorUsed, inventionRuns,1);	// Print stats for this decryptor only

		printf("\n\nAgain? [0/1]:");
		scanf(" %d", &finished);

	}while(finished);

	return 0;

}

void printTableHeader(){
	
	printf("%-33s - %11s - %-7s\n", "Name", "Avg Cost", "Ratio");
	int i;
	printf("-------------------------------------------------------\n");
	
}

//Print stats for a single decryptor
void printDecryptorStats(Decryptor decryptor, int inventionRuns, int verbose)
{

	register int successfulJobs = 0;
	int totalRuns = 0;
	int finalRunsPerCopy = baseRunsPerCopy + decryptor.decryptRuns;
	float finalInventionProbability = baseInventionProbability * (decryptor.decryptProb+1);
	
	if(verbose)printf("%s", decryptor.name);
	if(verbose)printf("\nCalc Invention Success Probability:%.3f\n", finalInventionProbability);	// Final invention success probability

	successfulJobs = 0;	// Counter for successful jobs
	register int c;
	
	for(c = 0; c < inventionRuns; c++)
		successfulJobs = (rand() % 100)/100.0 <= finalInventionProbability?successfulJobs+1:successfulJobs;	// Roll the dice!

	if(verbose)printf("Total Invention Runs:%d\nSuccessful Jobs:%d\n", inventionRuns, successfulJobs);

	int totalSuccessfulRuns = successfulJobs*finalRunsPerCopy;
	if(verbose)printf("Total Successful Runs:%d\n\n", totalSuccessfulRuns);

	float inventionCost = ((datacore1cost*(float)numDatacore1 + datacore2cost*(float)numDatacore2) + decryptor.decryptCost) * inventionRuns;
	float runRatio = (float)totalSuccessfulRuns/(float)inventionRuns;
	if(verbose){
	
		printf("Average invention cost per manufacturing job:%.2f\n", inventionCost/(float)totalSuccessfulRuns);	
		printf("Ratio of Invention Runs to Final Job Runs:%.3f\n", runRatio);

	}

	if(!verbose)printf("%-33s - %11.2f - %-7.3f\n", decryptor.name, inventionCost/(float)totalSuccessfulRuns, runRatio);

}

int initializeData(int verbose)
{

	// Data file expects values in this order:
	// numDecryptors baseRuns baseInventionProb
	// numDatacore1 costDatacore1 numDatacore2 costDatacore2
	// Then decryptor info: name probability runs cost
	// Data file should be called data.txt
	FILE *fp;
	fp = fopen("data.txt","r");
	
	int err;
	
	err = fscanf(fp, "%d %d %f", &numDecryptors, &baseRunsPerCopy, &baseInventionProbability);
	
	if(err != 3){
		printf("Could not read first three values. Values read: %d\n", err);
		return 0;
	}
	
	if(verbose)printf("Number of decryptors detected: %d\n", numDecryptors);
	
	decryptorArray = (Decryptor*)calloc(numDecryptors,sizeof(Decryptor));	// Clear and allocate our decryptor array
	
	err = fscanf(fp, "%d %f %d %f", &numDatacore1, &datacore1cost, &numDatacore2, &datacore2cost);
		
	if(err != 4){
		printf("Could not read datacore values. Values read: %d\n", err);
		return 0;
	}
	
	// Start reading decryptor info
	register int i;
	for(i = 0; i < numDecryptors; i++)
	{
	
		err = fscanf(fp, "%*c%[^0-9.-] %f %d %f", decryptorArray[i].name, &(decryptorArray[i].decryptProb), &(decryptorArray[i].decryptRuns), &(decryptorArray[i].decryptCost));
	
		if(verbose)printf("Scanned name: %s\nScanned Probability Augmentor: %.2f\nScanned Run Augmentor:%d\nScanned Cost:%.2f\n\n",
		decryptorArray[i].name, decryptorArray[i].decryptProb, decryptorArray[i].decryptRuns, decryptorArray[i].decryptCost);
	
		if(err != 4)
		{
		
			printf("Could not read decryptor %d.\n", i);
			return 0;
		
		}
	
	}
	
	fclose(fp);

	return 1;

}

void clear(){
	
	#ifdef __WIN32__
	system("cls");
	#else
	system("clear");
	#endif
	
}

