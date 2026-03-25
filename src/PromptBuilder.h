#ifndef PROMPT_BUILDER_H
#define PROMPT_BUILDER_H

#include <string>

class PromptBuilder {
public:
    std::string buildPrompt(const std::string& requirement);
};

#endif
