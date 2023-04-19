#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
//#include <windows.h>
#define BUFF 3

using namespace std;

void Nomen(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);
void Verb(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);
void Adjektiv(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);
void Rektion(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);

int main() {
    srand (time(NULL));
    int mode;

    int i, j, maxnum = 0/*weird init bug*/, randy[BUFF];
    fstream source, answer;
    string ans;

    cout << "Wybierz tryb:" << endl << "1) Rzeczownik" << endl << "2) Czasownik" << endl
    /*<< "3) Przymiotnik" << endl*/ << "4) Rekcja" << endl << "5) Wyjscie z programu" << endl;

    do {
    cin >> mode;
    if (mode < 1 || mode > 5)
        cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
    } while (mode < 1 || mode > 5);
    cout << endl;

    switch (mode) {
    case 1:
        Nomen(i, j, mode, maxnum, &randy[0], source, answer, ans);
        break;

    case 2:
        Verb(i, j, mode, maxnum, &randy[0], source, answer, ans);
        break;

    case 3:
        Adjektiv(i, j, mode, maxnum, &randy[0], source, answer, ans);
        break;

    case 4:
        Rektion(i, j, mode, maxnum, &randy[0], source, answer, ans);
        break;
    case 5:
        cout << "Do nastepnego razu!";
        exit(0);
        break;
    }

    return 0;
}

