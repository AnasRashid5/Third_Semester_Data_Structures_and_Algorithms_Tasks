# Mini Search Engine

A desktop search engine developed in C++ that indexes text documents, supports keyword-based searching, ranks search results, provides autocomplete suggestions using a Trie, maintains search history using a Stack, and connects to a web-based frontend through an HTTP server.

---

## Features

- Single-word search
- Multi-word AND search
- Multi-word OR search
- Frequency-based document ranking
- Inverted Index for fast searching
- Trie-based autocomplete
- Search history using Stack
- Case-insensitive searching
- Automatic document parsing
- Frontend connected with C++ backend

---

## Project Architecture

```
                User
                  │
                  ▼
        Frontend (HTML/CSS/JavaScript)
                  │
             HTTP Request
                  │
                  ▼
              C++ Backend
                  │
                  ▼
            Search Engine
                  │
     ┌────────────┴────────────┐
     ▼                         ▼
  Parser                  Search History
     │                       (Stack)
     ▼
  Clean Tokens
     │
     ▼
   Indexer
(Inverted Index)
     │
     ▼
 Candidate Documents
     │
     ▼
   Ranking
     │
     ▼
 Sorted Results
     │
     ▼
 HTTP Response (JSON)
     │
     ▼
 Frontend Display
```

---

## Data Structures Used

### 1. unordered_map
Used for the Inverted Index.

Stores

```
Word
    ↓
Document
    ↓
Frequency
```

Provides average O(1) lookup time.

---

### 2. unordered_set

Used for

- AND search (Intersection)
- OR search (Union)

Avoids duplicate documents.

---

### 3. vector

Used for

- Tokens
- Ranked results
- Document storage

---

### 4. Trie

Used for

- Autocomplete
- Prefix searching

Example

```
mach

↓

machine
machinery
machines
```

---

### 5. Stack

Used for

- Search history
- Back functionality

Implements LIFO (Last In First Out).

---

## Algorithms

- Tokenization
- Inverted Index Construction
- AND Search
- OR Search
- Frequency-Based Ranking
- Prefix Search using Trie
- Sorting using std::sort()

---

## Project Workflow

1. Documents are loaded.
2. Parser cleans each document.
3. Indexer builds the inverted index.
4. Trie stores every unique word.
5. User enters a query.
6. Query is parsed.
7. Matching documents are retrieved.
8. Documents are ranked.
9. Results are returned to the frontend.
10. Query is stored in Stack history.

---

## Technologies Used

- C++
- STL
- HTML
- CSS
- JavaScript
- cpp-httplib
- Visual Studio Code
- Git

---

## Author

Anas Rashid


Data Structures & Algorithms Project
