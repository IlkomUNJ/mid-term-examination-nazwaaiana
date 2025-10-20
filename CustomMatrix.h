#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H
#include <iostream>
using namespace std;
class CustomMatrix{
public:
    bool mat[3][3]={0};

    CustomMatrix(){
        for(int i=0; i<3; i++) for(int j=0; j<3; j++) mat[i][j] = false;
    }

    CustomMatrix(bool m[3][3]){
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
                mat[i][j] = m[i][j];
            }
        }
    }

    void fillMatrix(bool m[3][3]){
        for (int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
                mat[i][j] = m[i][j];
            }
        }
    }

    bool isEmpty() const {
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(mat[i][j]) return false;
            }
        }
        return true;
    }
};
#endif // CUSTOMMATRIX_H
