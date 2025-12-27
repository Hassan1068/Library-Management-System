# 📚 Library Management System (LMS) — C++

A **C++ console application implementing a full Library Management System with persistent storage and structured workflows**.

This project simulates real-world library operations such as book management, member management, issuing and returning books, fine handling, and policy management using a menu-driven interface and file-based data persistence.

---

## ✨ Features

### 🔐 Admin Authentication
- Secure admin login
- Username: `Admin`
- Password: `1234`
- Maximum 3 login attempts

---

### 📘 Book Management
- Add new books
- Search books by Book ID
- Remove books
- Check availability
- Issue books to members
- Return issued books
- Display all books with full details
- View total number of books
- Low book availability warning

---

### 👥 Member Management
- Add members
- Search members by Member ID
- Remove members
- Display all members
- View total member count
- Member count alerts (low / limit reached)

---

### 💰 Fine Management
- Check fine using Book ID
- Fine applies only to issued books
- Dynamic fine accumulation
- Displays issued member information

---

### 📜 Rules & Policies
- Library hours
- Borrowing privileges
- Fine policy
- University rights

---

### 💾 Persistent Storage
- Automatic data loading on startup
- Automatic data saving after every update
- File-based storage using `LMS.txt`
- No manual file editing required

---

## 🛠 Technologies Used

- **Language:** C++
- **File Handling:** `fstream`
- **Standard Libraries:** `iostream`, `string`, `chrono`, `thread`
- **Interface:** Command Line (CLI)
- **Storage Format:** Text File

---

## 📂 Project Structure

📦 Library-Management-System
- ┣ 📄 LMS.cpp
- ┣ 📄 LMS.txt
- ┗ 📄 README.md


---


⭐ If you find this project useful, consider giving it a star!

