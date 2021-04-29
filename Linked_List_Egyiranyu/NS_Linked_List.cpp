#include <iostream>
#include <algorithm>

struct Node
{
	int adat;
	Node *kovetkezo; 
};

void teljes_kereses(Node* listafej, int ertek)
{
	if(listafej == NULL)
		std::cout << "Üres a lista\n";
	
	auto x = listafej;

	while( x != NULL && x -> adat != ertek)
	{
		x = x -> kovetkezo;
	}

	if(x == NULL)
		std::cout << "Keresett érték: " << ertek << " <- nem található a listában..." <<  std::endl;
	else
		std::cout << "Keresett érték: " << x->adat << " <- található a listában..." << std::endl;

}

void beszur_eleje (struct Node** listafej, int ertek)
{
		struct Node* uj = new Node; 
		uj -> adat = ertek; 
		uj -> kovetkezo = (*listafej); 
		(*listafej) = uj; 
}

void beszur_vege (struct Node** listafej, int ertek)
{
	struct Node* uj = new Node;
	uj -> adat = ertek;
	uj -> kovetkezo = NULL;
	if ((*listafej) == NULL)
	{
		(*listafej) = uj;
	}
	else
	{
		auto x = (*listafej);
		while(x -> kovetkezo != NULL)
		{
			x = x -> kovetkezo;
		}
		x -> kovetkezo = uj;
	}
}

void bejar_elore(struct Node* listafej)
{
	auto x = listafej;
	while( x != NULL)
	{
		std::cout << x -> adat << "-->";
		x = x ->kovetkezo;
	}

	if(x == NULL)
		std::cout << " nil/null" << std::endl;
}


int main()
{
	struct Node* listafej = NULL;
	beszur_eleje(&listafej, 10);

	beszur_eleje(&listafej, 150);

	beszur_eleje(&listafej, 500);

	beszur_vege(&listafej, 333);

	std::cout << "Egyirányú láncolt lista: " << std::endl;
	bejar_elore(listafej);
	teljes_kereses(listafej,500);

	return 0;

}
