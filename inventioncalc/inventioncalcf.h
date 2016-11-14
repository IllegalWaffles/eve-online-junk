typedef struct decryptor {
		
		char name[30];
		float decryptProb;
		float decryptCost;
		int decryptRuns;
		
} Decryptor;

Decryptor initializeDecryptor(int);
