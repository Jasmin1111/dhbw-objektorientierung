#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <vector>
#include <iostream>
using namespace std;

enum Colour
{
	black,
	yellow,
	red
};

class GameWindow : public Gosu::Window
{
	double maus_pos_x;
	double maus_pos_y;
	Gosu::Image matrix;
public:
	GameWindow()
		: Window(900, 800), matrix("Matrix_ Hintergund leer.png")
	{
		set_caption("Vier_gewinnt");
	}

	void draw() override
	{
		//graphics().draw_rect(100, 150, 700, 600, Gosu::Color::BLUE, 0);
	}

	void display_square(int, int, Colour);
	void display_square(int line, int row, Colour c)
	{
		if (c == yellow)
		{
			for (int i = 0; i < row; i++)
			{
				graphics().draw_rect(100 + (line) * 100, 150 + (i + 1) * 100, 100, 100, Gosu::Color::YELLOW, 1);
			}
		}
		else if (c == red)
		{
			for (int i = 0; i < row; i++)
			{
				graphics().draw_rect(100 + (line) * 100, 150 + (i + 1) * 100, 100, 100, Gosu::Color::RED, 1);
			}
		}
	}

	void chip_position(int&, int&, Colour);
	void chip_position(int& line, int& row, Colour c)
	{

		maus_pos_x = input().mouse_x();
		maus_pos_y = input().mouse_y();

		int line_0 = -1; // line_0 is the inkremental number of the line (0 to 6) in row 0 
		int line_1 = -1;
		int line_2 = -1;
		int line_3 = -1;
		int line_4 = -1;
		int line_5 = -1;
		int line_6 = -1;

		if ((maus_pos_x) < (100) && ((maus_pos_x) < (200)) && (input().down(Gosu::MS_LEFT)))
		{
			line_0++;
			display_square(6 - line_0, 0, c);
			line = line_0;
			row = 0;
		}
		if ((maus_pos_x) < (200) && ((maus_pos_x) < (300)) && (input().down(Gosu::MS_LEFT)))
		{
			line_1++;
			display_square(6 - line_1, 1, c);
			line = line_1;
			row = 1;
		}
		if ((maus_pos_x) < (300) && ((maus_pos_x) < (400)) && (input().down(Gosu::MS_LEFT)))
		{
			line_2++;
			display_square(6 - line_2, 2, c);
			line = line_2;
			row = 2;
		}
		if ((maus_pos_x) < (400) && ((maus_pos_x) < (500)) && (input().down(Gosu::MS_LEFT)))
		{
			line_3++;
			display_square(6 - line_3, 3, c);
			line = line_3;
			row = 3;
		}
		if ((maus_pos_x) < (500) && ((maus_pos_x) < (600)) && (input().down(Gosu::MS_LEFT)))
		{
			line_4++;
			display_square(6 - line_4, 4, c);
			line = line_4;
			row = 4;
		}
		if ((maus_pos_x) < (600) && ((maus_pos_x) < (700)) && (input().down(Gosu::MS_LEFT)))
		{
			line_5++;
			display_square(6 - line_5, 5, c);
			line = line_5;
			row = 5;
		}
		if ((maus_pos_x) < (700) && ((maus_pos_x) < (800)) && (input().down(Gosu::MS_LEFT)))
		{
			line_6++;
			display_square(6 - line_4, 6, c);
			line = line_6;
			row = 6;
		}
	};

	void round();
	void round()
	{
		bool game_over;
		while (!game_over)
		{
			int line;
			int row;
			Colour c;
			int sports_move = 0; //sports_move == Spielzüge

			if (sports_move % 2 == 0) // bei der geraden Anzahl an Spielzügen ist der Rote dran
			{
				c = red;
			}
			else
			{
				c = yellow;
			}

			while (!game_over)
			{
				vector<vector<Colour>> matrix(6, vector<Colour>(7));
				for (vector<Colour> zeile : matrix)
				{
					for (Colour& elem : zeile)
					{
						elem = black;
					}
				}
				print_matrix(matrix);
				chip_position(line, row, c);
				matrix.at(line).at(row) = c;
			}
		}
	}

	void update() override
	{
		round();
	}
};

void print_matrix(vector<vector<Colour>>);
void sind_vier_elemente_gleich(Colour, Colour, Colour, Colour, bool&);
bool vier_gleiche_in_matrix(const vector< vector<Colour> >&, size_t, size_t);


