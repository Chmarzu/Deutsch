#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>

#define BUFF 5
#define NomenFilesNum 21 //number of files for function Nomen + 1
#define NomenMainOpt 14 //options in main menu in Nomen
#define VerbFilesNum 5  //number of files for function Verb + 1
#define AdjektivFilesNum 2  //number of files for function Adjektiv + 1
#define FAIL_NUM 2  //number of approved attempts

using namespace std;

void Nomen(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail, fstream &source, fstream &answer, string ans);
int Sachen(int i, int mode);
int Essen(int i, int mode);
void Nomen_options(int i, int j, int mode, bool *opt);
void Nomen_file_opener(int &mode, fstream &source);

void Verb(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail,  fstream &source, fstream &answer, string ans);
void Verb_options(int i, int j, int mode, bool *opt);
void Verb_file_opener(int &mode, fstream &source);

void Adjektiv(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail,  fstream &source, fstream &answer, string ans);
void Adjektiv_options(int i, int j, int mode, bool *opt);
void Adjektiv_file_opener(int &mode, fstream &source);

void Praposition(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail,  fstream &source, fstream &answer, string ans);
void Praposition_options(int i, int j, int mode, bool *opt);
void Praposition_file_opener(int &mode, fstream &source);

void Rektion(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);

int file_manager(int maxnum, int record_size, fstream &source, string ans);
void screen_cleaner(int i, int line);

int main() {
    srand (time(NULL));
    int i, j, mode /*control over flow of program*/, maxnum /*amount of words from a file*/, randy[BUFF] /*array of randomly generated words (indexes)*/;
    short fail_num;
    bool finished = true /*indicates if a mode can be finished*/, rand_file = false /*for randomised file source*/, fail = false /*mistake in answers indicator*/;
    fstream source /*file from database*/, answer /*UI file*/;
    string ans /*for answer check*/;

    do {
        cout << "Wybierz tryb:" << endl << "1) Rzeczownik" << endl << "2) Czasownik" << endl
        << "3) Przymiotnik" << endl << "4) Przyimek" << endl << "5) Rekcja" << endl << "6) Wyjscie z programu" << endl;

        do {
        cin >> mode;

        if (mode < 1 || mode > 6)
            cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
        } while (mode < 1 || mode > 6);

        screen_cleaner(i, 70);

        switch (mode) {
        case 1:
            Nomen(i, j, mode, maxnum, &randy[0], fail_num, finished, rand_file, fail, source, answer, ans);
            break;

       case 2:
            Verb(i, j, mode, maxnum, &randy[0], fail_num, finished, rand_file, fail, source, answer, ans);
            break;

        case 3:
            Adjektiv(i, j, mode, maxnum, &randy[0], fail_num, finished, rand_file, fail, source, answer, ans);
            break;

        case 4:
            Praposition(i, j, mode, maxnum, &randy[0], fail_num, finished, rand_file, fail, source, answer, ans);
            break;

        case 5:
            Rektion(i, j, mode, maxnum, &randy[0], source, answer, ans);
            break;

        case 6:
            cout << "Do nastepnego razu!";
            Sleep(700);
            exit(0);
        }
    } while (mode != 6);

    return 0;
}

