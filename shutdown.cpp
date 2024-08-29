#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Function to calculate time difference in seconds
long long calculateTimeDifference(std::tm shutdownTime) {
    // Get current system time
    std::time_t now = std::time(nullptr);
    std::tm* currentTime = std::localtime(&now);

    // Convert both times to time_t for difference calculation
    std::time_t current = std::mktime(currentTime);
    std::time_t target = std::mktime(&shutdownTime);

    // Calculate the difference in seconds
    return std::difftime(target, current);
}

// Function to shut down the remote computer
void shutdownRemoteComputer(const std::string& remoteComputerName) {
    std::string command = "shutdown /m \\\\" + remoteComputerName + " /s /f /t 0";
    system(command.c_str());
}

int main() {
    std::string remoteComputerName;
    int hour, minute;

    // Get remote computer name
    std::cout << "Enter the remote computer name (or IP address): ";
    std::getline(std::cin, remoteComputerName);

    // Get the shutdown time from the user
    std::cout << "Enter shutdown time (hour minute, 24-hour format): ";
    std::cin >> hour >> minute;

    // Prepare the shutdown time
    std::tm shutdownTime = {};
    shutdownTime.tm_hour = hour;
    shutdownTime.tm_min = minute;
    shutdownTime.tm_sec = 0;

    // Calculate the time difference
    long long timeDifference = calculateTimeDifference(shutdownTime);

    if (timeDifference > 0) {
        // Wait until the shutdown time
        std::cout << "Waiting for " << timeDifference << " seconds until shutdown...\n";
        std::this_thread::sleep_for(std::chrono::seconds(timeDifference));
        
        // Shutdown the remote computer
        shutdownRemoteComputer(remoteComputerName);
        std::cout << "Shutdown command sent to " << remoteComputerName << std::endl;
    } else {
        std::cerr << "The specified time is in the past!" << std::endl;
    }

    return 0;
}