int main()
{

	vector<vector<Colour>> matrix(6, vector<Colour>(7));
	for (vector<Colour> zeile : matrix)
	{
		for (Colour& elem : zeile)
		{
			elem = yellow;
			cout << elem << " ";
		}
		cout << endl;
	}
	cout << endl;

	print_matrix(matrix);
	cout << endl;


	vector<vector<Colour>> m(6, vector<Colour>(7));

	for (int zeile = 0; (zeile < m.size()); zeile++)
	{
		for (int spalte = 0; (spalte < m.at(0).size()); spalte++)
		{
			if (spalte % 2 == 0)
			{
				m.at(zeile).at(spalte) = black;
			}
			else
			{
				m.at(zeile).at(spalte) = black;
			}
		}
	}
	print_matrix(m);
	cout << endl;
	cout << "\nEs gibt vier gleiche: " << vier_gleiche_in_matrix(m, 6, 7) << endl;

	cout << "\n mit vier yellowen Elementen" << endl;
	m.at(0).at(0) = yellow;
	m.at(0).at(1) = yellow;
	m.at(0).at(2) = yellow;
	m.at(0).at(3) = yellow;

	print_matrix(m);

	cout << "\nEs gibt vier gleiche: " << vier_gleiche_in_matrix(m, 6, 7) << endl;

	GameWindow window;
	window.show();
}

void print_matrix(vector<vector<Colour>> m)
{
	for (vector<Colour> zeile : m)
	{
		for (Colour elem : zeile)
		{
			cout << elem << " ";
		}
		cout << endl;
	}
}

void sind_vier_elemente_gleich(Colour c0, Colour c1, Colour c2, Colour c3, bool& vier_gleiche)
{
	bool alle_gleich;
	alle_gleich = ((c0 == c1) && (c1 == c2) && (c2 == c3));
	if (alle_gleich && ((c1 == yellow) || (c1 == red)))
	{
		vier_gleiche = true;
	}
	else
	{
		vier_gleiche = false;
	}
}

bool vier_gleiche_in_matrix(const vector< vector<Colour> >& m, size_t max_zeile, size_t max_spalte)
{
	bool vier_gleiche = false;

	for (int zeile = 0; (zeile < m.size()) && (!vier_gleiche); zeile++)
	{
		for (int spalte = 0; (spalte < m.at(0).size()) && (!vier_gleiche); spalte++)
		{
			Colour elem_current = m.at(zeile).at(spalte);
			if ((spalte - 3) >= 0 && (zeile - 3) >= 0 && (!vier_gleiche)) // oben links sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile - 1).at(spalte - 1),
					m.at(zeile - 2).at(spalte - 2), m.at(zeile - 3).at(spalte - 3), vier_gleiche);
			}
			if ((spalte == 0) && (zeile - 3) >= 0 && (!vier_gleiche)) // oberhalb sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile - 1).at(spalte),
					m.at(zeile - 2).at(spalte), m.at(zeile - 3).at(spalte), vier_gleiche);
			}
			if ((spalte + 3) < max_spalte && (zeile - 3) >= 0 && (!vier_gleiche)) // oben rechts sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile - 1).at(spalte + 1),
					m.at(zeile - 2).at(spalte + 2), m.at(zeile - 3).at(spalte + 3), vier_gleiche);
			}
			if ((spalte - 3) >= 0 && (zeile == 0) && (!vier_gleiche)) // links sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile).at(spalte - 1),
					m.at(zeile).at(spalte - 2), m.at(zeile).at(spalte - 3), vier_gleiche);
			}
			if ((spalte + 3) < max_spalte && (zeile == 0) && (!vier_gleiche)) // rechts sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile).at(spalte + 1),
					m.at(zeile).at(spalte + 2), m.at(zeile).at(spalte + 3), vier_gleiche);
			}
			if ((spalte - 3) >= 0 && (zeile + 3) < max_zeile && (!vier_gleiche)) // unten links sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile + 1).at(spalte - 1),
					m.at(zeile + 2).at(spalte - 2), m.at(zeile + 3).at(spalte - 3), vier_gleiche);
			}
			if ((spalte == 0) && (zeile + 3) < max_zeile && (!vier_gleiche)) // unterhalb sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile + 1).at(spalte),
					m.at(zeile + 2).at(spalte), m.at(zeile + 3).at(spalte), vier_gleiche);
			}
			if ((spalte + 3) < max_spalte && (zeile + 3) < max_zeile && (!vier_gleiche)) // unten rechts sind vier Elemente möglich
			{
				sind_vier_elemente_gleich(elem_current, m.at(zeile + 1).at(spalte + 1),
					m.at(zeile + 2).at(spalte + 2), m.at(zeile + 3).at(spalte + 3), vier_gleiche);
			}
			if (vier_gleiche)
			{
				break;
			}
		}
	}
	return vier_gleiche;
}