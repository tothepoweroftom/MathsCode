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
