#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;
const int MAX_SOLDIERS = 1000;
const int MAX_EXP = 600;
const int MAX_SUPPLIES = 3000;
const int MAX_EVENT = 99;

// Task 0: Read input file
bool parseSoldierArray(const string &line, int arr[], int size) 
{
  if (line.front() != '[' || line.back() != ']') 
  {
    return false; // Ensure correct format
  } 

  string content = line.substr(1, line.length() - 2); // Remove brackets
  stringstream ss(content);
  string token;
  int index = 0;

  while (getline(ss, token, ',')) { // Split by commas
    int value;
    stringstream converter(token);
    if (!(converter >> value)) 
    {
      return false; // Convert to integer safely
    }

    if (value < 0) value = 0;
    else if (value > MAX_SOLDIERS) value = MAX_SOLDIERS;

    arr[index] = value;
    index++;
    if (index > size) 
    {
      return false; // Prevent overflow
    }
  }

  return (index == size); // Ensure exactly 17 elements
}

bool readFile(
    const string &filename,
    int LF1[], int LF2[],
    int &EXP1, int &EXP2,
    int &T1, int &T2, int &E)
{
  char data[MAX_LINES][MAX_LINE_LENGTH];
  int numLines = 0;

  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    return false;
  }

  while (numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
  {
    numLines++;
  }
  ifs.close();

  if (numLines < MAX_LINES)
  {
    return false;
  }

  // TODO: Extract values from the `data` array and store them in respective variables
  if (!parseSoldierArray(data[0], LF1, 17) || !parseSoldierArray(data[1], LF2, 17)) 
  {
    return false;
  }

  stringstream ss;

  // Parse EXP1 and EXP2
  ss.clear();
  ss.str(data[2]);
  if (!(ss >> EXP1 >> EXP2)) 
  {
    return false;
  }
  if (EXP1 < 0) EXP1 = 0; else if (EXP1 > MAX_EXP) EXP1 = MAX_EXP;
  if (EXP2 < 0) EXP2 = 0; else if (EXP2 > MAX_EXP) EXP2 = MAX_EXP;

  // Parse T1 and T2
  ss.clear();
  ss.str(data[3]);
  if (!(ss >> T1 >> T2)) 
  {
    return false;
  }
  if (T1 < 0) T1 = 0; else if (T1 > MAX_SUPPLIES) T1 = MAX_SUPPLIES;
  if (T2 < 0) T2 = 0; else if (T2 > MAX_SUPPLIES) T2 = MAX_SUPPLIES;

  // Parse E
  ss.clear();
  ss.str(data[4]);
  if (!(ss >> E)) 
  {
    return false;
  }
  if (E < 0) E = 0; else if (E > MAX_EVENT) E = MAX_EVENT;

  return true;
}

// Task 1
int gatherForces(int LF1[], int LF2[])
{
  // TODO: Implement this function
  const int weights[17] = {1, 2, 3, 4, 5, 7, 8, 9, 10, 12, 15, 18, 20, 30, 40, 50, 70};
  int totalForce = 0;

  for (int i = 0; i < 17; i++) {
    totalForce += LF1[i] * weights[i];
    totalForce += LF2[i] * weights[i];
  }

  return totalForce;
}

