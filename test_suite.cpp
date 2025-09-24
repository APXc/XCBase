/*
Test suite for XCBase Cryptography Package
Validates encryption, decryption, and file operations
*/

#include "pch_fixed.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstring>

using namespace std;

// External function declarations from xc_fixed.cpp
extern char *xcIn(char*);
extern char *xcOt(char*);

class XCBaseTest {
private:
    int testsRun;
    int testsPassed;
    
public:
    XCBaseTest() : testsRun(0), testsPassed(0) {}
    
    void runTest(const string& testName, bool condition) {
        testsRun++;
        cout << "Test " << testsRun << ": " << testName << " - ";
        if (condition) {
            cout << "PASSED" << endl;
            testsPassed++;
        } else {
            cout << "FAILED" << endl;
        }
    }
    
    void testEncryptionDecryption() {
        cout << "\n=== Testing Encryption/Decryption ===" << endl;
        
        // Test 1: Basic string
        char test1[] = "Hello";
        char original1[256];
        strcpy(original1, test1);
        char* encrypted = xcIn(test1);
        char* decrypted = xcOt(encrypted);
        runTest("Basic string round-trip", strcmp(original1, decrypted) == 0);
        
        // Test 2: String with spaces
        char test2[] = "Hello World";
        char original2[256];
        strcpy(original2, test2);
        strcpy(test2, original2); // Reset
        encrypted = xcIn(test2);
        strcpy(test2, encrypted);
        decrypted = xcOt(test2);
        runTest("String with spaces round-trip", strcmp(original2, decrypted) == 0);
        
        // Test 3: Empty string
        char test3[] = "";
        char original3[256];
        strcpy(original3, test3);
        strcpy(test3, original3);
        encrypted = xcIn(test3);
        strcpy(test3, encrypted);
        decrypted = xcOt(test3);
        runTest("Empty string round-trip", strcmp(original3, decrypted) == 0);
        
        // Test 4: Special characters
        char test4[] = "Test!@#$%";
        char original4[256];
        strcpy(original4, test4);
        strcpy(test4, original4);
        encrypted = xcIn(test4);
        strcpy(test4, encrypted);
        decrypted = xcOt(test4);
        runTest("Special characters round-trip", strcmp(original4, decrypted) == 0);
    }
    
    void testFileOperations() {
        cout << "\n=== Testing File Operations ===" << endl;
        
        // Create test file
        ofstream testFile("test_crypto.txt");
        testFile << "Test file content";
        testFile.close();
        
        runTest("Test file creation", ifstream("test_crypto.txt").good());
        
        // Test file reading
        ifstream readFile("test_crypto.txt");
        string content;
        getline(readFile, content);
        readFile.close();
        
        runTest("Test file reading", content == "Test file content");
        
        // Clean up
        remove("test_crypto.txt");
    }
    
    void printSummary() {
        cout << "\n=== Test Summary ===" << endl;
        cout << "Tests run: " << testsRun << endl;
        cout << "Tests passed: " << testsPassed << endl;
        cout << "Success rate: " << (testsPassed * 100.0 / testsRun) << "%" << endl;
        
        if (testsPassed == testsRun) {
            cout << "All tests PASSED!" << endl;
        } else {
            cout << "Some tests FAILED!" << endl;
        }
    }
};

#ifdef COMPILE_TESTS
int main() {
    cout << "XCBase Cryptography Package - Test Suite" << endl;
    cout << "========================================" << endl;
    
    XCBaseTest tester;
    tester.testEncryptionDecryption();
    tester.testFileOperations();
    tester.printSummary();
    
    return 0;
}
#endif