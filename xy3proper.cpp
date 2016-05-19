//----------------------------

//Thomas Power 11342626
//Question 3 - C(beta)

//---------------------------


#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdlib>
#include<random>
using namespace std;
#include "FieldQ3.h"
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
	//Set up lattice size 32
	int s=32;
	srand((time)(NULL));
	double beta = atof(argv[1])*0.1;
	double delta = 1.78;
	
	//Need periodic boundaries
	Field lattice(s);
	double S[2];
	double delE;
	double r;
	double C = 0;
	
	//Counters to count accepted and rejected changes
	int counter1, counter2;
	counter1 = 0;
	counter2 = 0;
	int max_time = 50;
	//Initialize with random spins
	for (int j=0; j<=s-1; j++){
		for (int i=0; i<=s-1; i++) 
		    {
		
				lattice(i,j) = RandomAngle(PI);

			}
		}	




	// Loop over time to allow system to reach an equilibrium 
	for(int time=0; time<max_time; time++){		
		//A loop for measurements
		for (int j=0; j<=s-1; j++){
    		for (int i=0; i<=s-1; i++) 
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
				//Take measurement

				
				


			}
		}
	}
//Take measurement
	for (int j=0; j<=s-1; j++){
		for (int i=0; i<=s-1; i++) {
			
			C+=cos(lattice(i,j) - lattice(i+(s/2), j));
			//cout << C << endl;
		}	
	}


	//Output the beta value and correlation function
	cout << beta << "\t" << (C/1024) << endl;
}



