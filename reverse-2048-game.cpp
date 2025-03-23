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

			for(int i = 0; i < gameSize; i++){
				for(int j = 0; j < gameSize; j++){
					if (initialPositionOne.x == i && initialPositionOne.y == j || initialPositionTwo.x == i && initialPositionTwo.y == j){
						cout << divider << setw(4) << startSize;
					}else{
						cout << divider << setw(4) << emptySpace;
					};
				};
				cout << endl;
			};
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
};

int main(){
	Game2048 object(3, 2048);
	object.setUpGame();
	return 0;
}
