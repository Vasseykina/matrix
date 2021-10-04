#include <iostream>
#include "Matrix.h"
using namespace std;
int main() {
    Matrix <int> m (2,2);
    Matrix <int> m2 (2,2);
    cin>>m>> m2;
    cout<<m <<m2;
    m*=m2;
    cout<<m<<endl;
}
