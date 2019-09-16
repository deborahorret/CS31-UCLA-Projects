//
//  lines.cpp
//  lines_real
//
//  Created by Deborah Orret on 5/8/17.
//  Copyright © 2017 Deborah Orret. All rights reserved.
//


#include <iostream>
#include <string>
#include <cctype>
#include "graphlib.hpp"
using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int BG = 0;
const int FG = 1;

bool plotLine (int r, int c, int dir, int distance, char plotChar, int fbbg) { // set lines in this function
    
    //check if starting coordinate is within the box
    if (r < 0 || c < 0) {
        if (r > 30 || c > 20) {
            return false;
        }
    }
    //check if direction is 1 or 0 (aka horizontal or vertical
    else if (dir != HORIZ || dir != VERT) {
        return false;
    }
    //check if distance exceeds bounds
    else if (dir != HORIZ) {
        if (distance < 0) {
            if (r+distance > 30) {
                return false;
            }
        }
        else if (distance > 0) {
            if (r - distance < 0) {
                return false;
            }
        }
    }
    else if (dir != VERT) {
        if (distance > 0 && c+distance > 20) {
            return false;
        }
        else if (distance < 0 && c - distance < 20) {
            return false;
        }
    }
    //checks if char is within the allowed chars
    else if (!isprint(plotChar)) {
        return false;
    }
    //check if fbbg is 0 or 1
    else if (fbbg != BG || fbbg != FG) {
        return false;
    }
    
    //all good
    
    else {
        if (dir == HORIZ){
            for (int i = 0; i <= distance; i++) {
                setChar(r, c+i, plotChar);
            }
        }
        else {
            for (int i = 0; i <= distance; i++) {
                setChar(r+i, c, plotChar);
            }
        }
        
        return true;
    }
    return true;
}

void clear_command (int& current_r, int& current_c, char& plotChar, int& mode, int& counter) { //if c or C
    clearGrid();
    current_r = 1;
    current_c = 1;
    plotChar = '*';
    mode = 0;
    counter++;
}

void foreground_command (string commandString, int& mode, int& counter, char& plotChar) {
    plotChar = commandString.at(counter + 1); //modify current character
    mode = 0;
    counter = counter + 2;
}

void background_command (string commandString, int& mode, int& counter, char& plotChar) {
    plotChar = commandString.at(counter + 1); //modify current character
    mode = 1;
    counter = counter + 2;
}

void horizontal_positive_command (string commandString, int& current_r, int& current_c, char& plotChar, int& mode, int& counter, int& num, int& returns) {
    
    if (counter + 2 < commandString.size() && isdigit(commandString.at(counter + 2))) { //ther is a second digit, tot: 3 char
        string number = commandString.substr(counter+1, 2);
        num = stoi(number);
        for (int z = current_c; z < current_c + num; z++) { //if background etc, goes inside for loop
            if (mode == 1) {
                if (getChar(current_r, z) == ' ') {
                    setChar(current_r, z, plotChar);
                }
            }
            else {
                setChar(current_r, z, plotChar);
            }
        }
        current_c = current_c + num;
        if (current_c > 30 || current_c < 0) {
            returns = 2;
        }
        counter = counter + 3;
    }
    
    else {
        string number = commandString.substr(counter+1,1);
        num = stoi(number);
        for (int z = current_c; z < current_c + num; z++) {
            if (mode== 1) {
                if (getChar(current_r, z) == ' ') {
                    setChar(current_r, z, plotChar);
                }
            }
            else {
                setChar(current_r, z, plotChar);
            }
        }
        current_c = current_c + num;
        if (current_c > 30 || current_c < 0) {
            returns = 2;
        }
        counter = counter + 2;
    } // there is only one digit, tot: 2 char
}

