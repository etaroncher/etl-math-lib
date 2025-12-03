# MathLib

MathLib is a modular C++ mathematics library designed for speed, clarity, and easy integration into other projects. The library provides reusable components such as vectors, matrices, geometry utilities, numerical methods, and more.

---

## 📁 Project Structure

```
MathLib/
 ├── CMakeLists.txt          # Main CMake file (to be added)
 ├── include/MathLib/        # Public headers
 ├── private/                # Internal/private headers
 ├── src/                    # Source files
 ├── lib/                    # Build outputs
 ├── build/                  # CMake/IDE build directory
 ├── .gitignore
 └── README.md
```

---

## 🛠️ Building with CMake

### Prerequisites

* CMake ≥ 3.20
* A C++17 compatible compiler

Once the CMake setup is added, building the library will be simple:

```
cmake -S . -B build
cmake --build build --config Release
```

The compiled library will be placed in:

```
lib/
```

---

## 📦 Using MathLib in another project

After installation support is added, you will be able to use it with:

```
target_link_libraries(your_target PRIVATE MathLib)
```


