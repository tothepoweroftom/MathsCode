//----------------------------

//Thomas Power 11342626
//Homework 4 Question 2

//---------------------------


#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<random>
using namespace std;
#include "Field.h"
#define PI 3.141

//Delta two decimal places
double RandomAngle(double delta)
{
	 double range_from  = -delta*100;
	 double range_to    = (delta)*100;
	random_device                  rand_dev;
	mt19937                        generator(rand_dev());
	uniform_int_distribution<double>  distr(range_from, range_to);

	return (distr(generator)/100);
}

int main(int argc, char* argv[]){
	//Set up lattice size 32+2(virtual)
	int s=34;
	srand((time)(NULL));
	double beta = 1.0;
	double delta = atof(argv[1])*0.01;
	
	//Need periodic boundaries
	Field lattice(s);
	double S[2];
	double delE;
	double prob;
	double r;
	
	//Counters to count accepted and rejected changes
	int counter1, counter2;
	counter1 = 0;
	counter2 = 0;
	int max_time = 25;

	for (int j=1; j<s-1; j++){
		for (int i=1; i<s-1; i++) 
		    {
		
				lattice(i,j) = RandomAngle(PI);
		
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




	// Loop over time to allow system to reach an equilibrium 
	for(int time=0; time<max_time; time++){		
		//A loop for measurements
		for (int j=1; j<s-1; j++){
    		for (int i=1; i<s-1; i++) 
    		{
				//Old Action

				S[0] = 4-cos(lattice(i,j)-lattice(i-1,j))-cos(lattice(i,j)-lattice(i+1,j))-cos(lattice(i,j)-lattice(i,j+1))-cos(lattice(i,j)-lattice(i,j-1));

				//New proposed spin angle for this site
				double deltachange = RandomAngle(delta);
				double theta = lattice(i,j) + deltachange;
				double magtheta = abs(theta);
				//Need a condition to protect the angle from escaping the bounds
				if(magtheta>PI){
					//Change the sign of the change so that it remains in bounds
					theta = lattice(i,j) - 2*deltachange;
				}
				//New Action
				S[1] = (4-cos(theta-lattice(i-1,j))-cos(theta-lattice(i+1,j))-cos(theta-lattice(i,j+1))-cos(theta-lattice(i,j-1)));
				//Calculate ratio
				delE = exp(-beta*(S[1]-S[0]));
		
				//Acceptance Probability random number between 0-1
				double ran = (double(rand())/RAND_MAX);

				//Acceptance Probability
				r = min(1.0,delE);

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
for(int j=s-2; j>0; j--){
	for(int i=1; i<s-1; i++){
		cout << lattice (i,j) << "\t";
	}
	cout << endl;
}
*/
double acceptancerate = double(counter1)/double(counter1+counter2);

cout << delta <<"\t"<< acceptancerate*100 << endl;
//cout << counter1 << "\t" << counter2 << endl;

}



