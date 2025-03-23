#include <iostream>
#include <vector>
#include <iomanip>
#include <random>

using namespace std;

struct xy{
	int x;
	int y;
};

class Game2048{
	int gameSize, startSize;
	vector<vector<int>> grid;
	vector<vector<int>> borderNeighbourWhoWasMerged;
	
	string emptySpace = "----", divider = " | ";
	public:
		Game2048(int a, int b):gameSize(a),startSize(b){
			grid.resize(gameSize, vector<int>(gameSize, 0));
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
			cout << "printing curent grid function"<<endl;
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid.size(); j++){
					if(grid[i][j] == 0){
						cout << divider << setw(4) << emptySpace;
					}else{
						cout << divider << setw(4) << grid[i][j];
					}
				};
				cout << endl;
			}
		};

		void moveUp(){
			for(int i = grid.size() - 1; i > 0; i--){
				for(int j = 0; j < grid.size(); j++){
					//check the bottom is not empty
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
		};
		
		bool checkIfElementWasChanged(vector<int> sendValue, char c){
			//if previous top element on x axis was modified, dont change current value
			for(vector<int> b:borderNeighbourWhoWasMerged){
				int x = b[0];
				if(c == 'd' && x + 1 == sendValue[0] && b[1] == sendValue[1]){
					return true;
				}else if(c == 'u' && x - 1 == sendValue[0] && b[1] == sendValue[1]){
					return true;
				}
			}
			return false;
		}

		void addElementToGrid(){
			xy newPosition = getRandomPosition();
			//cout how many empty spaces there are, check if the game is over or now
			//
			//
			//
			//get new position if below is not 0 
			while(grid[newPosition.x][newPosition.y] != 0){
				newPosition = getRandomPosition();
			};
			grid[newPosition.x][newPosition.y] = startSize;
		};
};

int main(){
	Game2048 object(3, 2048);
	int userInput = 1;
	object.setUpGame();

	while (userInput != 3){
		cout << "enter value: ";
		cin >> userInput;
		if(userInput == 1){
			object.moveUp();
		}else if(userInput == 2){
			object.moveDown();
		}
		object.addElementToGrid();
		object.printCurrentGrid();
	}
	return 0;
}
