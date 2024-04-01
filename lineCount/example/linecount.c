#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// C, C++, HTML, CSS, JavaScript, TypeScript, Rust, PHP, Python, Java and C#
struct lines {
  size_t cpp;
  size_t c;
  size_t cheader;
  size_t cppheader;
  size_t html;
  size_t css;
  size_t javaScript;
  size_t typeScript;
  size_t rust;
  size_t php;
  size_t python;
  size_t java;
  size_t csharp;
  size_t other;
};

/*
 *   Global variables
 */
static struct lines countedLines = {0};

/*
 *   Forward declarations
 */

void recurse(const char*);

// Terminates the programm and prints errno
void die(const char* err) {
  perror(err);
  exit(EXIT_FAILURE);
}

// Counts all non empty lines of a given file and adds them to countLines. Sets
// errno and returns 0 on problem, else returns counted lines
size_t countLines(const char* filePath) {
  FILE* file;
  char* buffer;
  ssize_t result = 0;
  size_t lines = 0, bufferSize = 0;
  errno = 0;

  file = fopen(filePath, "r");
  if (NULL == file) {
    return 0;
  }

  while (-1 != (result = getline(&buffer, &bufferSize, file))) {
    if (0 < result) lines++;
  }
  if (-1 == result && errno) {
    return 0;
  }

  // Find filetype
  char* end = filePath + strlen(filePath);
  while ('.' != *end && end != filePath) end--;

  if (!strcmp(end, ".c"))
    countedLines.c += lines;
  else if (!strcmp(end, ".cpp"))
    countedLines.cpp += lines;
  else if (!strcmp(end, ".h"))
    countedLines.cheader += lines;
  else if (!strcmp(end, ".hpp"))
    countedLines.cppheader += lines;
  else if (!strcmp(end, ".html"))
    countedLines.html += lines;
  else if (!strcmp(end, ".css"))
    countedLines.css += lines;
  else if (!strcmp(end, ".js"))
    countedLines.javaScript += lines;
  else if (!strcmp(end, ".ts"))
    countedLines.typeScript += lines;
  else if (!strcmp(end, ".rs"))
    countedLines.rust += lines;
  else if (!strcmp(end, ".php"))
    countedLines.php += lines;
  else if (!strcmp(end, ".py"))
    countedLines.python += lines;
  else if (!strcmp(end, ".java"))
    countedLines.java += lines;
  else if (!strcmp(end, ".cs"))
    countedLines.csharp += lines;
  else
    countedLines.other += lines;

  free(buffer);
  if (fclose(file)) {
    die("Failed to close file");
  }
}

// Iterates through a give directory
void iterateCurrentDir() {
  DIR* directory = opendir(".");
  struct dirent* dirEntry;
  if (NULL == directory) {
    char pwd[PATH_MAX];
    getcwd(pwd, sizeof(pwd));
    fprintf(stderr, "Failed to open directory: %s", pwd);
    perror(NULL);
    return;
  }
  errno = 0;
  while (dirEntry = readdir(directory)) {
    struct stat statbuf = {0};
    int result = 0;
    result = lstat(dirEntry->d_name, &statbuf);
    if (S_ISREG(statbuf.st_mode)) {
      size_t count = {0};
      count = countLines(dirEntry->d_name);
      if (!count) {
        char pwd[PATH_MAX];
        getcwd(pwd, sizeof(pwd));
        fprintf(stderr, "Failed to read file: %s/%s", pwd, dirEntry->d_name);
        perror(NULL);
      }
    } else if (S_ISDIR(statbuf.st_mode)) {
      recurse(dirEntry->d_name);
    }
  }

  if (errno) {
    char pwd[PATH_MAX];
    getcwd(pwd, sizeof(pwd));
    fprintf(stderr, "Failed to read directory: %s", pwd);
  }

  if (closedir(directory)) die("Failed to close directory");
}

void recurse(const char* path) {
  char pwd[PATH_MAX];
  int result = 0;
  result = chdir(path);
  if (result) {
    getcwd(pwd, sizeof(pwd));
    fprintf(stderr, "Failed to switch directory: %s/%s", pwd, path);
    perror(NULL);
    return;
  }
  iterateCurrentDir();
  result = chdir("..");
  if (result) {
    die("Failed to switch directory");
  }
}

void printResult() {
    printf("c: %ld\nother: %ld", countedLines.c, countedLines.other);
}

int main(int argc, char** argv) {
  if (2 < argc) {
    fprintf(stderr,
            "Error: Not enough arguments. Usage \"linecount <FOLDER>\"\n");
    exit(EXIT_FAILURE);
  }

  // Check if given path is a file or directory
  struct stat statbuf = {0};
  int res = {0};
  res = lstat(argv[1], &statbuf);
  if (res) {
    die("Failed to get file/directory stats");
  }

  if (S_ISREG(statbuf.st_mode)) {
    // Case given path is just a file
    size_t count = {0};
    count = countLines(argv[1]);
    if (!count) {
      char pwd[PATH_MAX];
      getcwd(pwd, sizeof(pwd));
      fprintf(stderr, "Failed to read file: %s/%s", pwd, argv[1]);
      perror(NULL);
    }
  } else if (S_ISDIR(statbuf.st_mode)) {
    // Case given path is a directory
    recurse(argv[1]);
  } else {
    fprintf(stderr,
            "Error: Given Path \"%s\" is neither a file nor a directory.\n",
            argv[1]);
    exit(EXIT_FAILURE);
  }

  printResult();
}