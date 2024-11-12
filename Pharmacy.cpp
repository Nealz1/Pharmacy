#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include <string>

//reSharper disable ALL

class Lek;
class LekiNaZyczenie;
class Uzytkownik;
class Administrator;

using listaZyczen = std::vector<LekiNaZyczenie*>;
using DrugShop = std::vector<Lek*>;
using Ilosc = int;
using Tekst = std::string;

listaZyczen zyczenia;
DrugShop shop;

std::vector<Uzytkownik*> users;



class Uzytkownik
{
protected:
	int id = 0;
	static int licznik;
	std::string login;
	std::string password;
	char userType;

public:
	friend std::ostream& operator<<(std::ostream& os, const Uzytkownik& u1);

	virtual ~Uzytkownik() = default;

	Uzytkownik(const std::string& login, const std::string& password) : login(login), password(password) {
		id = licznik;
		licznik++;
	}

	Uzytkownik()
	{
	}

	std::string getLogin()
	{
		return login;
	}

	std::string getPassword()
	{
		return password;
	}

	int getId()
	{
		return id;
	}

	char getUserType()
	{
		return userType;
	}

	virtual void daneKonta() = 0;
};

class FunkcjeOgolne
{
public:
	bool weryfikacja(std::vector<Uzytkownik*>& users, char userType, Uzytkownik*& logedUserPtr)
	{
		std::string loginInsertedByUser, passwordInsertedByUser;
		std::cout << "Podaj login: ";
		std::cin >> loginInsertedByUser;
		std::cout << "Podaj hasło: ";
		std::cin >> passwordInsertedByUser;
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i]->getLogin() == loginInsertedByUser && users[i]->getPassword() == passwordInsertedByUser && users[i]->getUserType() == userType)
			{
				logedUserPtr = users[i];
				return true;
			}
		}
		return false;
	}


	bool zwrocNazweiIlosc(std::string& chooseName, int& chooseAmount)
	{
		std::cout << "Podaj nazwe produktu do dodania do koszyka: \n";
		std::cin >> chooseName;
		if (chooseName == "q")
		{
			return false;
		}
		std::cout << "Podaj ilość produktu do dodania do koszyka: \n";
		std::cin >> chooseAmount;
		if (chooseAmount == reinterpret_cast<int>("q"))
		{
			return false;
		}
		return true;
	}

	std::string zwrocDate()
	{
		std::string date;
		time_t currentTime = time(nullptr);

		tm currentTm;
		localtime_s(&currentTm, &currentTime);

		int year = currentTm.tm_year + 1900;
		int month = currentTm.tm_mon + 1;
		int day = currentTm.tm_mday;
		return date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
	}
};

FunkcjeOgolne narzedzia;

class Lek
{
private:
	float cena;
	int numerLeku = 0;
	static int licznik;

protected:
	Tekst nazwa;
	Ilosc ilosc;
	bool czyRecepta;

public:
	friend int operator+(const Lek& d1, const Lek& d2);
	friend int operator-(const Lek& d1, const Lek& d2);

	Lek()
	{
	}

	Lek(std::string nazwa, int ilosc, bool czyRecepta, float cena)
	{
		this->nazwa = nazwa;
		this->ilosc = ilosc;
		this->czyRecepta = czyRecepta;
		this->cena = cena;
		//numerLeku to numer ktory wpisuje uzytkownik jako recepte
		numerLeku = licznik;
		licznik++;

	}

	Lek(std::string name, int amount)
	{
		this->nazwa = name;
		this->ilosc = amount;
	}

	std::string dajNazwe()
	{
		return nazwa;
	}

	void ustawNazwe(std::string name)
	{
		this->nazwa = name;
	}

	int zwrocIlosc()
	{
		return ilosc;
	}

	void ustawIlosc(int ilosc)
	{
		this->ilosc = ilosc;
	}

	float zwrocCene()
	{
		return cena;
	}

	void UstawCene(float price)
	{
		this->cena = price;
	}

	bool zwrocCzyRecepta()
	{
		return czyRecepta;
	}

	void ustawCzyRecepta(bool czyRecepta)
	{
		this->czyRecepta = czyRecepta;
	}

	int zwrocNumerRecepty()
	{
		return numerLeku;
	}

	void ustawNumerRecepty(int numerRecepty)
	{
		this->numerLeku = numerRecepty;
	}
};


const std::string FILENAME_BILLS = "rachunki.txt";

template <class T>
class Writer
{
public:
	void zapiszPlikTekstowyDoPliku(std::vector<Lek*> shoppingCart, T shoppingCartValue)
	{
		std::ofstream myFile;
		myFile.open(FILENAME_BILLS, std::ios::app);

		for (int i = 0; i < shoppingCart.size(); i++)
		{
			myFile << "Nazwa: " << shoppingCart[i]->dajNazwe() << " Ilość: " << shoppingCart[i]->
				zwrocIlosc() <<
				" Cena :" << shoppingCart[i]->zwrocCene() << "Koszt: " << shoppingCart[i]->
				zwrocIlosc() * shoppingCart[i]->zwrocCene() << " \n";
		}
		myFile << "Wartość koszyka: " << shoppingCartValue << "\n";
		myFile.close();
	}

