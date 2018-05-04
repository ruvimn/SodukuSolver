#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

struct rowsAndColumns {
	std::vector <int> rows;
	std::vector <int> cols;
};

rowsAndColumns returnRowColAtIndex(int rowIndex, int colIndex, vector<vector<int>> puzzleBoard)
{
	rowsAndColumns returnValue;
	
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (returnValue.rows.size() < 9)
				returnValue.rows.push_back(puzzleBoard[rowIndex][col]);
			if (returnValue.cols.size() < 9)
				returnValue.cols.push_back(puzzleBoard[col][colIndex]);}
		}
	return returnValue;
}

vector <int> returnsValidOptions(int rowIndex, int colIndex, vector<vector<int>> puzzleBoard)
{	//This method returns vector of valid options

	rowsAndColumns rowColAtIndex = returnRowColAtIndex(rowIndex, colIndex, puzzleBoard);
	vector <int> currentValues;
	vector <int> optionValues;

	for (int i = 0; i < 9; i++) {	// This removes any empty cells, adds row and col values to one vector
		if (rowColAtIndex.rows.at(i) != 0)
			currentValues.push_back(rowColAtIndex.rows.at(i));
		if (rowColAtIndex.cols.at(i) != 0)
			currentValues.push_back(rowColAtIndex.cols.at(i));
	}
	sort(currentValues.begin(), currentValues.end());
	currentValues.erase(unique(currentValues.begin(), currentValues.end()), currentValues.end());

	for (int i = 1; i <= 9; i++) {	//Checks the current value array, adds options not in the currentValues vector to optionsValue
		if (find(currentValues.begin(), currentValues.end(), i) == currentValues.end())
		{
			optionValues.push_back(i);	
		}
	}
	return optionValues;
}

vector <int> returnEmptyRowIndex(vector<vector<int>> puzzleBoard)
{	//This method returns vector(arraylist) of indexes referencing empty cells in puzzleboard
	vector <int> rowIndexVector;
	int rowIndex = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (puzzleBoard[i][j] == 0){
				rowIndex = i;
				rowIndexVector.push_back(rowIndex);	//adds index of row
			}
	return rowIndexVector;
}

vector <int> returnEmptyColIndex(vector<vector<int>> puzzleBoard)
{	//This method returns vector(arraylist) of indexes referencing empty cells in puzzleboard
	vector <int> colIndexVector;
	int colIndex = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (puzzleBoard[i][j] == 0){
				colIndex = j;
				colIndexVector.push_back(colIndex);}
	return colIndexVector;
}

vector <int> findMinCellIndex(vector<vector<int>> puzzleBoard)
{	//This method returns the index to the cell with min amount of options available
	vector <int> rowIndexOfEmpty = returnEmptyRowIndex(puzzleBoard);
	vector <int> colIndexOfEmpty = returnEmptyColIndex(puzzleBoard);
	vector <int> validOptionsAtIndex;
	vector <int> indexOfSizesUnsorted;
	vector <int> indexOfSizesSorted;
	vector <int> indexOfMinCellOptions;

	// returns vector of different vector sizes based off options array sizes
	for (int i = 0; i < rowIndexOfEmpty.size(); i++){
		validOptionsAtIndex = returnsValidOptions(rowIndexOfEmpty.at(i), colIndexOfEmpty.at(i), puzzleBoard);
		indexOfSizesUnsorted.push_back(validOptionsAtIndex.size());
	}
	
	indexOfSizesSorted.insert(indexOfSizesSorted.begin(), indexOfSizesUnsorted.begin(), indexOfSizesUnsorted.end());
	sort(indexOfSizesSorted.begin(), indexOfSizesSorted.end());

	for (int i = 0; i < indexOfSizesUnsorted.size(); i++)
		if ((indexOfSizesSorted.at(0) == indexOfSizesUnsorted.at(i)) && (indexOfMinCellOptions.size() < 2)) {
			indexOfMinCellOptions.push_back(rowIndexOfEmpty.at(i));
			indexOfMinCellOptions.push_back(colIndexOfEmpty.at(i));
		}
	return indexOfMinCellOptions;
}

void solvePuzzle(vector<vector<int>> startBoard)
{
	vector<vector<int>> testBoard = startBoard;
	stack <vector<int>> stackOfVectors;
	
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			while (testBoard[i][j] == 0)
			{
				vector <int> minCellIndex = findMinCellIndex(testBoard);
				vector <int> validOptions = returnsValidOptions(minCellIndex.at(0), minCellIndex.at(1), testBoard);

				if (validOptions.size() == 0)
				{
					if (!stackOfVectors.empty())
					{
						validOptions = stackOfVectors.top();
						stackOfVectors.pop();
					}
				}
				if (validOptions.size() != 0)
				{
					testBoard[minCellIndex[0]][minCellIndex[1]] = validOptions.back();
					validOptions.pop_back();
					if (validOptions.size() != 0)
						stackOfVectors.push(validOptions);
				}
				else
					break;
			}
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			cout << testBoard[i][j];
		cout << endl;
	}
	cout << endl;
}

int main()
{
	vector<vector<int>> soduku =
	{{5, 3, 0, 0, 7, 0, 0, 0, 0},
	{6, 0, 0, 1, 9, 5, 0, 0, 0},
	{0, 9, 8, 0, 0, 0, 0, 6, 0},

	{8, 0, 0, 0, 6, 0, 0, 0, 3},
	{4, 0, 0, 8, 0, 3, 0, 0, 1},
	{7, 0, 0, 0, 2, 0, 0, 0, 6},

	{0, 6, 0, 0, 0, 0, 2, 8, 0},
	{0, 0, 0, 4, 1, 9, 0, 0, 5},
	{0, 0, 0, 0, 8, 0, 0, 7, 9} };
	
	//------print board----------//
	cout << "Sodoku Puzzle To Solve: " << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++)
			cout << soduku[i][j];
		cout << endl;
	}
	cout << endl;

	//----Solve the puzzle----//
	cout << "Solved Board: " << endl;
	solvePuzzle(soduku);
	
	cin.get();
	return 0;
}