void horizontal_negative_command (string commandString, int& current_r, int& current_c, char& plotChar, int& mode, int& counter, int& num, int& returns) {
    if (counter + 3 < commandString.size() && isdigit(commandString.at(counter + 3))) {
        string number = commandString.substr(counter+1, 3);
        num = stoi(number);
        for (int y = current_c; y > current_c - num; y--) { //plotting my line, use plotline
            if (mode== 1) {
                if (getChar(current_r, y) == ' ') {
                    setChar(current_r, y, plotChar);
                }
            }
            else {
                setChar(current_r, y, plotChar);
            }
        }
        current_c = current_c - num;
        if (current_c > 30 || current_c < 0) {
            returns = 2;
        }
        counter = counter + 4;
    }
    else {
        string number = commandString.substr(counter+1, 2);
        num = stoi(number);
        for (int y = current_c; y > current_c - num; y--) {
            if (mode== 1) {
                if (getChar(current_r, y) == ' ') {
                    setChar(current_r, y, plotChar);
                }
            }
            else {
                setChar(current_r, y, plotChar);
            }
        }
        current_c = current_c - num;
        if (current_c > 30 || current_c < 0) {
            returns = 2;
        }
        counter = counter + 3;
    }
}

void vertical_negative_command (string commandString, int& current_r, int& current_c, char& plotChar, int& mode, int& counter, int& num, int& returns)
{
    //if it starts with a neg
    if (isdigit(commandString.at(counter+2))) { //first digit
        if (counter + 3 < commandString.size() && isdigit(commandString.at(counter+3))) {
            string number = commandString.substr(counter+2, 2);
            num = stoi(number);
            for(int a= current_r; a >= current_r - num; a--) {
                if (mode== 1) {
                    if (getChar(a, current_c) == ' ') {
                        setChar(a, current_c, plotChar);
                    }
                }
                else {
                    setChar(a, current_c, plotChar);
                }
                
            }
            current_r = current_r - num;
            if (current_r > 20 || current_r < 0) {
                returns = 2;
            }
            counter = counter + 4;
        }
        
        else {
            string number = commandString.substr(counter+2, 1);
            num = stoi(number);
            for(int a= current_r; a >= current_r - num; a--) {
                if (mode== 1) {
                    if (getChar(a, current_c) == ' ') {
                        setChar(a, current_c, plotChar);
                    }
                }
                else {
                    setChar(a, current_c, plotChar);
                }
                
            }
            current_r = current_r - num;
            if (current_r > 20 || current_r < 0) {
                returns = 2;
            }
            counter = counter + 3;
        } //if theres only one digit, total: 3 char, goes to else
    }
} //else if


void vertical_positive_command (string commandString, int& current_r, int& current_c, char& plotChar, int& mode, int& counter, int& num, int& returns)
{
    if (counter + 2 <= commandString.size() && isdigit(commandString.at(counter+2))) { //if theres a second digit, total: 3 char
        string number = commandString.substr(counter+1, 2);
        int num = stoi(number);
        for (int b= current_r; b <= current_r + num; b++) {
            if (mode== 1) {
                if (getChar(b, current_c) == ' ') {
                    setChar(b, current_c, plotChar);
                }
            }
            else {
                setChar(b, current_c, plotChar);
            }
        }
        current_r = current_r + num;
        if (current_r > 20 || current_r < 0) {
            returns = 2;
        }
        counter = counter + 3;
    } //+2 if
    else {
        string number = commandString.substr(counter+1, 1);
        int num = stoi(number);
        for (int b = current_r; b <= current_r + num; b++) {
            if (mode== 1) {
                if (getChar(b, current_c) == ' ') {
                    setChar(b, current_c, plotChar);
                }
            }
            else {
                setChar(b, current_c, plotChar);
            }
        }
        current_r = current_r + num;
        if (current_r > 20 || current_r < 0) {
            returns = 2;
        }
        counter = counter + 2;
        
    } //if theres only one digit, total: 2 char
} //if is digit bracket


