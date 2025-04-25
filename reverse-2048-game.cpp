#include <iostream>
#include <vector>
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

struct MoveAssessment {
	char direction;
	int immediate_score;
	int future_potential;
	int risk_factor;
};

struct gameProperties{
	int startingTitle;
	int gameSize;
};

class Game2048{
	int gameSize, startSize, algOneMove, algTwoMove;
	vector<vector<int>> gridAlgOne, gridAlgTwo;
	vector<vector<int>> borderNeighbourWhoWasMerged;
	
	string emptySpace = "--", divider = " | ";
	public:
		bool hasTwoAlgOne = false, hasTwoAlgTwo = false, noPossibleMovesAlgOne = false, noPossibleMovesAlgTwo = false;
		int emptySlotAlgOne, emptySlotAlgTwo;
		Game2048(int a, int b):gameSize(a),startSize(b){
			gridAlgOne.resize(gameSize, vector<int>(gameSize, 0));
			gridAlgTwo.resize(gameSize, vector<int>(gameSize, 0));
			emptySlotAlgOne = (gameSize*gameSize) -2;
			emptySlotAlgOne = (gameSize*gameSize) -2;
			algOneMove = 0;
			algTwoMove = 0;
		};

		void setUpGame(){
			xy initialPositionTwo = getRandomPosition();
			xy initialPositionOne = getRandomPosition();
			
			while (initialPositionOne.x == initialPositionTwo.x && initialPositionOne.y == initialPositionTwo.y) {
				initialPositionTwo = getRandomPosition();
			}
			
			gridAlgOne[initialPositionOne.x][initialPositionOne.y] = startSize;
			gridAlgOne[initialPositionTwo.x][initialPositionTwo.y] = startSize;

			
			gridAlgTwo[initialPositionOne.x][initialPositionOne.y] = startSize;
			gridAlgTwo[initialPositionTwo.x][initialPositionTwo.y] = startSize;

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
			for(int i = 0; i < gridAlgOne.size(); i++){
				cout << divider <<setw(2);
				for(int j = 0; j < gridAlgOne.size(); j++){
					if(gridAlgOne[i][j] == 0){
						cout << setw(6) << emptySpace;
					}else{
						cout << setw(6) << gridAlgOne[i][j];
					}
				};
				cout << setw(2) << divider;

				for(int j = 0; j < gridAlgTwo.size(); j++){
					if(gridAlgTwo[i][j] == 0){
						cout << setw(6) << emptySpace;
					}else{
						cout << setw(6) << gridAlgTwo[i][j];
					}
				};

				cout << endl;	
			}
		};
		
