### Commit tags
- [CORE]: Core library infrastructure and architecture changes
- [IMPL]: Algoritms implementation
- [UTIL]: Extend or update the utilities
- [PERF]: Performance optimizations
- [FIXS]: Bug fixes
- [TEST]: Writing or updating tests
- [DEMO]: Writing demos
- [DOCS]: Writing docs for the API
- [CICD]: CI/CD changes
> [!WARNING]
> If you worked on multiple things add the necessary tags like
[DOCS][DEMOS] etc. Always give a detailed commit message for the commit.
### Build process
```
mkdir -p build && cd build
cmake ..
cmake --build . --parallel $(nproc)
```
