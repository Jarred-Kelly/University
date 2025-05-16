Library Management System
Project Overview
The Library Management System is a C++ application built with Qt that provides a comprehensive solution for managing library resources. This console-based application allows librarians and users to manage books and magazines, including adding new items, searching the catalog, and handling the borrowing and returning process.

Features
Item Management: Add books and magazines to the library catalog
Search Functionality: Search for items by title, author, or ID
Borrowing System: Track the availability of items and manage the borrowing/returning process
Data Persistence: Save library data to files for persistent storage across sessions
Console Interface: User-friendly menu-driven interface for all operations
System Architecture
Class Structure
The system follows Object-Oriented Programming principles with the following class hierarchy:

LibraryItem (Abstract Base Class)
Contains common properties: title, author, ID, borrowing status
Defines interface methods for all library items
Book (Derived Class)
Inherits from LibraryItem
Adds genre-specific functionality
Magazine (Derived Class)
Inherits from LibraryItem
Adds issue number-specific functionality
LibraryManager
Manages the collection of library items
Handles file operations and search functionality
Setup Instructions
Prerequisites
Qt Creator (version 5.12 or higher recommended)
C++ compiler with C++11 support
Qt development libraries
Step 1: Install Qt Creator
Download Qt Creator from the official Qt website
Follow the installation instructions for your operating system
Make sure to include the Qt development libraries during installation
Step 2: Set Up the Project
Open Qt Creator
Go to File > New File or Project
Select "Qt Console Application" and click "Choose..."
Name your project (e.g., "LibraryManagementSystem") and set the location
Follow the wizard, selecting your preferred kit
Click "Finish" to create the project
Step 3: Add Source Files
Right-click your project in the Projects view
Select "Add New..." > "C++ Class" to add each class
Create the following files:
libraryitem.h and libraryitem.cpp
book.h and book.cpp
magazine.h and magazine.cpp
librarymanager.h and librarymanager.cpp
Replace main.cpp with the provided code
Step 4: Copy Code
Copy the code from each provided file into the respective files in your project
Make sure to use the exact file names as shown in the code
Step 5: Configure Data Directory
Modify the data file path in main.cpp:
cpp
QString sDataFilePath = QDir::current().absoluteFilePath("library_data.txt");
Or create a specific directory:
cpp
QDir().mkpath("C:/data");
QString sDataFilePath = "C:/data/library_data.txt";
Step 6: Build and Run
Click "Build" > "Build Project" (or press Ctrl+B)
After successful build, click "Build" > "Run" (or press Ctrl+R)
Usage Guide
Main Menu Options
When you start the application, you'll see the following menu options:

Add a new book: Add a book to the library by entering title, author, and genre
Add a new magazine: Add a magazine by entering title, publisher, and issue number
Search by title: Find items by their title (partial matches work)
Search by author: Find items by their author/publisher name
Search by ID: Look up a specific item by its unique ID
Borrow an item: Mark an item as borrowed by specifying its ID
Return an item: Process a return by specifying the item's ID
Display all items: Show all items in the library catalog
Exit: Close the application
Data Storage
The system saves all library data to a text file in a fixed-width format. The default location is specified in the main.cpp file. The file contains the following information for each item:

Item ID
Type (Book or Magazine)
Title
Author/Publisher
Availability status
Additional attributes (Genre for books, Issue Number for magazines)
Troubleshooting
Common Issues
File not found errors:
Check if the specified directory exists
Ensure write permissions for the data file directory
Try using an absolute path
Build errors:
Make sure Qt libraries are properly installed
Check that all files are correctly added to the project
Verify that the code is copied correctly without missing sections
Runtime errors:
Check the regular expression in LibraryManager::loadData() if you have issues with magazine parsing
Extending the System
To extend this system, consider:

Adding more item types (e.g., DVDs, Journals)
Implementing user accounts and authentication
Adding due dates and fine calculation for late returns
Creating a graphical user interface using Qt widgets
Adding statistical reporting features
Credits
Developed as a C++ Qt project demonstrating object-oriented programming principles, including inheritance, polymorphism, and encapsulation.

License
This project is provided for educational purposes. Feel free to use and modify as needed.

