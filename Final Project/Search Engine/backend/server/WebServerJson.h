#ifndef WEB_SERVER_JSON_H
#define WEB_SERVER_JSON_H

#include "../engine/SearchEngine.h"

#include <string>
#include <vector>

std::string makeSearchJson(const std::vector<SearchResult> &results,
                           const std::string &message);
std::string makeSuggestionsJson(const std::vector<std::string> &suggestions);

#endif
