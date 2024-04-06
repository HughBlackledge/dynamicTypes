
using namespace std;

class dyn{
public:
  void *data;
  char id;
  void operator =(int n){
    data = new int;
    (*(int*)data) = n;
    id = 'i';
  }
  void operator =(long n){
    data = new long;
    (*(long*)data) = n;
    id = 'l';
  }
  void operator =(double n){
    data = new double;
    (*(double*)data) = n;
    id = 'd';
  }
  dyn operator +(double n){
    if(id == 'd'){
      double d = (*(double*)data)+n;
    }

    (*(double*)data) = d;
    id = 'd';
  }
};

void println(dyn n){
  switch(n.id){
    case 'i':
    println((*(int*)(n.data)));
    break;
    case 'l':
    println(*(long*)(n.data));
    break;
    case 'd':
    println(*(double*)(n.data));
  }
}
