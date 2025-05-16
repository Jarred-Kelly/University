// MAGAZINE_H
#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"

class Magazine : public LibraryItem
{
private:
    int iIssueNumber;

public:
    Magazine(int ipiId,
             const QString &ipsTitle,
             const QString &ipsAuthor,
             int ipiIssueNumber,
             const QString &ipsType);

    // Get Method
    int getIssueNumber() const;

    // Set Method
    void setIssueNumber(int ipiIssueNumber);

    QString displayInfo() const override;
    QString toFileFormat() const override;
    QString itemType() const override;
};

#endif // MAGAZINE_H
