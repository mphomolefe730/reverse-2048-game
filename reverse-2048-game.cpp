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
			//cout << "printing curent grid function"<<endl;
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid.size(); j++){
					if(grid[i][j] == 0){
						cout << setw(4) << " " << emptySpace;
					}else{
						cout << setw(4) << " " << grid[i][j];
					}
				};
				cout << divider << endl;
			}
		};
		
		void moveLeft(){
			cout<< "moving puzzle right"<<endl;
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
			cout<< "moving puzzle right"<<endl;
			for(int i = 0; i < grid.size(); i++){
				for(int j = 0; j < grid.size() - 1;j++){
					if(grid[i][j+1] != 0){
						if(grid[i][j+1] == grid[i][j]){
							cout<< "exchange: " << i << j << " with " << i << j+1 << endl;
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
			cout<< "moving puzzle up"<<endl;
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
			cout<< "moving puzzle down"<<endl;
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
			cout<<"error invalid input for direction"<<endl;
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
	Game2048 object(5, 2048);
	char userInput = 1;
	object.setUpGame();

	while (userInput != 'c'){
		cout << "enter value: ";
		cin >> userInput;
		if(userInput == 'u'){
			object.moveUp();
		}else if(userInput == 'd'){
			object.moveDown();
		}else if(userInput == 'r'){
			object.moveRight();
		}else if(userInput == 'l'){
			object.moveLeft();
		}
		object.addElementToGrid();
		object.printCurrentGrid();
	}
	return 0;
}
