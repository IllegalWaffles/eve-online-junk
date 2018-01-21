#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#include "inventionCalc.h"

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
Decryptor **decryptorArray;
/////////////

const int inventionRuns = NUM_INVENTION_RUNS;

int main(){

	clear();

	info("%s","Test\n");

	srand(time(NULL));

	if(!initializeData(false)){

		printf("Error: invalid input\n");
		return 1;

	}

	printf("\n");

	bool finished;

	do{

		clear();

		printf("Choose a decryptor -\n");

		int i;
		for(i = 0; i < numDecryptors; i++){

			printf("%d - %s\n", i, decryptorArray[i]->name);

		}
		printf("a - Display Stats For All\n");
		printf("q - Quit\n> ");

		char decryptorType;
		scanf(" %c", &decryptorType);	//Read user input

		if(decryptorType == 'q' || decryptorType == 'Q'){	//User wants to quit
			printf("Byebye!\n");
			return 0;
		}else if(decryptorType == 'a' || decryptorType == 'A'){	//User wants to see info for all the decryptors

			finished = printAllDecryptorStats(decryptorArray, numDecryptors, inventionRuns);

		}else{

			Decryptor *decryptorUsed = decryptorArray[decryptorType-'0'];	// Get the decryptor the user wants

			printDecryptorStats(*decryptorUsed, inventionRuns, 0);  // Print stats for this decryptor only

			printf("\n\nAgain? [0/1]:");
			int temp;
			scanf(" %d", &temp);
			finished = !temp;

		}

	}while(!finished);

	return 0;

}

void printTableHeader(){

	printf("%-33s - %11s - %-7s\n", "Name", "Avg Cost", "Ratio");
	printHR();

}

void printHR(){

	printf("-------------------------------------------------------\n");

}

//Print stats for a single decryptor
void printDecryptorStats(const Decryptor decryptor, const int inventionRuns, const int brief)
{

	unsigned int finalRunsPerCopy = baseRunsPerCopy + decryptor.decryptRuns;
	float finalInventionProbability = baseInventionProbability * (decryptor.decryptProb+1);

	if(!brief){

		printf("%s", decryptor.name);
		printf("\nCalc Invention Success Probability:%.3f\n", finalInventionProbability);	// Final invention success probability

	}

	register unsigned int successfulJobs = 0;	// Counter for successful jobs
	register unsigned int c;

	//Number crunching. This should be multithreaded
	if(brief){

		//If this is brief, then we don't need to calculate jobs anymore.
		//Number of successful jobs has already been calculated in another thread.
		successfulJobs = decryptor.num_successful_runs;

	}else{

		//Otherwise, since we're doing a single decryptor, we need to calculate
		//Successful jobs on the fly.

		for(c = 0; c < inventionRuns; c++)
			successfulJobs = (rand() % 100)/100.0 <= finalInventionProbability?successfulJobs+1:successfulJobs;	// Roll the dice!

	}

	if(!brief)
		printf("Total Invention Runs:%d\nSuccessful Jobs:%d\n", inventionRuns, successfulJobs);

	unsigned int totalSuccessfulRuns = successfulJobs*finalRunsPerCopy;

	if(!brief)
		printf("Total Successful Runs:%d\n\n", totalSuccessfulRuns);

	float inventionCost = ((datacore1cost*(float)numDatacore1 + datacore2cost*(float)numDatacore2) + decryptor.decryptCost) * inventionRuns;
	float runRatio = (float)totalSuccessfulRuns/(float)inventionRuns;

	if(!brief){

		printf("Average invention cost per manufacturing job:%.2f\n", inventionCost/(float)totalSuccessfulRuns);
		printf("Ratio of Invention Runs to Final Job Runs:%.3f\n", runRatio);

	}

	if(brief)
		fprintf(stdout, "%-33s - %11.2f - %-7.3f\n", decryptor.name, inventionCost/(float)totalSuccessfulRuns, runRatio);

}

