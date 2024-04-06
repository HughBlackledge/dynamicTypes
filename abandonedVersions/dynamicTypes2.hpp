
using namespace std;

enum datatype{i,f,d,c,s,b};

datatype getType(int n){
  return i;
}

class dyn{
public:
  any data;
  dyn(){
    
  }
  dyn& operator=(T n){
    if(type!=getType(n)){
      ptr = new T;
    }
    ptr = *(T*)n;
  }
};
