#include<iostream>
#include<cstring>
#include<inttypes.h>
using namespace std;

class Events 
{

public:

  Events()
  {
  }
  virtual ~Events()
  {
  }

  /** Every event class should implement
    * this function.
    *
    * @param[in] data Raw event data.
    */
  virtual void initWithData(const unsigned char *data)=0;

};
  

