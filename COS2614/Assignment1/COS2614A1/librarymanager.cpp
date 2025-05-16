#include "librarymanager.h"
#include <QDebug>
#include <QDir>
#include <QRegularExpression>
#include <iomanip> // For setw()
#include <sstream> // For stringstream

LibraryManager::LibraryManager(const QString &ipsDataFile)
{
    sDataFile = ipsDataFile;
    iNextId = 1;
    qDebug() << "LibraryManager initialized with data file:" << sDataFile;
    loadData();
}

LibraryManager::~LibraryManager()
{
    saveData();
}

void LibraryManager::loadData()
{
    QFile file(sDataFile);

    if (!file.exists()) {
        qDebug() << "Data file does not exist. Starting with empty library.";
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open data file for reading:" << file.errorString();
        return;
    }

    QTextStream qin(&file);
    oItems.clear();

    // Skip the header line
    if (!qin.atEnd()) {
        qin.readLine();
    }

    while (!qin.atEnd()) {
        QString sLine = qin.readLine();

        // Parse fixed-widthn field
        if (sLine.length() < 50) continue;

        // Extract Fields using the position
        int iId = sLine.mid(0, 5).trimmed().toInt();
        QString sType = sLine.mid(5, 10).trimmed();
        QString sTitle = sLine.mid(15, 30).trimmed();
        QString sAuthor = sLine.mid(45, 25).trimmed();
        QString sBorrowedStr = sLine.mid(70, 10).trimmed();
        bool lIsBorrowed = (sBorrowedStr == "Rented");

        // Update next ID based on highest ID found
        if (iId >= iNextId) {
            iNextId = iId + 1;
        }

        std::shared_ptr<LibraryItem> oItem;

        if (sType == "Book") {
            QString sGenre = sLine.mid(80).trimmed();
            oItem = std::make_shared<Book>(iId, sTitle, sAuthor, sGenre, sType);
        } else if (sType == "Magazine") {
            QString sIssueNumber = sLine.mid(80).trimmed();
            int iIssueNumber = 0;

            QRegularExpression re("(\\d+");
            QRegularExpressionMatch oMatch = re.match(sIssueNumber);

            if (oMatch.hasMatch()) {
                iIssueNumber = oMatch.captured(1).toInt();
            } else {
                bool lDirectConverstion;
                iIssueNumber = sIssueNumber.toInt(&lDirectConverstion);
                if (!lDirectConverstion) iIssueNumber = 0;
            }

            oItem = std::make_shared<Magazine>(iId, sTitle, sAuthor, iIssueNumber, sType);
        }

        if (oItem) {
            oItem->setBorrowed(lIsBorrowed);
            oItems.append(oItem);
        }
    }

    file.close();
    qDebug() << "Loaded" << oItems.size() << "items from file.";
}

void LibraryManager::saveData()
{
    QFile file(sDataFile);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open data file for writing:" << file.errorString();
        return;
    }

    QTextStream qout(&file);

    std::stringstream headerSS;
    headerSS << std::left
             << std::setw(5)  << "ID"
             << std::setw(10) << "TYPE"
             << std::setw(30) << "TITLE"
             << std::setw(25) << "AUTHOR"
             << std::setw(20) << "AVAILABILITY"
             << std::setw(20) << "ISSUE/GENRE";


    qout << QString::fromStdString(headerSS.str()) << "\n";

    for (const auto &oItem : oItems) {
        qout << oItem->toFileFormat() << "\n";
    }

    qout.flush();
    file.close();
    qDebug() << "Saved" << oItems.size() << "items to file:" << sDataFile;
}

void LibraryManager::addBook(const QString &ipsTitle,
                             const QString &ipsAuthor,
                             const QString &ipsGenre,
                             const QString &ipsType)
{
    auto oBook = std::make_shared<Book>(iNextId++, ipsTitle, ipsAuthor, ipsGenre, ipsType);
    oItems.append(oBook);
    saveData();
    qDebug() << "Book added:" << oBook->displayInfo();
}

