#include "mylib.h"

struct Studentas
{
    string vardas="", pavarde="";
    vector<int> paz;
    float egz=0;
    double vid=0, med=0;
    int count=0;
};


void pild(Studentas &temp);
void spausd(Studentas &temp);

int main()
{
    char rezimas;
    int max_n = 10; // maksimalus studentu skaicius
    int n = 0; // kolkas ivestu studentu skaicius
    vector<Studentas> studentai(max_n); // paskiriama atmintis mokinių vektoriui
    do
    {
        // iskvieciama pild funkcija norint gauti dabartinio mokinio duomenis
        pild(studentai[n]);

        // paklausti naudotojo, ar jis nori įvesti kitą mokinį
        cout << "Ar norite ivesti dar vieno studento duomenis? Iveskite 1, jei norite. Iveskite 2, jei nenorite ";
        string answer;
        cin >> answer;

        // padidinamas mokinių skaičius ir tęsiamas arba nutraukiamas ciklas
        n++;
        if (answer == "2" || n >= max_n)
        {
            break;
        }
    }
    while (true);

    // spausdinti visų įvestų mokinių duomenis
    for(int i = 0; i<n; i++)
    {
        spausd(studentai[i]);
    }

    // išeinama
    return 0;
}

void pild(Studentas &temp)
{
    cout << "Iveskite varda: ";
    string vardas;
    cin >> vardas;
    while (cin.fail() || !all_of(vardas.begin(), vardas.end(), [](unsigned char c)
{
    return isalpha(c);
    }))
    {
        cout << "Klaida: vardas gali buti sudarytas tik is raidziu. Iveskite varda dar karta: ";
        cin.clear(); //isvalomi cin error flagai
        cin.ignore(10000, '\n'); //ignoruoja netinkamai ivestus simbolius
        cin >> vardas;
    }

    temp.vardas = vardas;

    cout << "Iveskite pavarde: ";
    string pavarde;
    cin >> pavarde;

    while (cin.fail() || !all_of(pavarde.begin(), pavarde.end(), [](unsigned char c)
{
    return isalpha(c);
    }))
    {
        cout << "Klaida: pavarde gali buti sudaryta tik is raidziu. Iveskite pavarde dar karta: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> pavarde;
    }

    temp.pavarde = pavarde;

    int max_paz_sk = 10; // maksimalus leidziamas pazymiu skaicius
    vector<int> paz;

    cout << "Iveskite pazymius. Baigti ivedima iveskite ne skaiciu: ";

    int grade;
    while (cin >> grade && temp.paz.size() < max_paz_sk)
    {
        temp.paz.push_back(grade);
    }

    cin.clear();
    cin.ignore(10000, '\n');

    temp.paz = paz;

    cout << "Iveskite egzamino pazymi: ";
    while (!(cin >> temp.egz))
    {
        cout << "Klaida: pazymys gali buti tik skaicius. Bandykite dar karta ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Duomenys irasyti." << endl;
}

void spausd(Studentas &temp)
{
    vector<int> pazymiai = temp.paz;
    double vidurkis = 0.0, mediana = 0.0;

// skaiciuoja vidurki
    if (!pazymiai.empty())
    {
        double sum = accumulate(pazymiai.begin(), pazymiai.end(), 0.0);
        vidurkis = sum / (temp.count-1);
    }

// skaiciuoja mediana
    if (!pazymiai.empty())
    {
        sort(pazymiai.begin(), pazymiai.end());
        int n = pazymiai.size();
        if (n % 2 == 0)
        {
            mediana = (pazymiai[n/2 - 1] + pazymiai[n/2]) / 2.0;
        }
        else
        {
            mediana = pazymiai[n/2];
        }
    }
    cout << "Ar norite galutinio balo vidurkio (1), ar medianos (2)? ";
    char rezimas;
    cin >> rezimas;
    while (rezimas != '1' && rezimas != '2')
    {
        cout << "Klaida: neteisingas pasirinkimas. Iveskite 1 arba 2: ";
        cin >> rezimas;
    }
    if (rezimas == '1')
    {
        temp.vid = 0.4 * vidurkis + 0.6 * temp.egz;
        cout<<endl<<left<<setw(15)<<"Vardas"
            <<setw(20)<<"Pavarde"
            <<setw(15)<<"Galutinis (Med.)"<<endl;
        cout<<"---------------------------------------------------"<<endl;
        cout<<endl<<left<<setw(15)<<temp.vardas
            <<setw(20)<<temp.pavarde;
        cout << fixed << setprecision(2) << right << setw(5) << ((rezimas == '1') ? temp.vid : temp.med) << endl;
    }
    else
    {
        temp.med = 0.4 * mediana + 0.6 * temp.egz;
        cout<<endl<<left<<setw(15)<<"Vardas"
            <<setw(20)<<"Pavarde"
            <<setw(15)<<"Galutinis (Med.)"<<endl;
        cout<<"---------------------------------------------------"<<endl;
        cout<<endl<<left<<setw(15)<<temp.vardas
            <<setw(20)<<temp.pavarde;
        cout << fixed << setprecision(2) << right << setw(5) << ((rezimas == '2') ? temp.vid : temp.med) << endl;
    }
}
