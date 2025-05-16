// LIBRARYITEM_H
#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QDebug>
#include <QString>
#include <iomanip> // For setw()
#include <sstream> // For stringstream

class LibraryItem
{
private:
    QString sTitle;
    QString sAuthor;
    QString sType;
    int iId;
    bool lIsBorrowed;

public:
    LibraryItem(int ipiId,
                const QString &ipsTitle,
                const QString &ipsAuthor,
                const QString &ipsType);

    // Get Methods
    QString getTitle() const;
    QString getAuthor() const;
    int getId() const;
    bool isBorrowed() const;

    // Set Methods
    void setTitle(const QString &ipsTitle);
    void setAuthor(const QString &ipsAuthor);
    void setId(int ipId);
    void setBorrowed(bool iplIsBorrowed);

    // Virtual Method
    virtual QString displayInfo() const;

    // File Handling Methods
    virtual QString toFileFormat() const;
    virtual QString itemType() const = 0;
};

#endif // LIBRARYITEM_H
