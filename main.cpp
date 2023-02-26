//Date: 9/7/2022

#include<iostream>
#include<random>
#include<vector>
using namespace std;

const char colors[] = { 'R','G','B','Y','O','P' };

struct gear {
	int orientation = 0; // 0="_", 1="/", 2="\", 3="-(inverse of solved)", 4="//", 5="\\"
	char clr1; //color 1 on gear
	char clr2; //color 2 on gear
};

struct face {
	char pieces[3][3];
};

struct ball {
	face faces[6]; //6 faces on ball
	gear gears[12]; //12 gears on ball
}gearball;

struct node {
	node* parent;
	ball state;
	int treeDepth;
	int hVal;
	int fVal;
};

void initGearball(ball &gb) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				gb.faces[i].pieces[j][k] = colors[i]; //load colors into non-gear pieces
			}
		}
	}
	//load default orientation/colors into gears (NOTE: gears are initialized in solved state)
	for (int i = 0; i < 12; i++) {
		if (i == 0) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[1];
			gb.gears[i].clr2 = colors[5];
		}
		if (i == 1) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[1];
			gb.gears[i].clr2 = colors[4];
		}
		if (i == 2) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[1];
			gb.gears[i].clr2 = colors[0];
		}
		if (i == 3) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[1];
			gb.gears[i].clr2 = colors[3];
		}
		if (i == 4) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[5];
			gb.gears[i].clr2 = colors[3];
		}
		if (i == 5) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[5];
			gb.gears[i].clr2 = colors[4];
		}
		if (i == 6) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[0];
			gb.gears[i].clr2 = colors[4];
		}
		if (i == 7) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[0];
			gb.gears[i].clr2 = colors[3];
		}
		if (i == 8) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[2];
			gb.gears[i].clr2 = colors[5];
		}
		if (i == 9) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[2];
			gb.gears[i].clr2 = colors[4];
		}
		if (i == 10) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[2];
			gb.gears[i].clr2 = colors[0];
		}
		if (i == 11) {
			gb.gears[i].orientation = 0;
			gb.gears[i].clr1 = colors[2];
			gb.gears[i].clr2 = colors[3];
		}
	}
}

//PRINT FUNCTIONS:
void printGear(ball &gb, int gearPos, int currentFace) {
	//check orientation is not negative
	while (gb.gears[gearPos].orientation < 0) {
		gb.gears[gearPos].orientation += 6;
	}

	if (gb.gears[gearPos].orientation % 6 == 0) {
		if (gb.gears[gearPos].clr1 != gb.faces[currentFace].pieces[1][1])
			cout << gb.gears[gearPos].clr2 << "_" << gb.gears[gearPos].clr1;
		else
			cout << gb.gears[gearPos].clr1 << "_" << gb.gears[gearPos].clr2;
	}
	else if (gb.gears[gearPos].orientation % 6 == 1) {
		cout << gb.gears[gearPos].clr1 << "/" << gb.gears[gearPos].clr2;
	}
	else if (gb.gears[gearPos].orientation % 6 == 2) {
		cout << gb.gears[gearPos].clr1 << "\\" << gb.gears[gearPos].clr2;
	}
	else if (gb.gears[gearPos].orientation % 6 == 3) {
		cout << gb.gears[gearPos].clr1 << "-" << gb.gears[gearPos].clr2;
	}
	else if (gb.gears[gearPos].orientation % 6 == 4) {
		cout << gb.gears[gearPos].clr1 << "//" << gb.gears[gearPos].clr2;
	}
	else if (gb.gears[gearPos].orientation % 6 == 5) {
		cout << gb.gears[gearPos].clr1 << "\\\\" << gb.gears[gearPos].clr2;
	}
}

void printInsidePiecesLine(ball &gb, int currFace, int currPieceRow) {
	for (int i = 0; i < 3; i++) {
		cout << gb.faces[currFace].pieces[currPieceRow][i];
	}
	if (currPieceRow == 0 || currPieceRow == 2) {
		cout << endl;
	}
	if (currPieceRow == 1) {
		cout << " ";
	}
}

