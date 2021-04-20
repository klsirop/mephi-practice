#include "library.h"
#include <iostream>

int main() {
	Library my_lib;

	Book documentary("Riot Days", "Maria Alexina", "St Petersburg",
					Section::SPECIAL_LIT, true, "change your life");
	Book almanac("Hate", "moloco plus", "Moscow",
					Section::FICTION, false, "the fifth issue");
	Book health("Come as you are", "Emily Nagoski", "Mann, Ivanov and Ferber",
					Section::FICTION, true, "has many pictures");

	my_lib.AddBook(documentary);
	my_lib.AddBook(almanac);
	my_lib.AddBook(health);

	auto mybook = my_lib.GetBookByAuthor("Maria Alexina");
	std::cout << "Maria Alexina's book has name - " << mybook.name_ << std::endl;

	auto books = my_lib.GetBooksBySection(Section::FICTION);
	std::cout << "Books in Fiction Section: " << std::endl;
	for (auto it : books) {
		std::cout << it.author_ << " - " << it.name_ << std::endl;
	}

	books = my_lib.GetBooksByExisting(true);
	std::cout << "Existing books: " << std::endl;
	for (auto it : books) {
		std::cout << it.author_ << " - " << it.name_ << std::endl;
	}

	my_lib.RemoveBook(health);
	books = my_lib.GetBooksByExisting(true);
	std::cout << "Existing books (after removing):" << std::endl;
	for (auto it : books) {
		std::cout << it.author_ << " - " << it.name_ << std::endl;
	}

	my_lib.ChangeAuthor(almanac, "MOLOCO PLUS");
	books = my_lib.GetBooksBySection(Section::FICTION);
	std::cout << "Books in Fiction Section (after author change): " << std::endl;
	for (auto it : books) {
		std::cout << it.author_ << " - " << it.name_ << std::endl;
	}

	my_lib.AddBook(health);
	my_lib.SaveData("storage");
}
