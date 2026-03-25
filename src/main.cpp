#include <iostream>
#include <string>
#include "PromptBuilder.h"
#include "ServiceGenerator.h"

int main() {
    std::cout << "=== GenAI SDV SoA Code Generator ===\n";

    const char* apiKey = std::getenv("GEMINI_API_KEY");
    if(!apiKey) {
        std::cout << "[ERROR] Gemini API Key not loaded\n";
        return 1;
    }

    PromptBuilder promptBuilder;
    ServiceGenerator generator;

    int serviceNumber = 1;
    std::string input;
    while(true) {
        std::cout << "\nEnter vehicle feature requirement (or 'exit' to quit):\n";
        std::getline(std::cin, input);
        if(input == "exit") break;

        std::string prompt = promptBuilder.buildPrompt(input);
        std::cout << "\nGenerating Code...\n";
        generator.generateService(prompt, serviceNumber);
        serviceNumber++;
    }

    std::cout << "\nAll requested services generated successfully!\n";
    return 0;
}
