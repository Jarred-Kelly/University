#include "magazine.h"
#include <iomanip> // For setw()
#include <sstream> // For stringstream

Magazine::Magazine(int ipiId,
                   const QString &ipsTitle,
                   const QString &ipsAuthor,
                   int ipiIssueNumber,
                   const QString &ipsType)
    : LibraryItem(ipiId, ipsTitle, ipsAuthor, ipsType)
{
    iIssueNumber = ipiIssueNumber;
}

int Magazine::getIssueNumber() const
{
    return iIssueNumber;
}

void Magazine::setIssueNumber(int ipiIssueNumber)
{
    iIssueNumber = ipiIssueNumber;
}

QString Magazine::displayInfo() const
{
    return LibraryItem::displayInfo() + QString(" | Issue: %1").arg(iIssueNumber);
}

QString Magazine::toFileFormat() const
{
    std::stringstream ss;
    ss << LibraryItem::toFileFormat().toStdString()
       << iIssueNumber;

    return QString::fromStdString(ss.str());

}

QString Magazine::itemType() const
{
    return "Magazine";
}
