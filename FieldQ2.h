#define PI 3.14159
#include<random>

double RandomAngle()
{
	 double range_from  = -PI*100000;
	 double range_to    = (PI-0.01)*100000;
	random_device                  rand_dev;
	mt19937                        generator(rand_dev());
	uniform_int_distribution<double>  distr(range_from, range_to);

	return (distr(generator)/100000);
}

class Field
{
  private: 
    double* data;
    int     n;
    int index(int x, int y) const { return x + (n+1)*y; } 
  public:
// constructor - takes one argument, which is grid spacing 
    Field(int ngrid)  : n(ngrid) 
    {
      data = new double[(ngrid+1)*(ngrid+1)];
      int l=(ngrid)*(ngrid); 
      for (int i=0;i<l;i++) data[i]=0.0; // Initialise field to 0 everywhere	  
    }
// destructor 
    ~Field()
    { 
      delete [] data;
    }

// Access a site 
    double& operator() (int x, int y)       { return data[index(x,y)];}
    double  operator() (int x, int y) const { return data[index(x,y)];}
 
    int size() const { return n;} 
};
