#include <iostream>

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
    int nendurance;
    int nintelligence;
    int nstrength;
};

void overeni(std::string &potvrzeni, std::string role, Hrac &h){
    bool platnost_potvrzeni = false;
        while (!platnost_potvrzeni){
            std::cout << "Jste si jisti ze chcete tuto roli? (Y/N): ";
            std::cin >> potvrzeni;

                if (potvrzeni == "Y" || potvrzeni == "y"){
                    std::cout << "Role schvalena!";
                    platnost_potvrzeni = true;
                } else if (potvrzeni == "N" || potvrzeni == "n"){
                    std::cout << "Vyberte si tedy znovu (Nix, Havel, Raven): ";
                    std::cin >> role;
                    if (role == "Nix"){
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
                    platnost_potvrzeni = false;
                }
        }
}

Hrac createHrac(const std::string &jmeno, const std::string &role){
    Hrac h;
    std::string potvrzeni;
    h.jmeno = jmeno;
        if (role == "Nix"){
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
    std::cout << "             " << "Strength: " << h.strength << std::endl;
    std::cout << std::endl;

    return h;
}

void zacatek(std::string &jmeno, std::string &role) {
    std::cout << "Vitej v me hre, dobrodruhu. Pred tebou se oteviraji dvere do sveta plneho nebezpeci, tajemstvi a dobrodruzstvi. Jako hrdina mas pred sebou spoustu vyzev." << std::endl << "Tvoje cesta zacina nyni, ale nez se vydas do boje, je treba pochopit, system utoku." << std::endl << "Boj bude probihat formou psani textu. Zadny obycejny boj s mecem nebo ciste random zaletisost to nebude." << std::endl << "Misto toho tedy budes muset rychle reagovat na vyzvy, ktere ti budou predkladany ve forme textu. Cely system bude zalezet na tom, jak rychle dokazes napsat odpoved." << std::endl << "Statistiky tve postavy ovlivni tvuj uspech v boji:" << std::endl;
    std::cout << std::endl;
    std::cout << "Vigor urcuje, jak dlouho vydrzis v boji" << std::endl;
    std::cout << "Endurance urcuje, casovy limit na psani odpovedi." << std::endl;
    std::cout << "Intelligence ovlivnuje slozitost textu, ktery budes muset napsat." << std::endl;
    std::cout << "Strength urcuje, velikost textu." << std::endl;
        for (int i = 0; i < 113; i++){
            std::cout << "_";
        }
    std::cout << std::endl << std::endl;
    std::cout << "Jak se budes jmenovat?: ";
    std::cin >> jmeno;
    std::cout << "Vyber roli (Nix, Havel, Raven): ";
    std::cin >> role;
}


main () {
    std::string jmeno;
    std::string role;
    std::string potvrzeni;

    zacatek(jmeno, role);

    Hrac hrac = createHrac(jmeno, role);

    overeni(potvrzeni, role, hrac);
    std::cout << "Zivoty postavy (" << hrac.jmeno << "): " << hrac.vigor << std::endl; //Oli to je třeba na vypsání životu


}