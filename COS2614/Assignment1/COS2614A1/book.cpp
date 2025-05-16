#include "book.h"
#include <iomanip> // For setw()
#include <sstream> // For stringstream

Book::Book(int ipiId,
           const QString &ipsTitle,
           const QString &ipsAuthor,
           const QString &ipsGenre,
           const QString &ipsType)
    : LibraryItem(ipiId, ipsTitle, ipsAuthor, ipsType)
{
    sGenre = ipsGenre;
}

QString Book::getGenre() const
{
    return sGenre;
}

void Book::setGenre(const QString &ipsGenre)
{
    sGenre = ipsGenre;
}

QString Book::displayInfo() const
{
    return LibraryItem::displayInfo() + QString(" | Genre: %1").arg(sGenre);
}

QString Book::toFileFormat() const
{
    std::stringstream ss;
    ss << LibraryItem::toFileFormat().toStdString()
       << sGenre.toStdString();

    return QString::fromStdString(ss.str());
}

QString Book::itemType() const
{
    return "Book";
}
