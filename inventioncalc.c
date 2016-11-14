#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){

	srand(time(NULL));

	//BASE VALUES
	const int inventionRuns = 1800;
	const int baseRunsPerCopy = 1;
	const float baseInventionProbability = .43;
	/////////////
	
	// DECRYPTOR VALUES
	const float decryptorInventionProbabilityAugmentor = -.4;
	const int decryptorJobRunAugmentor = 9;
	/////////////
	
	//PRICES AND PROFITS
	const int numDatacore1 = 2;
	const int numDatacore2 = 2;
	const float datacore1cost =  89991.00;
	const float datacore2cost = 118991.76;
	const float decryptorCost = 824998.94;
	/////////////
	
	//CALCULATED VALUES
	int finalRunsPerCopy = baseRunsPerCopy + decryptorJobRunAugmentor;
	float finalInventionProbability = baseInventionProbability * (decryptorInventionProbabilityAugmentor+1);
	/////////////
	
	register int successfulJobs = 0;
	int totalRuns = 0;
	float diceRoll;
	
	printf("Calc Invention Success Probability:%.2f\n", finalInventionProbability);
	
	printf("Simulation beginning...\n");
	
	register int c;
	for(c = 0; c < inventionRuns; c++){
	
		diceRoll = (rand() % 100)/100.0;
		//printf("%.2f\n", diceRoll);	
		
		if(diceRoll <= finalInventionProbability)
			successfulJobs++;
	
	}
	
	printf("Finished:\n");
	printf("Total Invention Runs:%d\n", inventionRuns);
	printf("Successful Jobs:%d\n", successfulJobs);
	
	int totalSuccessfulRuns = successfulJobs*finalRunsPerCopy;
	
	printf("Total Successful Runs:%d\n\n", totalSuccessfulRuns);

	float inventionCost = ((datacore1cost*(float)numDatacore1 + datacore2cost*(float)numDatacore2) + decryptorCost) * inventionRuns;
	printf("Average invention cost per manufacturing job:%.2f\n", inventionCost/(float)totalSuccessfulRuns);
	
	return 0;

}
