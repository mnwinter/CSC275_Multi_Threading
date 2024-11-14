/*
Matthew Winter
CSC 275 Assignment Multi Threading
11/11/2024

Assignment Overview
Multi-threading
    For this assignment, you will demonstrate the creation, execution, management of multiple threads.

Guidelines
    You will be making your first C++ Multithreading application!  It is even more fun than you think!

Expectations
    Clearly use true multithreading.
    Over comment all your code for the future you in your own words.
    Your program should do something, in addition, to clearly demonstrating Multithreading.
    You must have a good UX and keep the user over-informed of what is happening.

    Submission Deliverables
    Attach either a single cpp file or a link to your git repo if you want to share multiple files.
    Submit a video of your program in action or a few screenshots showing your program working with no errors.  Show all functionality.
    NO ZIP FILES!
*/

#include <iostream>      // For input and output operations
#include <thread>        // For multithreading
#include <chrono>        // For time functions like sleep
#include <mutex>         // For mutex to protect shared data

// Use the standard namespace to avoid typing std:: every time
using namespace std;

// Global variable to store sensor data
int sensorData = 0;

// Mutex to protect access to sensorData
mutex sensorMutex;

// Function to simulate reading sensor data
void readSensor() {
    for (int i = 0; i < 5; ++i) {
        // Simulate time taken to read sensor data
        this_thread::sleep_for(chrono::milliseconds(500));

        // Lock the mutex before modifying sensorData
        sensorMutex.lock();
        sensorData += 10;  // Simulate sensor data increment
        cout << "[Sensor] Sensor data updated to " << sensorData << endl;
        // Unlock the mutex after modification
        sensorMutex.unlock();
    }
}

// Function to simulate motor control based on sensor data
void controlMotor() {
    for (int i = 0; i < 5; ++i) {
        // Wait before checking sensor data
        this_thread::sleep_for(chrono::milliseconds(700));

        // Lock the mutex before reading sensorData
        sensorMutex.lock();
        int data = sensorData;  // Copy sensor data
        // Unlock the mutex after reading
        sensorMutex.unlock();

        // Control logic based on sensor data
        if (data >= 30) {
            cout << "[Motor] Motor activated. Sensor data: " << data << endl;
        }
        else {
            cout << "[Motor] Motor deactivated. Sensor data: " << data << endl;
        }
    }
}

// Function to simulate displaying system status
void displayStatus() {
    for (int i = 0; i < 5; ++i) {
        // Wait before updating display
        this_thread::sleep_for(chrono::milliseconds(600));

        // Lock the mutex before reading sensorData
        sensorMutex.lock();
        int data = sensorData;  // Copy sensor data
        // Unlock the mutex after reading
        sensorMutex.unlock();

        // Display the status
        cout << "[Display] Current sensor data: " << data << endl;
    }
}

// Main function
int main() {
    cout << "Starting Robotics Multithreading Simulation..." << endl;

    // Create threads for each task
    thread sensorThread(readSensor);
    thread motorThread(controlMotor);
    thread displayThread(displayStatus);

    // Wait for all threads to finish
    sensorThread.join();
    motorThread.join();
    displayThread.join();

    cout << "Simulation complete. All threads have finished." << endl;

    return 0;
}
