#ifndef GENAI_CLIENT_H
#define GENAI_CLIENT_H

#include <string>

class GenAIClient {
public:
    std::string sendPrompt(const std::string& prompt);
};

#endif
