#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class MediaItem {
public:
    std::string title;
    std::string author;
    int year;

    virtual void displayDetails() const = 0;

    void save(std::ofstream& file) const {
        file << title << "\n" << author << "\n" << year << "\n";
    }

    void load(std::ifstream& file) {
        std::getline(file, title);
        std::getline(file, author);
        file >> year;
        file.ignore();
    }
};

class Book : public MediaItem {
public:
    int numPages;
    std::string publisher;

    void displayDetails() const override {
        std::cout << "Title: " << title << "\nAuthor: " << author << "\nYear: " << year << "\nPages: " << numPages << "\nPublisher: " << publisher << "\n\n";
    }

    void save(std::ofstream& file) const {
        MediaItem::save(file);
        file << numPages << "\n" << publisher << "\n";
    }

    void load(std::ifstream& file) {
        MediaItem::load(file);
        file >> numPages;
        file.ignore();
        std::getline(file, publisher);
    }
};

class Magazine : public MediaItem {
public:
    int issueNumber;
    std::string theme;

    void displayDetails() const override {
        std::cout << "Title: " << title << "\nAuthor: " << author << "\nYear: " << year << "\nIssue Number: " << issueNumber << "\nTheme: " << theme << "\n\n";
    }

    void save(std::ofstream& file) const {
        MediaItem::save(file);
        file << issueNumber << "\n" << theme << "\n";
    }

    void load(std::ifstream& file) {
        MediaItem::load(file);
        file >> issueNumber;
        file.ignore();
        std::getline(file, theme);
    }
};

class Article : public MediaItem {
public:
    std::string publicationDate;
    std::string topic;

    void displayDetails() const override {
        std::cout << "Title: " << title << "\nAuthor: " << author << "\nYear: " << year << "\nPublication Date: " << publicationDate << "\nTopic: " << topic << "\n\n";
    }

    void save(std::ofstream& file) const {
        MediaItem::save(file);
        file << publicationDate << "\n" << topic << "\n";
    }

    void load(std::ifstream& file) {
        MediaItem::load(file);
        std::getline(file, publicationDate);
        std::getline(file, topic);
    }
};

template <typename T>
void addMediaItem(const T& item, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    item.save(file);
    file.close();
}

template <typename T>
void displayMediaItems(const std::string& filename) {
    std::ifstream file(filename);
    T item;
    while (!file.eof()) {
        item.load(file);
        if (!file.eof()) {
            item.displayDetails();
        }
    }
    file.close();
}

