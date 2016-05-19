//----------------------------

//Thomas Power 11342626
//Homework 4 Question 1

//---------------------------


#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<random>
using namespace std;
#include "Field.h"
#define PI 3.14159

//Generates a random number from [-Pi, Pi)
double RandomAngle()
{
	 double range_from  = -PI*100000;
	 double range_to    = (PI-0.01)*100000;
	random_device                  rand_dev;
	mt19937                        generator(rand_dev());
	uniform_int_distribution<double>  distr(range_from, range_to);

	return (distr(generator)/100000);
}

int main(int argc, char* argv[]){
	srand((time)(NULL));
	//Set up lattice size 32+(2 virtual) outer layers act as mirrors
	int s=34;
	
	double beta = atof(argv[1])*0.1;
	
	//Need periodic boundaries
	Field lattice(s);
	double S[2];
	double delE;
	double r;
	double P;
	
	//Counters to count accepted and rejected changes
	int counter1, counter2;
	counter1 = 0;
	counter2 = 0;
	int max_time = 50;
	
	// Loop over time 
	for(int time=0; time<max_time; time++){
		//A loop for measurements
		for (int j=1; j<s-1; j++){
		    for (int i=1; i<s-1; i++) 
		    {
				//Old Action
		
				S[0] = 4-cos(lattice(i,j)-lattice(i-1,j))-cos(lattice(i,j)-lattice(i+1,j))-cos(lattice(i,j)-lattice(i,j+1))-cos(lattice(i,j)-lattice(i,j-1));
		
				//New proposed spin angle for this site random angle between -pi and pi
				double theta = RandomAngle();
		
				//New Action
		
				S[1] = (4-cos(theta-lattice(i-1,j))-cos(theta-lattice(i+1,j))-cos(theta-lattice(i,j+1))-cos(theta-lattice(i,j-1)));
		

				//Calculate ratio
				delE = exp(beta*(-1)*(S[0]-S[1]));
				r = min(1.0, delE);
		
				//Acceptance Probability random number between 0-1
				double ran = (double(rand())/RAND_MAX);
				//cout << ran << "\t" << r << endl;	
				
			    // Determine if the flip is acceptable and perform flip
				//State changes with probability r=min()
			    if (r>=ran) {
			        lattice(i,j) = theta;
					counter1++;
			    } 
		
				// Else if r < random number stays the same
			    else{
					lattice(i,j) = lattice(i,j);
						counter2++;
			    }
        
		
			    //Update Boundary Conditions, updating after every change perhaps a little inefficient.

			    // TOP

			    for (int j=1; j<s-1; j++) {
			        lattice(0,j) = lattice(s-2,j);
			        lattice(s-1,j) = lattice(1,j);
			    }

			    // LEFT

			    for (int i=1; i<s-1; i++) {
			        lattice(i,0)=lattice(i,s-2);
			        lattice(i,s-1) =lattice(i,1);
			    } 
			}
		}
}






/*
//Print final configuration of field
for(int j=s-1; j>=0; j--){
	for(int i=0; i<s; i++){
		cout << lattice (i,j) << "\t";
	}
	cout << endl;
}
*/
double acceptancerate = double(counter1)/double(counter1+counter2);

cout << beta <<"\t"<< acceptancerate*100 << endl;
//cout << counter1 << "\t" << counter2 << endl;


}

