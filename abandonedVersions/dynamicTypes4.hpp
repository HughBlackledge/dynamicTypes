
using namespace std;

enum datatype{i,f,d,c,s,b};

datatype getType(int n){
  return i;
}

datatype getType(float n){
  return f;
}

datatype getType(double n){
  return d;
}

datatype getType(char n){
  return c;
}

datatype getType(string n){
  return s;
}

datatype getType(bool n){
  return b;
}

template<typename T>

class dyn{
public:
  void *ptr;
  datatype type;

  dyn(){
    ptr = new bool;
    type = b;
  }
  dyn& operator=(T&& n){
    if(type!=getType(n)){
      ptr = new T;
    }
    ptr = *(T*)n;
  }
};
