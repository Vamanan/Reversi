#include<iostream>
#include<vector>
#include<limits>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
int pos_weights[8][8] = { { 99, -8, 8, 6, 6, 8, -8, 99 }, { -8, -24, -4, -3, -3, -4, -24, -8 }, { 8, -4, 7, 4, 4, 7, -4, 8 }, { 6, -3, 4, 0, 0, 4, -3, 6 }, { 6, -3, 4, 0, 0, 4, -3, 6 }, { 8, -4, 7, 4, 4, 7, -4, 8 }, { -8, -24, -4, -3, -3, -4, -24, -8 }, { 99, -8, 8, 6, 6, 8, -8, 99 } };
int max_depth;
char alphabet[9] = "abcdefgh";
stringstream str;


bool is_onboard(int x,int y)
{
	
	if (x >= 0 && x < 8 && y >= 0 && y < 8)
		return true;
	return false;
	
}
struct state
{
	char board[8][8];
	char tile;
	char opptile;
	void init_opptile()
	{
		if (tile == 'X')
			opptile = 'O';
		else
			opptile = 'X';

	}
	vector<vector<int> > find_mytile()
	{
		vector<vector<int> > my_tiles;

		
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == tile)
				{
					vector<int>temp;
					temp.push_back(i);
					temp.push_back(j);
					my_tiles.push_back(temp);
				}
			}
		}
		return my_tiles;
	}
	vector<vector<int> > find_opptile()
	{
		vector<vector<int> > opp_tiles;

		
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] == opptile)
				{
					vector<int>temp;
					temp.push_back(i); temp.push_back(j);
					opp_tiles.push_back(temp);
				}
			}
		}
		return opp_tiles;
	}


}root;
bool contains_duplicate(vector<vector<int> >a, vector<int>b)
{
	bool duplicate = false;
	vector<vector<int> >::iterator row;
	for (row = a.begin(); row != a.end(); row++)
	{
		vector<int>temp = *row;
		if (temp[0] == b[0] && temp[1] == b[1])
			duplicate = true;
	}
	return duplicate;

}
vector<vector<int> > find_legalmoves(struct state s)
{
	/*cout << "board inside function:" << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << s.board[i][j];
		}
		cout << endl;
	}*/
	vector<vector<int> >legal_moves;
	vector<vector<int> > directions;
	vector<int>temp;
	temp.push_back(-1);
	temp.push_back(0);
	directions.push_back(temp); temp.clear();
	temp.push_back(1);
	temp.push_back(0);
	directions.push_back(temp); temp.clear();
	temp.push_back(0);
	temp.push_back(1);
	directions.push_back(temp); temp.clear();
	temp.push_back(0);
	temp.push_back(-1);
	directions.push_back(temp); temp.clear();
	temp.push_back(-1);
	temp.push_back(1);
	directions.push_back(temp); temp.clear();
	temp.push_back(-1);
	temp.push_back(-1);
	directions.push_back(temp); temp.clear();
	temp.push_back(1);
	temp.push_back(1);
	directions.push_back(temp); temp.clear();
	temp.push_back(1);
	temp.push_back(-1);
	directions.push_back(temp); temp.clear();
	int tempx, tempy;
	vector<vector<int> >my_tiles=s.find_mytile();
	vector<vector<int> >::iterator row;
	/*cout << "my tiles" << endl;
	for (row = my_tiles.begin(); row != my_tiles.end(); row++)
	{
		vector<int>foo = *row;
		cout << foo[0] << " " << foo[1] << endl;
	}
	cout << endl;*/
	vector<vector<int> >::iterator row1;
	for (row = my_tiles.begin(); row != my_tiles.end(); row++)
	{
		bool possible_dir[8] = { false, false, false, false, false, false, false, false };
		vector<int>temp_tile = *row;
		int j;
		for (row1 = directions.begin(), j = 0; row1 != directions.end(); row1++, j++)
		{
			vector<int>temp_dir = *row1;
			if (is_onboard(temp_tile[0] + temp_dir[0], temp_tile[1] + temp_dir[1]))
			{
				if (s.board[temp_tile[0] + temp_dir[0]][temp_tile[1] + temp_dir[1]] == s.opptile)
					possible_dir[j] = true;
			}
		}

		/*for (int i = 0; i < 8; i++)
			cout << possible_dir[i] << " ";
		cout << endl;*/

		vector<int>::iterator col;
		for (int k = 0; k < 8; k++)
		{
			if (possible_dir[k])
			{
				tempx = temp_tile[0] + directions[k][0]; tempy = temp_tile[1] + directions[k][1];
				while (s.board[tempx][tempy] == s.opptile)
				{
					tempx += directions[k][0];
					tempy += directions[k][1];
					//cout << "tempx=" << tempx << " " << "tempy=" << tempy << endl;
				}
				if (!is_onboard(tempx, tempy))
					break;
				vector<int>duparg;
				duparg.push_back(tempx);
				duparg.push_back(tempy);
				if (s.board[tempx][tempy] == '*'&&!contains_duplicate(legal_moves, duparg))
				{
					vector<int>temp;
					temp.push_back(tempx); temp.push_back(tempy);
					legal_moves.push_back(temp);
				}
			}
		}
	}
	//sort legal_moves rowwise using bubble sort if not empty
	if (!legal_moves.empty())
	{
		vector<int>temp;
		bool finished = false;
		while (!finished)
		{
			finished = true;
			for (int i = 0; i < legal_moves.size() - 1; i++)
			{
				vector<int>element = legal_moves[i];
				vector<int>next_element = legal_moves[i + 1];
				if (element[0]> next_element[0])
				{
					temp = legal_moves[i];
					legal_moves[i] = legal_moves[i + 1];
					legal_moves[i + 1] = temp;
					finished = false;
				}
				else if (element[0] == next_element[0])
				{
					if (element[1] > next_element[1])
					{
						temp = legal_moves[i];
						legal_moves[i] = legal_moves[i + 1];
						legal_moves[i + 1] = temp;
						finished = false;
					}

				}
			}
		}
	}

	return legal_moves;
}
struct state result(struct state s, vector<int>move)
{
	int tempx, tempy;
	struct state successor;
	successor.tile = s.opptile;
	successor.opptile = s.tile;
	s.board[move[0]][move[1]] = s.tile;
	//now convert opp tile to mytile
	vector<vector<int> >convert_list;
	vector<vector<int> >my_tiles = s.find_mytile();
	vector<vector<int> > directions;
	vector<int>temp;
	temp.push_back(-1);
	temp.push_back(0);
	directions.push_back(temp); temp.clear();
	temp.push_back(1);
	temp.push_back(0);
	directions.push_back(temp); temp.clear();
	temp.push_back(0);
	temp.push_back(1);
	directions.push_back(temp); temp.clear();
	temp.push_back(0);
	temp.push_back(-1);
	directions.push_back(temp); temp.clear();
	temp.push_back(-1);
	temp.push_back(1);
	directions.push_back(temp); temp.clear();
	temp.push_back(-1);
	temp.push_back(-1);
	directions.push_back(temp); temp.clear();
	temp.push_back(1);
	temp.push_back(1);
	directions.push_back(temp); temp.clear();
	temp.push_back(1);
	temp.push_back(-1);
	directions.push_back(temp); temp.clear();
	vector<vector<int> >::iterator row;
	vector<vector<int> >::iterator row1;
	for (row = my_tiles.begin(); row != my_tiles.end(); row++)
	{
		bool possible_dir[8] = { false, false, false, false, false, false, false, false };
		vector<int>temp_tile = *row;
		int j;
		for (row1 = directions.begin(), j = 0; row1 != directions.end(); row1++, j++)
		{
			vector<int>temp_dir = *row1;
			if (is_onboard(temp_tile[0] + temp_dir[0], temp_tile[1] + temp_dir[1]))
			{
				if (s.board[temp_tile[0] + temp_dir[0]][temp_tile[1] + temp_dir[1]] == s.opptile)
					possible_dir[j] = true;
			}
		}
		for (int k = 0; k < 8; k++)
		{
			if (possible_dir[k])
			{
				tempx = temp_tile[0] + directions[k][0]; tempy = temp_tile[1] + directions[k][1];

				while (s.board[tempx][tempy] == s.opptile)
				{
					vector<int>convertarg;
					convertarg.push_back(tempx);
					convertarg.push_back(tempy);
					convert_list.push_back(convertarg);
					tempx += directions[k][0];
					tempy += directions[k][1];

				//	cout << "tempx=" << tempx << " " << "tempy=" << tempy << endl;
				}
				if (!is_onboard(tempx, tempy))
				{ 
					convert_list.clear();
					break;
				
				}
					
				if (s.board[tempx][tempy] == s.tile)
				{
					vector<vector<int> >::iterator row;
					for (row = convert_list.begin(); row != convert_list.end(); row++)
					{
						vector<int> x = *row;
						s.board[x[0]][x[1]] = s.tile;
					}
				}
				else
					convert_list.clear();
			}
		}
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			successor.board[i][j] = s.board[i][j];
	return successor;
}
int evaluate_board(struct state s)
{
	int score;
	vector<vector<int> >my_tiles = s.find_mytile();
	vector<vector<int> >opp_tiles = s.find_opptile();
	int myscore = 0; int oppscore = 0;
	vector<vector<int> >::iterator row;
	for (row = my_tiles.begin(); row != my_tiles.end(); row++)
	{
		vector<int>temp = *row;
		myscore += pos_weights[temp[0]][temp[1]];
	}
	for (row = opp_tiles.begin(); row != opp_tiles.end(); row++)
	{
		vector<int>temp = *row;
		oppscore += pos_weights[temp[0]][temp[1]];
	}
	if (s.tile == root.tile)
		score = myscore - oppscore;
	else
		score = oppscore - myscore;
	//cout << "score=" << score << endl;
	return score;
}
int max(struct state s,int depth,vector<int>opmove,bool dblpass);
int min(struct state s,int depth, vector<int>opmove,bool dblpass)
{
	
//	cout << "inside min" << endl << "depth=" << depth << endl;
	int v = numeric_limits<int>::max();
	vector<vector<int> >my_tiles = s.find_mytile();
	vector<vector<int> >opp_tiles = s.find_opptile();
	if (dblpass)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;

	}
	if (my_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;
	}
	if (opp_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;
	}
	if (depth == max_depth)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0]==-1)?str<<"pass":str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;
	}
	vector < vector<int> >moves = find_legalmoves(s);
	if (moves.empty())//if min has no move
	{
		if (opmove[0] == -1)//if prev player had no move as well, we have reached end of game
		{
		//	int terminal_value = evaluate_board(s);
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == numeric_limits<int>::max()) ? str << "Infinity" : str << v); str << endl;
			struct state temp;
			temp.opptile = s.tile;
			temp.tile = s.opptile;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					temp.board[i][j] = s.board[i][j];
			vector<int>dummy_move;// = vector < int > {-1, -1};
			dummy_move.push_back(-1); dummy_move.push_back(-1);
			int max_call = max(temp, depth + 1, dummy_move,true);
			if (max_call < v)
				v = max_call;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == numeric_limits<int>::max()) ? str << "Infinity" : str << v); str << endl;
			return v;
		}
		
		else
		{
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == numeric_limits<int>::max()) ? str << "Infinity" : str << v); str << endl;
			struct state temp;
			temp.opptile = s.tile;
			temp.tile = s.opptile;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					temp.board[i][j] = s.board[i][j];
			vector<int>dummy_move;// = vector < int > {-1, -1};
			dummy_move.push_back(-1); dummy_move.push_back(-1);
			int max_call = max(temp, depth + 1, dummy_move,false);
			if (max_call < v)
				v = max_call;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == numeric_limits<int>::max()) ? str << "Infinity" : str << v); str << endl;
		}
	
	}
	else
	{
		vector<vector<int> >::iterator row;
		for (row = moves.begin(); row != moves.end(); row++)
		{
			vector<int>temp_move = *row;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == numeric_limits<int>::max()) ? str << "Infinity" : str << v); str << endl;

			struct state temp = result(s, *row);
			int max_call = max(temp, depth + 1, *row,false);
			if (max_call < v)
				v = max_call;
		}
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		((v == numeric_limits<int>::max()) ? str << "Infinity" : str << v); str << endl;
	}
	return v;

}
int max(struct state s,int depth,vector<int>opmove,bool dblpass)
{
	//cout << "inside min" << endl << "depth=" << depth << endl;
	int v = INT_MIN;
	vector<vector<int> >my_tiles = s.find_mytile();
	vector<vector<int> >opp_tiles = s.find_opptile();
	if (dblpass)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;

	}
	if (my_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;
	}
	if (opp_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;
	}

	if (depth == max_depth)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << "," << terminal_value << endl;
		return terminal_value;
	}
	vector < vector<int> >moves = find_legalmoves(s);
	if (moves.empty())//if max has no move
	{
		if (opmove[0] == -1)//if prev player had no move as well, we have reached end of game
		{
			//int terminal_value = evaluate_board(s);
			int min_call;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;
			struct state temp;
			temp.opptile = s.tile;
			temp.tile = s.opptile;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					temp.board[i][j] = s.board[i][j];
			vector<int>dummy_move;
			dummy_move.push_back(-1); dummy_move.push_back(-1);
			min_call = min(temp, depth + 1, dummy_move, true);
			if (min_call > v)
				v = min_call;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;

			return v;
		}
		else
		{
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;

			struct state temp;
			temp.opptile = s.tile;
			temp.tile = s.opptile;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					temp.board[i][j] = s.board[i][j];
			vector<int>dummy_move;// = vector < int > {-1, -1};
			dummy_move.push_back(-1); dummy_move.push_back(-1);

			int min_call = min(temp, depth + 1, dummy_move,false);
			if (min_call > v)
				v = min_call;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;
		}
	}
	else
	{
		vector<vector<int> >::iterator row;
		for (row = moves.begin(); row != moves.end(); row++)
		{
			vector<int>temp_move = *row;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;
			struct state temp = result(s, *row);
			int min_call = min(temp, depth + 1, *row,false);
			if (min_call > v)
				v = min_call;
		}
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;
	}
	return v;

}
vector<int>minimax(struct state s)
{
	int v = INT_MIN;
	//cout << "inside minimax" << endl << "v=" << v << endl;
	vector<int>move;
	vector<vector<int> >moves = find_legalmoves(s);
	vector<vector<int> >opp_tiles = s.find_opptile();
	vector<vector<int> >my_tiles = s.find_mytile();

	if (opp_tiles.empty())
	{
		int val = evaluate_board(s);
		str << "root,0," << val << endl;
		vector<int>rvector;
		rvector.push_back(-1); rvector.push_back(-1);
		return rvector;
	}
	if (my_tiles.empty())
	{
		int val = evaluate_board(s);
		str << "root,0," << val << endl;
		vector<int>rvector;
		rvector.push_back(-1); rvector.push_back(-1);
		return rvector;
	}

	if (moves.empty())//if no legal moves at root
	{
		str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;
		struct state temp;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				temp.board[i][j] = s.board[i][j];
		temp.opptile = s.tile;
		temp.tile = s.opptile;
		vector<int>dummy_move;// = vector < int > {-1, -1};
		dummy_move.push_back(-1); dummy_move.push_back(-1);
		int min_return = min(temp, 1, dummy_move,false);
		if (min_return > v)
		{
			v = min_return;
			
		}
		str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v); //str << endl;
		return dummy_move;
	}
	else
	{
		vector<vector<int> >::iterator row;
		for (row = moves.begin(); row != moves.end(); row++)
		{
			str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v); str << endl;
			struct state temp = result(s, *row);
			int min_return = min(temp, 1, *row,false);
			if (min_return > v)
			{
				v = min_return;
				move = *row;
			}

		}
	}
	str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v); //str << endl;
	return move;
}
int min_ab(struct state s, int depth, int alpha, int beta, vector<int>opmove,bool dblpass);
int max_ab(struct state s, int depth, int alpha, int beta, vector<int>opmove, bool dblpass);
vector<int>abdriver(struct state s)
{
	int v = INT_MIN;
	int alpha = INT_MIN;
	int beta = numeric_limits<int>::max();
	vector<vector<int> >moves = find_legalmoves(s);
	vector<vector<int> >::iterator row;
	vector<int>move;
	vector<vector<int> >opp_tiles = s.find_opptile();
	vector<vector<int> >my_tiles = s.find_mytile();
	if (opp_tiles.empty())
	{
		int val = evaluate_board(s);
		str << "root,0," << val << ","; (alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		vector<int>rvector;
		rvector.push_back(-1); rvector.push_back(-1);
		return rvector;
	}
	if (my_tiles.empty())
	{
		int val = evaluate_board(s);
		str << "root,0," << val << ","; (alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;

		vector<int>rvector;
		rvector.push_back(-1); rvector.push_back(-1);
		return rvector;
	}
	if (moves.empty())
	{
		str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v);
		str << ","; (alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		//printing board
	/*	for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
				str << s.board[x][y];

			str << endl;
		}*/
		struct state temp;
		temp.opptile = s.tile;
		temp.tile = s.opptile;
		for (int p = 0; p < 8; p++)
			for (int q = 0; q < 8; q++)
				temp.board[p][q] = s.board[p][q];
		vector<int>dummy_move;
		dummy_move.push_back(-1); dummy_move.push_back(-1);
		int min_return = min_ab(temp, 1, alpha, beta, dummy_move,false);
		if (min_return > v)
		{
			v = min_return;
		}
		if (v > alpha)
			alpha = v;
		
		str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v);
		str << ","; (alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity"  : str << beta ;
		//printing board
		/*for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
				str << s.board[x][y];

			str << endl;
		}
		*/
		vector<int>rvector;
		rvector.push_back(-1); rvector.push_back(-1);
		return rvector;

	}
	else
	{
		for (row = moves.begin(); row != moves.end(); row++)
		{
			str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v);
			str << ","; (alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
			//printing board
			/*for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
					str << s.board[x][y];

				str << endl;
			}*/
			struct state temp = result(s, *row);
			int min_return = min_ab(temp, 1, alpha, beta, *row,false);
			if (min_return > v)
			{
				v = min_return;
				move = *row;

			}
			if (v > alpha)
				alpha = v;

		}
	}
	str << "root,0,"; ((v == INT_MIN) ? str << "-Infinity" : str << v);
	str << ","; (alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
	(beta == numeric_limits<int>::max()) ? str << "Infinity": str << beta;
	//printing board
	/*for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
			str << s.board[x][y];

		str << endl;
	}*/
	return move;

}
int min_ab(struct state s, int depth, int alpha, int beta, vector<int>opmove, bool dblpass)
{
	int v = numeric_limits<int>::max();
	vector<vector<int> >my_tiles = s.find_mytile();
	vector<vector<int> >opp_tiles = s.find_opptile();
	if (dblpass)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		return terminal_value;


	}
	if (my_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		return terminal_value;

	}
	if (opp_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		return terminal_value;

	}
	if (depth == max_depth)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0]==-1)?str<<"pass":str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		//printing board
		/*for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
				str << s.board[x][y];

			str << endl;
		}*/
		return terminal_value;
	}
	vector<vector<int> >actions = find_legalmoves(s);
	if (actions.empty())
	{
		if (opmove[0] == -1)
		{
			//int terminal_value = evaluate_board(s);
			int max_call;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			(v == numeric_limits<int>::max()) ? str << "Infinity," : str << v << ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
			struct state temp;
			temp.tile = s.opptile;
			temp.opptile = s.tile;
			for (int p = 0; p < 8; p++)
				for (int q = 0; q < 8; q++)
					temp.board[p][q] = s.board[p][q];
			vector<int>dummy_move;
			dummy_move.push_back(-1); dummy_move.push_back(-1);
			max_call = max_ab(temp, depth + 1, alpha, beta, dummy_move, true);
			v = (max_call < v) ? max_call : v;
			if (v <= alpha)
			{
				//str << "pruning here" << endl;
				(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
				str << "," << depth << ",";
				(v == numeric_limits<int>::max()) ? str << "Infinity," : str << v << ",";
				(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
				(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
				return v;
			}
			beta = (v < beta) ? v : beta;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			str << v << ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;



			return v;

		}
		else
		{
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			(v == numeric_limits<int>::max()) ? str << "Infinity," : str << v << ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
			//printing board
			/*for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
					str << s.board[x][y];

				str << endl;
			}*/

			struct state temp;
			temp.opptile = s.tile;
			temp.tile = s.opptile;
			for (int p = 0; p < 8; p++)
				for (int q = 0; q < 8; q++)
					temp.board[p][q] = s.board[p][q];
			vector<int>dummy_move;
			dummy_move.push_back(-1); dummy_move.push_back(-1);

			int max_call = max_ab(temp, depth + 1, alpha, beta, dummy_move,false);
			if (max_call < v)
			{
				v = max_call;
			}
			
			if (v <= alpha)
			{
				//str << "pruning here" << endl;
				(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
				str << "," << depth << ",";
				(v == numeric_limits<int>::max()) ? str << "Infinity," : str << v << ",";
				(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
				(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
				//printing board
				/*for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
						str << s.board[x][y];

					str << endl;
				}
				*/
				return v;
			}
			beta = (v < beta) ? v : beta;
		}

	}
	else
	{
		vector<vector<int> >::iterator row;
		for (row = actions.begin(); row != actions.end(); row++)
		{
			struct state temp = result(s, *row);
			(opmove[0]==-1)?str<<"pass":str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			(v == numeric_limits<int>::max()) ? str << "Infinity," : str << v << ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
			//printing board
			/*for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
					str << s.board[x][y];

				str << endl;
			}
			*/
			int max_call = max_ab(temp, depth + 1, alpha, beta, *row,false);
			if (max_call < v)
			{
				v = max_call;
			}
			
			if (v <= alpha)
			{
				//str << "pruning here" << endl;
				(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
				str << "," << depth << ",";
				(v == numeric_limits<int>::max()) ? str << "Infinity," : str << v << ",";
				(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
				(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
				//printing board
				/*for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
						str << s.board[x][y];

					str << endl;
				}
				*/
				return v;
			}
			beta = (v < beta) ? v : beta;

		}
	}
	(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
	str << "," << depth << ",";
	(v == numeric_limits<int>::max()) ? str << "Infinity," : str << v << ",";
	(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
	(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
	//printing board
	/*
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
			str << s.board[x][y];

		str << endl;
	}
	*/
	return v;
}
int max_ab(struct state s, int depth, int alpha, int beta, vector<int>opmove,bool dblpass)
{
	int v = INT_MIN;
	vector<vector<int> >my_tiles = s.find_mytile();
	vector<vector<int> >opp_tiles = s.find_opptile();
	if (dblpass)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		return terminal_value;

	}
	if (my_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		return terminal_value;

	}
	if (opp_tiles.empty())
	{
		int terminal_value = evaluate_board(s);
		(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		return terminal_value;

	}
	if (depth == max_depth)
	{
		int terminal_value = evaluate_board(s);
		(opmove[0]==-1)?str<<"pass":str << alphabet[opmove[1]] << opmove[0] + 1;
		str << "," << depth << ",";
		str << terminal_value << ",";
		(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
		(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
		//printing board
		/*for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
				str << s.board[x][y];

			str << endl;
		}*/
		return terminal_value;
	}
	vector<vector<int> >actions = find_legalmoves(s);
	if (actions.empty())
	{
		if (opmove[0] == -1)
		{
			//int terminal_value = evaluate_board(s);
			int min_call;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			str << v<< ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
			struct state temp;
			temp.opptile = s.tile;
			temp.tile = s.opptile;
			for (int p = 0; p < 8; p++)
				for (int q = 0; q < 8; q++)
					temp.board[p][q] = s.board[p][q];
			vector<int>dummy_move;
			dummy_move.push_back(-1); dummy_move.push_back(-1);
			min_call = min_ab(temp, depth + 1, alpha, beta, dummy_move, true);
			v = (min_call>v) ? min_call : v;
			if (v >=beta)
			{
				//str << "pruning here" << endl;
				(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
				str << "," << depth << ",";
				(v == INT_MIN) ? str << "-Infinity," : str << v << ",";
				(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
				(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
				return v;
			}
			alpha = (v > alpha) ? v : alpha;
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			str << v << ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;

			return v;

		}
		else
		{
			(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			(v == INT_MIN) ? str << "-Infinity," : str << v << ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
			//printing board
			/*for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
					str << s.board[x][y];

				str << endl;
			}*/
			struct state temp;
			temp.opptile = s.tile;
			temp.tile = s.opptile;
			for (int p = 0; p < 8; p++)
				for (int q = 0; q < 8; q++)
					temp.board[p][q] = s.board[p][q];
			vector<int>dummy_move;
			dummy_move.push_back(-1); dummy_move.push_back(-1);
			int min_call = min_ab(temp, depth + 1, alpha, beta, dummy_move,false);
			if (min_call > v)
				v = min_call;
			
			if (v >= beta)
			{
				//str << "pruning here" << endl;
				(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
				str << "," << depth << ",";
				(v == INT_MIN) ? str << "-Infinity," : str << v << ",";
				(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
				(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
				//printing board
				/*for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
						str << s.board[x][y];

					str << endl;
				}
				*/
				return v;
			}
			alpha = (v > alpha) ? v : alpha;


		}

	}
	else
	{
		vector<vector<int> >::iterator row;
		for (row = actions.begin(); row != actions.end(); row++)
		{
			struct state temp = result(s, *row);
			(opmove[0]==-1)?str<<"pass":str << alphabet[opmove[1]] << opmove[0] + 1;
			str << "," << depth << ",";
			(v == INT_MIN) ? str << "-Infinity," : str << v << ",";
			(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
			(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
			//printing board
			/*for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
					str << s.board[x][y];

				str << endl;
			}
			*/
			int min_call = min_ab(temp, depth + 1, alpha, beta, *row,false);
			if (min_call > v)
				v = min_call;
			
			if (v >= beta)
			{
				//str << "pruning here" << endl;
				(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
				str << "," << depth << ",";
				(v == INT_MIN) ? str << "-Infinity," : str << v << ",";
				(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
				(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
				//printing board
				/*for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
						str << s.board[x][y];

					str << endl;
				}
				*/
				return v;
			}
			alpha = (v > alpha) ? v : alpha;


		}
	}
	(opmove[0] == -1) ? str << "pass" : str << alphabet[opmove[1]] << opmove[0] + 1;
	str << "," << depth << ",";
	(v == INT_MIN) ? str << "-Infinity," : str << v << ",";
	(alpha == INT_MIN) ? str << "-Infinity," : str << alpha << ",";
	(beta == numeric_limits<int>::max()) ? str << "Infinity" << endl : str << beta << endl;
	//printing board
	/*for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
			str << s.board[x][y];

		str << endl;
	}*/
	return v;

}

int main()
{
	//struct state root;
	int task;
	//root.tile = 'X'; 
	
	char c;
	fstream f;
	f.open("input.txt", ios::in);
	f >> task;
	f >> root.tile;
	root.init_opptile();
	f >> max_depth;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			f>> root.board[i][j];
	f.close();
	f.open("output.txt", ios::out);
	switch (task)
	{
		case 1:
		{

			vector<int>best_move = minimax(root);
			
			
			if (best_move[0] == -1)
			{
				for (int p = 0; p < 8; p++)
				{
					for (int q = 0; q < 8; q++)
						f << root.board[p][q];
					f << endl;
				}
				break;
			}
			else
			{
				struct state ans = result(root, best_move);
				for (int p = 0; p < 8; p++)
				{
					for (int q = 0; q < 8; q++)
						f << ans.board[p][q];
					f << endl;
				}
				break;
			}
		}
		case 2:
		{
			
			vector<int>best_move = minimax(root);
			if (best_move[0] == -1)
			{
				for (int p = 0; p < 8; p++)
				{
					for (int q = 0; q < 8; q++)
						f << root.board[p][q];
					f << endl;
				}
				f << "Node,Depth,Value" << endl;
				f << str.str();
				break;
			}
			else
			{
				struct state ans = result(root, best_move);
				for (int p = 0; p < 8; p++)
				{
					for (int q = 0; q < 8; q++)
						f << ans.board[p][q];
					f << endl;
				}
				f << "Node,Depth,Value" << endl;
				f << str.str();
				break;

			}

		}
		case 3:
		{
			vector<int>best_move = abdriver(root);
			if (best_move[0] == -1)
			{
				for (int p = 0; p < 8; p++)
				{
					for (int q = 0; q < 8; q++)
						f << root.board[p][q];
					f << endl;
				}
				f << "Node,Depth,Value,Alpha,Beta" << endl;
				f << str.str();
				break;

			}
			else
			{
				struct state ans = result(root, best_move);
				for (int p = 0; p < 8; p++)
				{
					for (int q = 0; q < 8; q++)
						f << ans.board[p][q];
					f << endl;
				}
				f << "Node,Depth,Value,Alpha,Beta" << endl;
				f << str.str();
				break;
			}
		}
	}
	f.close();
	/*vector<vector<int>>x = find_legalmoves(root);
	vector<vector<int>>::iterator i;
	vector<int>::iterator j;
	for (i = x.begin(); i != x.end(); i++)
	{
		for (j = i->begin(); j != i->end(); j++)
		{
			cout << *j << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int f = 0; f < x.size(); f++)
	{

		struct state blah = result(root, x[f]);
		cout << "after move " << x[f][0] << "," << x[f][1] <<":"<< endl;
		for (int p = 0; p < 8; p++)
		{
			for (int q = 0; q < 8; q++)
				cout << blah.board[p][q];
			cout << endl;
		}
	}
	cout << "minimax" << endl;*/
	//vector<int>best_move = minimax(root);
	/*vector<int>best_move = abdriver(root);
	struct state ans = result(root, best_move);
	for (int p = 0; p < 8; p++)
	{
		for (int q = 0; q < 8; q++)
			cout << ans.board[p][q];
		cout << endl;
	}
	if (max_depth>1)
		cout << str.str();
	cin >> c;*/
	return 0;
}