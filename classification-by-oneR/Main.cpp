#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Row
{
	int x[4];
	int y;
};

struct Rule
{
	int match;
	int total = -1;

	int i, value;
};

vector<Row> rows;
Rule rules[3];

void loadRows()
{
	ifstream inp("inp.txt");

	while (inp)
	{
		Row nextRow;
		for (int i = 0; i < 4; i++)
		{
			inp >> nextRow.x[i];
		}
		inp >> nextRow.y;

		rows.push_back(nextRow);
	}

	inp.close();
}

int main()
{
	loadRows();

	for (int classNumber = 0; classNumber < 3; classNumber++)
	{
		for (int col = 0; col < 4; col++)
		{
			for (int value = 1; ; value++)
			{
				int currMatch = 0, currTotal = 0;

				for (int r = 0; r < rows.size(); r++)
				{
					if (rows[r].x[col] == value)
					{
						currTotal++;
						if (rows[r].y != classNumber) currMatch++;
					}
				}

				if (currTotal == 0) break;

				Rule& currError = rules[classNumber];

				if (currError.total == -1 ||
					currMatch / (double)currTotal <
					currError.match / (double)currError.total ||
					(currMatch / (double)currTotal ==
					currError.match / (double)currError.total &&
					currTotal > currError.total))
				{
					currError.match = currMatch;
					currError.total = currTotal;
					currError.i = col;
					currError.value = value;
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		cout << i << " " 
			<< rules[i].i << " " 
			<< rules[i].value << " " 
			<< rules[i].match << "/" << rules[i].total << endl;
	}
}