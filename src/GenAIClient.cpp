#include "GenAIClient.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

std::string GenAIClient::sendPrompt(const std::string& prompt) {
    // Build command to call Python helper
    std::string command = "python genai_helper.py \"" + prompt + "\"";

    // Open pipe to read Python output
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "[ERROR] Could not run Python helper. Using mock response.\n";
        return "// MockService for: " + prompt;
    }

    char buffer[256];
    std::stringstream result;
    while (fgets(buffer, sizeof(buffer), pipe)) {
        result << buffer;
    }
    _pclose(pipe);

    return result.str();
}