void Nomen(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail, fstream &source, fstream &answer, string ans) {
    struct word {   //info about word
        string article, noun_sg, noun_pl, transl;
    } buffer[BUFF];
    bool opt[4] = {false, true, false, false}; /*visibility of word's data*/

    do {
        do {
            cout << endl << "Ustawienia: 0" << endl << endl;

            cout << "Wybierz zakres slownictwa:";
            for (i = 0; i < NomenMainOpt; i++) {
            cout << endl << i + 1 << ") ";
                switch (i) {
                    case 0:
                        cout << "Wszystko";
                        break;

                    case 1:
                        cout << "Kartka pocztowa";
                        break;

                    case 2:
                        cout << "Ludzie";
                        break;

                    case 3:
                        cout << "Rodzina";
                        break;

                    case 4:
                        cout << "Rzeczy (kategoria)";
                        break;

                    case 5:
                        cout << "Jedzenie (kategoria)";
                        break;

                    case 6:
                        cout << "Napoje";
                        break;

                    case 7:
                        cout << "Pomieszczenia";
                        break;

                    case 8:
                        cout << "Czesci ciala";
                        break;

                    case 9:
                        cout << "Choroby";
                        break;

                    case 10:
                        cout << "Lekarstwa";
                        break;

                    case 11:
                        cout << "Budynek";
                        break;

                    case 12:
                        cout << "Miasto";
                        break;

                    case 13:
                        cout << "Hobby";
                        break;
                }
            }
            cout << endl << endl;

            cout << "Powrot do  Menu Glownego: " << NomenMainOpt + 1 << endl;

            cin >> mode;

            screen_cleaner(i, 70);

            if (!mode && mode != 5 && mode != 6)    //should possibly be changed so as to avoid adding more cases
                Nomen_options(i, j, mode, &opt[0]);
            else if (mode < 1 || mode > NomenMainOpt + 1)
                cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
            } while (mode < 1 || mode > NomenMainOpt + 1);
            cout << endl;

            if  (mode == NomenMainOpt + 1)
                finished = false;
            else {
                if (mode == 1)
                    rand_file = true;
                else if (mode == 5)
                    mode = Sachen(i, mode);
                else if (mode == 6)
                    mode = Essen(i, mode);
                else {
                    switch (mode) {
                        case 7:
                            mode = 12;
                            break;

                        case 8:
                            mode = 14;
                            break;

                        case 9:
                            mode = 15;
                            break;

                        case 10:
                            mode = 16;
                            break;

                        case 11:
                            mode = 17;
                            break;

                        case 12:
                            mode = 19;
                            break;

                        case 13:
                            mode = 20;
                            break;

                        case 14:
                            mode = 21;
                            break;
                    }
                }

                Nomen_file_opener(mode, source);


            if (mode != NomenFilesNum + 1) {
                if (!rand_file)     //for non-random file
                    maxnum = file_manager(maxnum, 6, source, ans);

                //drawing a record
                for (i = 0; i < BUFF; i++) {

                    if (rand_file) {    //for random file
                       do {
                            mode = rand() % NomenFilesNum + 1;   //drawing a random file
                       } while (mode == 1);

                       Nomen_file_opener(mode, source);

                       maxnum = file_manager(maxnum, 6, source, ans);
                    }

                    source.close();
                    Nomen_file_opener(mode, source);

                    do {
                    randy[i] = rand() % maxnum / 6 + 1; //drawing a random number

                    for (j = 0; j < randy[i]; j++) {
                        getline(source, ans);
                        getline(source, buffer[i].article);
                        getline(source, buffer[i].noun_sg);
                        getline(source, buffer[i].noun_pl);
                        getline(source, buffer[i].transl);
                        getline(source, ans);
                    }

                    source.close();
                    Nomen_file_opener(mode, source);

                    if (i > 0 && rand_file == false) {  //duplicate & impossible to answer records check
                        for (j = 0; j < i; j++) {
                            if (randy[i] == randy[j] || (buffer[i].article == "Pl" && opt[2] == false && opt[3] == false))
                                break;
                        }
                    } else
                        break;
                    } while (j < i);

                    if (rand_file)
                        source.close();
                }

                //user interface
                answer.open("program.txt",ios::out);

                for (i = 0; i < BUFF; i++) {
                    answer << i + 1 << ") ";
                    if (opt[0])
                        answer << buffer[i].article << " ";
                    if (opt[1])
                        answer << buffer[i].noun_sg;
                    if (opt[2])
                        answer << " (" << buffer[i].noun_pl << ")";
                    if (opt[3])
                        answer << " - " << buffer[i].transl;
                    answer << endl;
                }

                for (i = 0; i < BUFF; i++) {
                    answer << i + 1 << ") " << endl;
                    if (!opt[0])
                        answer << "Rodzajnik:" << endl << endl;
                    if (!opt[1])
                        answer << "Rzeczownik (liczba pojedyncza):" << endl << endl;
                    if (!opt[2])
                        answer << "Rzeczownik (liczba mnoga):" << endl << endl;
                    if (!opt[3])
                        answer << "Tlumaczenie (PL):" << endl << endl;
                    answer << endl;
                }

                answer.close();

                cout << "W pliku \"program\" znajduja sie przygotowane zadania." << endl
                << "Tam tez podaj brakujace informacje we wskazanych miejscach." << endl
                << "Format wczytywania rodzajnikow: der - r, die - e, das - s, liczba mnoga - Pl." << endl << endl
                << "Powrot do Menu Glownego: 0." << endl
                << "Aby kontyunowac wprowadz: 1" << endl;

                do {
                    cin >> mode;

                    if (mode < 0 || mode > 1)
                        cout << endl << "Bledna wartosc!" << endl << endl;
                } while(mode < 0 || mode > 1);

                screen_cleaner(i, 70);

                    if (mode == 1) {
                        do {
                            answer.open("program.txt",ios::in);

                            for (i = 0; i < BUFF + 3; i++)
                                getline (answer, ans);

                            for (i = 0; i < BUFF; i++) {
                                cout << i + 1 << ")" << endl;

                                if (!opt[0]) {
                                    cout << "Rodzajnik: ";
                                    if (ans.compare(buffer[i].article) != 0) {
                                            cout << "X Falsch";
                                            if (fail_num == FAIL_NUM)
                                                cout << "   " << buffer[i].article;
                                            fail = true;
                                    } else cout << "V Richtig";
                                    cout << endl;
                                }

                                if (!opt[1]) {
                                    if (!opt[0]) {
                                        for (j = 0; j < 2; j++)
                                            getline (answer, ans);
                                    }

                                    cout << "Rzeczownik (liczba pojedyncza): ";
                                    if (ans.compare(buffer[i].noun_sg) != 0) {
                                            cout << "X Falsch";
                                            if (fail_num == FAIL_NUM)
                                                cout << "   " << buffer[i].noun_sg;
                                            fail = true;
                                    } else cout << "V Richtig";
                                    cout << endl;
                                }

                                if (!opt[2]) {
                                    if (!opt[0] || !opt[1]) {
                                        for (j = 0; j < 2; j++)
                                            getline (answer, ans);
                                    }

                                    cout << "Rzeczownik (liczba mnoga): ";
                                    if (ans.compare(buffer[i].noun_pl) != 0) {
                                            cout << "X Falsch";
                                            if (fail_num == FAIL_NUM)
                                                cout << "   " << buffer[i].noun_pl;
                                            fail = true;
                                    } else cout << "V Richtig";
                                    cout << endl;
                                }

                                if (!opt[3]) {
                                    if (!opt[0] || !opt[1] || !opt[2]) {
                                        for (j = 0; j < 2; j++)
                                            getline (answer, ans);
                                    }

                                    cout << "Tlumaczenie: ";
                                    if (ans.compare(buffer[i].transl) != 0) {
                                            cout << "X Falsch";
                                            if (fail_num == FAIL_NUM)
                                                cout << "   " << buffer[i].transl;
                                            fail = true;
                                    } else cout << "V Richtig";
                                    cout << endl;
                                }

                                for (j = 0; j < 4; j++)
                                    getline (answer, ans);
                            }

                            answer.close();

                            if (fail) {
                                fail_num++;

                                if (fail_num < 2)
                                    cout << endl << "Powrot do Menu Glownego: 0" << endl << "Ponowne sprawdzenie: 1" << endl;
                                else if (fail_num == 2)
                                    cout << endl << "Powrot do Menu Glownego: 0" << endl << "Prawidlowe odpowiedzi: 1" << endl;
                                else
                                    cout << endl << "Powrot do Menu Glownego: 0" << endl;

                                fail = false;
                            } else cout << endl << "Powrot do Menu Glownego: 0" << endl;

                            cin >> mode;

                            if (mode < 0 || mode > 1)
                                cout << endl << "Bledna wartosc!" << endl << endl;

                            screen_cleaner(i, 70);
                        } while(mode && fail_num < FAIL_NUM + 1);
                    }

                    fail_num = 0;

                    source.close();
                }
            }
        } while (finished);
}

