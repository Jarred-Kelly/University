#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include "librarymanager.h"

void displayMenu()
{
    qDebug() << "\nLibrary Management System";
    qDebug() << "-------------------------";
    qDebug() << "1. Add a new book";
    qDebug() << "2. Add a new magazine";
    qDebug() << "3. Search by title";
    qDebug() << "4. Search by author";
    qDebug() << "5. Search by ID";
    qDebug() << "6. Borrow an item";
    qDebug() << "7. Return an item";
    qDebug() << "8. Display all items";
    qDebug() << "0. Exit";
    qDebug() << "-------------------------";
    qDebug() << "Enter your choice: ";
}

QString readLine()
{
    QTextStream qin(stdin);
    return qin.readLine().trimmed();
}

void waitForUserInput()
{
    qDebug() << "\nPress Enter to continue...";
    QTextStream qin(stdin);
    qin.readLine();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream qout(stdout);

    QString sDataFilePath = QDir::current().absoluteFilePath("C:\\data\\library_data.txt");
    LibraryManager oLibraryManager(sDataFilePath);
    bool lRunning = true;
    int iIssueNumber, iId;
    QString sTitle, sAuthor, sGenre, sDummy = "";

    while (lRunning) {
        displayMenu();
        int iChoice = readLine().toInt();

        switch (iChoice) {
        case 1: {
            qout << "Enter Book Title: ";
            qout.flush();
            sTitle = readLine();

            qout << "Enter Author's Name: ";
            qout.flush();
            sAuthor = readLine();

            qout << "Enter Book Genre: ";
            qout.flush();
            sGenre = readLine();

            oLibraryManager.addBook(sTitle, sAuthor, sGenre, sDummy);
            qDebug() << "Book added successfully!";

            break;
        }
        case 2: {
            qout << "Enter Magazine Title: ";
            qout.flush();
            sTitle = readLine();

            qout << "Enter Publisher's Name: ";
            qout.flush();
            sAuthor = readLine();

            qout << "Enter Issue Number: ";
            qout.flush();
            iIssueNumber = readLine().toInt();

            oLibraryManager.addMagazine(sTitle, sAuthor, iIssueNumber, sDummy);
            qDebug() << "Magazine added successfully!";

            break;
        }
        case 3: {

            qout << "Book Title: ";
            qout.flush();

            sTitle = readLine();

            auto sTitleResults = oLibraryManager.searchByTitle(sTitle);

            qDebug() << "Found" << sTitleResults.size() << "items.";
            for (const auto &oItem : sTitleResults) {
                qDebug() << oItem->displayInfo();
            }

            waitForUserInput();
            break;
        }
        case 4: {
            qout << "Author Name: ";
            qout.flush();

            sAuthor = readLine();

            auto sAuthorResults = oLibraryManager.searchByAuthor(sAuthor);

            qDebug() << "Found" << sAuthorResults.size() << "items.";
            for (const auto &oItem : sAuthorResults) {
                qDebug() << oItem->displayInfo();
            }

            waitForUserInput();
            break;
        }
        case 5: {
            qout << "Book/Magazine ID: ";
            qout.flush();

            iId = readLine().toInt();

            auto sItem = oLibraryManager.searchById(iId);

            if (sItem) {
                qDebug() << "Item found:";
                qDebug() << sItem->displayInfo();
            } else {
                qDebug() << "No item found with ID:" << iId;
            }

            waitForUserInput();
            break;
        }
        case 6: {
            qout << "Enter ID of item to borrow: ";
            qout.flush();
            iId = readLine().toInt();

            oLibraryManager.borrowItem(iId);

            waitForUserInput();
            break;
        }
        case 7: {
            qout << "Enter ID of item to return: ";
            qout.flush();
            iId = readLine().toInt();

            oLibraryManager.returnItem(iId);

            waitForUserInput();
            break;
        }
        case 8: {
            oLibraryManager.displayAllItems();

            waitForUserInput();
            break;
        }
        case 0: {
            qDebug() << "Exiting Library Management System...";
            lRunning = false;

            break;
        }
        default: {
            qDebug() << "Invalid choice. Please try again.";
        }
        }
    }

    return 0;
}
