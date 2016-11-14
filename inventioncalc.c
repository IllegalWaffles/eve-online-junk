#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(){

	srand(time(NULL));

	//Table of decryptor types here
	typedef enum decryptor{
		
		none = 0,
		accelerant = 1,
		attainment = 2,
		augmentation = 3,
		optiAttainment = 4,
		optiAugmentation = 5,
		parity = 6,
		process = 7,
		symmetry = 8
		
	} Decryptor;

	// DECRYPTOR VALUES
	float decryptProb;
	int decryptRuns;
	float decryptCost;
	/////////////

	
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
	float diceRoll;
	/////////////
	
	int decryptorType;
	int finished = 0;
	
	do{
	
		printf("Choose a decryptor -\n0 - No Decryptor\n1 - Accelerant\n");
		printf("2 - Attainment\n3 - Augmentation\n4 - Optimized Augmentation\n");
		printf("5 - Optimized Augmentation\n6 - Parity\n7 - Process\n8 - Symmetry\n>");
		
		scanf("%d", &decryptorType);
		
		Decryptor decryptorUsed = decryptorType;
	
		switch(decryptorUsed){
			
			case none:
				decryptProb = 0;
				decryptRuns = 0;
				decryptCost = 0;
			break;
			
			case accelerant:
				decryptProb = .2;
				decryptRuns = 1;
				decryptCost = 325126.04;
			break;
			
			case attainment:
				decryptProb = .8;
				decryptRuns = 4;
				decryptCost = 2500000.00;
			break;
			
			case augmentation:
				decryptProb = -.4;
				decryptRuns = 9;
				decryptCost = 816055.61;
			break;
			
			case optiAttainment:
				decryptProb = .9;
				decryptRuns = 2;
				decryptCost = 3176002.01;
			break;
			
			case optiAugmentation: 
				decryptProb = -.1;
				decryptRuns = 7;
				decryptCost = 5005000.21;
			break;
			
			case parity:
				decryptProb = .5;
				decryptRuns = 3;
				decryptCost = 1012114.25;
			break;
			
			case process:
				decryptProb = .1;
				decryptRuns = 0;
				decryptCost = 1012114.25;
			break;
			
			case symmetry:
				decryptProb = 0;
				decryptRuns = 2;
				decryptCost = 322250.96;
			break;
			
		}
		
		//CALCULATED VALUES
		int finalRunsPerCopy = baseRunsPerCopy + decryptRuns;
		float finalInventionProbability = baseInventionProbability * (decryptProb+1);
		/////////////
		
		printf("\nCalc Invention Success Probability:%.2f\n", finalInventionProbability);
		
		//printf("Simulation beginning...\n");
		
		register int c;
		for(c = 0; c < inventionRuns; c++){
		
			diceRoll = (rand() % 100)/100.0;
			//printf("%.2f\n", diceRoll);	
			
			if(diceRoll <= finalInventionProbability)
				successfulJobs++;
		
		}
		
		//printf("Finished:\n");
		printf("Total Invention Runs:%d\n", inventionRuns);
		printf("Successful Jobs:%d\n", successfulJobs);
		
		int totalSuccessfulRuns = successfulJobs*finalRunsPerCopy;
		
		printf("Total Successful Runs:%d\n\n", totalSuccessfulRuns);
	
		float inventionCost = ((datacore1cost*(float)numDatacore1 + datacore2cost*(float)numDatacore2) + decryptCost) * inventionRuns;
		printf("Average invention cost per manufacturing job:%.2f\n", inventionCost/(float)totalSuccessfulRuns);
	
		printf("\n\nAgain? [0/1]:");
		scanf(" %d", &finished);
	
	}while(finished);
	
	return 0;

}
