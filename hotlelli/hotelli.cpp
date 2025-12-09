// hotlelli.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<string>
#include<limits>

using namespace std;


//hotellihuoneiden objekti
struct huone {
	string nimi;
	int varausnumero;
	int huoneennumero;
	bool varattu = 0;
	int yomaara;
};
//Alustetaan käytettäviä funktioita
void varaus(vector<huone>& huoneetlista, int hinta);
void etsivnum(vector<huone>& huoneetlista);
void etsinim(vector<huone>& huoneetlista);
void peruvaraus(vector<huone>& huoneetlista);



int main()
{
	setlocale(LC_ALL, "FI-fi");
	int valinta;
	bool lopeta;

	//Arvotaan huoneiden lukumäärä ja hinta
	const int huoneet = rand() % 41 + 30;
	const int hinta = rand() % 21 + 80;


	vector<huone> huoneetlista;

	//luodaan huotellihuoneet
	for (int i = 0; i <= huoneet; i++) {
		huoneetlista.push_back({"",0,i,0,0});
	}


	//Menu rakenne ja syötteen tarkistus

		do {
			lopeta = false;
			cout << "\n \n Hotelli Ankka \n 1. Varaa huone \n 2. Etsi varausnumerolla \n 3. Etsi nimellä \n 4. Peru varaus \n 5. Lopeta \n";
			cin >> valinta;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			//Tarkistetaan että syöte on numero
			if (cin.fail()) {
				cout << "\n Virhe syötä numero! \n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}

		switch (valinta) {
		case 1: 
			varaus(huoneetlista, hinta);
			break;
		case 2:
			etsivnum(huoneetlista);
			break;
		case 3:
			etsinim(huoneetlista);
			break;
		case 4:
			peruvaraus(huoneetlista);
			break;
		case 5:
			lopeta = true;
			break;
		default: 
			cout << "\n Virheellinen valinta \n";
		}

	} while (!lopeta);
	return 0;
}


//Huoneen varauksen funktio
void varaus(vector<huone>& huoneetlista, int hinta) {
	int varattuja = 0;
	string nimi;
	int yot;
	bool oikein;

	srand(time(0));

	//Ilmoitetaan perustietoja
	cout << "\n Vapaita huoneita on: ";
	for (int n = 0; n < huoneetlista.size(); n++) {
		if (!huoneetlista[n].varattu) {
			varattuja++;
		}
	}
	cout << varattuja<< " kpl";
	cout << "\n Yhden yön hinta on: " << hinta << " euroa" << endl;

	//kysytään käyttäjältä nimi ja montako yötä yövytään ja tarkistetaan onko syöte oikein, jos tyhjä nimi varaus nimellä tyhja

	do {
		oikein = true;

		cout << "\n Anna nimesi: ";
		getline(cin, nimi);

		if (nimi.empty()) {
			nimi = "Tyhja";
		}

		while (true) {
			cout << "\n Onko nimi: " << nimi << " oikein paina 1 jos kyllä, paina 0 jos ei : ";
			cin >> oikein;


			if (cin.fail() || (oikein != 0 && oikein != 1)) {
				cout << "\n Syötä joko 1 tai 0";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			break;
		}
	} while (!oikein);


	do {
		oikein = true;
		cout << "\n Montako yötä haluat varata: ";
		cin >> yot;

		if (cin.fail() || yot <= 0) {
			cout << "\n Anna positiivinen kokonaisluku";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			oikein = false;
		}
		else {

			while (true) {
				cout << "\n Haluat varata " << yot << " yötä? Vastaa 1 jos kyllä, 0 jos ei: ";
				cin >> oikein;


				if (cin.fail() || (oikein != 0 && oikein != 1)) {
					cout << "Syötä joko 1 tai 0";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				break;
			}
		}
	} while (!oikein);



	bool error;
	//varataan ensimmäinen vapaa huone
	for (int n = 0; n < huoneetlista.size(); n++) {
		if (!huoneetlista[n].varattu) {
			huoneetlista[n].varattu = true;
			huoneetlista[n].nimi = nimi;
			huoneetlista[n].varausnumero = rand() % 90000 + 10000;
			huoneetlista[n].yomaara = yot;

			//tarkistetaan varausnumero
				for (int i = 0; i < huoneetlista.size(); i++) {
					if (i == n) { continue; }
					if (huoneetlista[n].varausnumero == huoneetlista[i].varausnumero) {
						error = false;
						break;
					}
				}
			
			
			//ilmoitetaan onnistuneesta varauksesta
			cout << "\n Varaus onnistui huoneeseen: " << huoneetlista[n].huoneennumero<< " Nimellä: "<< nimi;
			cout << "\n Varausnumerosi on: " << huoneetlista[n].varausnumero;
			cout << "\n Yöpymesi maksaa: " << hinta * yot << " euroa";

			break;
		}
	}
}


//etsitään huone varausnumerolla
void etsivnum(vector<huone>& huoneetlista) {
	int varausnum;

	while(true) {

		//kysytään varausnumero ja syötteentarkistus
		cout << "\n Syötä varausnumerosi: ";
		cin >> varausnum;

		if (cin.fail() || varausnum<=0) {
			cout << "\n Virhe syötä positiivinen kokonaisluku! \n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}


		//etsitään huonetta varausnumerolla, jos löytyi annetaan huoneen tiedot jos ei takaisin alkuvalikkoon.
		for (int n = 0; n < huoneetlista.size(); n++) {
			if (huoneetlista[n].varausnumero == varausnum) {
				cout << "\n Varausnumerolla löytyi huone numero " << huoneetlista[n].huoneennumero;
				cout << "\n Huone on varattu nimellä: " << huoneetlista[n].nimi;
				cout << "\n Huone on varattu " << huoneetlista[n].yomaara << " yöksi";
				return;
			}
		}
		cout << "\n Varausnumerollasi ei ole varausta";
		return;

	}
}


//etsitään varattu huone nimellä
void etsinim(vector<huone>& huoneetlista) {
	string hakunimi;
	bool loyty = false;

	while (true) {
		//kysytään nimi
		cout << "\n Anna nimi jolla haetaan huonevarausta: ";
		getline(cin, hakunimi);

		if (hakunimi.empty()) {
			cout << "Syötä nimi \n";
		}
		else { break; }
	}


	//etsitään huone, jos löytyy vastauksena huoneen tiedot, jos ei takaisin alkuvalikkoon
	
		for (int n = 0; n < huoneetlista.size(); n++) {
			if (!huoneetlista[n].nimi.compare(hakunimi)) {
				cout << "\n Nimelle löytyi varattu huone numero " << huoneetlista[n].huoneennumero;
				cout << "\n Huoneen varausnumero on " << huoneetlista[n].varausnumero;
				cout << "\n Huone on varattu " << huoneetlista[n].yomaara << " yöksi \n";
				loyty = true;
			}
		}
		if (!loyty) {
			cout << "\n Nimellä ei löytynyt varattua huonetta.";
		}

}


//Peruutetaan varaus vain varausnumerolla, koska nimiä voi olla samoja
void peruvaraus(vector<huone>& huoneetlista) {
	int varausnum;


	//kysytään varausnumero ja virheentarkisus
	while(true) {

		cout << "Syötä varausnumerosi, jolle haluat peruuttaa varauksesi: ";
		cin >> varausnum;

		if (cin.fail() || varausnum <= 0) {
			cout << "\n Virhe syötä positiivinen kokonaisluku! \n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}


		//Tyhjenneään varatun huoneen tiedot ja ilmoitetaan onnisuneesta varauksesta sitten takaisin vlaikkoon
		for (int n = 0; n < huoneetlista.size(); n++) {
			if (huoneetlista[n].varausnumero == varausnum) {
				huoneetlista[n].varattu = false;
				huoneetlista[n].nimi = "";
				huoneetlista[n].yomaara = 0;
				huoneetlista[n].varausnumero = 0;

				cout << "\nVarauksesi " << varausnum << " on peruttu \n";

				return;
			}
		}
		cout << "\n Varausnumerollasi ei löytynyt varausta.";
		return;

	}
}
