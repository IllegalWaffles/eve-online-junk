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

// Not used, but keep me for convenience
enum decryptorPrice {

	none = 0,
	accel = 1,
	attain = 2,
	augment = 3,
	optiAttain = 4,
	optiAug = 5,
	parity = 6,
	process =7,
	symmetry = 8

};

void printDecryptorStats(Decryptor,int,int);
int initializeData();

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

	if(initializeData() == 0){
	
		printf("Exiting....\n");
		return 1;
		
	}

	int inventionRuns;
	printf("Enter number of invention runs:");
    scanf(" %d", &inventionRuns);
	printf("\n");
	
	int finished;

	do{

		system("cls");

		printf("Choose a decryptor -\n0 - No Decryptor\n1 - Accelerant\n");
		printf("2 - Attainment\n3 - Augmentation\n4 - Optimized Attainment\n");
		printf("5 - Optimized Augmentation\n6 - Parity\n7 - Process\n8 - Symmetry\n");
		printf("9 - Display Stats For All\n>");

		int decryptorType;
		scanf("%d", &decryptorType);

		Decryptor decryptorUsed;

		if(decryptorType == 9){

			int i;			
			for(i = 0; i < 9; i++){

				decryptorUsed = decryptorArray[i];
				printDecryptorStats(decryptorUsed, inventionRuns,0);

			}
			
			printf("\n\nAgain? [0/1]:");
			scanf(" %d", &finished);
			continue;

		}
		

		//decryptorUsed = initializeDecryptor(decryptorType);
		
		printDecryptorStats(decryptorUsed, inventionRuns,1);

		printf("\n\nAgain? [0/1]:");
		scanf(" %d", &finished);

	}while(finished);

	return 0;

}

//Print stats for a single decryptor
void printDecryptorStats(Decryptor decryptor, int inventionRuns, int verbose)
{

	register int successfulJobs = 0;
	int totalRuns = 0;
	int finalRunsPerCopy = baseRunsPerCopy + decryptor.decryptRuns;
	float finalInventionProbability = baseInventionProbability * (decryptor.decryptProb+1);
	
	if(verbose)printf("\nCalc Invention Success Probability:%.2f\n", finalInventionProbability);

	successfulJobs = 0;
	register int c;
	
	for(c = 0; c < inventionRuns; c++)
		successfulJobs = (rand() % 100)/100.0 <= finalInventionProbability?successfulJobs+1:successfulJobs;

	if(verbose)printf("Total Invention Runs:%d\nSuccessful Jobs:%d\n", inventionRuns, successfulJobs);

	int totalSuccessfulRuns = successfulJobs*finalRunsPerCopy;
	if(verbose)printf("Total Successful Runs:%d\n\n", totalSuccessfulRuns);

	float inventionCost = ((datacore1cost*(float)numDatacore1 + datacore2cost*(float)numDatacore2) + decryptor.decryptCost) * inventionRuns;
	if(verbose)printf("Average invention cost per manufacturing job:%.2f\n", inventionCost/(float)totalSuccessfulRuns);	

	if(!verbose)printf("Name: %-33s - %11.2f\n", decryptor.name, inventionCost/(float)totalSuccessfulRuns);


}

int initializeData(void)
{

	// Data file should be called data.txt
	FILE *fp;
	fp = fopen("data.txt","r");
	
	/*
	
//BASE VALUES
int baseRunsPerCopy = 1;
float baseInventionProbability = .43;
/////////////
	
//PRICES AND PROFITS
int numDatacore1 = 2;
float datacore1cost =  89991.00;
int numDatacore2 = 2;
float datacore2cost = 118991.76;
float decryptorPrices[9];
/////////////
	
	*/
	
	int err;
	
	err = fscanf(fp, "%d %d %f", &numDecryptors, &baseRunsPerCopy, &baseInventionProbability);
	
	if(err != 3){
		printf("Could not read first three values. Values read: %d\n", err);
		return 0;
	}
	
	printf("Number of decryptors detected: %d\n", numDecryptors);
	
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
	
		err = fscanf(fp, "%*c%[^0-9.] %f %d %f", decryptorArray[i].name, &(decryptorArray[i].decryptProb), &(decryptorArray[i].decryptRuns), &(decryptorArray[i].decryptCost));
	
		printf("Scanned name: %s\nScanned Probability Augmentor: %.2f\nScanned Run Augmentor:%d\nScanned Cost:%.2f\n\n",
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

