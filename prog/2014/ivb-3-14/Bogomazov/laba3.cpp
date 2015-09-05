#include <iostream>
#include <string>
#include <vector>

/* Лаб. работа 3
 Вариант 6
 ИВБ-3-14
 Богомазов Степан */

using namespace std;

// Переставить буквы в тексте с помощью заданного ключа.
string encrypt(string text, int key[]) 
{
    string new_text = "";
    for (int i = 0; i < 6; i++) {
        new_text += text[key[i] - 1];
    }
    return new_text;
}

int main() 
{
    string s;
    cin >> s;
    
    // Ключ для шифрования
    int key1[] = {1, 4, 2, 3, 6, 5};
    
    s = encrypt(s, key1);
    cout << s << endl;
    
    // Ключ для дешифрования
    int key2[] = {1, 3, 4, 2, 6, 5};
    
    s = encrypt(s, key2);
    cout << s << endl;
    cin.get();
    cin.get();
}