void printSide(ball &gb, int currFace) {
	if (currFace == 0) {
		cout << "    ";
		printGear(gb, 2, currFace);
		cout << "    " << endl << "    ";
		printInsidePiecesLine(gb, currFace, 0);
		printGear(gb, 7, currFace);
		cout << " ";
		printInsidePiecesLine(gb, currFace, 1);
		printGear(gb, 6, currFace);
		cout << endl << "    ";
		printInsidePiecesLine(gb, currFace, 2);
		cout << "    ";
		printGear(gb, 10, currFace);
		cout << endl;
	}
	if (currFace == 1) {
		cout << "    ";
		printGear(gb, 0, currFace);
		cout << "    " << endl << "    ";
		printInsidePiecesLine(gb, currFace, 0);
		printGear(gb, 3, currFace);
		cout << " ";
		printInsidePiecesLine(gb, currFace, 1);
		printGear(gb, 1, currFace);
		cout << endl << "    ";
		printInsidePiecesLine(gb, currFace, 2);
		cout << "    ";
		printGear(gb, 2, currFace);
		cout << endl;
	}
	if (currFace == 2) {
		cout << "    ";
		printGear(gb, 10, currFace);
		cout << "    " << endl << "    ";
		printInsidePiecesLine(gb, currFace, 0);
		printGear(gb, 11, currFace);
		cout << " ";
		printInsidePiecesLine(gb, currFace, 1);
		printGear(gb, 9, currFace);
		cout << endl << "    ";
		printInsidePiecesLine(gb, currFace, 2);
		cout << "    ";
		printGear(gb, 8, currFace);
		cout << endl;
	}
	if (currFace == 3) {
		cout << "    ";
		printGear(gb, 3, currFace);
		cout << "    " << endl << "    ";
		printInsidePiecesLine(gb, currFace, 0);
		printGear(gb, 4, currFace);
		cout << " ";
		printInsidePiecesLine(gb, currFace, 1);
		printGear(gb, 7, currFace);
		cout << endl << "    ";
		printInsidePiecesLine(gb, currFace, 2);
		cout << "    ";
		printGear(gb, 11, currFace);
		cout << endl;
	}
	if (currFace == 4) {
		cout << "    ";
		printGear(gb, 1, currFace);
		cout << "    " << endl << "    ";
		printInsidePiecesLine(gb, currFace, 0);
		printGear(gb, 6, currFace);
		cout << " ";
		printInsidePiecesLine(gb, currFace, 1);
		printGear(gb, 5, currFace);
		cout << endl << "    ";
		printInsidePiecesLine(gb, currFace, 2);
		cout << "    ";
		printGear(gb, 9, currFace);
		cout << endl;
	}
	if (currFace == 5) {
		cout << "    ";
		printGear(gb, 0, currFace);
		cout << "    " << endl << "    ";
		printInsidePiecesLine(gb, currFace, 0);
		printGear(gb, 4, currFace);
		cout << " ";
		printInsidePiecesLine(gb, currFace, 1);
		printGear(gb, 5, currFace);
		cout << endl << "    ";
		printInsidePiecesLine(gb, currFace, 2);
		cout << "    ";
		printGear(gb, 8, currFace);
		cout << endl;
	}
}

void printBall(ball &gb) {
	cout << "---------------" << endl;
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			cout << endl << "Front:\n" << endl;
		}//red (front)
		if (i == 1) {
			cout << endl << "Top:\n" << endl;
		}//green(top)
		if (i == 2) {
			cout << endl << "Bottom:\n" << endl;
		}//blue(bottom)
		if (i == 3) {
			cout << endl << "Side 1:\n" << endl;
		}//yellow (side 1)
		if (i == 4) {
			cout << endl << "Side 2:\n" << endl;
		}//orange (side 2)
		if (i == 5) {
			cout << endl << "Back:\n" << endl;
		}//pink (back)
		printSide(gb, i);
	}
	cout << "---------------" << endl;
}