void Nomen(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans) {
    struct word {
        string article, noun_sg, noun_pl, transl;
    } buffer[BUFF];
    bool rand_file = false;

    cout << "Wybierz zakres slownictwa:" << endl << "1) Wszystko" << endl << "2) Ogolne" << endl << "3) Czesci ciala"
    << endl << "4) Ubrania" << endl;

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
            source.open("data\\Nomen\\plik.txt",ios::in);
            break;

        case 3:
            source.open("data\\Nomen\\body.txt",ios::in);
            break;

        case 4:
            source.open("data\\Nomen\\kleidung.txt",ios::in);
            break;
        }

    if (!rand_file) {
        //file crash test
        if(source.good() == false) {
            cout << "Error! Source file doesn't exist!";
            getchar();
            exit(0);
        }

        //file contents check (amount of words)
        while (getline(source, ans))
            maxnum++;

        if (maxnum % 6 >= 1) {
            cout << "Error! Incorrect data file content!";
            getchar();
            exit(0);
        }
    }

    //drawing word
    for (i = 0; i < BUFF; i++) {

        if (rand_file) {
           do {
                mode = rand() % 4 + 1;   //drawing random file
           } while (mode == 1);

           switch (mode) { //opening file
        case 2:
            source.open("data\\Nomen\\plik.txt",ios::in);
            break;

        case 3:
            source.open("data\\Nomen\\body.txt",ios::in);
            break;

        case 4:
            source.open("data\\Nomen\\kleidung.txt",ios::in);
            break;
        }

           //file crash test
            if(source.good() == false) {
                cout << "Error! Source file doesn't exist!";
                getchar();
                exit(0);
            }

            //file contents check (amount of words)
            while (getline(source, ans))
                maxnum++;

            if (maxnum % 6 >= 1) {
                cout << "Error! Incorrect data file content!";
                getchar();
                exit(0);
            }
        }

        source.close();
        switch (mode) { //opening file
        case 2:
            source.open("data\\Nomen\\plik.txt",ios::in);
            break;

        case 3:
            source.open("data\\Nomen\\body.txt",ios::in);
            break;

        case 4:
            source.open("data\\Nomen\\kleidung.txt",ios::in);
            break;
        }

        do {
        randy[i] = rand() % maxnum / 6 + 1;

        if (i > 0 && rand_file == false) {
            for (j = 0; j < i; j++) {
                if (randy[i] == randy[j])
                    break;
            }
        } else
            break;
        } while (j < i);


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

void Verb(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans) {
    struct word {
        string infinitiv, imperfekt, partizip_perfekt, hilfsverb, transl;
    } buffer[BUFF];
    string ans2;

    source.open("data\\Verb\\mit_sein.txt",ios::in);

    //file crash test
    if(source.good() == false) {
        cout << "Error! Source file doesn't exist!";
        getchar();
        exit(0);
    }

    //file contents check (amount of words)
    while (getline(source, ans))
        maxnum++;

    if (maxnum % 7 >= 1) {
        cout << "Error! Incorrect data file content!";
        getchar();
        exit(0);
    }

    //drawing word
    for (i = 0; i < BUFF; i++) {
        source.close();
        source.open("data\\Verb\\mit_sein.txt",ios::in);

        do {
        randy[i] = rand() % maxnum / 7 + 1;

        if (i > 0) {
            for (j = 0; j < i; j++) {
                if (randy[i] == randy[j])
                    break;
            }
        } else
            break;
        } while (j < i);


        for (j = 0; j < randy[i]; j++) {
            getline(source, ans);
            getline(source, buffer[i].infinitiv);
            getline(source, buffer[i].imperfekt);
            getline(source, buffer[i].partizip_perfekt);
            getline(source, buffer[i].hilfsverb);
            getline(source, buffer[i].transl);
            getline(source, ans);
        }
    }

    //user interface
    answer.open("program.txt",ios::out);
    for (i = 0; i < BUFF; i++)
        answer << buffer[i].infinitiv << " - " << buffer[i].transl << endl;

    cout << "Jesli chcesz opuscic program wprowadz: 0" << endl;
    cout << "Podaj wlasciwa forme Partizip II a nastepnie czasownik pomocniczy (h lub s):" << endl << endl;

    for (i = 0; i < BUFF; i++) {
        for (j = 0; j < 2; j++) {
            cout << i + 1 << "." << endl;
            cin >> ans;
            cin >> ans2;

            if (ans.compare("0") == 0) {    //immediate exit
                cout << "Czy na pewno chcesz zamknac program?" << endl << "(Jesli tak ponownie wprowadz: 0)" << endl;
                cin >> ans;
                if (ans.compare("0") == 0)
                    exit(0);
            } else if (buffer[i].partizip_perfekt.compare(ans) == 1 || buffer[i].hilfsverb.compare(ans2) == 1)
                cout << endl << "Bledna odpowiedz!" << endl << endl;
            else if (buffer[i].partizip_perfekt.compare(ans) == 0 || buffer[i].hilfsverb.compare(ans2) == 0)
                break;
        }

        if (j == 2)
            cout << "Prawidlowa odpowiedz to: " << buffer[i].partizip_perfekt << " + " << buffer[i].hilfsverb;

        cout << endl;
    }

    source.close();
    answer.close();


}
void Adjektiv(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans) {

}

void Rektion(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans) {
    struct word {
        string reflexivpronomen, verb, praposition, kasus, transl;
    } buffer[BUFF];
    string ans2;

    source.open("data\\rektion.txt",ios::in);

    //file crash test
    if(source.good() == false) {
        cout << "Error! Source file doesn't exist!";
        getchar();
        exit(0);
    }

    //file contents check (amount of words)
    while (getline(source, ans))
        maxnum++;

    if (maxnum % 7 >= 1) {
        cout << "Error! Incorrect data file content!";
        getchar();
        exit(0);
    }

    //drawing word
    for (i = 0; i < BUFF; i++) {
        source.close();
        source.open("data\\rektion.txt",ios::in);

        do {
        randy[i] = rand() % maxnum / 7 + 1;

        if (i > 0) {
            for (j = 0; j < i; j++) {
                if (randy[i] == randy[j])
                    break;
            }
        } else
            break;
        } while (j < i);


        for (j = 0; j < randy[i]; j++) {
            getline(source, ans);
            getline(source, buffer[i].reflexivpronomen);
            getline(source, buffer[i].verb);
            getline(source, buffer[i].praposition);
            getline(source, buffer[i].kasus);
            getline(source, buffer[i].transl);
            getline(source, ans);
        }
    }

    //user interface
    answer.open("program.txt",ios::out);
    for (i = 0; i < BUFF; i++) {
            if (buffer[i].reflexivpronomen != "-")
                answer << buffer[i].reflexivpronomen << " ";
            answer << buffer[i].verb << " - " << buffer[i].transl << endl;
    }

    cout << "Jesli chcesz opuscic program wprowadz: 0" << endl;
    cout << "Podaj wlasciwy przyimek a nastepnie przypadek (D lub A):" << endl << endl;

    for (i = 0; i < BUFF; i++) {
        for (j = 0; j < 2; j++) {
            cout << i + 1 << "." << endl;
            cin >> ans;
            cin >> ans2;

            if (ans.compare("0") == 0) {    //immediate exit
                cout << "Czy na pewno chcesz zamknac program?" << endl << "(Jesli tak ponownie wprowadz: 0)" << endl;
                cin >> ans;
                if (ans.compare("0") == 0)
                    exit(0);
            } else if (buffer[i].praposition.compare(ans) == 1 || buffer[i].kasus.compare(ans2) == 1)
                cout << endl << "Bledna odpowiedz!" << endl << endl;
            else if (buffer[i].praposition.compare(ans) == 0 || buffer[i].kasus.compare(ans2) == 0)
                break;
        }

        if (j == 2)
            cout << "Prawidlowa odpowiedz to: " << buffer[i].praposition << " + " << buffer[i].kasus;

        cout << endl;
    }

    source.close();
    answer.close();
}