bool printAllDecryptorStats(Decryptor **decryptors, const int numDecryptors, const int inventionRuns){

	printf("\n\n");
	printTableHeader();

	//Start a thread for calculations
	pthread_t decryptor_threads[numDecryptors];

	for(int i = 0; i < numDecryptors; i++){

		if(pthread_create(&decryptor_threads[i], NULL, calc_successful_jobs, (void*)decryptorArray[i])){

			fprintf(stderr, "There was an error creating a thread\n");
			exit(1);

		}else{

			debug("Started thread %d for decryptor %s\n", i, decryptorArray[i]->name);

		}

	}

	for(int i = 0; i < numDecryptors; i++){

		//Calculate the number of successful invention runs in another thread
		pthread_join(decryptor_threads[i], NULL);
		debug("Value of thread %d: %lu\n", i, decryptorArray[i]->num_successful_runs);

		//Calculate the rest of the statistics here
		printDecryptorStats(*decryptorArray[i], inventionRuns, 1);

	}

	printf("\n\nAgain? [0/1]:");
	int temp;
	scanf(" %d", &temp);

	bool rtn = !temp;
	return rtn;

}

void *calc_successful_jobs(void *arg){

	Decryptor *decryptor = (Decryptor*)arg;

	float finalInventionProbability = baseInventionProbability * (decryptor->decryptProb+1);

	long successfulJobs = 0;	// Counter for successful jobs
	register unsigned int c;

	for(c = 0; c < inventionRuns; c++)
		successfulJobs = (rand() % 100)/100.0 <= finalInventionProbability?successfulJobs+1:successfulJobs;	// Roll the dice!

	debug("Decryptor ID: %d - Number of successful jobs: %lu\n", decryptor->id, successfulJobs);

	decryptor->num_successful_runs = successfulJobs;

	return 0;

}

Decryptor **initializeData(){

	// Data file expects values in this order:
	// numDecryptors baseRuns baseInventionProb
	// numDatacore1 costDatacore1 numDatacore2 costDatacore2
	// Then decryptor info: name probability runs cost
	// Data file should be called data.txt
	FILE *fp = fopen("data.txt","r");

	int err;

	err = fscanf(fp, "%d %d %f", &numDecryptors, &baseRunsPerCopy, &baseInventionProbability);

	if(err != 3){
		printf("Could not read first three values. Values read: %d\n", err);
		return 0;
	}

	info("Number of decryptors detected: %d\n", numDecryptors);

	decryptorArray = (Decryptor**)calloc(numDecryptors,sizeof(Decryptor*));	// Clear and allocate our decryptor array

	err = fscanf(fp, "%d %f %d %f", &numDatacore1, &datacore1cost, &numDatacore2, &datacore2cost);

	if(err != 4){
		printf("Could not read datacore values. Values read: %d\n", err);
		return 0;
	}

	// Start reading decryptor info
	register int i;
	for(i = 0; i < numDecryptors; i++)
	{

		decryptorArray[i] = calloc(1, sizeof(Decryptor));
		err = fscanf(fp, "%*c%[^0-9.-] %f %d %f", decryptorArray[i]->name, &(decryptorArray[i]->decryptProb), &(decryptorArray[i]->decryptRuns), &(decryptorArray[i]->decryptCost));

		debug("Scanned name: %s\nScanned Probability Augmentor: %.2f\nScanned Run Augmentor:%d\nScanned Cost:%.2f\n\n",
		decryptorArray[i]->name, decryptorArray[i]->decryptProb, decryptorArray[i]->decryptRuns, decryptorArray[i]->decryptCost);

		decryptorArray[i]->id = i;
		decryptorArray[i]->num_successful_runs = 0;

		if(err != 4)
		{

			printf("Could not read decryptor %d.\n", i);
			return 0;

		}

	}

	fclose(fp);

	return decryptorArray;

}
