#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

struct xy{
	int x;
	int y;
};

struct scoreObject{
	int newScore;
	int previousScore;
};

struct gameProperties{
	int startingTitle;
	int gameSize;
};

class Game2048{
	int gameSize, startSize, algOneMove;// emptySlot;
	//bool hasTwo = false;
	vector<vector<int>> grid;
	vector<vector<int>> borderNeighbourWhoWasMerged;
	
	string emptySpace = "----", divider = " | ";
	public:
		bool hasTwo = false, noPossibleMoves = false;
		int emptySlot;
		Game2048(int a, int b):gameSize(a),startSize(b){
			grid.resize(gameSize, vector<int>(gameSize, 0));
			emptySlot = (gameSize*gameSize) -2;
		};

		void setUpGame(){
			xy initialPositionTwo = getRandomPosition();
			xy initialPositionOne = getRandomPosition();
			
			while (initialPositionOne.x == initialPositionTwo.x && initialPositionOne.y == initialPositionTwo.y) {
				initialPositionTwo = getRandomPosition();
			}
			
			grid[initialPositionOne.x][initialPositionOne.y] = startSize;
			grid[initialPositionTwo.x][initialPositionTwo.y] = startSize;

			cout << "===================================================================" << endl;
			cout<< "first x & y: " << initialPositionOne.x << " " << initialPositionOne.y << " | " << "second x & y: " << initialPositionTwo.x << initialPositionTwo.y <<" | size: "<< gameSize <<" | Initial Board" <<endl;
			cout << "-------------------------------------------------------------------" << endl;

			printCurrentGrid();
		};
		
		xy getRandomPosition(){
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(0, gameSize-1);
			
			xy value = {};
			value.x = dis(gen);
			value.y = dis(gen);
			
			return value;
		};

