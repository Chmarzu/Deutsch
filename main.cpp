#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
//#include <windows.h>
#define BUFF 3

using namespace std;

void Nomen(/*int i, int j, int maxnum, int randy[0], fstream source, fstream answer, string ans*/);
void Verb(/*int &i, int &j, int &maxnum,int randy[0], fstream &source, fstream &answer, string &ans*/);
void Adjektiv(/*int &i, int &j, int &maxnum,int randy[0], fstream &source, fstream &answer, string &ans*/);

int main() {
    srand (time(NULL));
    int mode;
    /*
    int i, j, maxnum = 0/*weird init bug, randy[BUFF];
    fstream source, answer;
    string ans;
    */

    cout << "Wybierz tryb:" << endl << "1) Rzeczownik" << endl << "2) Czasownik" << endl
    << "3) Przymiotnik" << endl << "4) Wyjscie z programu" << endl;
    do {
    cin >> mode;
    if (mode < 1 || mode > 4)
        cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
    } while (mode < 1 || mode > 4);

    cout << endl;
    switch (mode) {
    case 1:
        Nomen(/*i, j, maxnum, randy[0], source, answer, ans*/);
        break;

    case 2:
        Verb();
        break;

    case 3:
        Adjektiv();
        break;

    case 4:
        cout << "Do nastepnego razu!";
        exit(0);
        break;
    }

    return 0;
}

void Nomen(/*int &i, int &j, int &maxnum,int randy[0], fstream &source, fstream &answer, string &ans*/) {
    struct word {
        string article, noun_sg, noun_pl, transl;
    } buffer[BUFF];

    int i, j, maxnum = 0/*weird init bug*/, randy[BUFF];
    fstream source, answer;
    string ans;
    int mode;
    bool rand_file = false;

    cout << "Wybierz zakres slownictwa:" << endl << "1)Wszystko" << endl << "2)Ogolne" << endl << "3)Czesci ciala" << endl << "4)Ubrania" << endl;
    do {
        cin >> mode;
        if (mode < 1 || mode > 4)
            cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
        } while (mode < 1 || mode > 4);

        cout << endl;

        switch (mode) { //opening file
        case 1:
            rand_file = true;
            break;

        case 2:
            source.open("data\\plik.txt",ios::in);
            break;

        case 3:
            source.open("data\\body.txt",ios::in);
            break;

        case 4:
            source.open("data\\kleidung.txt",ios::in);
            break;
        }

    if (!rand_file) {
        //file crash test
        if(source.good() == false) {
            cout << "Error! Source file doesn't exist!";
            getchar();
            exit(0);
        }

        //counting amount of words
        while (getline(source, ans))
            maxnum++;

        if (maxnum % 6 == 1) {
            cout << "Error! Incorrect data file content!";
            getchar();
            exit(0);
        }
    }

    //drawing word
    for (i = 0; i < BUFF; i++) {

        if (rand_file) {
           mode = rand() % 4 + 1;   //drawing random file
            cout << mode;

           switch (mode) { //opening file
        case 2:
            source.open("data\\plik.txt",ios::in);
            break;

        case 3:
            source.open("data\\body.txt",ios::in);
            break;

        case 4:
            source.open("data\\kleidung.txt",ios::in);
            break;
        }

           //file crash test
            if(source.good() == false) {
                cout << "Error! Source file doesn't exist!";
                getchar();
                exit(0);
            }

            //counting amount of words
            while (getline(source, ans))
                maxnum++;

            if (maxnum % 6 == 1) {
                cout << "Error! Incorrect data file content!";
                getchar();
                exit(0);
            }
        }

        source.close();
        switch (mode) { //opening file
        case 2:
            source.open("data\\plik.txt",ios::in);
            break;

        case 3:
            source.open("data\\body.txt",ios::in);
            break;

        case 4:
            source.open("data\\kleidung.txt",ios::in);
            break;
        }

        //do {  //anti-duplication module -- not working
        randy[i] = rand() % maxnum / 3 + 1;
        /*cout << randy[i] << " ";

        if (i > 0)
            for (j = 0; j < BUFF; j++) {
                if (randy[i] == randy[j]) {
                    break;
                }
            }
        else
            break;
        cout << j << endl;
        Sleep(1000);
        } while (j < BUFF);*/


        for (j = 0; j < randy[i]; j++) {
            getline(source, ans);
            getline(source, buffer[i].article);
            getline(source, buffer[i].noun_sg);
            getline(source, buffer[i].noun_pl);
            getline(source, buffer[i].transl);
            getline(source, ans);
        }

        if (rand_file)
            source.close();
    }

    //user interface
    answer.open("program.txt",ios::out);
    for (i = 0; i < BUFF; i++)
        answer << buffer[i].noun_sg << " - " << buffer[i].transl << endl << buffer[i].noun_pl  << endl;

    cout << "Jesli chcesz opuscic program wprowadz: 0" << endl;
    cout << "Podaj rodzajnik (der - r, die - e, das - s):" << endl << endl;

    for (i = 0; i < BUFF; i++) {

    do {
        cout << i + 1 << "." << endl;
        cin >> ans;

        if (ans.compare("0") == 0) {    //immediate exit
            cout << "Czy na pewno chcesz zamknac program?" << endl << "(Jesli tak ponownie wprowadz: 0)" << endl;
            cin >> ans;
            if (ans.compare("0") == 0)
                exit(0);
        } else if (buffer[i].article != ans)
            cout << endl << "Bledna odpowiedz!" << endl << endl;
    } while(buffer[i].article != ans);

    cout << endl;
    }

    source.close();
    answer.close();
}

void Verb(/*int &i, int &j, int &maxnum,int randy[0], fstream &source, fstream &answer, string &ans*/) {

}
void Adjektiv(/*int &i, int &j, int &maxnum,int randy[0], fstream &source, fstream &answer, string &ans*/) {

}
