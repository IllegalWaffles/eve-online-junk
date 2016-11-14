#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "inventioncalcf.h"

int main(){

	srand(time(NULL));
	
	//BASE VALUES
	const int inventionRuns = 1800;
	const int baseRunsPerCopy = 1;
	const float baseInventionProbability = .43;
	/////////////
	
	//PRICES AND PROFITS
	const int numDatacore1 = 2;
	const int numDatacore2 = 2;
	const float datacore1cost =  89991.00;
	const float datacore2cost = 118991.76;
	/////////////
	
	//TEMP VARS
	register int successfulJobs = 0;
	int totalRuns = 0;
	/////////////
	
	int decryptorType;
	int finished = 0;
	
	do{
	
		system("cls");
	
		printf("Choose a decryptor -\n0 - No Decryptor\n1 - Accelerant\n");
		printf("2 - Attainment\n3 - Augmentation\n4 - Optimized Augmentation\n");
		printf("5 - Optimized Augmentation\n6 - Parity\n7 - Process\n8 - Symmetry\n>");
		
		scanf("%d", &decryptorType);
		
		Decryptor decryptorUsed; 
		decryptorUsed = initializeDecryptor(decryptorType);
		
		
		//CALCULATED VALUES
		int finalRunsPerCopy = baseRunsPerCopy + decryptorUsed.decryptRuns;
		float finalInventionProbability = baseInventionProbability * (decryptorUsed.decryptProb+1);
		/////////////
		
		printf("\nCalc Invention Success Probability:%.2f\n", finalInventionProbability);
		
		//printf("Simulation beginning...\n");
		
		successfulJobs = 0;
		register int c;
		for(c = 0; c < inventionRuns; c++){
			
			successfulJobs = (rand() % 100)/100.0 <= finalInventionProbability?successfulJobs+1:successfulJobs;
				//successfulJobs++;
		
		}
		
		//printf("Finished:\n");
		printf("Total Invention Runs:%d\n", inventionRuns);
		printf("Successful Jobs:%d\n", successfulJobs);
		
		int totalSuccessfulRuns = successfulJobs*finalRunsPerCopy;
		
		printf("Total Successful Runs:%d\n\n", totalSuccessfulRuns);
	
		float inventionCost = ((datacore1cost*(float)numDatacore1 + datacore2cost*(float)numDatacore2) + decryptorUsed.decryptCost) * inventionRuns;
		printf("Average invention cost per manufacturing job:%.2f\n", inventionCost/(float)totalSuccessfulRuns);
	
		printf("\n\nAgain? [0/1]:");
		scanf(" %d", &finished);
	
	}while(finished);
	
	return 0;

}
