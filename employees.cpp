#include <iostream>
//Deklaracja bibliotek potrzebnych do wyswieltania daty.
#include <windows.h>
#include <winbase.h>

using namespace std;

//Klasa "Osoba"
class Person{
protected:
    string name, secName;
    int birth_year;
    //Deklaracja przyjazni z funkcj¹ globaln¹ "stworzEmerytow()", ktora wykorzystuje pola tej klasy.
    friend void createPensioners(Person *p);
public:
    //Konstruktory (kolejno domyslny i parametryzujacy)
    Person(){};
    Person(string name, string secName, int birth_year){
        this->name=name;
        this->secName=secName;
        this->birth_year=birth_year;
    };
    //Funkcja "wiek()" wyliczajaca wiek stworzonej osoby poprzez odjecie od pobranego z systemu roku, roku urodzenia osoby.
    int age(){
        SYSTEMTIME st;
        GetSystemTime(&st);
        return st.wYear-this->birth_year;
    };
    //Funkcja "pokazInfo()" wyswietla informacje o obiekcie klasy "Osoba".
    void showInfo(){
        cout<<"Information about the person"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Second name: "<<secName<<endl;
        cout<<"Year of birth: "<<birth_year<<endl<<endl;
    }
};
//Klasa "Pracownik" dziedziczaca publicznie z klasy "Osoba".
class Employee : public Person{
protected:
    string voivodeship;
    static const double min_wage;
public:
    //Konstruktor parametryzuj¹cy, który na liœcie ma pola zarówno swojej klasy jak i klasy bazowej.
    Employee(string name, string secName, int birth_year, string voivodeship):Person(name, secName, birth_year){
        this->voivodeship=voivodeship;
    }
    //Akcesor
    void setVoi(string v){
        this->voivodeship=v;
    }
};
//Definicja wartosci pola stalego stalego.
const double Employee::min_wage=3000;

//Klasa "Informatyk" dziedziczaca publicznie z klasy "Pracownik".
class ITspecialist : public Employee{
private:
    string specialization;
    double multiplier;
    double wage=multiplier*min_wage;
public:
    //Konstruktor parametryzuj¹cy zawieraj¹cy na swojej liscie pola swojej klasy jak i klas bazowych.
    ITspecialist(string name, string secName, int birth_year, string voivodeship, string specialization, double multiplier):Employee(name, secName, birth_year, voivodeship){
        this->specialization=specialization;
        this->multiplier=multiplier;
    };
    //Konstruktor kopiujacy przyjmuj¹cy za argumenty pola, ktore maja zostac zmienione oraz referencje do kopiowanego obiektu.
    ITspecialist(string name, string secName, int birth_year, const ITspecialist& c):Employee(name, secName, birth_year, voivodeship){
        this->name=name;
        this->secName=secName;
        this->birth_year=birth_year;
        voivodeship=c.voivodeship;
        specialization=c.specialization;
        multiplier=c.multiplier;
    }
    //Metoda "pokazInfo()" wyswietlajaca informacje o obiekcie.
    void showInfo(){
        cout<<"Name: "<<name<<endl;
        cout<<"Second name: "<<secName<<endl;
        cout<<"Year of birth: "<<birth_year<<endl;
        cout<<"Voivodeship: "<<voivodeship<<endl;
        cout<<"Specialization: "<<specialization<<endl;
        cout<<"Multiplier: "<<multiplier<<endl;
    }
};
//Klasa "Emeryt", ktora dziedziczy publicznie z klasy "Osoba".
class Pensioner : public Person{
private:
    double pension;
    //Deklaracja przyjazni z funkcj¹ globaln¹ "stworzEmerytow()", ktora wykorzystuje pole tej klasy.
    friend void createPensioners(Person *p);
};

//Funkcja "stworzEmerytow()" przyjmuje za argument wskaznik na tablice wskaznikow na obiekty klasy "Osoba".
//Na poczatku definiuje licznik z wartoscia poczatkowa rowna 0, ktora zliczy mi, ile obiektow zwraca wartosc funkcji "wiek()" wieksza od 65.
//Nastepnie tworze tablice dynamiczna obiektow klasy "Emeryt" o wielkosci takiej, jaka posiada licznik.
//Przeszukuje tablice osob w poszukiwaniu obiektow, ktorych funkcja "wiek()" zwraca wartosc wieksza niz 65.
//Definiuje nowa zmienna c2 (skrot od counter2) z wartoscia poczatkowa 0, ktora bedzie indeksem, pod ktory bede "kopiowal" obiekty.
//Miejsce zajete dotychczas przez "skopiowany" obiekt klasy "Osoba" zostaje zastapione pustym wskaznikiem.
//Na koncu tablica zostaje usunieta, aby zwolnic zajmowane przez siebie miejsce w pamieci.
void createPensioners(Person* p){
    int counter=0;
    for (int i=0;i<3;i++){
        if(p[i].age()>65){
            counter++;
        }
    }
    Pensioner* PenTab=new Pensioner[counter];
    for(int j=0;j<counter;j++){
        if(p[j].age()>65){
            static int c2=0;
            PenTab[c2].name=p->name;
            PenTab[c2].secName=p->secName;
            PenTab[c2].birth_year=p->birth_year;
            PenTab[c2].pension=2000*(j+1);
            PenTab[c2].showInfo();
            c2++;
            p[j]=nullptr;
        }
    }
    delete [] PenTab;
}
int main(){
    //Utworzenie obiektu p1 klasy "Osoba" i wyswietlenie informacji o nim.
    Person p1("Adam","Maciejczyk",1983);
    p1.showInfo();

    //Utworzenie obiektu i1 klasy "Informatyk" za pomoca konstruktora parametryzujacego i wyswietlenie informacji o nim razem z wywolaniem funkcji "wiek()".
    ITspecialist i1("Michael","Phillips",1974,"Masovian","graphics",2.4);
    cout<<"Information about specialist 1:"<<endl;
    i1.showInfo();
    cout<<"Age: "<<i1.age()<<endl<<endl;

    //Utworzenie obiektu i2 klasy "Informatyk za pomoca kontruktora kopiujacego i wyswietlenie informacji o nim razem z wywolaniem funkcji "wiek()".
    ITspecialist i2("Frank","Collins",1940,i1);
    cout<<"Information about specialist 2:"<<endl;
    i2.showInfo();
    cout<<"Age: "<<i2.age()<<endl<<endl;

    //Zmiana wartosci pola "wojewodztwo" dla obiektu i2 oraz ponowne wyswietlenie informacji o nim.
    i2.setVoi("Lesser Poland");
    cout<<"Information about specialist 2 after changes:"<<endl;
    i2.showInfo();
    cout<<"Age: "<<i2.age()<<endl<<endl;

    //Utworzenie tablicy dynamicznej wskaznikow na obiekty klasy "Osoba" i wpisanie ich do tablicy.
    Person** people_tab=new Person*[3]{&p1,&i1,&i2};

    //Wyswietlenie informacji o obiektach, na ktore wskazuja wskazniki w tablicy.
    for(int i=0;i<3;i++){
        people_tab[i]->showInfo();
    }

    //Wywolanie funkcji "stworzEmerytow()", ktora pzyjmuje za argument wskaznik na tablice wskaznikow na obiekty klasy "Osoba".
    createPensioners(*people_tab);
    //Usuniecie tablicy dynamicznej wskaznikow na obiekty klasy "Osoba", aby zwolnic miejsce w pamieci.
    delete [] people_tab;

    return 0;
}