	std::vector<std::string> odczytajDaneZPliku()
	{
		std::vector<std::string> dane;

		std::ifstream myFile(FILENAME_BILLS);
		if (myFile.is_open())
		{
			std::string line;
			while (std::getline(myFile, line))
			{
				dane.push_back(line);
			}
			myFile.close();
		}
		else
		{
			std::cout << "Błąd podczas otwierania pliku." << std::endl;
		}

		return dane;
	}

};

class LekiNaZyczenie : public Lek
{
private:
	char orderStatus;

public:
	friend int operator+(const Lek& d1, const Lek& d2);
	friend int operator-(const Lek& d1, const Lek& d2);

	LekiNaZyczenie operator*()
	{
		return {};
	}

	LekiNaZyczenie()
	{
	}

	LekiNaZyczenie(std::string name, bool isPrescription)
	{
		this->nazwa = name;
		this->czyRecepta = isPrescription;

	}
	void setOrderStatus(char orderStatus) { this->orderStatus = orderStatus; }
	char getOrderStatus() { return orderStatus; }
};

std::ostream& operator<<(std::ostream& os, const Uzytkownik& u1);
int operator+(const Lek& d1, const Lek& d2);
int operator-(const Lek& d1, const Lek& d2);

std::ostream& operator<<(std::ostream& os, const Uzytkownik& u1)
{
	os << " Osoba: " << u1.login << " Hasło: " << u1.password << " ID: " << u1.id << "\n";
	return os;
}

int operator+(const Lek& d1, const Lek& d2)
{
	return d1.ilosc + d2.ilosc;
}

int operator-(const Lek& d1, const Lek& d2)
{
	return d1.ilosc - d2.ilosc;
}


class Farmaceuta : public Uzytkownik
{
private:

public:
	Farmaceuta(std::string login, std::string password)
	{
		userType = 'F';
		this->login = login;
		this->password = password;
		id = licznik;
		licznik++;
	}

	void daneKonta() override
	{
		std::cout << "Login: " << login << " ID: " << id << " Typ konta: " << userType << " \n";
	};

	void printMenu()
	{
		std::cout << "1. Dodaj leki z listy zyczen\n";
		std::cout << "2. Lista leków \n";
		std::cout << "3. Sklep\n";
		std::cout << "4. Dodaj lek\n";
		std::cout << "5. Usun lek\n";
		std::cout << "6. Wyloguj\n";
	}

	void wypiszLeki()
	{
		DrugShop drugstmp = shop;
		for (int i = 0; i < drugstmp.size(); i++)
		{
			std::cout << i << ". " + drugstmp[i]->dajNazwe() << " Ilość " << drugstmp[i]->zwrocIlosc() << " Cena:"
				<<
				drugstmp.
				at(i)->zwrocCene() << "\n";
		}
		drugstmp.clear();
	}

	void shopMenu()
	{

		bool isPrescription = false;
		std::vector<Lek*> shoppingCart;

		std::vector<int> numeryRecept = { 0 };


		int choose = 100;
		float shoppingCartValue = 0;
		std::vector<Lek*> shopListtmp = shop;
		while (choose != 0)
		{
			std::cout << "Dostępne produkty\n";
			for (int i = 0; i < shopListtmp.size(); i++)
			{
				if (isPrescription)
					shopListtmp[i]->zwrocCzyRecepta() ? "Tak" : "Nie";
				std::cout << i << ". " + shopListtmp[i]->dajNazwe() << " " << shopListtmp[i]->zwrocIlosc() <<
					" Cena: "
					<<
					shopListtmp[i]->zwrocCene() << " Tylko na recepte:" << (shopListtmp[i]->zwrocCzyRecepta()
						? " Tak"
						: " Nie") << "\n";
			}
			std::cout << "Koszyk: \n";

			for (int i = 0; i < shoppingCart.size(); i++)
			{
				std::cout << "Nazwa: " << shoppingCart[i]->dajNazwe() << " Ilość: " << shoppingCart[i]->
					zwrocIlosc() <<
					" Cena :" << shoppingCart[i]->zwrocCene() << " \n";
				shoppingCartValue += shoppingCart[i]->zwrocCene() * shoppingCart[i]->zwrocIlosc();
			}
			std::cout << "Wartość koszyka: " << shoppingCartValue << "\n";
			std::cout << "1. Dodaj do koszyka\n";
			std::cout << "2. Usuń z koszyka\n";
			std::cout << "3. Zatwierdź transakcje 4\n";
			std::cout << "4. Spełnij życzenia klientów *\n";
			std::cout << "0. Wyjdź\n";
			std::cin >> choose;
			switch (choose)
			{
			case 0:

				break;
			case 1:
				addToShoppingCart(shoppingCart, shopListtmp);
				break;
			case 2:
				deleteFromShoppingCart(shoppingCart, shopListtmp);
				break;
			case 3:
				//Zatwierdzanie
			{
				std::ofstream myFile;
				Writer<float> wr;
				wr.zapiszPlikTekstowyDoPliku(shoppingCart, shoppingCartValue);
				shop = shopListtmp;
				shoppingCart.clear();
				shoppingCartValue = 0;
				return;
			}
			break;
			case 4:
				spelnijZyczenie();
				break;
			default:
				std::cout << "Zły wybór\n";
				break;
			}
		}
	}