void check_syntax (string commandString, int& badPos, int& returns)
 {
 for (int i = commandString.length()-1; i > 0; i--) {
 if (isdigit(i) && isdigit(i-1) && isdigit(i-2)) {
 badPos = i;
 returns = 1;
 }
 if (!isdigit(i) && !isalpha(i) && commandString.at(i-1) != 'f' && commandString.at(i-1) != 'F' && commandString.at(i-1) != 'b' && commandString.at(i-1) != 'B') {
 badPos = i;
 returns = 1;
 }
 
 //if first character is not a f, b, h, or v
 if (commandString.at(i) != 'H' || commandString.at(i) != 'h' || commandString.at(i) != 'v' ||commandString.at(i) != 'V' || commandString.at(i) != 'f' || commandString.at(i) != 'F' || commandString.at(i) != 'b' || commandString.at(i) != 'B'
 || commandString.at(i) != 'c' || commandString.at(i) != 'C') {
 badPos = i;
 returns = 1;
 }
 
 
 if (commandString.at(i) == '-' && (commandString.at(i-1) != 'F' | commandString.at(i-1) != 'f' || commandString.at(i-1) != 'b' || commandString.at(i-1) != 'B' || commandString.at(i-1) != 'h' || commandString.at(i-1) != 'H' || commandString.at(i-1) != 'h' || commandString.at(i-1) != 'V' || commandString.at(i-1) != 'v'))
 {
 badPos = i;
 returns = 1;
 }
 if (commandString.at(0) != 'F' | commandString.at(0) != 'f' || commandString.at(0) != 'b' || commandString.at(0) != 'B' || commandString.at(0) != 'h' || commandString.at(0) != 'H' || commandString.at(0) != 'h' || commandString.at(0) != 'V' || commandString.at(0) != 'v' || commandString.at(0) != 'C' || commandString.at(0) != 'c') {
 badPos = i;
 returns = 1;
 } //for loop closing bracket
 
 }
 }


int executeCommands(string commandString, char& plotChar, int& mode, int& badPos) {
    int current_r = 1;
    int current_c = 1;
    int counter= 0;
    int returns = 0;
    int num = 0;
    
    
    
    //check if has the right syntax
    
    check_syntax (commandString, badPos, returns);
    if (returns == 1) {
        return 1;
    }
    while (counter < commandString.size()) {
        
        if (commandString.at(counter) == 'h' || commandString.at(counter) == 'H') {
            if (commandString.at(counter + 1) == '-') {
                horizontal_negative_command (commandString, current_r, current_c, plotChar, mode, counter, num, returns);
            }
            else if (isdigit(commandString.at(counter + 1))) { //this is the positive
                horizontal_positive_command (commandString, current_r, current_c, plotChar, mode, counter, num, returns);
            }
            
        } //h if
        
        else if (commandString.at(counter) == 'v' || commandString.at(counter) == 'V') {
            if(commandString.at(counter+1) == '-')
                vertical_negative_command (commandString, current_r, current_c, plotChar, mode, counter, num, returns);
            
            else if (isdigit(commandString.at(counter+1)))
                vertical_positive_command (commandString, current_r, current_c, plotChar, mode, counter, num, returns);
        } //v if
        
        else if (commandString.at(counter) == 'b' || commandString.at(counter) == 'B')
            background_command (commandString, mode, counter, plotChar);
        else if (commandString.at(counter) == 'f' || commandString.at(counter) == 'F')
            foreground_command (commandString, mode, counter, plotChar);
        if ((counter >= 0 && counter < commandString.size()) && (commandString.at(counter) == 'c' || commandString.at(counter) == 'C'))
            clear_command (current_r, current_c, plotChar, mode, counter);
        
    }//while
    if (returns == 2) {
        return 2;
    }
    return 0;
}

int main()
{
    clearGrid();
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = executeCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot execute command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "executeCommands returned " << status << "!" << endl;
        }
    }
}

