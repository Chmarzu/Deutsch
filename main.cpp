#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#define BUFF 5
#define NomenFilesNum 9 //number of files for function Nomen + 1
#define VerbFilesNum 5  //number of files for function Verb + 1
#define FAIL_NUM 2  //number of approved attempts

using namespace std;

void Nomen(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);
void Nomen_options(int i, int j, int mode, bool *opt);
void Nomen_file_opener(int &mode, fstream &source);

void Verb(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);
void Verb_options(int i, int j, int mode, bool *opt);
void Verb_file_opener(int &mode, fstream &source);

void Adjektiv(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);
void Rektion(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans);
void screen_cleaner(int i, int line);

int main() {
    srand (time(NULL));
    int i, j, mode /*control over flow of program*/, maxnum /*amount of words from a file*/, randy[BUFF] /*array of randomly generated words (indexes)*/;
    fstream source /*file from database*/, answer /*UI file*/;
    string ans /*for answer check*/;

    do {
        cout << "Wybierz tryb:" << endl << "1) Rzeczownik" << endl << "2) Czasownik" << endl
        /*<< "3) Przymiotnik" << endl*/ << "4) Rekcja" << endl << "5) Wyjscie z programu" << endl;

        do {
        cin >> mode;

        if (mode < 1 || mode > 5)
            cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
        } while (mode < 1 || mode > 5);

        screen_cleaner(i, 70);

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
            Sleep(700);
            exit(0);
        }
    } while (mode != 5);

    return 0;
}

void Nomen(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans) {
    struct word {   //info about word
        string article, noun_sg, noun_pl, transl;
    } buffer[BUFF];
    bool rand_file = false /*for randomised file source*/, opt[4] = {false, true, false, false} /*visibility of word's data*/, fail = false /*mistake in answers indicator*/;

    do {
        cout << endl << "Ustawienia: 0" << endl << endl;

        cout << "Wybierz zakres slownictwa:";
        for (i = 0; i < NomenFilesNum; i++) {
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
                    cout << "Rzeczy";
                    break;

                case 5:
                    cout << "Meble";
                    break;

                case 6:
                    cout << "Ogolne";
                    break;

                case 7:
                    cout << "Czesci ciala";
                    break;

                case 8:
                    cout << "Ubrania";
                    break;
            }
        }
        cout << endl;

        cout << "Powrot do  Menu Glownego: " << NomenFilesNum + 1 << endl;

        cin >> mode;

        screen_cleaner(i, 70);

        if (!mode)
            Nomen_options(i, j, mode, &opt[0]);
        else if (mode < 1 || mode > NomenFilesNum + 1)
            cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
        } while (mode < 1 || mode > NomenFilesNum + 1);
        cout << endl;

        if  (mode != NomenFilesNum + 1) {
            if (mode == 1)
                rand_file = true;
            else
                Nomen_file_opener(mode, source);



        if (!rand_file) {   //for non-random file
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

        //drawing a record
        for (i = 0; i < BUFF; i++) {

            if (rand_file) {    //for random file
               do {
                    mode = rand() % NomenFilesNum + 1;   //drawing a random file
               } while (mode == 1);

                Nomen_file_opener(mode, source);

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
            Nomen_file_opener(mode, source);

            do {
            randy[i] = rand() % maxnum / 6 + 1; //drawing a random number

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
        << "Format wczytywania rodzajnikow: der - r, die - e, das - s." << endl << endl
        << "Powrot do Menu Rzeczownik: 0." << endl
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
                                    fail = true;
                            } else cout << "V Richtig";
                            cout << endl;
                        }

                        for (j = 0; j < 4; j++)
                            getline (answer, ans);
                    }

                    answer.close();

                    if (fail) {
                        cout << endl << "Powrot do Menu Glownego: 0" << endl << "Ponowne sprawdzenie: 1" << endl;
                        fail = false;
                    }
                    else cout << endl << "Powrot do Menu Glownego: 0" << endl;

                    cin >> mode;

                    if (mode < 0 || mode > 1)
                        cout << endl << "Bledna wartosc!" << endl << endl;

                    screen_cleaner(i, 70);
                } while(mode);
            }

            source.close();
        }
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

        if (!mode && (!num || num == 4)) {
            cout << endl << endl << "Niewlasciwa konfiguracja!" << endl
            << "Przynajmniej jeden element musi zostac wyswietlony oraz program nie moze wyswietlic wszystkich elementow." << endl << endl;
            Sleep(2000);
        }
    } while (mode || !num || num == 4);
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
            source.open("data\\Nomen\\plik.txt",ios::in);
            break;

        case 8:
            source.open("data\\Nomen\\body.txt",ios::in);
            break;

        case 9:
            source.open("data\\Nomen\\kleidung.txt",ios::in);
            break;
    }
}

