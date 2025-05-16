#include "libraryitem.h"

LibraryItem::LibraryItem(int ipiId,
                         const QString &ipsTitle,
                         const QString &ipsAuthor,
                         const QString &ipsType)
{
    iId = ipiId;
    sTitle = ipsTitle;
    sAuthor = ipsAuthor;
    sType = ipsType;
    lIsBorrowed = false;
}

QString LibraryItem::getTitle() const
{
    return sTitle;
}

QString LibraryItem::getAuthor() const
{
    return sAuthor;
}

int LibraryItem::getId() const
{
    return iId;
}

bool LibraryItem::isBorrowed() const
{
    return lIsBorrowed;
}

void LibraryItem::setTitle(const QString &ipsTitle)
{
    sTitle = ipsTitle;
}

void LibraryItem::setAuthor(const QString &ipsAuthor)
{
    sAuthor = ipsAuthor;
}

void LibraryItem::setId(int ipiId)
{
    iId = ipiId;
}

void LibraryItem::setBorrowed(bool iplIsBorrowed)
{
    lIsBorrowed = iplIsBorrowed;
}

QString LibraryItem::displayInfo() const
{
    return QString("ID: %1 | Title: %2 | Author: %3 | Status: %4")
        .arg(iId)
        .arg(sTitle)
        .arg(sAuthor)
        .arg(lIsBorrowed ? "Rented" : "Available");
}

QString LibraryItem::toFileFormat() const
{
    std::stringstream ss;
    ss << std::left
       << std::setw(5)  << iId
       << std::setw(10) << itemType().toStdString()
       << std::setw(30) << sTitle.toStdString()
       << std::setw(25) << sAuthor.toStdString()
       << std::setw(20) << (lIsBorrowed ? "Rented" : "Available");

    return QString::fromStdString(ss.str());

}
