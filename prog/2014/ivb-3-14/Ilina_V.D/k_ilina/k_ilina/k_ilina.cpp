#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

vector<string> readLines(char* path);
string generate(string title);
string getStringName(char* msg);
string getCurrentYear();
string generateText();
string getRandomLines(int npart);
string getRandomLine(vector<string>* linesCollection);
void replaceStringInPlace(string& subject, const string& search, const string& replace);
void writeToFile(string* content, char* path);

#define REVIEWPATH "lines.txt"
#define FIGHTINGPATH "fighting.txt"
#define GAMEPLAYPATH "gameplay.txt"
#define DOWNLOADPATH "url.txt"

vector<string> reviewLines;
vector<string> fightingLines;
vector<string> gameplayLines;
vector<string> downloadLines;

string g_gameName;
string g_urlName;
string g_yearName;

int main()
{
	setlocale(LC_ALL, "Russian");
	//system("chcp 1251");
	srand((unsigned int)time(NULL));
	g_gameName = getStringName("Пожалуйста, введите имя игры");
	g_yearName = getCurrentYear();
	g_urlName = getStringName("Пожалуйста, введите адрес сайта игры");
	reviewLines = readLines(REVIEWPATH);
	fightingLines = readLines(FIGHTINGPATH);
	gameplayLines = readLines(GAMEPLAYPATH);
	downloadLines = readLines(DOWNLOADPATH);
	string result = generateText();
	writeToFile(&result, "output.txt");
	printf("\n\n%s\n\n", result.c_str());
	system("pause");
	return 0;
}

vector<string> readLines(char* path)
{
	vector<string> result;
	if (path == 0)
		return result;
	ifstream fs(path, ios::app);
	string line;
	while (getline(fs, line))
		result.push_back(line);
	fs.close();
	return result;
}

string getStringName(char* msg)
{
	char buf[100];
	printf("%s:\n", msg);
	fgets(buf, 100, stdin);
	if ((strlen(buf)>0) && (buf[strlen(buf) - 1] == '\n'))
		buf[strlen(buf) - 1] = '\0';
	return string(buf);
}

string getCurrentYear()
{
	time_t theTime = time(NULL);
	struct tm time_info;
	localtime_s(&time_info, &theTime);
	return to_string(time_info.tm_year + 1900);
}

string generateText()
{
	string result;
	for (int i = 0; i < 4; i++)
		result += getRandomLines(i) + " ";
	replaceStringInPlace(result, "%GAMENAME%", g_gameName);
	replaceStringInPlace(result, "%URLNAME%", g_urlName);
	replaceStringInPlace(result, "%YEARNAME%", g_yearName);
	return result;
}

string getRandomLines(int npart)
{
	string lines;
	switch (npart) {
	case 0:
		lines += getRandomLine(&reviewLines);
		break;
	case 1:
		lines += getRandomLine(&fightingLines);
		break;
	case 2:
		lines += getRandomLine(&gameplayLines);
		break;
	case 3:
		lines += getRandomLine(&downloadLines);
		break;
	default:
		break;
	}
	return lines;
}

string getRandomLine(vector<string>* linesCollection)
{
	return linesCollection->at(rand() % linesCollection->size());
}

void replaceStringInPlace(string& subject, const string& search, const string& replace) 
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

void writeToFile(string* content, char* path)
{
	ofstream out(path);
	out << *content;
	out.close();
}