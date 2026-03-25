#include "PromptBuilder.h"

std::string PromptBuilder::buildPrompt(const std::string& requirement) {
    std::string prompt;
    prompt += "You are an automotive software expert.\n";
    prompt += "Generate MISRA-compliant C++ Service-Oriented code.\n";
    prompt += "Requirement:\n";
    prompt += requirement;
    prompt += "\nGenerate service interface, implementation, and test logic.";
    return prompt;
}
