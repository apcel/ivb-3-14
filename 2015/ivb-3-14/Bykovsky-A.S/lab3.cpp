//вариант 7
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <clocale>
#include <string>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    int const MAX = 100; //максимум 100 слов
    string s1;
    string s2;
    //массивы слов
    string words1[MAX];
    string words2[MAX];
    //счетчики для слов
    int count_w1 = 1;
    int count_w2 = 1;
    string st[2*MAX]; //для обработки строк
    int w = 0;
    int i;
    int j; //для циклов
    cout << "введите строку 1: ";
    getline(cin, s1);
    cout << "введите строку 2: ";
    getline(cin, s2);

    for(i = 0; i < s1.size(); i++)
        if(s1[i] == ' ')
            count_w1++;
    for(i = 0; i < s2.size(); i++)
        if(s2[i] == ' ')
            count_w2++;
    int i1 = 0; //счетчик для 1-й строки
    int i2 = 0; //счетчик для 2-й строки
    for(i = 0; i < s1.size(); i++) {
        if(s1[i] == ' ') {
            i1++;
            continue;
        }
        words1[i1] += s1[i];
    }
    for(i = 0; i < s2.size(); i++) {
        if(s2[i] == ' ') {
            i2++;
            continue;
        }
        words2[i2] += s2[i];
    }
    cout << "слова встречаются хотя бы в 1 строке" << endl;
    bool opt;
    for(i = 0; i < count_w1; i++) {
        opt = false;
        for(j = 0; j < w; j++)
            if(st[j] == words1[i]) {
                opt = true;
                break;
            }
        if(!opt) {
            st[w] = words1[i];
            w++;
        }
    }
    for(i = 0; i < count_w2; i++) {
        opt = false;
        for(j = 0; j < w; j++)
            if(st[j] == words2[i]) {
                opt = true;
                break;
            }
        if(!opt) {
            st[w] = words2[i];
            w++;
        }
    }
    for(i = 0; i < w; i++) {
        cout << st[i] << ' ';
        st[i] = "";
    }
    w = 0;
    cout << endl << endl;
    cout << "встречаются только в 1-й строке" << endl;
    for(i = 0; i < count_w1; i++) {
        opt = false;
        for(j = 0; j < count_w2; j++)
            if(words1[i] == words2[j]) {
                opt = true;
                break;
            }
            if(!opt) {
                st[w] =  words1[i];
                w++;
                cout << words1[i] << ' ';
            }
    }
    cout << endl << endl << "Встречаются только в одной из строк" << endl;
    for(i = 0; i < w; i++)
        cout << st[i] << ' ';
    for(i = 0; i < count_w2; i++) {
        opt = false;
        for(j = 0; j < count_w1; j++)
            if(words2[i] == words1[j]) {
                opt = true;
                break;
            }
            if(!opt) {
                cout << words2[i] << ' ';
            }
    }
    cout << endl;
    _getch();
    return 0;
}
