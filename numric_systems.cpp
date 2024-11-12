#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
using namespace std;
map<string, string> numricSystems = {
    {"10", "decimal"},
    {"2", "binary"},
    {"16", "hexdecimal"},
    {"8", "octal"}};
map<char, string> binMap = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"},
};
string capitalize(string text)
{
    if (!text.empty())
    {
        text[0] = toupper(text[0]);
        for (int i = 1; i < text.size(); i++)
        {
            text[i] = tolower(text[i]);
        }
    }
    return text;
}
string takeInput(string sysType = "0")
{
    cout << "---------------\n";
    string ans;
    for (const auto &pair : numricSystems)
    {
        if (pair.first == sysType)
        {
            continue;
        }
        cout << "- " << capitalize(pair.second) << ": " << pair.first << endl;
    }
    cout << "Type the base of the numric system: ";
    cin >> ans;
    if (numricSystems.count(ans) && ans != sysType)
        return ans;
    cout << "Not valid input\n";
    return "Not valid";
}
string takeValue(string t)
{
    cout << "---------------\n";
    cout << "Enter the value: ";
    string value;
    cin >> value;
    bool valid = true;
    if (t == "10")
    {
        for (char c : value)
        {
            if (!isdigit(c))
            {
                valid = false;
            }
        }
    }
    else if (t == "2")
    {
        for (char c : value)
        {
            if (c != '0' && c != '1')
            {
                valid = false;
            }
        }
    }
    else if (t == "8")
    {
        for (char c : value)
        {
            if (!isdigit(c) || c == '8' || c == '9')
            {
                valid = false;
            }
        }
    }
    else if (t == "16")
    {
        for (char c : value)
        {
            if (!(isdigit(c) ||
                  tolower(c) == 'a' ||
                  tolower(c) == 'b' ||
                  tolower(c) == 'c' ||
                  tolower(c) == 'd' ||
                  tolower(c) == 'e' ||
                  tolower(c) == 'f'))
            {
                valid = false;
            }
        }
    }
    return valid ? value : "Not valid";
}
string toDec(string value, string t)
{

    int ans = 0, power = 0, ty = stoi(t);
    for (int i = value.size() - 1; i >= 0; i--)
    {
        if (isdigit(value[i]))
        {

            ans += (value[i] - 48) * pow(ty, power);
        }
        else
        {
            switch (tolower(value[i]))
            {
            case 'a':
                ans += 10 * pow(ty, power);
                break;
            case 'b':
                ans += 11 * pow(ty, power);
                break;
            case 'c':
                ans += 12 * pow(ty, power);
                break;
            case 'd':
                ans += 13 * pow(ty, power);
                break;
            case 'e':
                ans += 14 * pow(ty, power);
                break;
            case 'f':
                ans += 15 * pow(ty, power);
                break;
            }
        }
        power++;
    }
    return to_string(ans);
}
string toBin(string value, string t)
{
    string ans = "";
    if (t == "10")
    {
        int num = stoi(value);
        while (num != 0)
        {

            ans.insert(0, to_string(num % 2));
            num /= 2;
        }
    }
    else if (t == "8")
    {
        for (int i = 0; i < value.size(); i++)
        {
            ans += binMap.at(value[i]).substr(1);
        }
    }
    else if (t == "16")
    {
        for (int i = 0; i < value.size(); i++)
        {
            ans += binMap.at(toupper(value[i]));
        }
    }

    return ans;
}
string toOct(string value, string t)
{
    string ans = "";
    if (t == "10")
    {
        int num = stoi(value);
        while (num != 0)
        {
            ans.insert(0, to_string(num % 8));
            num /= 8;
        }
    }
    else if (t == "2")
    {
        while (value.size() % 3 != 0)
        {
            value.insert(0, "0");
        }
        for (int i = 0; i < value.size(); i += 3)
        {
            string st = value.substr(i, 3);
            int v = 2, a = 0;
            for (char c : st)
            {
                a += (c - 48) * pow(2, v);
                v--;
            }
            ans += to_string(a);
        }
    }
    else if (t == "16")
    {
        ans = toOct(toBin(value, t), "2");
    }
    return ans;
}
string toHex(string value, string t)
{
    string ans = "";
    if (t == "10")
    {
        int num = stoi(value);
        int rem;
        while (num != 0)
        {
            rem = num % 16;
            if (rem < 10)
            {
                ans.insert(0, to_string(rem));
            }
            else
            {
                switch (rem)
                {
                case 10:
                    ans.insert(0, "A");
                    break;
                case 11:
                    ans.insert(0, "B");
                    break;
                case 12:
                    ans.insert(0, "C");
                    break;
                case 13:
                    ans.insert(0, "D");
                    break;
                case 14:
                    ans.insert(0, "E");
                    break;
                case 15:
                    ans.insert(0, "F");
                    break;
                }
            }
            num /= 16;
        }
    }
    else if (t == "2")
    {
        while (value.size() % 4 != 0)
        {
            value.insert(0, "0");
        }
        for (int i = 0; i < value.size(); i += 4)
        {
            string st = value.substr(i, 4);
            int v = 3, a = 0;
            for (char c : st)
            {
                a += (c - 48) * pow(2, v);
                v--;
            }
            if (a < 10)
            {

                ans += to_string(a);
            }
            else
            {
                switch (a)
                {
                case 10:
                    ans += "A";
                    break;
                case 11:
                    ans += "B";
                    break;
                case 12:
                    ans += "C";
                    break;
                case 13:
                    ans += "D";
                    break;
                case 14:
                    ans += "E";
                    break;
                case 15:
                    ans += "F";
                    break;
                }
            }
        }
    }
    else if (t == "8")
    {
        ans = toHex(toBin(value, t), "2");
    }
    return ans;
}
int main()
{
    cout << "Numric system changer\n";
    string in, ou, value;
    string ans;
    do
    {
        in = takeInput();
    } while (in == "Not valid");
    do
    {
        ou = takeInput(in);
    } while (ou == "Not valid");
    do
    {
        value = takeValue(in);
    } while (value == "Not valid");
    if (ou == "10")
    {
        ans = toDec(value, in);
    }
    else if (ou == "2")
    {

        ans = toBin(value, in);
    }
    else if (ou == "8")
    {
        ans = toOct(value, in);
    }
    else if (ou == "16")
    {
        ans = toHex(value, in);
    }
    cout << ans << endl;
    return 0;
}