		void printCurrentGrid(){
			//cout << "printing curent grid function"<<endl;
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid.size(); j++){
					if(grid[i][j] == 0){
						cout << setw(4) << " " << emptySpace;
					}else{
						cout << setw(4) << " " << grid[i][j];
					}
				};
				cout << setw(4) << divider << endl;
			}
		};
		
		void moveLeft(){
			for(int i = 0; i < grid.size(); i++){
				for(int j = grid.size() -1; j > 0;j--){
					if(grid[i][j-1] != 0){
						if(grid[i][j-1] == grid[i][j]){
							vector<int> cord = {i, j-1};
							if(checkIfElementWasChanged(cord, 'l')){
							}else{
								grid[i][j-1] = grid[i][j]/2;
								borderNeighbourWhoWasMerged.push_back(cord);
								grid[i][j] = 0;
							}
						}
					}else{
						grid[i][j-1] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			}
			borderNeighbourWhoWasMerged = {};
			for(int i = 0; i < grid.size(); i++){
				for(int j = grid.size() - 1 ; j > 0;j--){
					if(grid[i][j-1] == 0){
						grid[i][j-1] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			}
		};
		
		void moveRight(){
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid.size() - 1;j++){
					if(grid[i][j+1] != 0){
						if(grid[i][j+1] == grid[i][j]){
							vector<int> cord = {i, j+1};
							if(checkIfElementWasChanged(cord, 'r')){
							}else{
								grid[i][j+1] = grid[i][j]/2;
								borderNeighbourWhoWasMerged.push_back(cord);
								grid[i][j] = 0;
							}
						}
					}else{
						grid[i][j+1] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			}
			borderNeighbourWhoWasMerged = {};
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid.size() - 1;j++){
					if(grid[i][j+1] == 0){
						grid[i][j+1] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			};
		};

		void moveUp(){
			for(int i = gameSize - 1; i > 0; i--){
				for(int j = 0; j < grid.size(); j++){
					//check the top is not empty
					if(grid[i-1][j] != 0){
						//check if bottom value has same value as current, then divid the value place
						if(grid[i-1][j] == grid[i][j]){
							vector<int> cord = {i-1, j};
							if(checkIfElementWasChanged(cord, 'u')){
							}else{
								grid[i-1][j] = grid[i][j]/2;
								borderNeighbourWhoWasMerged.push_back(cord);
								grid[i][j] = 0;
							}
						};
					}else{
						grid[i-1][j] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			};
			borderNeighbourWhoWasMerged = {};
			//removing any additional empty spaces if ever
			for(int i = gameSize - 1; i > 0; i--){
				for(int j = 0; j < grid.size(); j++){
					if(grid[i-1][j] == 0){
						grid[i-1][j] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			}
		};

		void moveDown(){
			for(int i = 0; i< grid.size() - 1; i++){
				for(int j = 0; j < grid.size(); j++){
					//check the bottom is not empty
					if(grid[i+1][j] != 0){
						//check if bottom value has same value as current, then divid the value place
						if(grid[i+1][j] == grid[i][j]){
							vector<int> cord = {i+1, j};
							if(checkIfElementWasChanged(cord, 'd')){
							}else{
								grid[i+1][j] = grid[i][j]/2;
								borderNeighbourWhoWasMerged.push_back(cord);
								grid[i][j] = 0;
							}
						};
					}else{
						grid[i+1][j] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			};
			borderNeighbourWhoWasMerged = {};
			//removing any additional empty spaces if ever
			for(int i = 0; i < grid.size() - 1; i++){
				for(int j = 0; j < grid.size(); j++){
					if(grid[i+1][j] == 0){
						grid[i+1][j] = grid[i][j];
						grid[i][j] = 0;
					}
				}
			}
		};
		
		scoreObject evaluateMove(char direction){
			//im going to modify the grid so i can find move with the lost score
			vector<vector<int>> originalGrid = grid;
			int newScore = 0, previousScore = 0;
			
			if(direction == 'u'){
				moveUp();
			}else if(direction == 'd'){
				moveDown();
			}else if(direction == 'l'){
				moveLeft();
			}else{
				moveRight();
			};

			for(auto& row:originalGrid){
				for(int value: row){
					previousScore += value;
				};
			};
			
			for(auto& row:grid){
				for(int value: row){
					newScore += value;
				};
			};

			grid = originalGrid; // bring grid back to original shape
			
			scoreObject ob = {newScore, previousScore };
			return ob;
		}

		void AlgOneGreedyAlgorithm(){
			vector<char> directions = {'u', 'd', 'l', 'r'};
			char bestMove = 'u';
			int lowestScore = 9999;

			for (char direction : directions) {
				scoreObject currentMoveScore = evaluateMove(direction);
				if (currentMoveScore.newScore < lowestScore) {
					lowestScore = currentMoveScore.newScore;
					bestMove = direction;
				}
			}

			if(bestMove == 'u'){
				moveUp();
			}else if(bestMove == 'd'){
				moveDown();
			}else if(bestMove == 'l'){
				moveLeft();
			}else{
				moveRight();
			};
			algOneMove ++;
			cout<< "Move "<< algOneMove << ": Alg_1: "<< bestMove << endl;
		}
		
		void checkIfSolved(){
			emptySlot = 0;
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid.size(); j++){
					if(grid[i][j] == 2){
						hasTwo = true;
					}else if(grid[i][j] == 0){
						emptySlot ++;
					}
				}
			};
			//cout << "| empty slots: " << emptySlot << endl;
			
			//checks if all possible moves have been done
			vector<char> directions = {'u', 'd', 'l', 'r'};
			scoreObject leftScore, rightScore, upScore, downScore;
			
			for(auto& direction: directions){
				if(direction == 'u'){
					upScore = evaluateMove(direction);
				}else if(direction == 'd'){
					downScore = evaluateMove(direction);
				}else if(direction == 'l'){
					leftScore = evaluateMove(direction);
				}else{
					rightScore = evaluateMove(direction);
				};
			};

			if(algOneMove > 1000){
				cout<<"Maximum moves reached"<<endl;
				emptySlot = 0;
				noPossibleMoves = true;
			};

			if(emptySlot == 0 && upScore.previousScore == upScore.newScore && downScore.previousScore == downScore.newScore && leftScore.previousScore == leftScore.newScore && rightScore.previousScore == rightScore.newScore){
				noPossibleMoves = true;
			}
		}
		
		bool checkIfElementWasChanged(vector<int> sendValue, char c){
			//if previous top element on x axis was modified, dont change current value
			for(vector<int> b:borderNeighbourWhoWasMerged){
				int x = b[0], y = b[1];
				if(c == 'd' && x + 1 == sendValue[0] && y == sendValue[1]){
					return true;
				}else if(c == 'u' && x - 1 == sendValue[0] && y == sendValue[1]){
					return true;
				}else if(c == 'r' && x == sendValue[0] && y + 1 == sendValue[1]){
					return true;
				}else if(c == 'l' && x == sendValue[0] && y - 1 == sendValue[1]){
					return true;
				}
			}
			//cout<<"error invalid input for direction, value: "<< c <<endl;
			return false;
		};

		void addElementToGrid(){
			xy newPosition = getRandomPosition();
			//cout how many empty spaces there are, check if the game is over or now
			
			//get new position if below is not 0 
			while(grid[newPosition.x][newPosition.y] != 0){
				newPosition = getRandomPosition();
			};
			grid[newPosition.x][newPosition.y] = startSize;
		};
};

vector<gameProperties> openFile(string fileName){
	vector<gameProperties> gp = {};
	
	fstream file(fileName);
	if (!file.is_open()) {
		cerr << "Error opening file!" << endl;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		int openingTitle, gameSize;
		char comma;
		ss >> openingTitle >> comma >> gameSize;
		gameProperties temp = {openingTitle, gameSize};
		gp.push_back(temp);
	}
	
	file.close();
	return gp;
};

int main(){
	
	string fileName = "reverse_2048.txt";
	int games = 1;
	vector<gameProperties> values = openFile(fileName);
	
	for(auto& v:values){
		cout << "Game: " << games<< endl;
		Game2048 object(v.gameSize,v.startingTitle);
		object.setUpGame();

		//run the algorithm, check if solved, checck if there spaces
		while (object.emptySlot != 0 && object.noPossibleMoves != true){
			cout << "-------------------------------------------------------------------" << endl;
			object.AlgOneGreedyAlgorithm();
			object.checkIfSolved();
			if(object.hasTwo == true){
				cout << "you won!" << endl;
				break;
			}
			if(object.emptySlot == 0 && object.noPossibleMoves == true){
				object.printCurrentGrid();
				cout << "not empty spaces and possible moves left\nGAME OVER" << endl;
				break;
			}
			
			;
			/*if(userInput == 'u'){
				object.moveUp();
			}else if(userInput == 'd'){
				object.moveDown();
			}else if(userInput == 'r'){
				object.moveRight();
			}else if(userInput == 'l'){
				object.moveLeft();
			}*/
			object.addElementToGrid();
			object.printCurrentGrid();
		}
		games++;
	}
	return 0;
}
