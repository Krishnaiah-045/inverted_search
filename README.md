

# 📘 Inverted Search Engine – Project Documentation

## 📌 Overview

This project implements an **Inverted Search Engine** in C.
It reads multiple text files, processes all words from them, and builds an **inverted index**—a data structure that maps each unique word to the list of files in which it appears.

The project uses:

* **Hash table** for fast lookup
* **Linked lists** for storing words and file occurrences
* **File validation** and **database update/search/display** operations

---

## 🧩 Data Structures Summary

### 🔹 1. Main Node (`MainNode`)

Represents each **unique word**.

| Field        | Description                                              |
| ------------ | -------------------------------------------------------- |
| `word[100]`  | The word itself                                          |
| `file_count` | Number of files containing this word                     |
| `ms_link`    | Pointer to the linked list of file occurrences (SubNode) |
| `m_link`     | Pointer to next MainNode                                 |

---

### 🔹 2. Sub Node (`SubNode`)

Represents each **file in which the word appears**.

| Field            | Description                                  |
| ---------------- | -------------------------------------------- |
| `file_name[100]` | Name of file containing the word             |
| `word_count`     | Number of times the word occurs in that file |
| `s_link`         | Pointer to next SubNode                      |

---

### 🔹 3. Hash Table (`Hashtable`)

Used for fast indexing of words by hashing their first character.

| Field    | Description                             |
| -------- | --------------------------------------- |
| `index`  | Hash bucket index                       |
| `h_link` | Points to first MainNode in this bucket |

---

### 🔹 4. File List (`Node`)

Singly linked list holding **input file names**.

| Field            | Description             |
| ---------------- | ----------------------- |
| `file_name[100]` | Name of file to process |
| `link`           | Next file node          |

---

## ⚙️ Functional Overview

### ✔ File Validation

* `read_and_validate()` — Validates command line arguments and file existence.
* `valid_filename()` — Checks filename format.
* `is_file_empty()` — Rejects empty files.
* `is_duplicate()` — Checks if file name already exists in list.
* `insert_file()` — Adds file to linked list.
* `remove_file()` — Removes a file from list.

---

### ✔ Database Operations

* `create_database()` — Reads files & builds the inverted index.
* `insert_to_database()` — Inserts word occurrences into hash table.
* `is_hash_empty()` — Checks if database contains any words.
* `update_database()` — Adds new file data into existing database.

---

### ✔ Search & Display

* `search_database()` — Searches for a word across all input files.
* `display_database()` — Prints the full inverted index in a readable format.
* `Save_database()` — Exports index to a file.

---

## 🔢 Hashing Logic

The size of the hash table is defined as:

```
#define SIZE 28
```

Indexing is usually based on:

* `'a' to 'z'` → 0 to 25
* `'0'` & `'1'` or special characters → remaining buckets

---

## 🛠 Build & Run Instructions

### **Compile:**

```sh
gcc main.c inverted.c -o inverted_search
```

### **Run:**

```sh
./inverted_search file1.txt file2.txt file3.txt
```

---

## 📤 Features

✅ Supports dynamic addition/removal of files
✅ Efficient searching using hash table
✅ Stores frequency of words per file
✅ Saves database to external file
✅ Color-coded console output (ANSI colors defined)

---

## 📂 Folder Structure (recommended)

```
/project
│
├── main.c
├── inverted.c
├── inverted.h
├── Makefile        # optional
└── README.md
```

---

## 💡 Example Output (Illustrative)

```
Word: "embedded"
Found in:
  → file1.txt (3 times)
  → file2.txt (1 time)
```

---

## 🧑‍💻 Author Notes

This header indicates a **modular**, **well-structured**, and **extendable** C project.
You can easily plug in new modules (like stop-word removal, case folding, stemming, etc.) without breaking core architecture.


