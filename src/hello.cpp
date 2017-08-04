#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <emscripten/fetch.h>

// Default place to look for data in the local virtual file system
const char* default_load_path = "/models/hello.txt";

// Attempt to fetch data from the following URL
// and replace the contents of `default_load_path` with its data.
const char* replacement_fetch_path = "/models/world.txt";

// Print the contents of the file at `path` from the local virtual file system
void print_path(const char* path) {
	int bufferSz = 128;
	char* buffer = (char*) malloc(sizeof(char) * bufferSz);
	FILE* fp = fopen(path, "rb");
	size_t retCode = fread(buffer, sizeof(char), bufferSz, fp);
	fclose(fp);

	printf("%s\n", buffer);
	free(buffer);
}

// Callback for when the Emscripten fetch succceeds;
// Overwrites `default_load_path` with the data from the Emscripten fetch.
void download_succeeded(emscripten_fetch_t* fetch) {
  printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
	FILE* fp = fopen(default_load_path, "wb");
	size_t retCode = fwrite(fetch->data, 1, fetch->numBytes, fp);
	fclose(fp);
  emscripten_fetch_close(fetch); // Free data associated with the fetch.
  print_path(default_load_path);
}

// Callback for when the Emscripten fetch fails
// and then prints the contents of "/models/hello.txt"
void download_failed(emscripten_fetch_t* fetch) {
  printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
  emscripten_fetch_close(fetch); // Also free data on failure.
  print_path(default_load_path);
}

//
int main(int argc, char** argv) {
	emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "GET");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
  attr.onsuccess = download_succeeded;
  attr.onerror = download_failed;
  emscripten_fetch(&attr, replacement_fetch_path);

  return 0;
}
