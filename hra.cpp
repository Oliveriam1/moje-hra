#include <iostream>
#include <chrono>
#include <thread>
#include <random>

using namespace std::chrono;
// Nezapomen poupravit statistiky u postav(vigor, ...)

struct Hrac {
    std::string jmeno;
    std::string role;
    int vigor; // Urcuje zivoty
    int endurance; // Urcuje cas na psani textu
    int intelligence; // Urcuje slozitost textu
    int strength; // Urcuje mnozstvi textu
    int penize;
};

struct Nepritel {
    std::string njmeno;
    int nvigor;
    int nstrength; //Jak velke poskozeni ti bude udelovat
};

struct Miniboss {
    std::string mbjmeno;
    int mbvigor;
    int mbstrength;
};

struct Boss {
    std::string bjmeno;
    int bvigor;
    int bstrength;
    int bspecials;
};

struct Vesnice {
    std::string obchod; //Pro koupeni potion ktery pridaji boost do zivotu, nebo inteligennce, ...
    std::string mlekarna; //Pro vyhealeni
    std::string mag; //Pro vylepsen
};

std::string randomtext(){
    std::string moznosti[6] = {
        "Skibdii boilet",
        "bobardinokrokodini",
        "bombinigusini",
        "kapucinoassasino",
        "Tralelotralala",
        "zibrazubrazibralini"
    };
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(0, 5);
    int index = distrib(gen);
    return moznosti[index];

}

void utok(){
    std::string zadanytext = randomtext();
    std::cout << "Mate 5 sekund na napsani: " << zadanytext << std::endl;
    
    auto start = steady_clock::now();

    std::string vstupnitext;
    std::cin >> vstupnitext;

    auto end = steady_clock::now();
    
    auto trvani = duration_cast<seconds>(end - start).count();

    if (trvani <= 5 && vstupnitext == zadanytext) {
        std::cout << "Vyborne! Ubral si " << std::endl; //dodelat vypsani damage
    } else {
        std::cout << "Ubral ti -1 zivot (" << trvani << " sekund)" << std::endl; //dodelat vypsani emocionalniho poskozeni
    }
}

void overeni(std::string &potvrzeni, std::string role, Hrac &h) {
    bool platnost_potvrzeni = false;
    while (!platnost_potvrzeni){
        std::cout << "Jste si jisti ze chcete tuto roli? (Y/N): ";
        std::cin >> potvrzeni;

            if (potvrzeni == "Y" || potvrzeni == "y"){
                std::cout << "Role schvalena!";
                platnost_potvrzeni = true;
            } else if (potvrzeni == "N" || potvrzeni == "n"){
                std::cout << "Vyberte si tedy znovu (N!x, Havel, Raven): ";
                std::cin >> role;
                if (role == "N!x"){
                    h.vigor = 7;
                    h.endurance = 6;
                    h.intelligence = 18;
                    h.strength = 5;
                    std::cout << std::endl;
                    std::cout << "  " << "Statistiky: " << std::endl;
                    std::cout << "             " << "Vigor: " << h.vigor << std::endl;
                    std::cout << "             " << "Endurance: " << h.endurance << std::endl;
                    std::cout << "             " << "Intelligence: " << h.intelligence << std::endl;
                    std::cout << "             " << "Strength: " << h.strength << std::endl;
                    std::cout << std::endl;
                } else if (role == "Havel"){
                    h.vigor  = 15;
                    h.endurance = 12;
                    h.intelligence = 5;
                    h.strength = 18;
                    std::cout << std::endl;
                    std::cout << "  " << "Statistiky: " << std::endl;
                    std::cout << "             " << "Vigor: " << h.vigor << std::endl;
                    std::cout << "             " << "Endurance: " << h.endurance << std::endl;
                    std::cout << "             " << "Intelligence: " << h.intelligence << std::endl;
                    std::cout << "             " << "Strength: " << h.strength << std::endl;
                    std::cout << std::endl;
                } else if (role == "Raven"){
                    h.vigor  = 10;
                    h.endurance = 14;
                    h.intelligence = 7;
                    h.strength = 9;
                    std::cout << std::endl;
                    std::cout << "  " << "Statistiky: " << std::endl;
                    std::cout << "             " << "Vigor: " << h.vigor << std::endl;
                    std::cout << "             " << "Endurance: " << h.endurance << std::endl;
                    std::cout << "             " << "Intelligence: " << h.intelligence << std::endl;
                    std::cout << "             " << "Strength: " << h.strength << std::endl;
                    std::cout << std::endl;
                }
            platnost_potvrzeni = false;
        }
    }
}

