# emscripten hello world

This demonstrates in Emscripten:

1. Loading a file from the local virtual file system
2. Making an Emscripten fetch to dynamically load data from a URL,
   and then replacing the contents of the local virtual file system
   with that fetched data.

The code uses two default input parameters:

```cpp
// Default place to look for data in the local virtual file system
const char* default_load_path = "/models/hello.txt";

// Attempt to fetch data from the following URL
// and replace the contents of `default_load_path` with its data.
const char* replacement_fetch_path = "/models/world.txt";
```

You can see the difference in the behavior of the code when:

1. If `replacement_fetch_path` is a valid fetchable URL, then the code will
   replace the `default_load_path` and print its contents.
2. If `replacement_fetch_path` is unfetchable (e.g. 404), then the code will
   print the default preloaded contents of `default_load_path`.

This demonstrates both default local file pre-loading, and dynamic fetching.


## Compiling and Running

The following command will compile and run the entire package
(with standalone `emrun` web server)

```bash
./build.sh
```