	void addToShoppingCart(std::vector<Lek*>& cart, std::vector<Lek*>& shopList)
	{
		std::string chooseName;
		int chooseAmount = 100;

		while (chooseAmount != 0)
		{
			std::cout << "Dostępne produkty\n";
			for (int i = 0; i < shopList.size(); i++)
			{
				std::cout << i << ". " + shopList[i]->dajNazwe() << " " << shopList[i]->zwrocIlosc() << " Cena: "
					<<
					shopList[i]->zwrocCene() << "Recepta: " << shopList[i]->zwrocCzyRecepta() << "\n";
			}
			if (!narzedzia.zwrocNazweiIlosc(chooseName, chooseAmount))
				return;
			for (int i = 0; i < shopList.size(); i++)
			{
				if (shopList[i]->dajNazwe() == chooseName && shopList.
					at(i)->zwrocIlosc() <= chooseAmount)
				{
					if (shopList[i]->zwrocCzyRecepta() == false)
					{
						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << shopList.
							at(i)->zwrocIlosc();
						auto tmp = new Lek(*shopList[i]);
						int j = 0;
						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + shopList[i]->zwrocIlosc());

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList.erase(shopList.begin() + i);
					}
					else//wariant z recepta
					{
						int numerReceptyPodanyPrzezUzytkownika;
						std::cout << "Podaj numer recepty:";
						std::cin >> numerReceptyPodanyPrzezUzytkownika;
						if (numerReceptyPodanyPrzezUzytkownika != shopList[i]->zwrocNumerRecepty())
						{
							std::cout << "ZŁY Numer recpety\n";
							break;
						}

						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << shopList.
							at(i)->zwrocIlosc();
						auto tmp = new Lek(*shopList[i]);
						int j = 0;

						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + shopList[i]->zwrocIlosc());

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList.erase(shopList.begin() + i);
					}

				}
				else if (shopList[i]->dajNazwe() == chooseName && shopList[i]->zwrocIlosc() > chooseAmount)
				{
					if (shopList[i]->zwrocCzyRecepta() == false)
					{
						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << chooseAmount;
						auto tmp = new Lek(*shopList[i]);
						tmp->ustawIlosc(chooseAmount);
						int j = 0;
						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + chooseAmount);

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList[i]->ustawIlosc(shopList[i]->zwrocIlosc() - chooseAmount);
					}
					else//wariant z recepta
					{
						int numerReceptyPodanyPrzezUzytkownika;
						std::cout << "Podaj numer recepty:";
						std::cin >> numerReceptyPodanyPrzezUzytkownika;
						if (numerReceptyPodanyPrzezUzytkownika != shopList[i]->zwrocNumerRecepty())
						{
							std::cout << "ZŁY Numer recpety\n";
							break;
						}

						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << shopList.
							at(i)->zwrocIlosc();
						auto tmp = new Lek(*shopList[i]);
						int j = 0;

						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + shopList[i]->zwrocIlosc());

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList.erase(shopList.begin() + i);
					}

				}
			}
		}
	}

	void deleteFromShoppingCart(std::vector<Lek*>& cart, std::vector<Lek*>& shopList)
	{
		std::string chooseName;
		int chooseAmount = 100;
		float shoppingCartValue = 0;
		while (chooseAmount != 0)
		{
			std::cout << "Koszyk: \n";

			for (int i = 0; i < cart.size(); i++)
			{
				std::cout << "Nazwa: " << cart[i]->dajNazwe() << " Ilość: " << cart[i]->zwrocIlosc() << " Cena :"
					<< cart
					[i]->zwrocCene() << " \n";
				shoppingCartValue += cart[i]->zwrocCene() * cart[i]->zwrocIlosc();
			}
			std::cout << "Wartość koszyka: " << shoppingCartValue << "\n";
			std::cout << "Podaj nazwe produktu do usunięcia z koszyka: \n";
			std::cin >> chooseName;
			if (chooseName == "0")
				return;
			std::cout << "Podaj ilość produktu do usunięcia z koszyka: \n";
			std::cin >> chooseAmount;
			if (chooseAmount == 0)
				return;
			for (int i = 0; i < cart.size(); i++)
				if (cart[i]->dajNazwe() == chooseName && cart[i]->zwrocIlosc() <= chooseAmount)
				{
					std::cout << "Usunięto z koszyka:\n";
					std::cout << "Nazwa: " << chooseName;
					std::cout << "Ilość: " << cart[i]->zwrocIlosc();
					int j = 0;
					auto tmp = new Lek(*cart[i]);
					shoppingCartValue -= cart[i]->zwrocCene() * cart[i]->zwrocIlosc();
					cart.erase(cart.begin() + i);
					for (j = 0; j < shopList.size(); j++)
						if (shopList[j]->dajNazwe() == tmp->dajNazwe() && shopList[j]->zwrocCzyRecepta() == tmp->
							zwrocCzyRecepta())
						{
							shopList[j]->ustawIlosc(shopList[j]->zwrocIlosc() + tmp->zwrocIlosc());
							break;
						}

					if (shopList.empty() || j == cart.size() || shopList[j]->dajNazwe() != tmp->dajNazwe())
						shopList.push_back(tmp);
				}
				else if (cart[i]->dajNazwe() == chooseName && cart[i]->zwrocIlosc() > chooseAmount)
				{
					std::cout << "Usunięto z koszyka:\n";
					std::cout << "Nazwa: " << chooseName;
					std::cout << "Ilość: " << chooseAmount;
					auto tmp = new Lek(*cart[i]);
					tmp->ustawIlosc(chooseAmount);
					int j = 0;
					for (j = 0; j < shopList.size(); j++)
						if (shopList[j]->dajNazwe() == tmp->dajNazwe() && shopList[j]->zwrocCzyRecepta() == tmp->
							zwrocCzyRecepta())
						{
							shopList[j]->ustawIlosc(shopList[j]->zwrocIlosc() + chooseAmount);

							break;
						}

					if (shopList.empty() || j == cart.size() || shopList[j]->dajNazwe() != tmp->dajNazwe())
						shopList.push_back(tmp);

					cart[i]->ustawIlosc(cart[i]->zwrocIlosc() - chooseAmount);
				}
			for (int i = 0; i < cart.size(); i++)
			{
				std::cout << "Nazwa: " << cart[i]->dajNazwe() << " Ilość: " << cart[i]->zwrocIlosc() << " Cena :"
					<< cart
					[i]->zwrocCene() << " \n";
				shoppingCartValue += cart[i]->zwrocCene() * cart[i]->zwrocIlosc();
			}
		}
	}

	void spelnijZyczenie()
	{
		char wybor;
		for (int i = 0; i < zyczenia.size(); i++)
		{
			std::cout << "Czy chcesz dać klientowi(t/n): " + zyczenia[i]->dajNazwe() << "\n";
			std::cin >> wybor;
			switch (wybor)
			{
			case 't':
			{
				float cena;
				int ilosc;
				bool czyNaRecepte;
				std::cout << "Jaką cene pragniesz?\n";
				std::cin >> cena;
				std::cout << "Podaj ilosc leku\n";
				std::cin >> ilosc;
				std::cout << "Czy produkt ma być dostępny dla śmiertelników nie znających numeru recepty?(t/n)\n";
				std::cin >> wybor;
				if (wybor == 't')
					czyNaRecepte = true;
				else
					czyNaRecepte = false;

				Lek* nowyLek = new Lek(zyczenia[i]->dajNazwe(), ilosc, czyNaRecepte, cena);
				shop.push_back(nowyLek);
				zyczenia.erase(zyczenia.begin() + i);
				break;
			}
			case 'n':
				break;
			default:
				std::cout << "Złą odpowiedz odbieram jako Nie\n";
				break;
			}
		}
		std::cout << "To wszystkie zyczenia klientow\n";
	}

	void dodajLek()
	{
		Lek* lekTmp = new Lek;
		std::string nazwa;
		int ilosc;
		float cena;
		bool czyNaRecepte;
		char wybor;

		std::cout << "Podaj nazwe leku \n";
		std::cin >> nazwa;
		lekTmp->ustawNazwe(nazwa);
		std::cout << "Podaj ilość leku\n";
		std::cin >> ilosc;
		lekTmp->ustawIlosc(ilosc);
		std::cout << "Podaj cene leku\n";
		std::cin >> cena;
		lekTmp->UstawCene(cena);
		std::cout << "Podaj czy na recepte(y/n)\n";
		std::cin >> wybor;
		if (wybor == 'y')
			czyNaRecepte = true;
		else
			czyNaRecepte = false;
		int numer;
		std::cout << "Podaj numer recepty jaki ma mieć\n";
		std::cin >> numer;
		lekTmp->ustawNumerRecepty(numer);

		lekTmp->ustawCzyRecepta(czyNaRecepte);
		shop.push_back(lekTmp);

	}

	void usunLek()
	{
		std::string nazwaLekuDoUsuniecia;
		std::cout << "Podaj nazwe leku do usunięcia: \n";
		std::cin >> nazwaLekuDoUsuniecia;
		for (int i = 0; i < shop.size(); i++)
		{
			if (shop[i]->dajNazwe() == nazwaLekuDoUsuniecia)
			{
				std::cout << "Usunięto: " + shop[i]->dajNazwe() + "\n";
				shop.erase(shop.begin() + i);
				return;
			}
		}
		std::cout << "Nie znaleziono!\n";
		return;
	}
};