void LibraryManager::addMagazine(const QString &ipsTitle,
                                 const QString &ipsAuthor,
                                 int ipiIssueNumber,
                                 const QString &ipsType)
{
    auto oMagazine = std::make_shared<Magazine>(iNextId++,
                                                ipsTitle,
                                                ipsAuthor,
                                                ipiIssueNumber,
                                                ipsType);
    oItems.append(oMagazine);
    saveData();
    qDebug() << "Magazine added:" << oMagazine->displayInfo();
}

QList<std::shared_ptr<LibraryItem>> LibraryManager::searchByTitle(const QString &ipsTitle) const
{
    QList<std::shared_ptr<LibraryItem>> sResults;

    for (const auto &oItem : oItems) {
        if (oItem->getTitle().toLower().contains(ipsTitle.toLower())) {
            sResults.append(oItem);
        }
    }

    return sResults;
}

QList<std::shared_ptr<LibraryItem>> LibraryManager::searchByAuthor(const QString &ipsAuthor) const
{
    QList<std::shared_ptr<LibraryItem>> sResults;

    for (const auto &oItem : oItems) {
        if (oItem->getAuthor().toLower().contains(ipsAuthor.toLower())) {
            sResults.append(oItem);
        }
    }

    return sResults;
}

std::shared_ptr<LibraryItem> LibraryManager::searchById(int ipiId) const
{
    for (const auto &oItem : oItems) {
        if (oItem->getId() == ipiId) {
            return oItem;
        }
    }

    return nullptr;
}

bool LibraryManager::borrowItem(int ipiId)
{
    auto oItem = searchById(ipiId);

    if (!oItem) {
        qDebug() << "Item with ID" << ipiId << "not found.";
        return false;
    }

    if (oItem->isBorrowed()) {
        qDebug() << "Item is already rented!";
        qDebug() << oItem->displayInfo();
        return false;
    }

    oItem->setBorrowed(true);
    saveData();
    qDebug() << "Item rented successfully!";
    qDebug() << oItem->displayInfo();
    return true;
}

bool LibraryManager::returnItem(int ipiId)
{
    auto oItem = searchById(ipiId);

    if (!oItem) {
        qDebug() << "Item with ID" << ipiId << "not found.";
        return false;
    }

    if (!oItem->isBorrowed()) {
        qDebug() << "Item is not currently borrowed!";
        qDebug() << oItem->displayInfo();
        return false;
    }

    oItem->setBorrowed(false);
    saveData();
    qDebug() << "Item returned successfully!";
    qDebug() << oItem->displayInfo();
    return true;
}

void LibraryManager::displayAllItems() const
{
    if (oItems.isEmpty()) {
        qDebug() << "The library is empty.";
        return;
    }

    qDebug() << "Library Inventory:";
    qDebug() << "------------------";

    std::stringstream headerSS;
    headerSS << std::left
             << std::setw(5)  << "ID"
             << std::setw(10) << "TYPE"
             << std::setw(30) << "TITLE"
             << std::setw(25) << "AUTHOR"
             << std::setw(20) << "AVAILABILITY"
             << std::setw(25) << "ISSUE/GENRE";

    qDebug().noquote() << QString::fromStdString(headerSS.str());

    for (const auto &oItem : oItems) {
        std::string sType = oItem->itemType().toStdString();
        std::string sTitle = oItem->getTitle().toStdString();
        std::string sAuthor = oItem->getAuthor().toStdString();
        std::string sStatus = oItem->isBorrowed() ? "Rented" : "Available";

        std::stringstream bodySS;
        bodySS << std::left
           << std::setw(5) << oItem->getId()
           << std::setw(10) << sType
           << std::setw(30) << (sTitle.length() > 27 ? sTitle.substr(0, 27) + "..." : sTitle)
           << std::setw(25) << (sAuthor.length() > 22 ? sAuthor.substr(0, 22) + "..." : sAuthor)
           << std::setw(20) << sStatus;

        // Add genre for books or issue number for magazines
        if (sType == "Book") {
            auto oBook = std::dynamic_pointer_cast<Book>(oItem);
            if (oBook) {
                bodySS << oBook->getGenre().toStdString();
            }
        } else if (sType == "Magazine") {
            auto oMagazine = std::dynamic_pointer_cast<Magazine>(oItem);
            if (oMagazine) {
                bodySS << std::to_string(oMagazine->getIssueNumber());
            }
        }

        qDebug().noquote() << QString::fromStdString(bodySS.str());
    }
}
