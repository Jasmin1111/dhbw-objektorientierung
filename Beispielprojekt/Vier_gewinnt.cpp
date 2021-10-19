#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <vector>
#include <iostream>
using namespace std;

class GameWindow : public Gosu::Window
{
public:

	GameWindow()
		: Window(800, 700)
	{
		set_caption("Vier_gewinnt");
	}

	void draw() override
	{
		graphics().draw_rect(50, 50, 700, 600, Gosu::Color::BLUE, 0);
	}

	void update() override
	{

	}
};

enum Farbe {
	schwarz,
	gelb,
	rot
};

void print_matrix(vector<vector<Farbe>>);
void sind_vier_elemente_gleich(Farbe, Farbe, Farbe, Farbe, bool&);
bool vier_gleiche_in_matrix(const vector< vector<Farbe> >&, size_t, size_t);

int main()
{
	/*
	vector<vector<Farbe>> matrix(6, vector<Farbe>(7));
	for (vector<Farbe> zeile : matrix)
	{
		for (Farbe elem : zeile)
		{
			elem = schwarz;
			cout << elem << " ";
		}
		cout << endl;
	}
	cout << endl;

	print_matrix(matrix);
	cout << endl;
	*/

	vector<vector<Farbe>> m(6, vector<Farbe>(7));

	for (int zeile = 0; (zeile < m.size()); zeile++)
	{
		for (int spalte = 0; (spalte < m.at(0).size()); spalte++)
		{
			if (spalte % 2 == 0)
			{
				m.at(zeile).at(spalte) = schwarz;
			}
			else
			{
				m.at(zeile).at(spalte) = schwarz;
			}
		}
	}
	print_matrix(m);
	cout << endl;
	cout << "\nEs gibt vier gleiche: " << vier_gleiche_in_matrix(m, 6, 7)<< endl;

	cout << "\n mit vier gelben Elementen" << endl;
	m.at(0).at(0) = gelb;
	m.at(0).at(1) = gelb;
	m.at(0).at(2) = gelb;
	m.at(0).at(3) = gelb;

	print_matrix(m);
	
	cout << "\nEs gibt vier gleiche: " << vier_gleiche_in_matrix(m, 6, 7) << endl;
	
	GameWindow window;
	window.show();
}

void print_matrix(vector<vector<Farbe>> m)
{
	for (vector<Farbe> zeile : m)
	{
		for (Farbe elem : zeile)
		{
			cout << elem << " ";
		}
		cout << endl;
	}
}

void sind_vier_elemente_gleich(Farbe c0, Farbe c1, Farbe c2, Farbe c3, bool& vier_gleiche)
{
	bool alle_gleich;
	alle_gleich = ((c0 == c1) && (c1 == c2) && (c2 == c3));
	if (alle_gleich && ((c1 == gelb) || (c1 == rot)))
	{
		vier_gleiche = true;
	}
	else
	{
		vier_gleiche = false;
	}
}

bool vier_gleiche_in_matrix(const vector< vector<Farbe> >& m, size_t max_zeile, size_t max_spalte)
{
	/*
	Farbe elem_oben;
	Farbe elem_unten;
	Farbe elem_rechts;
	Farbe elem_links;
	Farbe elem_or;
	Farbe elem_ur;
	Farbe elem_ol;
	Farbe elem_ul;
	*/

	bool vier_gleiche = false;

	//Farbe elem_current = m.at(0).at(0);
	for (int zeile = 0; (zeile < m.size()) && (!vier_gleiche); zeile++)
	{
		for (int spalte = 0; (spalte < m.at(0).size()) && (!vier_gleiche); spalte++)
		{
			Farbe elem_current = m.at(zeile).at(spalte);
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
