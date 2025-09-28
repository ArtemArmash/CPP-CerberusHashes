# Cerberus Hashes - High-Performance File Hashing Utility

Cerberus Hashes is a C++ console application designed for the high-performance calculation of multiple cryptographic hashes for one or more files. This project was developed to demonstrate a deep understanding of low-level data processing, multithreading, and the inner workings of common hashing algorithms.

Unlike tools that rely on external libraries like OpenSSL, Cerberus uses **from-scratch implementations** of the MD5 and SHA-256 algorithms, showcasing a fundamental grasp of the underlying cryptographic principles.

## Features

-   **Multiple Hash Algorithms:** Calculates **MD5** and **SHA-256** hashes. The modular design allows for easy addition of other algorithms.
-   **High Performance:**
    -   Utilizes **multithreading** (`std::thread`) to compute multiple hashes in parallel, significantly speeding up the process.
    -   Employs **chunk-based file reading** to efficiently process large files without consuming excessive memory.
-   **From-Scratch Implementations:** Core hashing logic for MD5 and SHA-256 was implemented based on their respective RFC standards, demonstrating deep technical knowledge.
-   **Professional Project Structure:** The project is managed and built using **CMake**, with a clean, modular structure separating hashing logic, file processing, and the main application.

## Project Structure

```
.
├── src
│   ├── file_processor  # Handles efficient file reading
│   │   ├── FileProcessor.cpp
│   │   └── FileProcessor.h
│   ├── hashing         # Contains from-scratch hashing algorithm implementations
│   │   ├── md5.cpp
│   │   ├── md5.h
│   │   ├── sha256.cpp
│   │   └── sha256.h
│   └── main            # Main application logic
│       └── main.cpp
├── CMakeLists.txt      # Main CMake build script
└── README.md
```

## How It Works

The application takes a file path as input. It first reads the entire file into memory using an efficient chunking mechanism to handle large files. Then, it launches separate threads to calculate the MD5 and SHA-256 hashes concurrently. Once both threads complete their work, the final hashes are printed to the console along with the file's metadata.

## Building the Project

The project uses CMake for building.

```bash
# 1. Clone the repository
git clone https://github.com/your-username/CerberusHashes.git
cd CerberusHashes

# 2. Create a build directory
mkdir build
cd build

# 3. Configure and build the project
cmake ..
make

# 4. Run the executable
./cerberus /path/to/your/file.txt
```


## Example Usage

```bash
./cerberus gg.txt
```

**Example Output:**
```
File: gg.txt
Bytes: 14
MD5: 3afd018a6a26a8ce9f42bbba8fc6cdf3
SHA256: 8d7112771a71f9b2028686e8d230e22578181519ecba3f1d9f92cd3812ba28
```

## Purpose

This project serves as a practical demonstration of advanced C++ skills, including:
-   Concurrent programming and thread management.
-   Low-level algorithm implementation.
-   Efficient I/O operations.
-   Modern C++ project structure and build systems.
```