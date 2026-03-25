#include "ServiceGenerator.h"
#include "GenAIClient.h"
#include <fstream>
#include <iostream>

void ServiceGenerator::generateService(const std::string& prompt, int serviceNumber) {
    GenAIClient client;
    std::string genAIOutput = client.sendPrompt(prompt);

    std::string fileName = "GeneratedService_" + std::to_string(serviceNumber) + ".cpp";
    std::ofstream file(fileName);
    if(!file.is_open()) {
        std::cout << "[ERROR] Cannot create file " << fileName << "\n";
        return;
    }

    file << "// Auto-generated Service-Oriented Application #" << serviceNumber << "\n";
    file << "// Prompt Used:\n// " << prompt << "\n\n";
    file << genAIOutput;
    file.close();

    std::cout << fileName << " created successfully.\n";
}