		void moveLeft(vector<vector<int>>& grid){
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
		
		void moveRight(vector<vector<int>>& grid){
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

		void moveUp(vector<vector<int>>& grid){
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

		void moveDown(vector<vector<int>>& grid){
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
		
		scoreObject evaluateMove(char direction, vector<vector<int>>& grid){
			//im going to modify the grid so i can find move with the lost score
			vector<vector<int>> originalGrid = grid;
			int newScore = 0, previousScore = 0;
			
			if(direction == 'u'){
				moveUp(grid);
			}else if(direction == 'd'){
				moveDown(grid);
			}else if(direction == 'l'){
				moveLeft(grid);
			}else{
				moveRight(grid);
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
			if(noPossibleMovesAlgOne == true){
				return;
			};

			vector<char> directions = {'u', 'd', 'l', 'r'};
			char bestMove = 'u';
			int lowestScore = 9999;

			for (char direction : directions) {
				scoreObject currentMoveScore = evaluateMove(direction, gridAlgOne);
				if (currentMoveScore.newScore < lowestScore) {
					lowestScore = currentMoveScore.newScore;
					bestMove = direction;
				}
			}

			if(bestMove == 'u'){
				moveUp(gridAlgOne);
			}else if(bestMove == 'd'){
				moveDown(gridAlgOne);
			}else if(bestMove == 'l'){
				moveLeft(gridAlgOne);
			}else{
				moveRight(gridAlgOne);
			};
			algOneMove++;
			cout<< "Move "<< algOneMove << ": Alg_1: "<< bestMove << setw(2) << divider;
		}

	void AlgTwoStrategicMinimax() {
			if(noPossibleMovesAlgTwo == true){
				return;
			};

		    vector<char> directions = {'u', 'd', 'l', 'r'};
		    MoveAssessment best_move = { 'u', INT_MAX, INT_MAX, 0 };

		    for (char first_move : directions) {
		        vector<vector<int>> original_grid = gridAlgTwo;
		        vector<scoreObject> second_scores;
		        scoreObject first_score = evaluateMove(first_move, gridAlgTwo);
		        
		        // Apply first move temporarily
		        if(first_move == 'u') moveUp(gridAlgTwo);
		        else if(first_move == 'd') moveDown(gridAlgTwo);
		        else if(first_move == 'l') moveLeft(gridAlgTwo);
		        else moveRight(gridAlgTwo);

		        // Second move evaluation
		        for (char second_move : directions) {
		            second_scores.push_back(evaluateMove(second_move, gridAlgTwo));
		        }

		        int max_second_score = INT_MIN;
		        int min_second_score = INT_MAX;
		        for (auto& score : second_scores) {
		            max_second_score = max(max_second_score, score.newScore);
		            min_second_score = min(min_second_score, score.newScore);
		        }
		        int risk_factor = max_second_score - min_second_score;

		        int avg_future_potential = 0;
		        for (auto& score : second_scores) {
		            avg_future_potential += score.newScore;
		        }
		        avg_future_potential /= directions.size();

		        int strategic_value = first_score.newScore * 0.6 + avg_future_potential * 0.3 - risk_factor * 0.1;

		        if (strategic_value < best_move.immediate_score) {
		            best_move = {
		                first_move,
		                first_score.newScore,
		                avg_future_potential,
		                risk_factor
		            };
		        }

		        gridAlgTwo = original_grid;
		    }

		    // Execute best move
		    if(best_move.direction == 'u') moveUp(gridAlgTwo);
		    else if(best_move.direction == 'd') moveDown(gridAlgTwo);
		    else if(best_move.direction == 'l') moveLeft(gridAlgTwo);
		    else moveRight(gridAlgTwo);
		    
		    algTwoMove++;
			cout<< "Move "<< algTwoMove << ": Alg_2: "<< best_move.direction << endl;
		    //cout << "Move " << algStrategicMove << ": Alg_Strategic: " << best_move.direction  << " (Score: " << best_move.immediate_score  << ", Future: " << best_move.future_potential  << ", Risk: " << best_move.risk_factor << ")" << endl;
		}
		
		void checkIfSolved(){
			emptySlotAlgOne = 0; 
			emptySlotAlgTwo = 0;

			for(int i = 0; i < gridAlgOne.size(); i++){
				for(int j = 0; j < gridAlgOne.size(); j++){
					if(gridAlgOne[i][j] == 2){
						hasTwoAlgOne = true;
					}else if(gridAlgOne[i][j] == 0){
						emptySlotAlgOne ++;
					}
				}

				for(int j = 0; j < gridAlgTwo.size(); j++){
					if(gridAlgTwo[i][j] == 2){
						hasTwoAlgTwo = true;
					}else if(gridAlgTwo[i][j] == 0){
						emptySlotAlgTwo ++;
					}
				}
			};
			
			//checks if all possible moves have been done
			vector<char> directions = {'u', 'd', 'l', 'r'};
			scoreObject leftScoreAlgOne, rightScoreAlgOne, upScoreAlgOne, downScoreAlgOne;
			scoreObject leftScoreAlgTwo, rightScoreAlgTwo, upScoreAlgTwo, downScoreAlgTwo;
			
			for(auto& direction: directions){
				if(direction == 'u'){
					upScoreAlgOne = evaluateMove(direction, gridAlgOne);
				}else if(direction == 'd'){
					downScoreAlgOne = evaluateMove(direction, gridAlgOne);
				}else if(direction == 'l'){
					leftScoreAlgOne = evaluateMove(direction, gridAlgOne);
				}else{
					rightScoreAlgOne = evaluateMove(direction, gridAlgOne);
				};
			};

			for(auto& direction: directions){
				if(direction == 'u'){
					upScoreAlgTwo = evaluateMove(direction, gridAlgTwo);
				}else if(direction == 'd'){
					downScoreAlgTwo = evaluateMove(direction, gridAlgTwo);
				}else if(direction == 'l'){
					leftScoreAlgTwo = evaluateMove(direction, gridAlgTwo);
				}else{
					rightScoreAlgTwo = evaluateMove(direction, gridAlgTwo);
				};
			};

			if(algOneMove == 1000){
				cout<<"Maximum moves reached Alg 1"<<endl;
				emptySlotAlgOne = 0;
				noPossibleMovesAlgOne = true;
			};

			if(emptySlotAlgOne == 0 && upScoreAlgOne.previousScore == upScoreAlgOne.newScore && downScoreAlgOne.previousScore == downScoreAlgOne.newScore && leftScoreAlgOne.previousScore == leftScoreAlgOne.newScore && rightScoreAlgOne.previousScore == rightScoreAlgOne.newScore){
				cout<<"No moves available Alg 1"<<endl;
				noPossibleMovesAlgOne = true;
			}

			if(algTwoMove == 1000){
				cout<<"Maximum moves reached Alg 2"<<endl;
				emptySlotAlgTwo = 0;
				noPossibleMovesAlgTwo = true;
			};

			if(emptySlotAlgTwo == 0 && upScoreAlgTwo.previousScore == upScoreAlgTwo.newScore && downScoreAlgTwo.previousScore == downScoreAlgTwo.newScore && leftScoreAlgTwo.previousScore == leftScoreAlgTwo.newScore && rightScoreAlgTwo.previousScore == rightScoreAlgTwo.newScore){
				cout<<"No moves available Alg 2"<<endl;
				noPossibleMovesAlgTwo = true;
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
			if(noPossibleMovesAlgOne != true){
				while(gridAlgOne[newPosition.x][newPosition.y] != 0){
					newPosition = getRandomPosition();
				};
				gridAlgOne[newPosition.x][newPosition.y] = startSize;
			};

			if(noPossibleMovesAlgTwo != true){
				while(gridAlgTwo[newPosition.x][newPosition.y] != 0){
					newPosition = getRandomPosition();
				};
				gridAlgTwo[newPosition.x][newPosition.y] = startSize;
			};
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
		while (object.noPossibleMovesAlgOne != true || object.noPossibleMovesAlgTwo != true){
			cout << "-------------------------------------------------------------------" << endl;
			object.AlgOneGreedyAlgorithm();
			object.AlgTwoStrategicMinimax();
			object.checkIfSolved();

			if(object.hasTwoAlgOne == true){
				cout << "Alg 1 you won!" << endl;
				break;
			};

			if(object.hasTwoAlgTwo == true){
				cout << "Alg 2 you won!" << endl;
				break;
			};

			if(object.emptySlotAlgOne == 0 && object.emptySlotAlgTwo == 0){
				object.printCurrentGrid();
				cout << "not empty spaces and possible moves left\nGAME OVER" << endl;
				break;
			};

			object.addElementToGrid();
			object.printCurrentGrid();
		}
		games++;
	}
	return 0;
}
