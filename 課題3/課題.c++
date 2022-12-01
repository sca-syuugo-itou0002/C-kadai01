#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const char X = 'X';
const char* pX = &X;
const char O = 'O';
const char* pO = &O;
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instructions();
char askYesNo(string question);
int askNumber(string question,int high,int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(vector<char> *const board);
char winner(vector<char> *const board);
bool isLegal(vector<char> *const board, int move);
int humanMove(vector<char> *const board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);
int main() {
  int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	
	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = *pX;
	displayBoard(&board);
	
	while (winner(&board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(&board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(&board);
		turn = opponent(turn);
	}
	
	announceWinner(winner(&board), computer, human);
	
	return 0;
}
void instructions()
{

	// 三目並べ：人間対AI
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	// 人間の脳がシリコン・プロセッサーと対戦する。
	cout << "--where human brain is pit against silicon processor\n\n";
	// 0～8の数字を入力する。
	cout << "Make your move known by entering a number, 0-8. The number\n";
	// 数字は下記のように盤の位置を示す。
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	
	cout << "		0 | 1 | 2\n";
	cout << "		3 | 4 | 5\n";
	cout << "		6 | 7 | 8\n\n";
	
	// 人間、準備せよ。戦いが始まる。
	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');
	
	return response;
}

int askNumber(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);
	
	return number;
}

char humanPiece()
{
	// 先攻になる必要ある？
	char go_first = askYesNo("Do you require the first move?");
	if (go_first == 'y')
	{
		//先攻どうぞ。どうせ負ける
		cout << "\nThen take the first move. You will need it.\n";
		return *pX;
	}
	else
	{
		//なんて勇敢さ、負けるに決まっている。では、先にやるよ。
		cout << "\nYour bravery will be your undoing... I will go first.\n";
		return *pO;
	}
}

char opponent(char piece)
{
	if (piece == *pX)
	{
		return *pO;
	}
	else
	{
		return *pX;
	}
}

void displayBoard(vector<char> *const board)
{
  vector<char>Newboard = *board;
	cout << "\n\t" << Newboard[0] << " | " << Newboard[1] << " | " << Newboard[2];
	cout << "\n\t" << "--------";
	cout << "\n\t" << Newboard[3] << " | " << Newboard[4] << " | " << Newboard[5];
	cout << "\n\t" << "--------";
	cout << "\n\t" << Newboard[6] << " | " << Newboard[7] << " | " << Newboard[8];
	cout << "\n\t" << "\n\n";	
}

char winner(vector<char> *const board)
{
	// 勝利条件
	// all possible winning rows
	const int WINNING_ROWS[8][3] = { {0, 1, 2},
									{3, 4, 5},
									{6, 7, 8},
									{0, 3, 6},
									{1, 4, 7},
									{2, 5, 8},
									{0, 4, 8},
									{2, 4, 6} };
	
	const int TOTAL_ROWS = 8;
	
	// いずれかの勝利行に同じ3つの値がある（空じゃない）場合は
	// if any winning row has three values that are the same (and not EMPTY),
	// 勝者が決まる
	// then we have a winner
  vector<char> Newboard = *board;
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if (	(Newboard[WINNING_ROWS[row][0]] != EMPTY) &&
				(Newboard[WINNING_ROWS[row][0]] == Newboard[WINNING_ROWS[row][1]]) &&
				(Newboard[WINNING_ROWS[row][1]] == Newboard[WINNING_ROWS[row][2]]) )
		{
			return Newboard[WINNING_ROWS[row][0]];
		}
	}
	
	// 勝者が出てないので、引き分けであることを確認
	// since nobody has won, check for a tie (no empty squares left)
	if (count(board->begin(), board->end(), EMPTY) == 0)
		return TIE;
	
	// 勝者が出ていなくて引き分けになっていないので、ゲームオーバーじゃない。
	// since nobody has won and it isn't a tie, the game isn't over
	return NO_ONE;
}

inline bool isLegal(int move, vector<char> *const board)
{
  vector<char> Newboard = *board;
	return (Newboard[move] == EMPTY);
}

int humanMove(vector<char> *const board, char human)
{
	//次はどうする？
	int move = askNumber("Where will you move?", (board->size() - 1));
	while (!isLegal(move, board))
	{
		//愚かな人間め、そのマスはもう埋まっているぞ
		cout << "\nThat square is already occupied, foolish human.\n";
		//次はどうする？
		move = askNumber("Where will you move?", (board->size() - 1));
	}
	//　わかった
	cout << "Fine...\n";
	
	return move;
}

int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	
	// もし次の番AIが勝つならこうする
	// if computer can win on next move, that's the move to make
	while (!found && move < board.size())
	{
		if (isLegal(move, &board))
		{
			board[move] = computer;
			found = winner(&board) == computer;
			board[move] = EMPTY;
		}
		
		if (!found)
		{
			++move;
		}
	}
	
	// それとも、もし次の番プレイヤーが勝つならこうする
	// otherwise, if human can win on next move, that's the move to make
	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		
		while (!found && move < board.size())
		{
			if (isLegal(move, &board))
			{
				board[move] = human;
				found = winner(&board) == human;
				board[move] = EMPTY;
			}
			
			if (!found)
			{
				++move;
			}
		}
	}

	// そうではない場合、今空いているマスのうちにもっとも良い選択をする
	// otherwise, moving to the best open square is the move to make
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		
		const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
		//　もっとも良いマスを決める
		// pick best open square
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, &board))
			{
				found = true;
			}
			
			++i;
		}
	}
	
	// 目のマスを埋めるぞ。
	cout << "I shall take square number " << move << endl;
	return move;
}

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		// が勝った
		cout << winner << "'s won!\n";
		// 思った通り、またオラの勝ちだ。
		cout << "As I predicted, human, I am triumphant once more -- proof\n";
		// AIは人間より優れていることの証拠だ
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (winner == human)
	{
		//　が勝った
		cout << winner << "'s won!\n";
		//　うそだ。ありえない。オラ負けるはずがない。騙されたに決まっている。
		cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
		// もう２度と負けない。絶対にな。
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else
	{
		// 引き分けだ
		cout << "It's a tie.\n";
		// とても運のいい人間だな。引き分けになってくれやがった。
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		// 祝うといい。引き分け以上になることはないのだ。
		cout << "Celebrate... for this is the best you will ever achieve.\n";
	}
}