class Klient : public Uzytkownik
{
private:

public:
	Klient(std::string login, std::string password)
	{
		userType = 'K';
		this->login = login;
		this->password = password;
		id = licznik;
		licznik++;
	}

	void daneKonta() override
	{
		std::cout << "Login: " << login << " ID: " << id << " Typ konta: " << userType << " \n";
	};

	void printMenu()
	{
		std::cout << "1. Sklep\n";
		std::cout << "2. Wyloguj\n";
	}


	void dodajLekDoListyZyczen()
	{
		LekiNaZyczenie* lekTmp = new LekiNaZyczenie;
		std::string nazwa;

		std::cout << "Podaj nazwe leku dla listy zyczen \n";
		std::cin >> nazwa;
		lekTmp->ustawNazwe(nazwa);
		zyczenia.push_back(lekTmp);
	}

	void menuSklepu()
	{

		bool isPrescription = false;
		std::vector<Lek*> shoppingCart;


		int choose = 100;
		float shoppingCartValue = 0;
		std::vector<Lek*> shopListtmp = shop;
		while (choose != 0)
		{
			std::cout << "Dostępne produkty\n";
			for (int i = 0; i < shopListtmp.size(); i++)
			{
				if (isPrescription)
					shopListtmp[i]->zwrocCzyRecepta() ? "Tak" : "Nie";
				std::cout << i << ". " + shopListtmp[i]->dajNazwe() << " " << shopListtmp[i]->zwrocIlosc() <<
					" Cena: "
					<<
					shopListtmp[i]->zwrocCene() << " Tylko na recepte:" << (shopListtmp[i]->zwrocCzyRecepta()
						? " Tak"
						: " Nie") << "\n";
			}
			std::cout << "Koszyk: \n";

			for (int i = 0; i < shoppingCart.size(); i++)
			{
				std::cout << "Nazwa: " << shoppingCart[i]->dajNazwe() << " Ilość: " << shoppingCart[i]->
					zwrocIlosc() <<
					" Cena :" << shoppingCart[i]->zwrocCene() << " \n";
				shoppingCartValue += shoppingCart[i]->zwrocCene() * shoppingCart[i]->zwrocIlosc();
			}
			std::cout << "Wartość koszyka: " << shoppingCartValue << "\n";
			std::cout << "1. Dodaj do koszyka\n";
			std::cout << "2. Usuń z koszyka\n";
			std::cout << "4. Zatwierdź transakcje 4\n";
			std::cout << "5. Nie ma leku, który potrzebujesz? Żaden problem dodaj go do listy zyczen, to może kiedys będzie dostępny \n";
			std::cout << "0. Wyjdź\n";
			std::cin >> choose;
			switch (choose)
			{
			case 0:

				break;
			case 1:
				addToShoppingCart(shoppingCart, shopListtmp);
				break;
			case 2:
				deleteFromShoppingCart(shoppingCart, shopListtmp);
				break;
			case 4:
				//Zatwierdzanie
			{
				std::ofstream myFile;
				Writer<float> wr;
				wr.zapiszPlikTekstowyDoPliku(shoppingCart, shoppingCartValue);
				//zapis listy sklepowej
				shop = shopListtmp;
				shoppingCart.clear();
				shoppingCartValue = 0;
				return;
			}
			break;
			case 5:
				dodajLekDoListyZyczen();
				break;
			default:
				std::cout << "Zły wybór\n";
				break;
			}
		}
	}