void Verb(int i, int j, int mode, int maxnum, int *randy, fstream &source, fstream &answer, string ans) {
    struct word {   //info about word
        string infinitiv, imperfekt, partizip_perfekt, hilfsverb, transl;
    } buffer[BUFF];
    bool rand_file = false /*for randomised file source*/, opt[5] = {true, false, false, false, false} /*visibility of word's data*/, fail = false /*mistake in answers indicator*/;
    short fail_num;

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
        cout << endl;

        cout << "Powrot do  Menu Glownego: " << VerbFilesNum + 1 << endl;

        cin >> mode;

        screen_cleaner(i, 70);

        if (!mode)
            Verb_options(i, j, mode, &opt[0]);
        else if (mode < 1 || mode > VerbFilesNum + 1)
            cout << endl << endl << "Niewlasciwa liczba!" << endl << endl;
        } while (mode < 1 || mode > VerbFilesNum + 1);
        cout << endl;

        if  (mode != VerbFilesNum + 1) {
            if (mode == 1)
                rand_file = true;
            else
                Verb_file_opener(mode, source);

            if (!rand_file) {   //for non-random file
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
            }

            //drawing a record
            for (i = 0; i < BUFF; i++) {

                if (rand_file) {    //for random file
                   do {
                        mode = rand() % VerbFilesNum + 1;   //drawing a random file
                   } while (mode == 1);

                    Verb_file_opener(mode, source);

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
                    else if (opt[0])
                            answer << " ";

                    if (opt[2])
                        answer << buffer[i].partizip_perfekt << " ";
                    else if (opt[0] || opt[1])
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
                << "Powrot do Menu Czasownik: 0." << endl
                << "Aby kontyunowac wprowadz: 1" << endl;

            for (i = 0; i < BUFF; i++)
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
                        if (fail_num != 2)
                            cout << endl << "Powrot do Menu Glownego: 0" << endl << "Ponowne sprawdzenie: 1" << endl;
                        else
                            cout << "Powrot do Menu Glownego: 0" << endl;
                        fail_num++;
                        fail = false;
                    } else cout << endl << "Powrot do Menu Glownego: 0" << endl;

                    cin >> mode;

                    if (mode < 0 || mode > 1)
                        cout << endl << "Bledna wartosc!" << endl << endl;

                    screen_cleaner(i, 70);
                } while(mode);
            }

            source.close();
        }
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

        if (!mode && (!num || num == 5)) {
            cout << endl << endl << "Niewlasciwa konfiguracja!" << endl
            << "Przynajmniej jeden element musi zostac wyswietlony oraz program nie moze wyswietlic wszystkich elementow." << endl << endl;
            Sleep(2000);
        }
    } while (mode || !num || num == 5);
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

//Funkcja "screen_cleaner" odpowiada za "czyszczenie ekranu" - przesuwanie modeu tak, aby nie bylo widac wczesniejszych, niepotrzebnych komunikatow.
void screen_cleaner (int i, int line) {
    for (i = 0; i < line; i++)
        cout << endl;
}
