#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

enum Section {
	SPECIAL_LIT,
	FICTION
};

class Book {
public:
	Book(std::string name, std::string author, std::string publish,
		Section section, bool existing, std::string opinion) {

		name_ = name;
		author_ = author;
		publish_ = publish;
		section_ = section;
		existing_ = existing;
		opinion_ = opinion;
	}

	std::string name_;
	std::string author_;
	std::string publish_;

	Section		section_;

	bool		existing_;
	std::string	opinion_;
};

class Library {
private:
	std::vector<class Book> storage_;

	auto FindBook(class Book &book) {
		auto it = std::find(storage_.begin(), storage_.end(), book);
		return it;
	}
public:
	void AddBook(class Book &book) {
		storage_.push_back(book);
	}
	void RemoveBook(class Book &book) {
		auto it = FindBook(book);
		if (it != storage_.end())
			storage_.erase(it);
	}

	void ChangeAuthor(class Book &book, std::string author) {
		auto it = FindBook(book);
		if (it != storage_.end())
			it->author_ = author;
	}

	Book GetBookByAuthor(std::string name) {
		auto it = std::find_if(storage_.begin(), storage_.end(),
			[name] (class Book &book) {
				return book.author_ == name;
			});
		return *it;
	}

	std::vector<Book> GetBooksBySection(Section section) {
		std::vector<Book> books;
		for (auto it : storage_) {
			if (it.section_ == section)
				books.push_back(it);
		}
		return books;
	}

	std::vector<Book> GetBooksByExisting(bool existing) {
		std::vector<Book> books;
		for (auto it : storage_) {
			if (it.existing_ == existing)
				books.push_back(it);
		}
		return books;
	}

	Book SaveData(std::string filename) {
		std::ofstream file;
		file.open(filename);

		file << "Author::Name::Publish::Section::Existing::Opinion" << std::endl;
		for (auto it : storage_) {
			file << it.author_ << "::" <<
			it.name_ << "::" << it.publish_ << "::";

			if (it.section_ == 0)
				file << "SPECIAL_LIT";
			else if (it.section_ == 1)
				file << "FICTION";
			file << "::";

			if (it.existing_)
				file << "EXISTS";
			else
				file << "NO";
			file << "::" << it.opinion_ << std::endl;
		}
		file.close();
	}
};

bool operator==(Book &lhs, const Book &rhs) {
	return	lhs.author_ == rhs.author_ &&
			lhs.name_ == rhs.name_ &&
			lhs.publish_ == rhs.publish_ &&
			lhs.section_ == rhs.section_ &&
			lhs.existing_ == rhs.existing_ &&
			lhs.opinion_ == rhs.opinion_;
}