	void addToShoppingCart(std::vector<Lek*>& cart, std::vector<Lek*>& shopList)
	{
		std::string chooseName;
		int chooseAmount = 100;

		while (chooseAmount != 0)
		{
			std::cout << "Dostępne produkty\n";
			for (int i = 0; i < shopList.size(); i++)
			{
				std::cout << i << ". " + shopList[i]->dajNazwe() << " " << shopList[i]->zwrocIlosc() << " Cena: "
					<<
					shopList[i]->zwrocCene() << "Recepta: " << shopList[i]->zwrocCzyRecepta() << "\n";
			}
			if (!narzedzia.zwrocNazweiIlosc(chooseName, chooseAmount))
				return;
			for (int i = 0; i < shopList.size(); i++)
			{
				if (shopList[i]->dajNazwe() == chooseName && shopList.
					at(i)->zwrocIlosc() <= chooseAmount)
				{
					if (shopList[i]->zwrocCzyRecepta() == false)
					{
						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << shopList.
							at(i)->zwrocIlosc();
						auto tmp = new Lek(*shopList[i]);
						int j = 0;
						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + shopList[i]->zwrocIlosc());

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList.erase(shopList.begin() + i);
					}
					else//wariant z recepta
					{
						int numerReceptyPodanyPrzezUzytkownika;
						std::cout << "Podaj numer recepty:";
						std::cin >> numerReceptyPodanyPrzezUzytkownika;
						if (numerReceptyPodanyPrzezUzytkownika != shopList[i]->zwrocNumerRecepty())
						{
							std::cout << "ZŁY Numer recpety\n";
							break;
						}

						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << shopList[i]->zwrocIlosc();
						auto tmp = new Lek(*shopList[i]);
						int j = 0;

						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + shopList[i]->zwrocIlosc());

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList.erase(shopList.begin() + i);
					}

				}
				else if (shopList[i]->dajNazwe() == chooseName && shopList[i]->zwrocIlosc() > chooseAmount)
				{
					if (shopList[i]->zwrocCzyRecepta() == false)
					{
						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << chooseAmount;
						auto tmp = new Lek(*shopList[i]);
						tmp->ustawIlosc(chooseAmount);
						int j = 0;
						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + chooseAmount);

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList[i]->ustawIlosc(shopList[i]->zwrocIlosc() - chooseAmount);
					}
					else//wariant z recepta
					{
						int numerReceptyPodanyPrzezUzytkownika;
						std::cout << "Podaj numer recepty:";
						std::cin >> numerReceptyPodanyPrzezUzytkownika;
						if (numerReceptyPodanyPrzezUzytkownika != shopList[i]->zwrocNumerRecepty())
						{
							std::cout << "ZŁY Numer recpety\n";
							break;
						}

						std::cout << "Dodano do koszyka:\n";
						std::cout << "Nazwa: " << chooseName;
						std::cout << "Ilość: " << shopList.
							at(i)->zwrocIlosc();
						auto tmp = new Lek(*shopList[i]);
						int j = 0;

						for (j = 0; j < cart.size(); j++)
							if (cart[j]->dajNazwe() == tmp->dajNazwe() && cart[j]->zwrocCzyRecepta() == tmp->
								zwrocCzyRecepta())
							{
								cart[j]->ustawIlosc(cart[j]->zwrocIlosc() + shopList[i]->zwrocIlosc());

								break;
							}

						if (cart.empty() || j == cart.size() || cart[j]->dajNazwe() != tmp->dajNazwe())
							cart.push_back(tmp);

						shopList.erase(shopList.begin() + i);
					}

				}
			}
		}
	}

	void deleteFromShoppingCart(std::vector<Lek*>& cart, std::vector<Lek*>& shopList)
	{
		std::string chooseName;
		int chooseAmount = 100;
		float shoppingCartValue = 0;
		while (chooseAmount != 0)
		{
			std::cout << "Koszyk: \n";

			for (int i = 0; i < cart.size(); i++)
			{
				std::cout << "Nazwa: " << cart[i]->dajNazwe() << " Ilość: " << cart[i]->zwrocIlosc() << " Cena :"
					<< cart
					[i]->zwrocCene() << " \n";
				shoppingCartValue += cart[i]->zwrocCene() * cart[i]->zwrocIlosc();
			}
			std::cout << "Wartość koszyka: " << shoppingCartValue << "\n";
			std::cout << "Podaj nazwe produktu do usunięcia z koszyka: \n";
			std::cin >> chooseName;
			if (chooseName == "0")
				return;
			std::cout << "Podaj ilość produktu do usunięcia z koszyka: \n";
			std::cin >> chooseAmount;
			if (chooseAmount == 0)
				return;
			for (int i = 0; i < cart.size(); i++)
				if (cart[i]->dajNazwe() == chooseName && cart[i]->zwrocIlosc() <= chooseAmount)
				{
					std::cout << "Usunięto z koszyka:\n";
					std::cout << "Nazwa: " << chooseName;
					std::cout << "Ilość: " << cart[i]->zwrocIlosc();
					int j = 0;
					auto tmp = new Lek(*cart[i]);
					shoppingCartValue -= cart[i]->zwrocCene() * cart[i]->zwrocIlosc();
					cart.erase(cart.begin() + i);
					for (j = 0; j < shopList.size(); j++)
						if (shopList[j]->dajNazwe() == tmp->dajNazwe() && shopList[j]->zwrocCzyRecepta() == tmp->
							zwrocCzyRecepta())
						{
							shopList[j]->ustawIlosc(shopList[j]->zwrocIlosc() + tmp->zwrocIlosc());
							break;
						}

					if (shopList.empty() || j == cart.size() || shopList[j]->dajNazwe() != tmp->dajNazwe())
						shopList.push_back(tmp);
				}
				else if (cart[i]->dajNazwe() == chooseName && cart[i]->zwrocIlosc() > chooseAmount)
				{
					std::cout << "Usunięto z koszyka:\n";
					std::cout << "Nazwa: " << chooseName;
					std::cout << "Ilość: " << chooseAmount;
					auto tmp = new Lek(*cart[i]);
					tmp->ustawIlosc(chooseAmount);
					int j = 0;
					for (j = 0; j < shopList.size(); j++)
						if (shopList[j]->dajNazwe() == tmp->dajNazwe() && shopList[j]->zwrocCzyRecepta() == tmp->
							zwrocCzyRecepta())
						{
							shopList[j]->ustawIlosc(shopList[j]->zwrocIlosc() + chooseAmount);

							break;
						}

					if (shopList.empty() || j == cart.size() || shopList[j]->dajNazwe() != tmp->dajNazwe())
						shopList.push_back(tmp);

					cart[i]->ustawIlosc(cart[i]->zwrocIlosc() - chooseAmount);
				}
		}
	}

};

