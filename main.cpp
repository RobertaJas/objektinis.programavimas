#include "mylib.h"

int main()
{
    int max_n = 10; // maksimalus studentu skaicius
    int n = 0; // kolkas ivestu studentu skaicius
    vector<Studentas> studentai; // paskiriama atmintis mokinių vektoriui
    char rezimas;
    studentai.reserve(10);
    string answer;
    do
    {
        // iskvieciama pild funkcija norint gauti dabartinio mokinio duomenis
        pild(studentai,n);
        // paklausti naudotojo, ar jis nori įvesti kitą mokinį
        cout << "Ar norite ivesti dar vieno studento duomenis? Iveskite 1, jei norite. Iveskite 2, jei nenorite ";
        cin >> answer;
        // padidinamas mokinių skaičius ir tęsiamas arba nutraukiamas ciklas
        n++;
        if (answer == "2" || n >= max_n)
        {
            break;
        }
    }
    while (true);
    cout << "Ar norite galutinio balo vidurkio (1), ar medianos (2)? ";
    cin >> rezimas;
    while (rezimas != '1' && rezimas != '2')
    {
        cout << "Klaida: neteisingas pasirinkimas. Iveskite 1 arba 2: ";
        cin >> rezimas;
    }
    cout<<endl<<left<<setw(15)<<"Vardas"<<setw(20)<<"Pavarde";
    if (rezimas == '1')
    {
        cout<<setw(15)<<"Galutinis (Vid.)"<<endl;
    }
    else
    {
        cout<<setw(15)<<"Galutinis (Med.)"<<endl;
    }
    cout<<"---------------------------------------------------"<<endl;
    // spausdinti visų įvestų mokinių duomenis
    for(int i = 0; i<n; i++)
    {
        spausd(studentai[i],rezimas);
    }
    return 0;
}

void pild(vector<Studentas> &studentai, int n)
{
    string vardas;
    string pavarde;
    int p;
    cout << "Iveskite varda: ";
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
    studentai[n].vardas = vardas;
    cout << "Iveskite pavarde: ";
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
    studentai[n].pavarde = pavarde;
    cout << "Iveskite pazymius. Noredami baigti ivedima iveskite ne skaiciu: ";
    do{
        bool nerapazymiu = true;
        cin>>p;
        if(!cin){
            if(studentai[n].paz.empty()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Iveskite bent viena pazymi. ";
                nerapazymiu = false;
            }
            else
                break;
        }
        if(p >= 0 && p <= 10 && nerapazymiu)
            studentai[n].paz.push_back(p);
        else
            cout << "Pazymys gali buti tik skaicius tarp 0 ir 10" << endl;
    } while(cin || studentai[n].paz.empty());
    cin.clear();
    cin.ignore(10000, '\n');

    cout << "Iveskite egzamino pazymi: ";
    while (!(cin >> studentai[n].egz) || studentai[n].egz<0 || studentai[n].egz>10 )
    {
        cout << "Klaida: pazymys gali buti tik skaicius tarp 0 ir 10. Bandykite dar karta ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Duomenys irasyti." << endl;
}

void spausd(Studentas &temp, char rezimas)
{
    double vidurkis = 0.0, mediana = 0.0;


    if (rezimas == '1') // skaiciuoja vidurki
    {
        double sum = accumulate(temp.paz.begin(),temp.paz.end(),0.);
        vidurkis = sum / temp.paz.size();
        temp.vid = 0.4 * vidurkis + 0.6 * temp.egz;
        cout<<endl<<left<<setw(15)<<temp.vardas<<setw(20)<<temp.pavarde;
        cout << fixed << setprecision(2) << right << setw(5) << temp.vid;
    }
    else // skaiciuoja mediana
    {
        sort(temp.paz.begin(), temp.paz.end());
        int n = temp.paz.size();
        if (n % 2 == 0)
        {
            mediana = (temp.paz[n/2 - 1] + temp.paz[n/2]) / 2.0;
        }
        else
        {
            mediana = temp.paz[n/2];
        }
        temp.med = 0.4 * mediana + 0.6 * temp.egz;
        cout<<endl<<left<<setw(15)<<temp.vardas<<setw(20)<<temp.pavarde;
        cout << fixed << setprecision(2) << right << setw(5) << temp.med;
    }
}