Nepritel createNepritel (const std::string &njmeno) {
    Nepritel n;
    n.njmeno = njmeno;
        if (njmeno == "1"){ // PRIDAT JMENA
            n.nvigor = 10;
            n.nstrength = 10;
        } else if (njmeno == "2"){
            n.nvigor = 20;
        } else if (njmeno == "3"){
            n.nvigor = 20;
        }
}

Miniboss createMiniboss (const std::string &mbjmeno) {
    Miniboss mb;
    mb.mbjmeno = mbjmeno;

}

Boss createBoss (const std::string &bjmeno) {
    Boss b;
    b.bjmeno = bjmeno;
    b.bjmeno = "Thornhost";
    b.bvigor = 100;
    b.bspecials = -10;

}

Hrac createHrac(const std::string &jmeno, const std::string &role) {
    Hrac h;
    std::string potvrzeni;
    h.jmeno = jmeno;
        if (role == "N!x"){
            h.vigor = 7;
            h.role = role;
            h.endurance = 6;
            h.intelligence = 18;
            h.strength = 5;
        } else if (role == "Havel"){
            h.vigor  = 15;
            h.endurance = 12;
            h.intelligence = 5;
            h.strength = 18;
        } else if (role == "Raven"){
            h.vigor  = 10;
            h.endurance = 14;
            h.intelligence = 7;
            h.strength = 9;
        }

    std::cout << std::endl;
    std::cout << "  " << "Statistiky: " << std::endl;
    std::cout << "             " << "Vigor: " << h.vigor << std::endl;
    std::cout << "             " << "Endurance: " << h.endurance << std::endl;
    std::cout << "             " << "Intelligence: " << h.intelligence << std::endl;
    std::cout << "             " << "Strength: " << h.strength << std::endl; //Kdztak pozdejs strcit do funkce pro estetiku
    std::cout << std::endl;

    return h;
}

void zacatek(std::string &jmeno, std::string &role) {
    std::cout << "Vitej v me hre, dobrodruhu. Pred tebou se oteviraji dvere do sveta plneho nebezpeci, tajemstvi a dobrodruzstvi. Jako hrdina mas pred sebou spoustu vyzev." << std::endl << "Tvoje cesta zacina nyni, ale nez se vydas do boje, je treba pochopit, system utoku." << std::endl << "Boj bude probihat formou psani textu. Zadny obycejny boj s mecem nebo ciste random zaletisost to nebude." << std::endl << "Misto toho tedy budes muset rychle reagovat na vyzvy, ktere ti budou predkladany ve forme textu. Cely system bude zalezet na tom, jak rychle dokazes napsat odpoved." << std::endl << "Statistiky tve postavy ovlivni tvuj uspech v boji:" << std::endl;
    std::cout << std::endl;
    std::cout << "Vigor urcuje, jak dlouho vydrzis v boji." << std::endl;
    std::cout << "Endurance urcuje, casovy limit na psani odpovedi." << std::endl;
    std::cout << "Intelligence ovlivnuje slozitost textu, ktery budes muset napsat." << std::endl;
    std::cout << "Strength urcuje, velikost textu." << std::endl;
        for (int i = 0; i < 113; i++){
            std::cout << "_";
        }
    std::cout << std::endl << std::endl;
    std::cout << "Jak se budes jmenovat?: ";
    std::cin >> jmeno;
    std::cout << "Vyber roli (N!x, Havel, Raven): ";
    std::cin >> role;
}


main() {
    std::string njmeno;

    std::string jmeno;
    std::string role;
    std::string potvrzeni;

    zacatek(jmeno, role);

    Hrac hrac = createHrac(jmeno, role);

    overeni(potvrzeni, role, hrac);

    utok();
    std::cout << "Zivoty postavy (" << hrac.jmeno << "): " << hrac.vigor << std::endl; //Oli to je treba na vypsani zivotu


}