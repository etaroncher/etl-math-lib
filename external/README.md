# External Dependencies

## Catch2 v3.11.0
- **Files:** catch2/v3.11.0/catch_amalgamated.hpp & .cpp
- **Size:** ~950 KB
- **License:** BSL-1.0
- **Downloaded from:** https://github.com/catchorg/Catch2/releases/tag/v3.11.0/
- **Date added:** 2025-12-08

Unit testing framework. No installation or build required.

### Updating Catch2

1. Check latest release: https://github.com/catchorg/Catch2/releases
2. Download amalgamated files:
```bash
   mkdir -p external/catch2/vX.Y.Z
   cd external/catch2/vX.Y.Z
   wget https://raw.githubusercontent.com/catchorg/Catch2/vX.Y.Z/extras/catch_amalgamated.hpp
   wget https://raw.githubusercontent.com/catchorg/Catch2/vX.Y.Z/extras/catch_amalgamated.cpp
```
3. Update tests/CMakeLists.txt to point to new version
4. Test everything
5. Remove old version


