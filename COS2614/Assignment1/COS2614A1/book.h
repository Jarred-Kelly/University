// BOOK_H
#ifndef BOOK_H
#define BOOK_H

#include "libraryitem.h"

class Book : public LibraryItem
{
private:
    QString sGenre;

public:
    Book(int ipiId,
         const QString &ipsTitle,
         const QString &ipsAuthor,
         const QString &ipsGenre,
         const QString &ipsType);

    // Get Method
    QString getGenre() const;

    // Set Method
    void setGenre(const QString &ipsGenre);

    QString displayInfo() const override;
    QString toFileFormat() const override;
    QString itemType() const override;
};

#endif // BOOK_H