void Nomen_options(int i, int j, int mode, bool *opt) {
    short num;

    do {
        cout << endl << "Ustawienia" << endl << endl;

        cout << "1. Rodzajnik: ";
        if (!opt[0])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "2. Liczba pojedyncza: ";
        if (!opt[1])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "3. Liczba mnoga: ";
        if (!opt[2])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "4. Tlumaczenie (PL): ";
        if (!opt[3])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << endl << "Wybierz numer elemntu, ktory chcesz zmodyfikowac." << endl << "Wcisnij \"0\", aby opuscic panel ustawien." << endl;

        cin >> mode;

        screen_cleaner(i, 70);

        if (mode)
            opt[mode-1] = !opt[mode-1];

        num = opt[0] + opt[1] + opt[2] + opt[3];

        if (!mode) {
            if (!num || num == 4) {
                cout << endl << endl << "Niewlasciwa konfiguracja!" << endl
                << "Przynajmniej jeden element musi zostac wyswietlony oraz program nie moze wyswietlic wszystkich elementow." << endl << endl;
                Sleep(2000);
            } else if (!opt[1] && !opt[2] && !opt[3]) {
                cout << endl << endl << "Musi zostac wybrana jedna z opcji: 2-4." << endl << endl;
                Sleep(2000);
            }
        }

    } while (mode || !num || num == 4 || !opt[1] && !opt[2] && !opt[3]);
}

void Nomen_file_opener(int &mode, fstream &source) {
    switch (mode) {
        case 2:
            source.open("data\\Nomen\\Postkarte.txt",ios::in);
            break;

        case 3:
            source.open("data\\Nomen\\Leute.txt",ios::in);
            break;

        case 4:
            source.open("data\\Nomen\\Familie.txt",ios::in);
            break;

        case 5:
            source.open("data\\Nomen\\Sachen.txt",ios::in);
            break;

        case 6:
            source.open("data\\Nomen\\Möbel.txt",ios::in);
            break;

        case 7:
            source.open("data\\Nomen\\Essen.txt",ios::in);
            break;

        case 8:
            source.open("data\\Nomen\\Gemüse.txt",ios::in);
            break;

        case 9:
            source.open("data\\Nomen\\Obst.txt",ios::in);
            break;

        case 10:
            source.open("data\\Nomen\\Fleisch.txt",ios::in);
            break;

        case 11:
            source.open("data\\Nomen\\Süßigkeiten.txt",ios::in);
            break;

        case 12:
            source.open("data\\Nomen\\Getränke.txt",ios::in);
            break;

        case 13:
            source.open("data\\Nomen\\Geschirr.txt",ios::in);
            break;

        case 14:
            source.open("data\\Nomen\\Räume.txt",ios::in);
            break;

        case 15:
            source.open("data\\Nomen\\Körper.txt",ios::in);
            break;

        case 16:
            source.open("data\\Nomen\\Krankheit.txt",ios::in);
            break;

        case 17:
            source.open("data\\Nomen\\Medikamenten.txt",ios::in);
            break;

        case 18:
            source.open("data\\Nomen\\kleidung.txt",ios::in);
            break;

        case 19:
            source.open("data\\Nomen\\Gebäude.txt",ios::in);
            break;

        case 20:
            source.open("data\\Nomen\\Stadt.txt",ios::in);
            break;

        case 21:
            source.open("data\\Nomen\\Hobby.txt",ios::in);
            break;
    }
}