template <typename T>
void deleteMediaItem(const std::string& filename, const std::string& titleToDelete) {
    std::ifstream inFile(filename);
    std::ofstream outFile("temp.dat");

    T item;
    std::string line;
    bool found = false;
    while (!inFile.eof()) {
        item.load(inFile);
        if (item.title == titleToDelete) {
            found = true;
            item.displayDetails();
            char confirm;
            std::cout << "Do you want to delete this item? (y/n): ";
            std::cin >> confirm;

            if (confirm == 'n') {

            } else {
                for (int i = 0; i < 4; ++i) {
                    std::getline(inFile, line);
                }
            }
        } else {
            item.save(outFile);
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove(filename.c_str());
        rename("temp.dat", filename.c_str());
    } else {
        std::cout << "Item not found!\n";
        remove("temp.dat");
    }
}


int main() {
    int choice;
    do {
        std::cout << "\n\n\tMenu:\n"
                  << "1. Add Media Item\n"
                  << "2. Delete Media Item\n"
                  << "3. List Books\n"
                  << "4. List Magazines\n"
                  << "5. List Articles\n"
                  << "6. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int itemType;
                std::cout << "\n----------Select the type of Media Item--------\n"
                          << "1. Book\n"
                          << "2. Magazine\n"
                          << "3. Article\n"
                          << "Enter your choice: ";
                std::cin >> itemType;

                if (itemType == 1) {
                    Book newBook;
                    std::cout <<"\n--------------------------";
                    std::cout << "\n\tEnter Book details";
                    std::cout <<"\n---------------------------\n";
                    std::cin.ignore();
                    std::cout << "Title: ";
                    std::getline(std::cin, newBook.title);
                    std::cout << "Author: ";
                    std::getline(std::cin, newBook.author);
                    std::cout << "Year: ";
                    std::cin >> newBook.year;
                    std::cout << "Number of Pages: ";
                    std::cin >> newBook.numPages;
                    std::cout << "Publisher: ";
                    std::cin.ignore();
                    std::getline(std::cin, newBook.publisher);
                    std::cout <<"\n--------------------------";
                    addMediaItem(newBook, "Buku.dat");
                } else if (itemType == 2) {
                    Magazine newMagazine;
                    std::cout <<"\n--------------------------";
                    std::cout << "\n\tEnter Magazine details";
                    std::cout <<"\n---------------------------\n";
                    std::cin.ignore();
                    std::cout << "Title: ";
                    std::getline(std::cin, newMagazine.title);
                    std::cout << "Author: ";
                    std::getline(std::cin, newMagazine.author);
                    std::cout << "Year: ";
                    std::cin >> newMagazine.year;
                    std::cout << "Issue Number: ";
                    std::cin >> newMagazine.issueNumber;
                    std::cout << "Theme: ";
                    std::cin.ignore();
                    std::getline(std::cin, newMagazine.theme);
                    std::cout <<"--------------------------";
                    addMediaItem(newMagazine, "Majalah.dat");
                } else if (itemType == 3) {
                    Article newArticle;
                    std::cout <<"\n--------------------------";
                    std::cout << "\n\tEnter Article details";
                    std::cout <<"\n---------------------------\n";
                    std::cin.ignore();
                    std::cout << "Title: ";
                    std::getline(std::cin, newArticle.title);
                    std::cout << "Author: ";
                    std::getline(std::cin, newArticle.author);
                    std::cout << "Year: ";
                    std::cin >> newArticle.year;
                    std::cout << "Publication Date: ";
                    std::cin.ignore();
                    std::getline(std::cin, newArticle.publicationDate);
                    std::cout << "Topic: ";
                    std::getline(std::cin, newArticle.topic);
                    std::cout <<"--------------------------";
                    addMediaItem(newArticle, "Artikel.dat");
                } else {
                    std::cout << "Invalid choice!\n";
                }
                break;
            }
            case 2: {
                int itemType;
                std::cout << "\n-----Select the type of Media Item to delete----\n"
                          << "1. Book\n"
                          << "2. Magazine\n"
                          << "3. Article\n"
                          << "Enter your choice: ";
                std::cin >> itemType;

                std::string titleToDelete;
                std::cout << "\nEnter the title of the item to delete: ";
                std::cin.ignore();
                std::getline(std::cin, titleToDelete);
                std::cout <<"--------------------------\n";

                if (itemType == 1) {
                    deleteMediaItem<Book>("Buku.dat", titleToDelete);
                } else if (itemType == 2) {
                    deleteMediaItem<Magazine>("Majalah.dat", titleToDelete);
                } else if (itemType == 3) {
                    deleteMediaItem<Article>("Artikel.dat", titleToDelete);
                } else {
                    std::cout << "\nInvalid choice!\n";
                }
                break;
            }
            case 3: {
                std::cout << "\n----List of Books----\n";
                displayMediaItems<Book>("Buku.dat");
                break;
            }
            case 4: {
                std::cout << "\n----List of Magazines----\n";
                displayMediaItems<Magazine>("Majalah.dat");
                break;
            }
            case 5: {
                std::cout << "\n----List of Articles-----\n";
                displayMediaItems<Article>("Artikel.dat");
                break;
            }
            case 6:
                std::cout << "\nExiting...\n";
                break;
            default:
                std::cout << "\nInvalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
