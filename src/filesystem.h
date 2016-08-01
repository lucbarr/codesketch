#ifndef CODESKETCH_CORE_FILESYSTEM_H
#define CODESKETCH_CORE_FILESYSTEM_H

#include <experimental/filesystem>
#include <array>
#include <string>
#include <vector>
#include <functional>
#include <utility>

#include "externs.h"

typedef std::function<void (const std::vector<std::string>&)> ShellFn;

namespace codesketch {

// TODO(naum): remove const and do better!
/*
const int shellX = 20,
          shellY = 60,
          shellW = windowWidth - 40,
          shellH = windowHeight - 80;
const std::string shellPS1 = "> ", shellPS2 = "- ";
*/

void shellOpLs  (const std::vector<std::string>&);
void shellOpCd  (const std::vector<std::string>&);
void shellOpRun (const std::vector<std::string>&);
void shellOpHelp(const std::vector<std::string>&);
void shellOpMan (const std::vector<std::string>&);
void shellOpExit(const std::vector<std::string>&);

const std::pair<std::string, ShellFn> shellOps[] = {
  { "cd",   &shellOpCd   },
  { "ls",   &shellOpLs   },
  { "run",  &shellOpRun  },
  { "help", &shellOpHelp },
  { "man",  &shellOpMan  },
  { "exit", &shellOpExit }
};
const int shellOpsSize = sizeof(shellOps)/sizeof(shellOps[0]);

void shellAddHistory(const std::string&);
void shellParse(const std::string&);

}

#endif
