
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <ctime>

using namespace std;
int playMenu(int game1[][10][5]);
void newGame(int game1[][10][5]);
void hitmiss(int hitmiss);
int loadGame(int game1[][10][5]);


void display(int game1[][10][5], int play, int start)
{
	system("cls");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char rows[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	cout << "\t 1   2   3   4   5   6   7   8   9   10" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (j == 0)
				cout << endl << "    " << rows[i] << "\t";
			if (j == 9 && game1[i][j][play] == 0)
			{
				SetConsoleTextAttribute(hConsole, 11);
				cout << " ~ ";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (game1[i][j][play] == 0)
			{
				SetConsoleTextAttribute(hConsole, 11);
				cout << " ~ ";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "|";
			}
			else if (j == 9 && game1[i][j][play] == 1)
			{
				SetConsoleTextAttribute(hConsole, 9);
				cout << " O ";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (game1[i][j][play] == 0)
			{
				SetConsoleTextAttribute(hConsole, 9);
				cout << " O ";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "|";
			}
			else if (j == 9 && game1[i][j][play] == 2 && start == 0)
			{
				SetConsoleTextAttribute(hConsole, 10);
				cout << " S ";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (game1[i][j][play] == 2 && start == 0)
			{
				SetConsoleTextAttribute(hConsole, 10);
				cout << " S ";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "|";
			}
			else if (j == 9 && game1[i][j][play] == 2 && start == 1)
			{
				SetConsoleTextAttribute(hConsole, 11);
				cout << " ~ ";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (game1[i][j][play] == 2 && start == 1)
			{
				SetConsoleTextAttribute(hConsole, 11);
				cout << " ~ ";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "|";
			}
			else if (j == 9 && game1[i][j][play] == 3)
			{
				SetConsoleTextAttribute(hConsole, 12);
				cout << " X ";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (game1[i][j][play] == 3)
			{
				SetConsoleTextAttribute(hConsole, 12);
				cout << " X ";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "|";
			}
			else if (j == 9 && game1[i][j][play] == 1)
			{
				SetConsoleTextAttribute(hConsole, 9);
				cout << " O ";
				SetConsoleTextAttribute(hConsole, 7);
			}
			else if (game1[i][j][play] == 1)
			{
				SetConsoleTextAttribute(hConsole, 9);
				cout << " O ";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "|";
			}
		}
		cout << endl;
		if (i != 9)
			cout << "\t---+---+---+---+---+---+---+---+---+---";
	}
}
void aiplace(int game1[][10][5])
{
	int ships[5][5] = { { 2,2,2,2 },{ 2,2,2 },{ 2,2 },{ 2,2 },{ 2 } };
	int size[5] = { 5,4,3,3,2 };
	int play = 1;

	for (int s = 0; s < 5; s++)
	{
		int col = (rand() % 9);
		int introw = (rand() % 9);
		int direction = (rand() % 2);
		int fail = 0;
		bool colide = false;
		if (direction == 0)
		{
			for (int c = 0; fail == 0 && c < size[s]; c++)
			{
				if (game1[introw][col + c][play] == 2)
				{
					colide = true;
					s--;
					fail = 1;
				}
			}
			if (!colide)
			{
				for (int i = 0; fail == 0 && i < size[s]; i++)
				{
					if (introw + size[s] > 10)
					{
						s--;
						fail = 1;
					}
					else
						game1[introw + i][col][play] = 2;
				}
			}
		}
		else if (direction == 1)
		{
			for (int c = 0; fail == 0 && c < size[s]; c++)
			{
				if (game1[introw][col + c][play] == 2)
				{
					colide = true;
					s--;
					fail = 1;
				}
			}
			if (!colide)
			{
				for (int i = 0; fail == 0 && i < size[s]; i++)
				{
					if (col + size[s] > 10)
					{
						s--;
						fail = 1;
					}
					else
						game1[introw][col + i][play] = 2;
				}
			}
		}
		else
		{
			s--;
		}
		//display(game1 , play, 0);

	}

	Sleep(3000);

}
void buildGame(int game1[][10][5], int play)
{
	char input[3];
	int ships[5][5] = { { 2,2,2,2 },{ 2,2,2 },{ 2,2 },{ 2,2 },{ 2 } };
	int size[5] = { 5,4,3,3,2 };
	char ship[5][32] = { "Carrier","Battleship","Cruiser","Submarine","Destroyer" };
	int col;
	char row;
	char direction;
	char rows[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int introw = 0;
	for (play = 0; play <= 1; play++)
	{
		display(game1, play, 0);
		cout << "player " << play + 1 << " Place your ships" << endl;
		for (int s = 0; s < 5; s++)
		{
			cout << "Where do you want to place your " << ship[s]
				<< " (" << size[s] << "): ";
			cin >> input;
			cin.ignore();
			row = input[0];
			row = toupper(row);
			col = input[1] - '0';
			if (col > 9)
			{
				row = input[1];
				row = toupper(row);
				col = input[0] - '0';
			}
			for (int i = 0; i < 10; i++)
			{
				if (row == rows[i])
				{
					introw = i;
				}
			}
			if (input[2] == '0')
			{
				col = 10;
			}
			col -= 1;

			cout << "D for going down\n";
			cout << "R for going Right\n";
			cin >> direction;
			direction = toupper(direction);
			int fail = 0;
			bool colide = false;
			if (direction == 'D')
			{
				for (int c = 0; fail == 0 && c < size[s]; c++)
				{
					if (game1[introw][col + c][play] == 2)
					{
						colide = true;
						s--;
						fail = 1;
						cout << "You cant place a ship there the spot is taken\n";
						Sleep(1500);
					}
				}
				if (!colide)
				{
					for (int i = 0; fail == 0 && i < size[s]; i++)
					{
						if (introw + size[s] > 10)
						{
							cout << "cant place ship there try agian" << endl;
							s--;
							fail = 1;
							Sleep(2000);
						}
						else
							game1[introw + i][col][play] = 2;
					}
				}
				display(game1, play, 0);
			}
			else if (direction == 'R')
			{
				for (int c = 0; fail == 0 && c < size[s]; c++)
				{
					if (game1[introw][col + c][play] == 2)
					{
						colide = true;
						s--;
						fail = 1;
						cout << "You cant place a ship there the spot is taken\n";
						Sleep(1500);
					}
				}
				if (!colide)
				{
					for (int i = 0; fail == 0 && i < size[s]; i++)
					{
						if (col + size[s] > 10)
						{
							cout << "cant place ship there try agian" << endl;
							s--;
							fail = 1;
							Sleep(2000);
						}
						else
							game1[introw][col + i][play] = 2;
					}
				}
				display(game1, play, 0);
			}
			else
			{
				cout << "ERROR not valid choice\n";
				s--;
			}
		}
		if (game1[9][9][2] == 0)
		{
			play++;
			aiplace(game1);
		}
		cout << "Great! pass game to the next player\n";
		Sleep(2000);

	}
}
void saveGame(char fileName2[], int game1[][10][5])
{
	ofstream fout(fileName2);
	if (fout.fail())
	{
		cout << "Failed";
		return;
	}
	for (int k = 0; k < 5; k++)
	{
		for (int r = 0; r < 10; r++)
		{
			for (int c = 0; c < 10; c++)
			{
				if (c == 9)
					fout << game1[r][c][k] << endl;
				else
					fout << game1[r][c][k] << " ";
			}
		}
		fout << endl;
	}
	cout << "Board written successfully" << endl;
	return;
}
void checkWeight(int game1[][10][5], int & play, int & weight)
{
	int check = 1;
	for (int i = 0; check == 1 && i < 10; i++)
	{
		for (int j = 0; check == 1 && j < 10; j++)
		{
			if (game1[i][j][3] == 1 && game1[i][j][0] == 2)
			{
				if (game1[i][j][3] == 1 && game1[i + 1][j][3] == 2)
				{
          if (j == 1 && i == 1)
          {
             game1[i + 1][j + 1][3] = 0;
          }
					else if (j == 8 && i == 8)
          {
            game1[i + 1][j - 1][3] = 0;
            game1[i - 1][j][3] = 1;
          }
					else if (i == 0)
          {
					   game1[i + 1][j - 1][3] = 0;
					   game1[i + 1][j + 1][3] = 0;
          }
          else if (j == 0)
          {
            game1[i - 1][j][3] = 1;
            game1[i + 1][j + 1][3] = 0;
          }
          else if (i == 8)
          {
             game1[i + 1][j - 1][3] = 0;
             game1[i + 1][j + 1][3] = 0;
          }
          else if (j == 9)
          {
            game1[i - 1][j][3] = 1;
            game1[i + 1][j - 1][3] = 0;
          }
          else
          {
            game1[i - 1][j][3] = 1;
            game1[i + 1][j - 1][3] = 0;
            game1[i + 1][j + 1][3] = 0;
          }
				}
				else if (game1[i][j][3] == 1 && game1[i][j + 1][3] == 2)
				{
          if (j == 0 && i == 0)
          {
             game1[i + 1][j + 1][3] = 0;
          }
          else if (j == 8 && i == 9)
          ;
          else if (i == 0)
          {
            game1[i][j - 1][3] = 1;
            game1[i + 1][j + 1][3] = 0;
          }
          else if (j == 0)
          {
            game1[i + 1][j + 1][3] = 0;
          }
          else if (i == 9)
          ;
          else
          {
            game1[i][j - 1][3] = 1;
            game1[i + 1][j + 1][3] = 0;
          }
				}
				else if (game1[i][j][3] == 1 && game1[i][j - 1][3] == 2)
				{

          if (j == 9 && i == 9)
          ;
          else if (i == 9)
          ;
          else
          {
            game1[i + 1][j - 1][3] = 0;
          }
        }
				else if (game1[i][j][3] == 1 && game1[i - 1][j][3] == 2)
				{
           if (i == 1)
              game1[i + 1][j][3] = 1;
           else if (i == 9)
					    game1[i - 2][j][3] = 1;
           else
           {
             game1[i - 2][j][3] = 1;
             game1[i + 1][j][3] = 1;
           }
				}
				   game1[i][j][0] = 3;
					 game1[i][j][3] = 2;
					 game1[7][7][2] += 1;
					 display(game1, 0, 1);
					 Sleep(1500);
					 hitmiss(0);
					 Sleep(1000);
					 check = 0;
					 play = 1;
					 weight = 1;
				}
				else if (game1[i][j][0] == 0 && game1[i][j][3] == 1)
				{
					display(game1, 0, 1);
					Sleep(1500);
					hitmiss(1);
          check = 0;
					game1[i][j][3] = 0;
					game1[i][j][0] = 1;
				}
		}
	}
}
void aiEdit(int game1[][10][5], int & play)
{
	int weight = 0;
	checkWeight(game1, play, weight);
	if (weight == 1)
	{

	}
	else
	{
		bool check = true;
		while (check)
		{
			int col = (rand() % 9);
			int row = (rand() % 9);
			if (game1[row][col][0] == 2)
			{
				game1[7][7][2] += 1;
				game1[row][col][0] = 3;
				game1[row][col][3] = 2;
				display(game1, play, 1);
				Sleep(1500);
				hitmiss(0);
				for (int i = -1; i < 2; i += 2)
				{
					if (row == 0 && i == -1)
						;
					else if (row == 9 && i == 1)
						;
					else
						game1[row + i][col][3] = 1;
				}
				for (int j = -1; j < 2; j += 2)
				{
					if (col == 0 && j == -1)
						;
					else if (col == 9 && j == 1)
						;
					else
						game1[row][col + j][3] = 1;
				}
			}
			else if (game1[row][col][0] == 0)
			{
				game1[row][col][0] = 1;
				display(game1, play, 1);
				Sleep(1500);
				hitmiss(1);
			}
			if (game1[row][col][0] != 1 || game1[row][col][0] != 4)
				check = false;
		}
		//display(game1 , play , 1);
		play = 1;
		//Sleep(2000);
	}
}

void editSquare(int game1[][10][5], int & play)
{

	char input[3];
	char rows[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	int introw = 0;
	cout << "What are the coordinates of the square: ";
	cin >> input;
	cin.ignore();
	char row = input[0];
	row = toupper(row);
	int col = input[1] - '0';
	if (col > 9)
	{
		row = input[1];
		row = toupper(row);
		col = input[0] - '0';
	}
	if (input[2] == '0')
	{
		col = 10;
	}
	for (int i = 0; i < 10; i++)
	{
		if (row == rows[i])
		{
			introw = i;
		}
	}
	col -= 1;
	if (game1[introw][col][play] == 2)
	{
		game1[introw][col][play] = 3;
		game1[8][8][2] += 1;
		hitmiss(0);

	}
	else if (game1[introw][col][play] == 0)
	{
		game1[introw][col][play] = 1;
		hitmiss(1);
	}
	cout << endl;

	if (play == 0)
		play = 1;
	else
		play = 0;
	Sleep(2000);
}
void debug(int game1[][10][5], int & player)
{
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if (c == 9)
				cout << game1[r][c][3] << endl;
			else
				cout << game1[r][c][3] << " ";
		}
	}
}
void hitmiss(int hitmiss)
{
	system("cls");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hitmiss == 0)
	{
		SetConsoleTextAttribute(hConsole, 12);
		cout << "\n\n\n\n\n\n\n\n";
		cout << "                                         _ ._  _ , _ ._\n";
		cout << "                                       (_ ' ( `  )_  .__)\n";
		cout << "\t _   _   _   _____            ( (  (    )   `)  ) _)\n";
		cout << "\t| | | | | | |_   _|          (__ (_   (_ . _) _) ,__)\n";
		cout << "\t| |_| | | |   | |                `~~`\\ ' . /`~~`\n";
		cout << "\t|  _  | | |   | |                     ;   ;\n";
		cout << "\t| | | | | |   | |                     /   \\\n";
		cout << "\t|_| |_| |_|   |_|       _____________/_ __ \\_____________\n";
		SetConsoleTextAttribute(hConsole, 7);
		Sleep(1500);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 9);
		cout << "\n\n\n\n\n\n\n\n";
		cout << "\t     ___  ___   _   _____   _____  \n";
		cout << "\t    /   |/   | | | /  ___/ /  ___/ \n";
		cout << "\t   / /|   /| | | | | |___  | |___  \n";
		cout << "\t  / / |__/ | | | | \\___  \\ \\___  \\ \n";
		cout << "\t / /       | | | |  ___| |  ___| | \n";
		cout << "\t/_/        |_| |_| /_____/ /_____/ \n";
		SetConsoleTextAttribute(hConsole, 7);
		Sleep(1500);
	}
}
int playMenu(int game1[][10][5], int & player)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char fileName2[256];
	char play = '?';
	while (play != 'Q')
	{
		if (game1[8][8][2] == 17 || game1[7][7][2] == 17)
		{
			play = 'Q';
			cout << "Game Over Player ";
			if (game1[8][8][2] == 17)
				cout << "1 WINS!";
			else
				cout << "2 WINS!";
			return -1;
		}
		cout << player;
		display(game1, player, 1);
		if (player == 1)
		{
			SetConsoleTextAttribute(hConsole, 14);
			cout << " _____  _           __     ________ _____    __ \n";
			cout << "|  __ \\| |        /\\\\ \\   / /  ____|  __ \\  /_ |\n";
			cout << "| |__) | |       /  \\\\ \\_/ /| |__  | |__) |  | |\n";
			cout << "|  ___/| |      / /\\ \\\\   / |  __| |  _  /   | |\n";
			cout << "| |    | |____ / ____ \\| |  | |____| | \\ \\   | |\n";
			cout << "|_|    |______/_/    \\_\\_|  |______|_|  \\_\\  |_|\n";
			SetConsoleTextAttribute(hConsole, 7);
		}
		else if (player == 0 && game1[9][9][2] == 1)
		{
			SetConsoleTextAttribute(hConsole, 13);
			cout << "  _____  _           __     ________ _____    ___  \n";
			cout << " |  __ \\| |        /\\\\ \\   / /  ____|  __ \\  |__ \\ \n";
			cout << " | |__) | |       /  \\\\ \\_/ /| |__  | |__) |    ) |\n";
			cout << " |  ___/| |      / /\\ \\\\   / |  __| |  _  /    / / \n";
			cout << " | |    | |____ / ____ \\| |  | |____| | \\ \\   / /_\n";
			cout << " |_|    |______/_/    \\_\\_|  |______|_|  \\_\\ |____|\n";
			SetConsoleTextAttribute(hConsole, 7);
		}
		if ((player == 0 || player == 1) && game1[9][9][2] == 1)
		{
			cout << "Options:\n";
			cout << "   F  fire on a square\n";
			cout << "   Q  Save and Quit\n";
			cout << "   S  Show Board\n";
			//cout << " D for debug\n";
			cout << "\t> ";
			cin >> play;
			char pick = toupper(play);
			if (pick == 'F')
			{
				editSquare(game1, player);
			}
			else if (pick == 'Q')
			{
				play = 'Q';
				cout << "What file would you like to write your board to: ";
				cin >> fileName2;
				saveGame(fileName2, game1);
				return -1;
			}
			else if (pick == 'D')
				debug(game1, player);
			else if (pick == 'S')
			{
				display(game1, player, 1);
				Sleep(3000);
			}
			else
			{
				cout << "ERROR: Invalid command" << endl;
			}
		}
		else if (player == 1 && game1[9][9][2] == 0)
		{

			cout << "Options:\n";
			cout << "   F  fire on a square\n";
			cout << "   Q  Save and Quit\n";
			cout << "   S  Show Board\n";
			//cout << " D for debug\n";
			cout << "\t> ";
			cin >> play;
			char pick = toupper(play);
			if (pick == 'F')
			{
				editSquare(game1, player);
			}
			else if (pick == 'Q')
			{
				play = 'Q';
				cout << "What file would you like to write your board to: ";
				cin >> fileName2;
				saveGame(fileName2, game1);
				return -1;
			}
			else if (pick == 'D')
				debug(game1, player);
			else if (pick == 'S')
			{
				int show;
				cout << "\t 1 or 2 which board? ";
				cin >> show;
				display(game1, show - 1, 1);
			}
			else
			{
				cout << "ERROR: Invalid command" << endl;
			}
		}
		else if (game1[9][9][2] == 0 && player == 0)
		{
			aiEdit(game1, player);
		}
	}

	return(0);
}
int main()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	srand(time(NULL));
	cout << endl;
	cout << "\t _____       ___   _____   _____   _       _____   _____   _   _   _   _____  \n";
	cout << "\t|  _  \\     /   | |_   _| |_   _| | |     | ____| /  ___/ | | | | | | |  _  \\ \n";
	cout << "\t| |_| |    / /| |   | |     | |   | |     | |__   | |___  | |_| | | | | |_| | \n";
	cout << "\t|  _  {   / / | |   | |     | |   | |     |  __|  \\___  \\ |  _  | | | |  ___/ \n";
	cout << "\t| |_| |  / /  | |   | |     | |   | |___  | |___   ___| | | | | | | | | |     \n";
	cout << "\t|_____/ /_/   |_|   |_|     |_|   |_____| |_____| /_____/ |_| |_| |_| |_|     \n";
	SetConsoleTextAttribute(hConsole, 7);
	int game1[10][10][5];
	int agian = 0;
	newGame(game1);
	char start;
	int ai = 0;
	//cout << "Options:\n";
	cout << "\n\n\n\n   N  New game\n";
	cout << "   L  Load Game\n\n";
	cout << "\tEntry : ";
	cin >> start;
	start = toupper(start);
	int player = 0;
	if (start == 'N')
	{
		cout << "   1   Player\n";
		cout << "   2   Player\n\n";
		cout << "\tEntry : ";
		cin >> ai;
		if (ai == 1)
		{
			game1[9][9][2] = 0;
			buildGame(game1, player);
			player = 1;
		}
		else if (ai == 2)
		{
			game1[9][9][2] = 1;
			buildGame(game1, player);
			player = 0;
		}


	}
	else if (start == 'L')
	{
		loadGame(game1);
		player = 1;
	}
	int taco = playMenu(game1, player);
	return 0;
}
void getfileName(char fileName[])
{
	cout << "Where is your board located? ";
	cin >> fileName;
}


int loadGame(int game1[][10][5])
{
	char fileName[256];
	getfileName(fileName);
	ifstream fin(fileName);
	if (fin.fail())
		return -1;
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				fin >> game1[i][j][k];
			}
		}
	}

	fin.close();
}

void newGame(int game1[][10][5])
{
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				game1[i][j][k] = 0;

			}
		}
	}
}
