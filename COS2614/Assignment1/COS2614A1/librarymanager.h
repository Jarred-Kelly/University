// LIBRARYMANAGER_H
#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QFile>
#include <QList>
#include <QTextStream>
#include "book.h"
#include "magazine.h"
#include <memory>

class LibraryManager
{
private:
    QList<std::shared_ptr<LibraryItem>> oItems;
    QString sDataFile;
    int iNextId;

    void loadData();
    void saveData();

public:
    LibraryManager(const QString &ipsDataFile);
    ~LibraryManager();

    void addBook(const QString &ipsTitle,
                 const QString &ipsAuthor,
                 const QString &ipsGenre,
                 const QString &ipsType = "Book");
    void addMagazine(const QString &ipsTitle,
                     const QString &ipsAuthor,
                     int ipiIssueNumber,
                     const QString &ipsType = "Magazine");

    QList<std::shared_ptr<LibraryItem>> searchByTitle(const QString &ipsTitle) const;
    QList<std::shared_ptr<LibraryItem>> searchByAuthor(const QString &ipsAuthor) const;
    std::shared_ptr<LibraryItem> searchById(int ipiId) const;

    bool borrowItem(int ipiId);
    bool returnItem(int ipiId);

    void displayAllItems() const;
};

#endif // LIBRARYMANAGER_H
