#include <iostream>
#include <windows.h>
#include <conio.h>

int isRunning = true;

#define NL std::endl

namespace Color {
	void setColor(std::string text, int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		std::cout << text;
		SetConsoleTextAttribute(hConsole, 15);
	}
}

class Product {
public:
	Product() {};
	Product(std::string name, float price) :name(name), price(price) {
	}
	std::string name;
	float price;
};

class Shop {
public:
	static const int size = 5;

public:
	Shop() {
		showInstruction();
		showProducts();
	}

	void showAll() {
		for (int i = 0; i < size; i++) {
			std::cout << all_items[i];
		}
	}

	void addToCart() {
		std::cout << "Wprowadz produkt: " << NL;
		std::cin >> product;
		std::cout << NL;
		for (int i = 0; i < size; i++) {
			if (product == all_items[i]) {
				cart[last_elem].name = product;
				cart[last_elem].price = all_items_prices[i];
				last_elem++;
				break;
			}
		}
	}

	void showProducts() {
		std::cout << NL << "Produkty to: woda 3zl | chleb 10zl | sok 5zl | czekolada 6zl | maslo 11zl" << NL;
	}

	void showCart() {
		std::cout << NL;
		for (int i = 0; i < last_elem; i++) {
			std::cout << i + 1 << " | " << cart[i].name << std::endl;
		}
		std::cout << NL;
	}

	void dropFromCart() {
		std::cout << "Wprowadz produkt do usuniecia: " << NL;
		std::cin >> product;
		std::cout << NL;
		for (int i = 0; i < size; i++) {
			if (cart[i].name == product) {
				cart[i] = cart[last_elem - 1];
				last_elem--;
				break;
			}
		}
	}

	void leaveShop() {
		isRunning = false;
	}

	void pay() {
		if (last_elem == 0) {
			std::cout << "Nie masz niczego w koszyku." << NL;
		}
		else {
			std::cout << "Jakim banknotem chcesz zaplacic: " << NL;
			float cost = 0;
			float money = 0;
			for (int i = 0; i < last_elem; i++) {
				cost += cart[i].price;
			}
			while (money < cost) {
				std::cin >> money;
				if (money >= cost) {
					std::cout << "Kupiles " << last_elem << " produtow. Reszta to : " << money - cost << " zl";
				}
				else {
					std::cout << "za malo pieniedzy, potrzebujesz: " << cost << " zl" << NL;
				}
			}
		}
	}

	void showInstruction() {
		std::cout << "D - Dodaj do koszyka | P - Pokaz koszyk | U - Usun z koszyka | Z - Zaplac | W - Wyjdz | I - Instrukcja | L - Pokaz produkty" << NL;
	}

private:
	Product cart[size];
	std::string product;
	int last_elem = 0;
	const std::string all_items[size] = { "woda","chleb","sok","czekolada","maslo" };
	const float all_items_prices[size] = { 3,10,5,6,11 };
};

int main() {
	Shop shop;
	// 		std::cout << "D - Dodaj do koszyka | P - Pokaz koszyk | U - Usun z koszyka | Z - Zaplac | W - Wyjdz | L - Pokaz Produkty";;
	while (isRunning) {
		char key = _getch();
		switch (key) {
		case 'd':
			shop.addToCart();
			shop.showCart();
			break;
		case 'p':
			shop.showCart();
			break;
		case 'u':
			shop.dropFromCart();
			break;
		case 'z':
			shop.pay();
			break;
		case 'w':
			shop.leaveShop();
			return 0;
		case 'l':
			shop.showProducts();
			break;
		case 'i':
			shop.showInstruction();
			break;
		}
	}
}
