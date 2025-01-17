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
	Shop() {
		std::cout << "D - Dodaj do koszyka | P - Pokaz koszyk | U - Usun z koszyka | Z - Zaplac | W - Wyjdz | i - Instrukcja" << NL;
		showProducts();
	}
	static const int size = 5;
	std::string cart[5] = { "0","0","0","0","0" };
	const std::string all_items[size] = { "woda","chleb","sok","czekolada","maslo" };
	const float all_items_prices[size] = { 3,10,5,6,11 };
	int last_elem = 0;

	void showAll() {
		for (int i = 0; i < size; i++) {
			std::cout << all_items[i];
		}
	}

	void addToCart(std::string product) {
		for (int i = 0; i < size; i++) {
			if (product == all_items[i]) {
				allProducts[last_elem].name = product;
				allProducts[last_elem].price = all_items_prices[i];
				cart[last_elem] = product;
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
			std::cout << i + 1 << " | " << cart[i] << std::endl;
		}
		std::cout << NL;
	}

	void dropFromCart(std::string product) {
		for (int i = 0; i < size; i++) {
			if (cart[i] == product) {
				cart[i] = cart[last_elem - 1];
				allProducts[i] = allProducts[last_elem - 1];
				last_elem--;
				break;
			}
		}
	}

	void leaveShop() {
		isRunning = false;
	}

	void pay() {
		float cost = 0;
		float money = 0;
		for (int i = 0; i < last_elem; i++) {
			cost += allProducts[i].price;
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
private:
	Product allProducts[5];
};

int main() {
	Shop shop;
	std::string product;
	// 		std::cout << "D - Dodaj do koszyka | P - Pokaz koszyk | U - Usun z koszyka | Z - Zaplac | W - Wyjdz | L - Pokaz Produkty";;
	while (isRunning) {
		char key = _getch();
		if (key == 'd') {
			std::cout << "Wprowadz produkt: " << NL;
			std::cin >> product;
			std::cout << NL;
			shop.addToCart(product);
			shop.showCart();
		}
		if (key == 'p') {
			shop.showCart();
		}
		if (key == 'u') {
			std::cout << "Wprowadz produkt do usuniecia: " << NL;
			std::cin >> product;
			std::cout << NL;
			shop.dropFromCart(product);
		}
		if (key == 'z') {
			std::cout << "Jakim banknotem chcesz zaplacic: " << NL;
			shop.pay();

		}
		if (key == 'w') {
			shop.leaveShop();
			return 0;
		}
		if (key == 'l') {
			shop.showProducts();
		}
		if (key == 'i') {
			std::cout << "D - Dodaj do koszyka | P - Pokaz koszyk | U - Usun z koszyka | Z - Zaplac | W - Wyjdz | I - Instrukcja" << NL;
		}
	}
}