class Administrator : public Uzytkownik
{
private:

public:
	Administrator(std::string login, std::string password)
	{
		userType = 'A';
		this->login = login;
		this->password = password;
		id = licznik;
		licznik++;
	}

	void daneKonta() override
	{
		std::cout << "Login: " << login << " ID: " << id << " Typ konta: " << userType << " \n";
	}

	void odczytajDaneZArchiwum()
	{
		Writer<std::string> wr;
		std::vector<std::string> dane = wr.odczytajDaneZPliku();

		// Przetwarzanie odczytanych danych
		for (const auto& line : dane)
		{
			// Tutaj możesz wykonać odpowiednie operacje na odczytanych danych
			std::cout << line << std::endl;
		}

	}

	void printMenu()
	{
		int option;
		std::cout << "1. Dodaj użytkownika\n";
		std::cout << "2. Usuń użytkownika\n";
		std::cout << "3. Znajdz uzytkownika\n";
		std::cout << "4. Podaj liste użytkowników\n";
		std::cout << "5. Lista leków\n";
		std::cout << "6. Dodaj lek\n";
		std::cout << "7. Usun lek\n";
		std::cout << "8. Odczytaj dane z archiwum sprzedazy\n";
		std::cout << "9. Wyloguj\n";
	}

	void dodajUzytkownika(std::vector<Uzytkownik*>& users)
	{
		char choosedType = '1';
		while (choosedType != '0')
		{
			std::cout << "Wybierz typ konta:\n";
			std::cout << "[A] - Administrator\n";
			std::cout << "[F] - Farmaceuta \n";
			std::cout << "[K] - Klient\n";
			std::cout << "0. Wyjdź\n";
			std::cin >> choosedType;
			switch (choosedType)
			{
			case '0':
				break;
			case 'A':
			{
				std::string login, password;
				std::cout << "Podaj login: \n";
				std::cin >> login;
				std::cout << "Podaj hasło: \n";
				std::cin >> password;
				auto o = new Administrator(login, password);
				users.push_back(o);
			}
			break;
			case 'F':
			{
				std::string login, password;
				std::cout << "Podaj login: \n";
				std::cin >> login;
				std::cout << "Podaj hasło: \n";
				std::cin >> password;
				auto o = new Farmaceuta(login, password);
				users.push_back(o);
			}
			break;
			case 'K':
			{
				std::string login, password;
				std::cout << "Podaj login: \n";
				std::cin >> login;
				std::cout << "Podaj hasło: \n";
				std::cin >> password;
				auto o = new Klient(login, password);
				users.push_back(o);
			}
			break;
			default:
				std::cout << "Zły wybór\n";
				break;
			}
		}
	}