//ROTATE FUNCTIONS:
void rotateRightClkWseHoldingCenter(ball &gb) { //rotate right face clockwise holding center
	cout << "Rotating right face clock wise holding the center." << endl;
	//move right column of front up, left down
	char temp[4][3];
	for (int i = 0; i < 3; i++) {
		temp[0][i] = gb.faces[0].pieces[i][2];
	}
	for (int i = 0; i < 3; i++) {
		temp[1][i] = gb.faces[1].pieces[i][2];
	}
	for (int i = 0; i < 3; i++) {
		temp[2][i] = gb.faces[5].pieces[i][2];
	}
	for (int i = 0; i < 3; i++) {
		temp[3][i] = gb.faces[2].pieces[i][2];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[1].pieces[i][2] = temp[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[i][2] = temp[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[2].pieces[i][2] = temp[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[i][2] = temp[3][i];
	}
	//move gears
	gear tempGear[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear[i] = gb.gears[6];
		if (i == 1)
			tempGear[i] = gb.gears[1];
		if (i == 2)
			tempGear[i] = gb.gears[5];
		if (i == 3)
			tempGear[i] = gb.gears[9];
	}
	gb.gears[1] = tempGear[0];
	gb.gears[5] = tempGear[1];
	gb.gears[9] = tempGear[2];
	gb.gears[6] = tempGear[3];
	//left down
	char temp2[4][3];
	for (int i = 0; i < 3; i++) {
		temp2[0][i] = gb.faces[0].pieces[i][0];
	}
	for (int i = 0; i < 3; i++) {
		temp2[1][i] = gb.faces[2].pieces[i][0];
	}
	for (int i = 0; i < 3; i++) {
		temp2[2][i] = gb.faces[5].pieces[i][0];
	}
	for (int i = 0; i < 3; i++) {
		temp2[3][i] = gb.faces[1].pieces[i][0];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[2].pieces[i][0] = temp2[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[i][0] = temp2[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[1].pieces[i][0] = temp2[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[i][0] = temp2[3][i];
	}
	//move gears
	gear tempGear2[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear2[i] = gb.gears[7];
		if (i == 1)
			tempGear2[i] = gb.gears[11];
		if (i == 2)
			tempGear2[i] = gb.gears[4];
		if (i == 3)
			tempGear2[i] = gb.gears[3];
	}
	gb.gears[11] = tempGear2[0];
	gb.gears[4] = tempGear2[1];
	gb.gears[3] = tempGear2[2];
	gb.gears[7] = tempGear2[3];
	gb.gears[0].orientation--;
	gb.gears[8].orientation--;
	gb.gears[10].orientation--;
	gb.gears[2].orientation--;
}

void rotateRightCtrClkWseHoldingCenter(ball &gb) { //rotate right face counter clockwise holding center
	//rotate right(side 2)
	//move right column of front down, left up
	char temp[4][3];
	for (int i = 0; i < 3; i++) {
		temp[0][i] = gb.faces[0].pieces[i][2];
	}
	for (int i = 0; i < 3; i++) {
		temp[1][i] = gb.faces[2].pieces[i][2];
	}
	for (int i = 0; i < 3; i++) {
		temp[2][i] = gb.faces[5].pieces[i][2];
	}
	for (int i = 0; i < 3; i++) {
		temp[3][i] = gb.faces[1].pieces[i][2];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[2].pieces[i][2] = temp[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[i][2] = temp[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[1].pieces[i][2] = temp[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[i][2] = temp[3][i];
	}
	//move gears
	gear tempGear[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear[i] = gb.gears[6];
		if (i == 1)
			tempGear[i] = gb.gears[9];
		if (i == 2)
			tempGear[i] = gb.gears[5];
		if (i == 3)
			tempGear[i] = gb.gears[1];
	}
	gb.gears[9] = tempGear[0];
	gb.gears[5] = tempGear[1];
	gb.gears[1] = tempGear[2];
	gb.gears[6] = tempGear[3];
	//move left side up
	char temp2[4][3];
	for (int i = 0; i < 3; i++) {
		temp2[0][i] = gb.faces[0].pieces[i][0];
	}
	for (int i = 0; i < 3; i++) {
		temp2[1][i] = gb.faces[2].pieces[i][0];
	}
	for (int i = 0; i < 3; i++) {
		temp2[2][i] = gb.faces[5].pieces[i][0];
	}
	for (int i = 0; i < 3; i++) {
		temp2[3][i] = gb.faces[1].pieces[i][0];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[1].pieces[i][0] = temp2[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[i][0] = temp2[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[2].pieces[i][0] = temp2[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[i][0] = temp2[3][i];
	}
	//update gears
	gear tempGear2[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear2[i] = gb.gears[7];
		if (i == 1)
			tempGear2[i] = gb.gears[3];
		if (i == 2)
			tempGear2[i] = gb.gears[4];
		if (i == 3)
			tempGear2[i] = gb.gears[11];
	}
	gb.gears[3] = tempGear2[0];
	gb.gears[4] = tempGear2[1];
	gb.gears[11] = tempGear2[2];
	gb.gears[7] = tempGear2[3];
	gb.gears[0].orientation++;
	gb.gears[2].orientation++;
	gb.gears[10].orientation++;
	gb.gears[8].orientation++;
}

void rotateTopClkWseHoldingCenter(ball &gb) {
	cout << "Rotating top face clock wise holding the center" << endl;
	//top to the left bottom to the right
	char temp[4][3];
	for (int i = 0; i < 3; i++) {
		temp[0][i] = gb.faces[0].pieces[0][i];
	}
	for (int i = 0; i < 3; i++) {
		temp[1][i] = gb.faces[3].pieces[0][i];
	}
	for (int i = 0; i < 3; i++) {
		temp[2][i] = gb.faces[5].pieces[0][i];
	}
	for (int i = 0; i < 3; i++) {
		temp[3][i] = gb.faces[4].pieces[0][i];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[3].pieces[0][i] = temp[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[0][i] = temp[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[4].pieces[0][i] = temp[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[0][i] = temp[3][i];
	}
	//update gears
	gear tempGear[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear[i] = gb.gears[2];
		if (i == 1)
			tempGear[i] = gb.gears[3];
		if (i == 2)
			tempGear[i] = gb.gears[0];
		if (i == 3)
			tempGear[i] = gb.gears[1];
	}
	gb.gears[3] = tempGear[0];
	gb.gears[0] = tempGear[1];
	gb.gears[1] = tempGear[2];
	gb.gears[2] = tempGear[3];
	//bottom to right
	char temp2[4][3];
	for (int i = 0; i < 3; i++) {
		temp2[0][i] = gb.faces[0].pieces[2][i];
	}
	for (int i = 0; i < 3; i++) {
		temp2[1][i] = gb.faces[4].pieces[2][i];
	}
	for (int i = 0; i < 3; i++) {
		temp2[2][i] = gb.faces[5].pieces[2][i];
	}
	for (int i = 0; i < 3; i++) {
		temp2[3][i] = gb.faces[3].pieces[2][i];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[4].pieces[2][i] = temp2[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[2][i] = temp2[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[3].pieces[2][i] = temp2[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[2][i] = temp2[3][i];
	}
	//update gears
	gear tempGear2[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear2[i] = gb.gears[10];
		if (i == 1)
			tempGear2[i] = gb.gears[9];
		if (i == 2)
			tempGear2[i] = gb.gears[8];
		if (i == 3)
			tempGear2[i] = gb.gears[11];
	}
	gb.gears[9] = tempGear2[0];
	gb.gears[8] = tempGear2[1];
	gb.gears[11] = tempGear2[2];
	gb.gears[10] = tempGear2[3];
	gb.gears[7].orientation -= 2;
	gb.gears[6].orientation -= 2;
	gb.gears[5].orientation -= 2;
	gb.gears[4].orientation -= 2;
}

void rotateTopCtrClkWseHoldingCenter(ball &gb) {
	//top to the right, bottom to the left
	char temp[4][3];
	for (int i = 0; i < 3; i++) {
		temp[0][i] = gb.faces[0].pieces[0][i];
	}
	for (int i = 0; i < 3; i++) {
		temp[1][i] = gb.faces[4].pieces[0][i];
	}
	for (int i = 0; i < 3; i++) {
		temp[2][i] = gb.faces[5].pieces[0][i];
	}
	for (int i = 0; i < 3; i++) {
		temp[3][i] = gb.faces[3].pieces[0][i];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[4].pieces[0][i] = temp[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[0][i] = temp[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[3].pieces[0][i] = temp[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[0][i] = temp[3][i];
	}
	//update gears
	gear tempGear[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear[i] = gb.gears[2];
		if (i == 1)
			tempGear[i] = gb.gears[1];
		if (i == 2)
			tempGear[i] = gb.gears[0];
		if (i == 3)
			tempGear[i] = gb.gears[3];
	}
	gb.gears[1] = tempGear[0];
	gb.gears[0] = tempGear[1];
	gb.gears[3] = tempGear[2];
	gb.gears[2] = tempGear[3];
	char temp2[4][3];
	for (int i = 0; i < 3; i++) {
		temp2[0][i] = gb.faces[0].pieces[2][i];
	}
	for (int i = 0; i < 3; i++) {
		temp2[1][i] = gb.faces[3].pieces[2][i];
	}
	for (int i = 0; i < 3; i++) {
		temp2[2][i] = gb.faces[5].pieces[2][i];
	}
	for (int i = 0; i < 3; i++) {
		temp2[3][i] = gb.faces[4].pieces[2][i];
	}
	//update state
	for (int i = 0; i < 3; i++) {
		gb.faces[3].pieces[2][i] = temp2[0][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[5].pieces[2][i] = temp2[1][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[4].pieces[2][i] = temp2[2][i];
	}
	for (int i = 0; i < 3; i++) {
		gb.faces[0].pieces[2][i] = temp2[3][i];
	}
	//update gears
	gear tempGear2[4];
	for (int i = 0; i < 4; i++) {
		if (i == 0)
			tempGear2[i] = gb.gears[10];
		if (i == 1)
			tempGear2[i] = gb.gears[11];
		if (i == 2)
			tempGear2[i] = gb.gears[8];
		if (i == 3)
			tempGear2[i] = gb.gears[9];
	}
	gb.gears[11] = tempGear2[0];
	gb.gears[8] = tempGear2[1];
	gb.gears[9] = tempGear2[2];
	gb.gears[10] = tempGear2[3];
	gb.gears[7].orientation += 2;
	gb.gears[6].orientation += 2;
	gb.gears[5].orientation += 2;
	gb.gears[4].orientation += 2;
}

void randomizeBall(ball &gb, int numMoves) {
	for (int i = 0; i < numMoves; i++) {
		int tempRotation = 0;
		//choose random rotation
		random_device randNum1;
		mt19937 gen(randNum1());
		uniform_int_distribution<> rotation(1, 2); //distribute generated nums between 1-2
		tempRotation = rotation(gen);
		switch (tempRotation) {
		case 1:
			rotateRightClkWseHoldingCenter(gb); //rotating right clockwise = rotating left counter clockwise
			printBall(gb);
			break;
		case 2:
			rotateTopClkWseHoldingCenter(gb);
			printBall(gb);
			break;
		}
	}
}

bool isSolved(ball gb) {
	bool facesSolved = true, gearsSolved = true;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (gb.faces[i].pieces[j][k] != colors[i]) {
					facesSolved = false;
					break;
				}
			}
		}
	}//check faces
	for (int l = 0; l < 12; l++) {
		if (gb.gears[l].orientation != 0) {
			gearsSolved = false;
			break;
		}
	}//check gears

	return facesSolved && gearsSolved;
}

void nodeInit(node &nd, node* ptr, ball state, int heur) {
	nd.parent = ptr;
	nd.state = state;
	if (ptr != NULL)
		nd.treeDepth = ptr->treeDepth + 1;
	else
		nd.treeDepth = 0;
	nd.hVal = heur;
	nd.fVal = nd.treeDepth + heur;
}

int heuristic(ball gb) {
	if (isSolved(gb)) {
		return 0;
	}
	else {
		return 1;
	}
}

node aStar(node root, vector<node> &closed) {
	vector<node> open; //list of nodes visited but not all children visited
	open.reserve(100000); //reserve 1000000 vector slots to prevent memory deallocation on push_back
	open.push_back(root);

	while (!open.empty()) {
		int current = open[0].fVal;
		int location = 0;
		for (int i = 0; i < open.size(); i++) {
			if (open[i].fVal < current) {
				current = open[i].fVal;
				location = i;
			}
		}
		if (isSolved(open[location].state)) {
			cout << "SOLVED!" << endl;
			return open[location];
		}
		else {
			node child1;
			node child2;
			ball temp = open[location].state; //grab state before changing
			closed.push_back(open[location]);

			//make children nodes by performing rotations
			rotateRightCtrClkWseHoldingCenter(temp);
			nodeInit(child1, &closed[closed.size()-1], temp, heuristic(temp));
			open.push_back(child1);

			temp = open[location].state; //reset ball to previous state before changing for child 2

			rotateTopCtrClkWseHoldingCenter(temp);
			nodeInit(child2, &closed[closed.size()-1], temp, heuristic(temp));
			open.push_back(child2);

			//move parent node to closed
			open.erase(open.begin() + location);
		}
	}
}

int main() {
	initGearball(gearball);
	printBall(gearball);

	/* Non-Working randomizer function: if you would like to test(and get caught in infinite loop), uncomment
		int userNumMoves = 0;
		cout << "Input how many number of moves should be made on the gearball (3-20): ";
		cin >> userNumMoves;
		randomizeBall(gearball, userNumMoves);
	*/
	
	
	for (int i = 0; i < 5; i++) {
		vector<node> closed; //list of nodes visited and all children visited
		closed.reserve(100000);
		node root, solved;
		nodeInit(root, NULL, gearball, heuristic(gearball));
		nodeInit(solved, NULL, gearball, heuristic(gearball));
		initGearball(gearball);

		//HERE:: MAKE NUMBER OF DESERIRED CLOCKWISE ROTATION FUNCTION CALLS
		rotateRightClkWseHoldingCenter(gearball);
		rotateTopClkWseHoldingCenter(gearball);
		rotateTopClkWseHoldingCenter(gearball);
		rotateRightClkWseHoldingCenter(gearball);
		rotateTopClkWseHoldingCenter(gearball);
		rotateRightCtrClkWseHoldingCenter(gearball);

		solved = aStar(root, closed);

		cout << "K = 6: " << endl;
		cout << "Number of nodes visited: " << closed.size() << endl;
	}


	return 0;
}