// Task 2
string determineRightTarget(const string &target)
{
  // TODO: Implement this function
  int numbers[4]; // Max 4 numbers for validation
  int count = 0;
  size_t len = target.length();

  // Extract numbers
  for (size_t i = 0; i < len; i++) {
    if (isdigit(target[i])) {
      int num = 0;

      // Extract the full number
      while (i < len && isdigit(target[i])) {
        num = num * 10 + (target[i] - '0'); // Multi-digit number
        i++;
      }

      if (num >= 0 && num <= 100 && count < 4) { // Only allow numbers in range [0,100]
        numbers[count] = num;
        count++;
      }
    }
  }

  // No numbers or more than 3 numbers
  if (count == 0 || count > 3)
  {
    return "INVALID";
  }

  int targetID;
  // 1 number
  if (count == 1) {
    targetID = numbers[0];

    // Actual primary target
    if (targetID == 3) return "Buon Ma Thuot";
    if (targetID == 4) return "Duc Lap";
    if (targetID == 5) return "Dak Lak";
    if (targetID == 6) return "National Route 21";
    if (targetID == 7) return "National Route 14";

    // DECOY
    if (targetID == 0 || targetID == 1 || targetID == 2)
    {
      return "DECOY";
    }

    return "INVALID";
  }
  // 2 numbers
  else if (count == 2) {
    targetID = ((numbers[0] + numbers[1]) % 5) + 3;
  }
  // 3 numbers
  else if (count == 3) {
    int maxValue = numbers[0];
    if (maxValue < numbers[1]) {
      maxValue = numbers[1];
    }
    if (maxValue < numbers[2]) {
      maxValue = numbers[2];
    }
    targetID = (maxValue % 5) + 3;
  }

  if (targetID == 3) return "Buon Ma Thuot";
  if (targetID == 4) return "Duc Lap";
  if (targetID == 5) return "Dak Lak";
  if (targetID == 6) return "National Route 21";
  if (targetID == 7) return "National Route 14";

  return "INVALID";
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
  // TODO: Implement this function
  string decodedMessage = "";

  if (EXP1 >= 300 && EXP2 >= 300) {
    int shift = (EXP1 + EXP2) % 26;
    string temp = "";

    for (char ch : message) {
      if (isalpha(ch)) {
        char base = 'a'; // All to lowercase
        temp += (char)(((tolower(ch) - base + shift) % 26) + base);
      }
      else if (isdigit(ch) || ch == ' ') {
        temp += ch;
      }
      else {
        return "INVALID";
      }
    }

    // Capitalize first letter of each word
    bool newWord = true;
    for (size_t i = 0; i < temp.length(); i++) {
      if (newWord && isalpha(temp[i])) {
        temp[i] = toupper(temp[i]);
        newWord = false;
      } else if (temp[i] == ' ') {
        newWord = true;
      }
    }

    decodedMessage = temp;
  }
  else {
    string temp = "";
    for (char ch : message) {
      temp += tolower(ch);
    }

    // Reverse string
    for (int i = temp.length() - 1; i >= 0; i--) {
      decodedMessage += temp[i];
    }

    // Capitalize first letter of each word
    bool newWord = true;
    for (size_t i = 0; i < decodedMessage.length(); i++) {
      if (newWord && isalpha(decodedMessage[i])) {
        decodedMessage[i] = toupper(decodedMessage[i]);
        newWord = false;
      } else if (decodedMessage[i] == ' ') {
        newWord = true;
      }
    }
  }

  if (decodedMessage == "Buon Ma Thuot") {
    return "Buon Ma Thuot";
  } else if (decodedMessage == "Duc Lap") {
    return "Duc Lap";
  } else if (decodedMessage == "Dak Lak") {
    return "Dak Lak";
  } else if (decodedMessage == "National Route 21") {
    return "National Route 21";
  } else if (decodedMessage == "National Route 14") {
    return "National Route 14";
  }

  return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
  // TODO: Implement this function
  double newT1 = T1;
  double newT2 = T2;

  if (E == 0) {
    double totalSupply = newT1 + newT2;
    double deltaT1 = (LF1 / (double)(LF1 + LF2)) * totalSupply * (1 + (EXP1 - EXP2) / 100.0);
    double deltaT2 = totalSupply - deltaT1;
  
    newT1 += deltaT1;
    newT2 += deltaT2;
  }
  else if (E >= 1 && E <= 9) {
    newT1 -= ((E * 0.01) * newT1);
    newT2 -= ((E * 0.005) * newT2);
  }
  else if (E >= 10 && E <= 29) {
    newT1 += E * 50;
    newT2 += E * 50;
  }
  else if (E >= 30 && E <= 59) {
    newT1 += ((E * 0.005) * newT1);
    newT2 += ((E * 0.002) * newT2);
  }
  else if (E >= 60 && E <= 99) {
    return;
  }

  T1 = (int)ceil(newT1);
  T2 = (int)ceil(newT2);

  // Ensure T1 and T2 in range
  if (T1 < 0) T1 = 0; else if (T1 > MAX_SUPPLIES) T1 = MAX_SUPPLIES;
  if (T2 < 0) T2 = 0; else if (T2 > MAX_SUPPLIES) T2 = MAX_SUPPLIES;
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
  // TODO: Implement this function
  double S = (LF1 + LF2) + (EXP1 + EXP2) * 5 + (T1 + T2) * 2;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i % 2 == 1) {
        S -= ((battleField[i][j] * 3.0) / 2.0);
      } else {
        S -= ((battleField[i][j] * 2.0) / 3.0);
      }
    }
  }

  // Fix loi lam tron khi S ra so .000000
  S -= 0.000005;

  return (int)ceil(S);
}

// Task 5
int resupply(int shortfall, int supply[5][5])
{
  // TODO: Implement this function
  int values[25];
  int index = 0;

  // Store the 5x5 matrix into a 1D array
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      values[index] = supply[i][j];
      index++;
    }
  }

  // Selection Sort
  for (int i = 0; i < 24; i++) {
    int minIdx = i;
    for (int j = i + 1; j < 25; j++) {
      if (values[j] < values[minIdx]) {
        minIdx = j;
      }
    }

    // Swap values[i] and values[minIdx]
    int temp = values[i];
    values[i] = values[minIdx];
    values[minIdx] = temp;
  }

  int bestTotal = -1; // In case cannot find 5-cell combination satisfies our shortfall

  for (int a = 0; a < 21; a++) {
    for (int b = a + 1; b < 22; b++) {
      for (int c = b + 1; c < 23; c++) {
        for (int d = c + 1; d < 24; d++) {
          for (int e = d + 1; e < 25; e++) {
            int total = values[a] + values[b] + values[c] + values[d] + values[e];
            if (total >= shortfall) {
              if (bestTotal == -1 || total < bestTotal) {
                bestTotal = total;
              }
            }
          }
        }
      }
    }
  }

  return bestTotal;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