	void usunUzytkownika(std::vector<Uzytkownik*>& users)
	{
		int choosed;
		std::cout << "Podaj id uźytkownika do usunięcia: ";
		std::cin >> choosed;
		if (this->id == choosed)
		{
			std::cout << "Nie możesz usunąć konta na ktrórym aktualnie jesteś\n";
			return;
		}
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i]->getId() == choosed)
			{
				std::cout << "Usunięto: " << *users[i];
				users.erase(users.begin() + i);

				return;
			}
		}
		std::cout << "Nie znaleziono użytkownika o takim ID \n";
		system("pause");
	}

	void znajdzUzytkownika(std::vector<Uzytkownik*>& users)
	{
		int choosed;
		std::string nazwaUzytkownika;
		std::cout << "Podaj nazwe oraz id uzytkowika do znalezienia:\nNazwa:";
		std::cin >> nazwaUzytkownika;
		std::cout << "ID";
		std::cin >> choosed;
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i]->getId() == choosed && users[i]->getLogin() == nazwaUzytkownika)
			{
				std::cout << "Znaleziono wskazanego uzytkownika: " << *users[i];
				users[i]->daneKonta();
				return;
			}
		}
		std::cout << "Nie znaleziono użytkownika o takiej nazwie oraza ID\n";
		system("pause");
	}

	void printUsers(const std::vector<Uzytkownik*>& users)
	{
		for (int i = 0; i < users.size(); i++)
		{
			std::cout << *users[i] << "\n";
		}
	}

	void printListOfDrugs()
	{
		DrugShop drugstmp = shop;
		for (int i = 0; i < drugstmp.size(); i++)
		{
			std::cout << drugstmp[i]->zwrocNumerRecepty() << ". " + drugstmp[i]->dajNazwe() << " Ilość " << drugstmp[i]->zwrocIlosc() << " Cena:"
				<< drugstmp[i]->zwrocCene() << "\n";
		}
		drugstmp.clear();
	}

	void dodajLek()
	{
		Lek* lekTmp = new Lek;
		std::string nazwa;
		int ilosc;
		float cena;
		bool czyNaRecepte;
		char wybor;

		std::cout << "Podaj nazwe leku \n";
		std::cin >> nazwa;
		lekTmp->ustawNazwe(nazwa);
		std::cout << "Podaj ilość leku\n";
		std::cin >> ilosc;
		lekTmp->ustawIlosc(ilosc);
		std::cout << "Podaj cene leku\n";
		std::cin >> cena;
		lekTmp->UstawCene(cena);
		std::cout << "Podaj czy na recepte(y/n)\n";
		std::cin >> wybor;
		if (wybor == 'y')
			czyNaRecepte = true;
		else
			czyNaRecepte = false;
		int numer;
		std::cout << "Podaj numer recepty jaki ma mieć\n";
		std::cin >> numer;
		lekTmp->ustawNumerRecepty(numer);

		lekTmp->ustawCzyRecepta(czyNaRecepte);
		shop.push_back(lekTmp);

	}

	void usunLek()
	{
		std::string nazwaLekuDoUsuniecia;
		std::cout << "Podaj nazwe leku do usunięcia: \n";
		std::cin >> nazwaLekuDoUsuniecia;
		for (int i = 0; i < shop.size(); i++)
		{
			if (shop[i]->dajNazwe() == nazwaLekuDoUsuniecia)
			{
				std::cout << "Usunięto: " + shop[i]->dajNazwe() + "\n";
				shop.erase(shop.begin() + i);
				return;
			}
		}
		std::cout << "Nie znaleziono!\n";
		return;
	}

	void dodajLekDoListaZyczen()
	{
		LekiNaZyczenie* lekTmp = new LekiNaZyczenie;
		std::string nazwa;
		float cena;

		std::cout << "Podaj nazwe leku \n";
		std::cin >> nazwa;
		lekTmp->ustawNazwe(nazwa);
		std::cout << "Podaj cene leku\n";
		std::cin >> cena;
		lekTmp->ustawIlosc(cena);
		zyczenia.push_back(lekTmp);

	}

	void usunLekListaZyczen()
	{
		std::string nazwaLekuDoUsuniecia;
		std::cout << "Podaj nazwe leku do usunięcia: \n";
		std::cin >> nazwaLekuDoUsuniecia;
		for (int i = 0; i < zyczenia.size(); i++)
		{
			if (zyczenia[i]->dajNazwe() == nazwaLekuDoUsuniecia)
			{
				std::cout << "Usunięto: " + zyczenia[i]->dajNazwe() + "\n";
				zyczenia.erase(zyczenia.begin() + i);
				return;
			}
		}
		std::cout << "Nie znaleziono!\n";
		return;
	}
};