void Verb(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail, fstream &source, fstream &answer, string ans) {
    struct word {   //info about word
        string infinitiv, imperfekt, partizip_perfekt, hilfsverb, transl;
    } buffer[BUFF];
    bool opt[5] = {true, false, false, false, false}; /*visibility of word's data*/

    do {
        do {
            cout << endl << "Ustawienia: 0" << endl << endl;

            cout << "Wybierz zakres slownictwa:";
            for (i = 0; i < VerbFilesNum; i++) {
            cout << endl << i + 1 << ") ";
                switch (i) {
                    case 0:
                        cout << "Wszystko";
                        break;

                    case 1:
                        cout << "Czasowniki slabe";
                        break;

                    case 2:
                        cout << "Czasowniki mocne";
                        break;

                    case 3:
                        cout << "Czasowniki z sein";
                        break;

                    case 4:
                        cout << "Formy podstawowe";
                        break;
                }
            }
            cout << endl << endl;

            cout << "Powrot do  Menu Glownego: " << VerbFilesNum + 1 << endl;

            cin >> mode;

            screen_cleaner(i, 70);

            if (!mode)
                Verb_options(i, j, mode, &opt[0]);
            else if (mode < 1 || mode > VerbFilesNum + 1)
                cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
            } while (mode < 1 || mode > VerbFilesNum + 1);
            cout << endl;

            if  (mode == VerbFilesNum + 1)
                finished = false;
            else {
                if (mode == 1)
                    rand_file = true;
                else
                    Verb_file_opener(mode, source);

                if (!rand_file)     //for non-random file
                    maxnum = file_manager(maxnum, 7, source, ans);

                //drawing a record
                for (i = 0; i < BUFF; i++) {

                    if (rand_file) {    //for random file
                       do {
                            mode = rand() % VerbFilesNum + 1;   //drawing a random file
                       } while (mode == 1);

                       Verb_file_opener(mode, source);

                       maxnum = file_manager(maxnum, 7, source, ans);
                    }

                    source.close();
                    Verb_file_opener(mode, source);

                    do {
                    randy[i] = rand() % maxnum / 7 + 1; //drawing a random number

                    if (i > 0 && rand_file == false) {  //duplicate check
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

                    if (rand_file)
                        source.close();
                }

                //user interface
                answer.open("program.txt",ios::out);

                for (i = 0; i < BUFF; i++) {
                        answer << i + 1 << ") ";

                        if (opt[0])
                            answer << buffer[i].infinitiv << " ";

                        if (opt[1])
                            answer << buffer[i].imperfekt << " ";
                        else if (opt[0] && (opt[2] || opt[3]))
                                answer << " ";

                        if (opt[2])
                            answer << buffer[i].partizip_perfekt << " ";
                        else if (opt[0] || opt[1] && opt[3])
                                answer << " ";

                        if (opt[3])
                            answer << buffer[i].hilfsverb << " ";
                        else if (opt[0] || opt[1] || opt[2])
                                answer << " ";

                        if (opt[4])
                            answer << " - " << buffer[i].transl;
                        answer << endl;
                    }

                    for (i = 0; i < BUFF; i++) {
                        answer << i + 1 << ") " << endl;
                        if (!opt[0])
                            answer << "Bezokolicznik (Infinitiv):" << endl << endl;
                        if (!opt[1])
                            answer << "Partizip I:" << endl << endl;
                        if (!opt[2])
                            answer << "Partizip II:" << endl << endl;
                        if (!opt[3])
                            answer << "Czasownik pomocniczy:" << endl << endl;
                        if (!opt[4])
                            answer << "Tlumaczenie (PL):" << endl << endl;
                        answer << endl;
                    }

                    answer.close();

                    cout << "W pliku \"program\" znajduja sie przygotowane zadania." << endl
                    << "Tam tez podaj brakujace informacje we wskazanych miejscach." << endl
                    << "Format wczytywania czasownikow pomocniczych: haben - h, sein - s." << endl << endl
                    << "Powrot do Menu Glownego: 0." << endl
                    << "Aby kontyunowac wprowadz: 1" << endl;

                for (i = 0; i < BUFF; i++)  //probably to be ereased
                    answer << buffer[i].infinitiv << " - " << buffer[i].transl << endl;

                do {
                        cin >> mode;

                        if (mode < 0 || mode > 1)
                            cout << endl << "Bledna wartosc!" << endl << endl;
                    } while(mode < 0 || mode > 1);

                screen_cleaner(i, 70);

                if (mode == 1) {
                    do {
                        answer.open("program.txt",ios::in);

                        for (i = 0; i < BUFF + 3; i++)
                            getline (answer, ans);

                        for (i = 0; i < BUFF; i++) {
                            cout << i + 1 << ")" << endl;

                            if (!opt[0]) {
                                cout << "Bezokolicznik (Infinitiv): ";
                                if (ans.compare(buffer[i].infinitiv) != 0) {
                                        cout << "X Falsch";
                                        if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].infinitiv;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            if (!opt[1]) {
                                if (!opt[0]) {
                                    for (j = 0; j < 2; j++)
                                        getline (answer, ans);
                                }

                                cout << "Partizip I: ";
                                if (ans.compare(buffer[i].imperfekt) != 0) {
                                        cout << "X Falsch";
                                        if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].imperfekt;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            if (!opt[2]) {
                                if (!opt[0] || !opt[1]) {
                                    for (j = 0; j < 2; j++)
                                        getline (answer, ans);
                                }

                                cout << "Partizip II: ";
                                if (ans.compare(buffer[i].partizip_perfekt) != 0) {
                                        cout << "X Falsch";
                                        if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].partizip_perfekt;
                                        fail = true;
                                } else cout << "V Richtig";
                                  cout << endl;
                            }

                            if (!opt[3]) {
                                if (!opt[0] || !opt[1] || !opt[2]) {
                                    for (j = 0; j < 2; j++)
                                        getline (answer, ans);
                                }

                                cout << "Czasownik pomocniczy: ";
                                if (ans.compare(buffer[i].hilfsverb) != 0) {
                                    cout << "X Falsch";
                                    if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].hilfsverb;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            if (!opt[4]) {
                                if (!opt[0] || !opt[1] || !opt[2] || !opt[3]) {
                                    for (j = 0; j < 2; j++)
                                        getline (answer, ans);
                                }

                                cout << "Tlumaczenie: ";
                                if (ans.compare(buffer[i].transl) != 0) {
                                    cout << "X Falsch";
                                    if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].transl;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            for (j = 0; j < 4; j++)
                                getline (answer, ans);
                        }

                        answer.close();

                        if (fail) {
                            fail_num++;

                            if (fail_num < 2)
                                cout << endl << "Powrot do Menu Glownego: 0" << endl << "Ponowne sprawdzenie: 1" << endl;
                            else if (fail_num == 2)
                                cout << endl << "Powrot do Menu Glownego: 0" << endl << "Prawidlowe odpowiedzi: 1" << endl;
                            else
                                cout << endl << "Powrot do Menu Glownego: 0" << endl;

                            fail = false;
                        } else cout << endl << "Powrot do Menu Glownego: 0" << endl;

                        cin >> mode;

                        if (mode < 0 || mode > 1)
                            cout << endl << "Bledna wartosc!" << endl << endl;

                        screen_cleaner(i, 70);
                    } while(mode && fail_num < FAIL_NUM + 1);
                }

                fail_num = 0;

                source.close();
            }
        } while (finished);
}

int Sachen(int i, int mode) {
    cout << "Wybierz zakres slownictwa (Rzeczy) :";
    for (i = 0; i < 4; i++) {
        cout << endl << i + 1 << ") ";
        switch (i) {
            case 0:
                cout << "Ogolne";
                break;

            case 1:
                cout << "Meble";
                break;

            case 2:
                cout << "Naczynia";
                break;

            case 3:
                cout << "Ubrania";
                break;
        }
    }
    cout << endl << endl;

    cout << "Powrot do  Menu Glownego: 5" << endl;

    cin >> mode;

    switch (mode) {
        case 1:
            mode = 5;
            break;

        case 2:
            mode = 6;
            break;

        case 3:
            mode = 13;
            break;

        case 4:
            mode = 18;
            break;

        case 5:
            mode = NomenFilesNum + 1;
            break;
    }

    screen_cleaner(i, 70);

    return mode;
}

int Essen(int i, int mode) {
    cout << "Wybierz zakres slownictwa (Jedzenie) :";
    for (i = 0; i < 5; i++) {
        cout << endl << i + 1 << ") ";
        switch (i) {
            case 0:
                cout << "Ogolne";
                break;

            case 1:
                cout << "Warzywa";
                break;

            case 2:
                cout << "Owoce";
                break;

            case 3:
                cout << "Mieso";
                break;

            case 4:
                cout << "Slodycze";
                break;
        }
    }
    cout << endl << endl;

    cout << "Powrot do  Menu Glownego: 6" << endl;

    cin >> mode;

    switch (mode) {
        case 1:
            mode = 7;
            break;

        case 2:
            mode = 8;
            break;

        case 3:
            mode = 9;
            break;

        case 4:
            mode = 10;
            break;

        case 5:
            mode = 11;
            break;

        case 6:
            mode = NomenFilesNum + 1;
            break;
    }

    screen_cleaner(i, 70);

    return mode;
}

void Verb_options(int i, int j, int mode, bool *opt) {
    short num;

    do {
        cout << endl << "Ustawienia" << endl << endl;

        cout << "1. Bezokolicznik (Infinitiv): ";
        if (!opt[0])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "2. Partizip I: ";
        if (!opt[1])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "3. Partizip II: ";
        if (!opt[2])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "4. Czasownik pomocniczy: ";
        if (!opt[3])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "5. Tlumaczenie (PL): ";
        if (!opt[4])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << endl << "Wybierz numer elemntu, ktory chcesz zmodyfikowac." << endl << "Wcisnij \"0\", aby opuscic panel ustawien." << endl;

        cin >> mode;

        screen_cleaner(i, 70);

        if (mode)
            opt[mode-1] = !opt[mode-1];

        num = opt[0] + opt[1] + opt[2] + opt[3] + opt[4];

        if (!mode) {
            if (!num || num == 5) {
                cout << endl << endl << "Niewlasciwa konfiguracja!" << endl
                << "Przynajmniej jeden element musi zostac wyswietlony oraz program nie moze wyswietlic wszystkich elementow." << endl << endl;
                Sleep(2000);
            } else if (!opt[0] && !opt[1] && !opt[2] && !opt[4]) {
                cout << endl << endl << "Musi zostac wybrana jedna z opcji: 1-3 lub 5." << endl << endl;
                Sleep(2000);
            }
        }
    } while (mode || !num || num == 5 || !opt[0] && !opt[1] && !opt[2] && !opt[4]);
}

void Verb_file_opener(int &mode, fstream &source) {
    switch (mode) {
        case 2:
            source.open("data\\Verb\\Schwache.txt",ios::in);
            break;

        case 3:
            source.open("data\\Verb\\Starke.txt",ios::in);
            break;

        case 4:
            source.open("data\\Verb\\Mit Sein.txt",ios::in);
            break;

        case 5:
            source.open("data\\Verb\\Grundformen.txt",ios::in);
            break;
    }
}

void Adjektiv(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail,  fstream &source, fstream &answer, string ans) {
    struct word {   //info about word
        string adjektiv, transl;
    } buffer[BUFF];
    bool opt[2] = {true, false}; /*visibility of word's data*/

    do {
        do {
            cout << endl << "Ustawienia: 0" << endl << endl;

            cout << "Wybierz zakres slownictwa:";
            for (i = 0; i < AdjektivFilesNum; i++) {
            cout << endl << i + 1 << ") ";
                switch (i) {
                    case 0:
                        cout << "Wszystko";
                        break;

                    case 1:
                        cout << "Stan cywilny";
                        break;
                }
            }
            cout << endl << endl;

            cout << "Powrot do  Menu Glownego: " << AdjektivFilesNum + 1 << endl;

            cin >> mode;

            screen_cleaner(i, 70);

            if (!mode)
                Adjektiv_options(i, j, mode, &opt[0]);
            else if (mode < 1 || mode > AdjektivFilesNum + 1)
                cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
            } while (mode < 1 || mode > AdjektivFilesNum + 1);
            cout << endl;

            if  (mode == AdjektivFilesNum + 1)
                finished = false;
            else {
                if (mode == 1)
                    rand_file = true;
                else
                    Adjektiv_file_opener(mode, source);

                if (!rand_file)     //for non-random file
                    maxnum = file_manager(maxnum, 2, source, ans);

                //drawing a record
                for (i = 0; i < BUFF; i++) {

                    if (rand_file) {    //for random file
                       do {
                            mode = rand() % AdjektivFilesNum + 1;   //drawing a random file
                       } while (mode == 1);

                       Adjektiv_file_opener(mode, source);

                       maxnum = file_manager(maxnum, 2, source, ans);
                    }

                    source.close();
                    Adjektiv_file_opener(mode, source);

                    do {
                    randy[i] = rand() % maxnum / 2 + 1; //drawing a random number

                    if (i > 0 && rand_file == false) {  //duplicate check
                        for (j = 0; j < i; j++) {
                            if (randy[i] == randy[j])
                                break;
                        }
                    } else
                        break;
                    } while (j < i);


                    for (j = 0; j < randy[i]; j++) {
                        getline(source, ans);
                        getline(source, buffer[i].adjektiv);
                        getline(source, buffer[i].transl);
                        getline(source, ans);
                    }

                    if (rand_file)
                        source.close();
                }

                //user interface
                answer.open("program.txt",ios::out);

                for (i = 0; i < BUFF; i++) {
                        answer << i + 1 << ") ";

                        if (opt[0])
                            answer << buffer[i].adjektiv << " ";

                        if (opt[1])
                            answer << " - " << buffer[i].transl;
                        answer << endl;
                    }

                    for (i = 0; i < BUFF; i++) {
                        answer << i + 1 << ") " << endl;
                        if (!opt[0])
                            answer << "Przymiotnik:" << endl << endl;
                        if (!opt[1])
                            answer << "Tlumaczenie (PL):" << endl << endl;
                        answer << endl;
                    }

                    answer.close();

                    cout << "W pliku \"program\" znajduja sie przygotowane zadania." << endl
                    << "Tam tez podaj brakujace informacje we wskazanych miejscach." << endl << endl
                    << "Powrot do Menu Glownego: 0." << endl
                    << "Aby kontyunowac wprowadz: 1" << endl;

                do {
                        cin >> mode;

                        if (mode < 0 || mode > 1)
                            cout << endl << "Bledna wartosc!" << endl << endl;
                    } while(mode < 0 || mode > 1);

                screen_cleaner(i, 70);

                if (mode == 1) {
                    do {
                        answer.open("program.txt",ios::in);

                        for (i = 0; i < BUFF + 3; i++)
                            getline (answer, ans);

                        for (i = 0; i < BUFF; i++) {
                            cout << i + 1 << ")" << endl;

                            if (!opt[0]) {
                                cout << "Przymiotnik: ";
                                if (ans.compare(buffer[i].adjektiv) != 0) {
                                        cout << "X Falsch";
                                        if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].adjektiv;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            if (!opt[1]) {
                                if (!opt[0]) {
                                    for (j = 0; j < 2; j++)
                                        getline (answer, ans);
                                }

                                cout << "Tlumaczenie: ";
                                if (ans.compare(buffer[i].transl) != 0) {
                                        cout << "X Falsch";
                                        if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].transl;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            for (j = 0; j < 4; j++)
                                getline (answer, ans);
                        }

                        answer.close();

                        if (fail) {
                            fail_num++;

                            if (fail_num < 2)
                                cout << endl << "Powrot do Menu Glownego: 0" << endl << "Ponowne sprawdzenie: 1" << endl;
                            else if (fail_num == 2)
                                cout << endl << "Powrot do Menu Glownego: 0" << endl << "Prawidlowe odpowiedzi: 1" << endl;
                            else
                                cout << endl << "Powrot do Menu Glownego: 0" << endl;

                            fail = false;
                        } else cout << endl << "Powrot do Menu Glownego: 0" << endl;

                        cin >> mode;

                        if (mode < 0 || mode > 1)
                            cout << endl << "Bledna wartosc!" << endl << endl;

                        screen_cleaner(i, 70);
                    } while(mode && fail_num < FAIL_NUM + 1);
                }

                fail_num = 0;

                source.close();
        }
    } while (finished);
}

void Adjektiv_options(int i, int j, int mode, bool *opt) {
    short num;

    do {
        cout << endl << "Ustawienia" << endl << endl;

        cout << "1. Przyimek: ";
        if (!opt[0])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "2. Tlumaczenie (PL): ";
        if (!opt[1])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << endl << "Wybierz numer elemntu, ktory chcesz zmodyfikowac." << endl << "Wcisnij \"0\", aby opuscic panel ustawien." << endl;

        cin >> mode;

        screen_cleaner(i, 70);

        if (mode)
            opt[mode-1] = !opt[mode-1];

        num = opt[0] + opt[1];

        if (!mode) {
            if (!num || num == 2) {
                cout << endl << endl << "Niewlasciwa konfiguracja!" << endl
                << "Przynajmniej jeden element musi zostac wyswietlony oraz program nie moze wyswietlic wszystkich elementow." << endl << endl;
                Sleep(2000);
            }
        }
    } while (mode || !num || num == 2);
}

void Adjektiv_file_opener(int &mode, fstream &source) {
    switch (mode) {
        case 2:
            source.open("data\\Adjektiv\\Familienstand.txt",ios::in);
            break;
    }
}

void Praposition(int i, int j, int mode, int maxnum, int *randy, short fail_num, bool finished, bool rand_file, bool fail,  fstream &source, fstream &answer, string ans) {
    struct word {   //info about word
        string prap, kasus, transl;
    } buffer[BUFF];
    bool opt[3] = {true, false, false}; /*visibility of word's data*/

    do {
        do {
            cout << endl << "Ustawienia: 0" << endl << endl;

            cout << "Wybierz zakres slownictwa:";
            for (i = 0; i < 4; i++) {
            cout << endl << i + 1 << ") ";
                switch (i) {
                    case 0:
                        cout << "Wszystko";
                        break;

                    case 1:
                        cout << "Dativ";
                        break;

                    case 2:
                        cout << "Akkusativ";
                        break;

                    case 3:
                        cout << "Dativ/Akkusativ";
                        break;
                }
            }
            cout << endl << endl;

            cout << "Powrot do  Menu Glownego: " << 5 << endl;

            cin >> mode;

            screen_cleaner(i, 70);

            if (!mode)    //should possibly be changed so as to avoid adding more cases
                Praposition_options(i, j, mode, &opt[0]);
            else if (mode < 1 || mode > 5)
                cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
        } while (mode < 1 || mode > 5);
        cout << endl;

        if  (mode == 5)
                finished = false;
            else {
                if (mode == 1)
                    rand_file = true;
                else
                    Praposition_file_opener(mode, source);

                if (!rand_file)     //for non-random file
                    maxnum = file_manager(maxnum, 5, source, ans);

                //drawing a record
                for (i = 0; i < BUFF; i++) {

                    if (rand_file) {    //for random file
                       do {
                            mode = rand() % 4;   //drawing a random file
                       } while (mode == 1);

                       Praposition_file_opener(mode, source);

                       maxnum = file_manager(maxnum, 5, source, ans);
                    }

                    source.close();
                    Praposition_file_opener(mode, source);

                    do {
                    randy[i] = rand() % maxnum / 5 + 1; //drawing a random number

                    if (i > 0 && rand_file == false) {  //duplicate check
                        for (j = 0; j < i; j++) {
                            if (randy[i] == randy[j])
                                break;
                        }
                    } else
                        break;
                    } while (j < i);


                    for (j = 0; j < randy[i]; j++) {
                        getline(source, ans);
                        getline(source, buffer[i].prap);
                        getline(source, buffer[i].kasus);
                        getline(source, buffer[i].transl);
                        getline(source, ans);
                    }

                    if (rand_file)
                        source.close();
                }

                //user interface
                answer.open("program.txt",ios::out);

                for (i = 0; i < BUFF; i++) {
                    answer << i + 1 << ") ";

                    if (opt[0])
                        answer << buffer[i].prap << " ";

                    if (opt[1])
                        answer << " + " << buffer[i].kasus << " ";
                    else if (opt[0] && (opt[2] || opt[3]))
                        answer << " ";

                    if (opt[2])
                        answer << " - " << buffer[i].transl;
                    answer << endl;
                }

                for (i = 0; i < BUFF; i++) {
                    answer << i + 1 << ") " << endl;
                    if (!opt[0])
                        answer << "Przyimek:" << endl << endl;
                    if (!opt[1])
                        answer << "Prypadek:" << endl << endl;
                    if (!opt[2])
                        answer << "Tlumaczenie (PL):" << endl << endl;
                    answer << endl;
                }

                answer.close();

                cout << "W pliku \"program\" znajduja sie przygotowane zadania." << endl
                << "Tam tez podaj brakujace informacje we wskazanych miejscach." << endl
                << "Format wczytywania przypadków: D lub A." << endl << endl
                << "Powrot do Menu Glownego: 0." << endl
                << "Aby kontyunowac wprowadz: 1" << endl;

                do {
                    cin >> mode;

                    if (mode < 0 || mode > 1)
                        cout << endl << "Bledna wartosc!" << endl << endl;
                } while(mode < 0 || mode > 1);

                screen_cleaner(i, 70);

                if (mode == 1) {
                    do {
                        answer.open("program.txt",ios::in);

                        for (i = 0; i < BUFF + 3; i++)
                            getline (answer, ans);

                        for (i = 0; i < BUFF; i++) {
                            cout << i + 1 << ")" << endl;

                            if (!opt[0]) {
                                cout << "Przyimek: ";
                                if (ans.compare(buffer[i].prap) != 0) {
                                        cout << "X Falsch";
                                        if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].prap;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            if (!opt[1]) {
                                if (!opt[0]) {
                                    for (j = 0; j < 2; j++)
                                        getline (answer, ans);
                                }

                                cout << "Prypadek: ";
                                if (ans.compare(buffer[i].kasus) != 0) {
                                        cout << "X Falsch";
                                        if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].kasus;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            if (!opt[2]) {
                                if (!opt[0] || !opt[1]) {
                                    for (j = 0; j < 2; j++)
                                        getline (answer, ans);
                                }

                                cout << "Tlumaczenie: ";
                                if (ans.compare(buffer[i].transl) != 0) {
                                    cout << "X Falsch";
                                    if (fail_num == FAIL_NUM)
                                            cout << "   " << buffer[i].transl;
                                        fail = true;
                                } else cout << "V Richtig";
                                cout << endl;
                            }

                            for (j = 0; j < 4; j++)
                                getline (answer, ans);
                        }

                        answer.close();

                        if (fail) {
                            fail_num++;

                            if (fail_num < 2)
                                cout << endl << "Powrot do Menu Glownego: 0" << endl << "Ponowne sprawdzenie: 1" << endl;
                            else if (fail_num == 2)
                                cout << endl << "Powrot do Menu Glownego: 0" << endl << "Prawidlowe odpowiedzi: 1" << endl;
                            else
                                cout << endl << "Powrot do Menu Glownego: 0" << endl;

                            fail = false;
                        } else cout << endl << "Powrot do Menu Glownego: 0" << endl;

                        cin >> mode;

                        if (mode < 0 || mode > 1)
                            cout << endl << "Bledna wartosc!" << endl << endl;

                        screen_cleaner(i, 70);
                    } while(mode && fail_num < FAIL_NUM + 1);
                }

                fail_num = 0;

                source.close();
            }
    } while (finished);
}

void Praposition_options(int i, int j, int mode, bool *opt) {
    short num;

    do {
        cout << endl << "Ustawienia" << endl << endl;

        cout << "1. Przyimek: ";
        if (!opt[0])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "2. Przypadek: ";
        if (!opt[1])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << "3. Tlumaczenie (PL): ";
        if (!opt[2])
            cout << "wyl" << endl;
        else
            cout << "wl" << endl;

        cout << endl << "Wybierz numer elemntu, ktory chcesz zmodyfikowac." << endl << "Wcisnij \"0\", aby opuscic panel ustawien." << endl;

        cin >> mode;

        screen_cleaner(i, 70);

        if (mode)
            opt[mode-1] = !opt[mode-1];

        num = opt[0] + opt[1] + opt[2];

        if (!mode) {
            if (!num || num == 3) {
                cout << endl << endl << "Niewlasciwa konfiguracja!" << endl
                << "Przynajmniej jeden element musi zostac wyswietlony oraz program nie moze wyswietlic wszystkich elementow." << endl << endl;
                Sleep(2000);
            }
        }

    } while (mode || !num || num == 3);
}

void Praposition_file_opener(int &mode, fstream &source) {
    switch (mode) {
        case 2:
            source.open("data\\Präposition\\Dativ.txt",ios::in);
            break;

        case 3:
            source.open("data\\Präposition\\Akkusativ.txt",ios::in);
            break;

        case 4:
            source.open("data\\Präposition\\Dativ-Akkusativ.txt",ios::in);
            break;
    }
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

int file_manager(int maxnum, int record_size, fstream &source, string ans) {
    //record_size - amount of lines of which contains a record

    //file crash test
    if(source.good() == false) {
        cout << "Error! Source file doesn't exist!";
        getchar();
        exit(0);
    }

    //file contents check (amount of words)
    while (getline(source, ans))
        maxnum++;

    if (maxnum % record_size >= 1) {
        cout << "Error! Incorrect data file content!";
        getchar();
        exit(0);
    }

    return maxnum;
}

//Funkcja "screen_cleaner" odpowiada za "czyszczenie ekranu" - przesuwanie modeu tak, aby nie bylo widac wczesniejszych, niepotrzebnych komunikatow.
void screen_cleaner (int i, int line) {
    for (i = 0; i < line; i++)
        cout << endl;
}
