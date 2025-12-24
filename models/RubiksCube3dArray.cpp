#include <algorithm>
#include "RubiksCube.h"
class RubiksCube3dArray : public RubiksCube {
private:
    char cube[6][3][3]{};

    void rotateFace(int ind) {
        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 3; j++) {
                swap(cube[ind][i][j], cube[ind][j][i]);
            }
        }

        for (int i = 0; i < 3; i++) {
            reverse(cube[ind][i], cube[ind][i] + 3);
        }
    }

public:
    RubiksCube3dArray() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k] = getColorLetter(COLOR(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[int(face)][row][col];
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
                    if (cube[i][j][k] != getColorLetter(COLOR(i))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    RubiksCube &u() override{
        this->rotateFace(0);
        char temp[3]={};

        for(int i=0;i<3;i++){
          temp[i]=cube[4][0][i];
        }
        
        for(int i=0;i<3;i++){
          cube[4][0][i]=cube[1][0][i];
        }
        for(int i=0;i<3;i++){
          cube[1][0][i]=cube[2][0][i];
        }
        for(int i=0;i<3;i++){
          cube[2][0][i]=cube[3][0][i];
        }
        for(int i=0;i<3;i++){
          cube[3][0][i]=temp[i];
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
   
};