class Menu
{
public:
	void wypiszGlowneMenu(Uzytkownik* zalogowanyUzytkownikWskaznik)
	{


		int choose = 69;
		while (choose != 0)
		{
			std::cout << "Wybierz uźytkownika: \n";
			std::cout << "1. Administrator\n";
			std::cout << "2. Farmaceuta\n";
			std::cout << "3. Klient\n";
			std::cout << "0. Koniec programu\n";
			std::cout << "Opcja >> \n";
			std::cin >> choose;

			switch (choose)
			{
			case 0:
				exit(0);
				break;
			case 1:
				opcjeAdmina(zalogowanyUzytkownikWskaznik);
				break;
			case 2:
				opcjeFarmaceuty(zalogowanyUzytkownikWskaznik);
				break;
			case 3:
				opcjeKlienta(zalogowanyUzytkownikWskaznik);
				break;
			case 4:
				printf("Wylogowano\n");
				break;
			default:
				std::cout << "Zły wybór\n";
			}
		}

	}

	void opcjeAdmina(Uzytkownik* zalogowanyUzytkownikWskaznik)
	{
		if (narzedzia.weryfikacja(users, 'A', zalogowanyUzytkownikWskaznik))
		{
			auto adminPtr = dynamic_cast<Administrator*>(zalogowanyUzytkownikWskaznik);
			std::cout << "Pomyslne logowanie! \n";
			adminPtr->daneKonta();
			int option = 69;
			while (option != 0)
			{
				adminPtr->printMenu();
				std::cin >> option;
				switch (option)
				{
				case 1:
					adminPtr->dodajUzytkownika(users);
					break;
				case 2:
					adminPtr->usunUzytkownika(users);
					break;
				case 3:
					adminPtr->znajdzUzytkownika(users);
					break;
				case 4:

					adminPtr->printUsers(users);
					break;
				case 5:
					adminPtr->printListOfDrugs();
					break;
				case 6:
					adminPtr->dodajLek();
					break;
				case 7:
					adminPtr->usunLek();
					break;
				case 8:
					adminPtr->odczytajDaneZArchiwum();
					break;
				case 9://wylogowanie
					return;
				default:
					std::cout << "Zły wybór\n";
					break;
				}
			}
		}
		else
			std::cout << "Błędny login lub hasło\n";
	}
	void opcjeFarmaceuty(Uzytkownik* zalogowanyUzytkownikWskaznik)
	{
		if (narzedzia.weryfikacja(users, 'F', zalogowanyUzytkownikWskaznik))
		{
			auto pharmacistPtr = dynamic_cast<Farmaceuta*>(zalogowanyUzytkownikWskaznik);
			pharmacistPtr->daneKonta();
			int option = 100;

			while (option != 0)
			{
				pharmacistPtr->printMenu();
				std::cin >> option;
				switch (option)
				{
				case 1:
					pharmacistPtr->spelnijZyczenie();
					break;
				case 2:
					pharmacistPtr->wypiszLeki();
					break;
				case 3:
					pharmacistPtr->shopMenu();
					break;
				case 4:
					pharmacistPtr->dodajLek();
					break;
				case 5:
					pharmacistPtr->usunLek();
					break;
				case 6://wylogowanie
					return;
				default:
					std::cout << "Zły wybór\n";
					break;
				}
			}
		}
		else
			std::cout << "Błędny login lub hasło\n";
	}
	void opcjeKlienta(Uzytkownik* zalogowanyUzytkownikWskaznik)
	{
		if (narzedzia.weryfikacja(users, 'K', zalogowanyUzytkownikWskaznik))
		{
			auto klientptr = dynamic_cast<Klient*>(zalogowanyUzytkownikWskaznik);
			system("cls");
			klientptr->daneKonta();
			int option = 100;

			while (option != 0)
			{
				klientptr->printMenu();
				std::cin >> option;
				switch (option)
				{
				case 0:
					break;
				case 1:
					klientptr->menuSklepu();
					break;
				case 2://wylogowanie
					return;
				default:
					std::cout << "Zły wybór\n";
					break;
				}
			}
		}
		else
			std::cout << "Błędny login lub hasło";
	}
};

int Uzytkownik::licznik = 0;
int Lek::licznik = 0;

int main()
{
	setlocale(LC_ALL, "");

	auto a1 = Administrator("Karol", "1234");
	auto a2 = Farmaceuta("Kacper", "pass");
	auto a3 = Klient("Kamil", "pass");
	users.push_back(&a1);
	users.push_back(&a2);
	users.push_back(&a3);

	auto d1 = Lek("Maść na ból dupy", 69, true, 6900);
	auto d2 = Lek("Vocaler", 106, false, 123);
	auto d3 = Lek("Viagra", 39, true, 1);

	auto z1 = LekiNaZyczenie("Dolix", true);


	zyczenia.push_back(&z1);

	shop.push_back(&d1);
	shop.push_back(&d2);
	shop.push_back(&d3);
	Uzytkownik* zalogowanyUzytkownikWskaznik = nullptr;



	Menu m = Menu();
	m.wypiszGlowneMenu(zalogowanyUzytkownikWskaznik);

	return 0;
}
