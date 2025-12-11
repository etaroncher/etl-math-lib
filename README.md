# 🎮 ETL::Math | The Game Engine Math Library

A high-performance, template-based C++ math library providing comprehensive 2D and 3D primitives, specifically engineered for real-time applications and game engine development.

---

## 🎯 Overview: Engineered for Transforms and Performance

$\text{ETL::Math}$ is designed to be the foundational math layer for game engines and simulation projects. It offers robust implementations of core geometric operations, with a unique focus on precision safety and type versatility.

Unlike general-purpose linear algebra libraries, this library is optimized for the geometric operations central to game loops and rendering pipelines.

---

## ✨ Key Features

### 🔧 2D and 3D Transform Support
- **Vectors**: Fundamental building blocks for positions, directions, and displacements (Vector2, Vector3)
- **Matrices**: Matrix-based transformations for rotation, scaling, and translation (Matrix3x3, with Matrix4x4 planned)
- **Quaternions**: Efficient and stable 3D rotation representation (planned)
- **Transform Objects**: High-level transform representation combining position (vector), rotation (quaternion), and scale (vector) (planned)
- **Transform Hierarchies**: Parent-child transform relationships for scene graphs (planned)
- **Dual Quaternions**: Advanced skinning and blending support (planned)

### 🎨 Template-Based Architecture
Flexible type support through template implementation with intuitive aliases and deduction guides:
```cpp
Vector2<float>  → Vec2
Vector2<double> → Vec2d
Vector2<int>    → Vec2i

Vector2{2.0f, 1.0f} -> Vector2<float>
Vector2{2.0, 1.0}   -> Vector2<double>
Vector2{2, 1}       -> Vector2<int>
```

### 📊 Precision Versatility
Supports both standard floating-point (`float`, `double`) and fixed-point arithmetic. Matrix operations over integral types enable fixed-point transformations, providing deterministic behavior for networked games and embedded systems.

### ⚡ Performance-First Design
- **Zero-cost abstractions** through modern C++ features
- **Cache-friendly data layouts** minimizing memory overhead
- **Frequently-used operations** optimize away completely

### 🔒 Type Safety
- Strong type guarantees through C++23 template mechanisms
- Compile-time dimension checking
- No implicit conversions between incompatible types

### 🧩 Modular & Extensible
Clean separation between:
- Public API (`include/MathLib/`)
- Internal implementation details (`src/`;`private/`)
- Easy integration as a library dependency

---

## 📋 Requirements

- **C++ Standard:** C++23 or higher
- **Build System:** CMake ≥ 4.2.0
- **Compiler:** Any modern C++23-compliant compiler (GCC, Clang, MSVC)

---

## 🛠️ Building the Library

### Using Build Scripts (Recommended)

The project includes convenient build scripts for different platforms:

**Windows:**
```batch
# Run the batch script
tools/generate.bat --no-tests
tools/build.bat --config Release
```

**Linux/macOS:** (planned)
```bash

```

### Manual CMake Build

Alternatively, you can build directly with CMake:

```bash
cmake -S . -B build
cmake --build build --config Release
```

### Output

The project will be generated in:
```
build/
```

The compiled library will be placed in:
```
lib/
```

---

## 📦 Integration into Your Project

### CMake Integration

```cmake
# Add as subdirectory
add_subdirectory(path/to/MathLib)

# Link against your target
target_link_libraries(your_target PRIVATE MathLib)
```

### Basic Usage Example

```cpp
#include <MathLib/Vector2.hpp>
#include <MathLib/Matrix3x3.hpp>

using ETL::Math;

// Create a 2D position vector of floats
Vec2 position{10.0f, 20.0f};

// Apply a transformation matrix
Mat3x3 transform = Mat3x3::Rotation(0.86f);
Vec2 transformed = transform * position;

// Chain transformations
Mat3x3 transform2 = Mat3x3::Identity();
transform2.translate(3.f, 4.f).rotate(0.5f).scale(2.0f, 2.0f);
```

---

## 📁 Project Structure

```
MathLib/
 ├── .gitignore
 ├── build/                  # CMake build artifacts
 ├── external/               # Third-party dependencies
 ├── include/                # Public API headers
 ├── lib/                    # Build output directory
 ├── private/                # Internal implementation headers
 ├── src/                    # Source implementations
 ├── tests/                  # Unit test suite
 ├── tools/                  # Development utilities
 ├── CMakeLists.txt          # Main CMake configuration
 └── README.md
```

---

## 🚀 Roadmap

- [ ] **Matrix4x4**: Full 3D transformation support
- [ ] **Quaternions**: Efficient 3D rotation representation
- [ ] **Transforms**: High-level transformation objects and arithmetic
- [ ] **SIMD Optimizations**: AVX/SSE vectorization
- [ ] **Geometry Utilities**: Intersection tests, bounding volumes
- [ ] **Numerical Methods**: Interpolation, curve fitting
- [ ] **Installation Support**: CMake install targets

---

## 🤝 Contributing

This is currently a personal project, but issues and suggestions can be opened on the repository.

---

## 📄 License

*[License information to be added]*

---

## 👤 Author

**etaroncher**  
GitHub: [@etaroncher](https://github.com/etaroncher)

---

**Built with precision. Optimized for speed. Designed for games.**