#include <algorithm>
#include "RubiksCube.h"


class RubiksCube1dArray:public RubiksCube{
  private:
    char cube[54]={};
    static inline int getIndex(int ind,int row,int col){
        return 9*ind+row*3+col;
    }



    void rotate(int ind){
         for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                swap(cube[getIndex(ind,i,j)], cube[getIndex(ind,j,i)]);
            }
        }

        for (int i = 0; i < 3; i++) {
           reverse(
    cube+getIndex(ind, i, 0),
    cube+getIndex(ind, i, 0)+3
);

        }
    }
  public:
    RubiksCube1dArray(){
      for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[getIndex(i,j,k)] = getColorLetter(COLOR(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[getIndex(int(face),row,col)];
        switch (color) {
            case 'B': return COLOR::BLUE;
            case 'W': return COLOR::WHITE;
            case 'Y': return COLOR::YELLOW;
            case 'O': return COLOR::ORANGE;
            case 'G': return COLOR::GREEN;
            case 'R': return COLOR::RED;
        }
        return COLOR::WHITE; 
    }

    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (cube[getIndex(i,j,k)] != getColorLetter(COLOR(i))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    RubiksCube &u() override{
        this->rotate(0);
        char temp[3]={};

        for(int i=0;i<3;i++){
          temp[i]=cube[getIndex(4,0,2-i)];
        }
        
        for(int i=0;i<3;i++){
          cube[getIndex(4,0,2-i)]=cube[getIndex(1,0,2-i)];
        }
        for(int i=0;i<3;i++){
          cube[getIndex(1,0,2-i)]=cube[getIndex(2,0,2-i)];
        }
        for(int i=0;i<3;i++){
          cube[getIndex(2,0,2-i)]=cube[getIndex(3,0,2-i)];
        }
        for(int i=0;i<3;i++){
          cube[getIndex(3,0,2-i)]=temp[i];
        }


        return *this;

    }
   

    RubiksCube &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    }

    RubiksCube &u2() override {
        this->u();
        this->u();
 
        return *this;
    }
   
    RubiksCube &l() override{

        this->rotate(1);
        char temp[3]={};
        for(int i=0;i<3;i++){
            temp[i]=cube[getIndex(0,i,0)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(0,i,0)]=cube[getIndex(4,2-i,2)];
        }
        for(int i=0;i<3;i++){
          cube[getIndex(4,2-i,2)]=cube[getIndex(5,i,0)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(5,i,0)]=cube[getIndex(2,i,0)];
        }
        for(int i=0;i<3;i++){
            cube[getIndex(2,i,0)]=temp[i];
        }


        return *this;

    }

    RubiksCube &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    }

    RubiksCube &l2() override {
        this->l();
        this->l();

        return *this;
    }

    RubiksCube &f() override{
        this->rotate(2);
         char temp[3]={};
         for(int i=0;i<3;i++){
            temp[i]=cube[getIndex(0,2,i)];
         }
         for(int i=0;i<3;i++){
            cube[getIndex(0,2,i)]=cube[getIndex(1,2-i,2)];
         }
         for(int i=0;i<3;i++){
            cube[getIndex(1,2-i,2)]=cube[getIndex(5,0,2-i)];
         }
         for(int i=0;i<3;i++){
            cube[getIndex(5,0,2-i)]=cube[getIndex(3,i,0)];
         }
         for(int i=0;i<3;i++){
            cube[getIndex(3,i,0)]=temp[i];
         }

        return *this;
    }
    RubiksCube &fPrime() override {
        this->f();
        this->f();
        this->f();

        return *this;
    }

    RubiksCube &f2() override {
        this->f();
        this->f();

        return *this;
    }
bool operator==(const RubiksCube1dArray &r1) const {
        for (int i = 0; i < 54; i++) {
            if (cube[i] != r1.cube[i]) return false;
        }
        return true;
    }

    RubiksCube1dArray &operator=(const RubiksCube1dArray &r1) {
        for (int i = 0; i < 54; i++) {
            cube[i] = r1.cube[i];
        }
        return *this;
    }
};
struct Hash1d{
  size_t operator()(const RubiksCube1dArray &r1) const {
        string str = "";
        for (int i = 0; i < 54; i++) str += r1.cube[i];
        return hash<string>()(str);
    }
}
