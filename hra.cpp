#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <cstdlib>

#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

using namespace std::chrono;
using namespace std::this_thread;
// Nezapomen poupravit statistiky u postav(vigor, ...)
void pauza(std::string typpauzy){
    if (typpauzy == "1"){
        sleep_for(seconds(2));
    }
    else if (typpauzy == "3"){
        sleep_for(seconds(4));
    }
}

void cara(){
    for (int i = 0; i < 113; i++){
        std::cout << "_";
    }
}



struct Hrac{
    std::string jmeno;
    std::string role;
    int maxvigor; // Urcuje max pocet zivotu
    int vigor; // Urcuje zivoty
    int endurance; // Urcuje cas na psani textu
    int intelligence; // Urcuje slozitost textu -- uprimne nakonec z toho pada takze to tu necham jako maly easter egg
    int strength; // Urcuje poskozeni zakolik ubere
    int penize;
    int xp;
    int healpotion; //DODELEJ HEALPOTIONS A VYMEN TO VVVVVVV MLEKARNE ZE SI TO BUDE MOCT NOSIT V INV AA POUZIT TO TREBA PRI UTOCENI
};

struct Nepritel{
    std::string njmeno;
    int nvigor;
    int nstrength; //Jak velke poskozeni ti bude udelovat
};

struct Miniboss{
    std::string mbjmeno;
    int mbvigor;
    int mbstrength;
    bool mbspecials;
};

struct Boss{
    std::string bjmeno;
    int bvigor;
    int bmaxvigor;
    int bstrength;
    int bspecials;
};

struct Vesnice{
    std::string obchod; //Pro koupeni potion ktery pridaji boost do zivotu, nebo inteligennce, ...
    std::string mlekarna; //Pro vyhealeni
    std::string mag; //Pro vylepsen
};

std::string randomtext(){ //dodat vic textuu co psatt
    std::string moznosti[6] = {
        "Skibiditoilet",
        "bobardinokrokodini",
        "bombombinigusini",
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

void leceni(Hrac &hrac){
    if (hrac.healpotion > 0){
        if (hrac.vigor == hrac.maxvigor){
            std::cout << "Mas plne zivoty..." << std::endl;
        } else if (hrac.vigor < hrac.maxvigor){
            hrac.healpotion--;
            std::cout << "Vylecil ses z: " << hrac.vigor;
            hrac.vigor = hrac.vigor + 3;
            std::cout << " na: " << hrac.vigor << " HP." << std::endl;
        }
    } else if (hrac.healpotion == 0) {
        std::cout << "Nemas healpotion..." << std::endl;
    } else {
        std::cout << "Mas maximalni pocet zivotu... neni duvod se healit.." << std::endl;
    }
}

void statistiky(Hrac &hrac){ //funkcce na vypsani statistikkk, umoznit hraci kdykoliv tuto funkci zavolattt
    std::cout << "\n=== TVE STATISTIKY ===" << std::endl;
    std::cout << "HP: " << hrac.vigor << " / " << hrac.maxvigor << std::endl;
    std::cout << "Strength: " << hrac.strength << std::endl;
    std::cout << "Endurance: " << hrac.endurance << std::endl;
    std::cout << "XP: " << hrac.xp << std::endl;
    std::cout << "Zlato: " << hrac.penize << std::endl;
    std::cout << "=============================\n";
}

void levelup(Hrac &hrac){ // funkce na level up
    int xpmax = 100;
    if (hrac.xp >= xpmax){
        hrac.strength = hrac.strength + 2;
        hrac.maxvigor = hrac.maxvigor + 20;
        hrac.vigor = hrac.maxvigor;
        hrac.xp = hrac.xp - xpmax;
        std::cout << "\n=== LEVEL UP!! ===\n Zvysili se ti zivoty na: " << hrac.maxvigor << " a sila na: " << hrac.strength << std::endl << std::endl;
    }   
}

void gamba(Hrac &hrac){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1); // 0 nebo 1

    if (distrib(gen) == 1) {
        std::cout << "Ziskal si 20 penez!!" << std::endl;
        hrac.penize = hrac.penize + 20;
    } else {
        std::cout << "Zadne penize si nedostal..." << std::endl;
    }
}

void utok(Nepritel &nepritel, Hrac &hrac){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 100);
    
    int pocetkol = 0;
    while(hrac.vigor > 0 && nepritel.nvigor > 0) {
        pocetkol++;

        pauza("1");
        std::cout << std::endl << std::endl;
        std::cout << "=== Kolo " << pocetkol << " ===" << std::endl;
        std::cout << "Tvoje zivoty: " << hrac.vigor << "/" << hrac.maxvigor << std::endl;
        std::cout << "Nepritelovi zivoty: " << nepritel.nvigor << std::endl;
        std::cout << std::endl;

        std::string zadanytext = randomtext();
        char odpovedutok;
        do {
            std::cout << "Chces utocit (a) nebo se pouzit healpotion (b)?: ";
            std::cin >> odpovedutok;
        } while (odpovedutok != 'a' && odpovedutok != 'b');

        if (odpovedutok == 'a'){
        std::cout << "Priprav se na utok..." << std::endl;
        pauza("1");
        std::cout << "Mate " << hrac.endurance << " sekund na napsani: " << zadanytext << std::endl;
        auto start = steady_clock::now();

        std::string vstupnitext;
        std::cin >> vstupnitext;

        auto end = steady_clock::now();
    
        auto trvani = duration_cast<seconds>(end - start).count();
        // udleat funkci na vybrani nepritele oliku nezapomen
        if (trvani <= hrac.endurance && vstupnitext == zadanytext) {
                nepritel.nvigor = nepritel.nvigor - hrac.strength;
                int gambautok = dist(gen);
                if (gambautok <= 20){
                    nepritel.nvigor = nepritel.nvigor - (hrac.strength + 10);
                }
                std::cout << "\nVyborne zasahl si hit... " << std::endl << "Zivoty nepritele: " << RED << nepritel.nvigor << RESET << std::endl;
                if (nepritel.nvigor <= 0){
                    std::cout << std::endl;
                    std::cout << "=== VYHRAL SI SOUBOUJJ ===" << std::endl;
                    hrac.xp = hrac.xp + 20;
                    std::cout << "Ziskal si 20 XP!!" << std::endl;
                    gamba(hrac);
                    levelup(hrac);
                    break;
                }    
        } else {
                hrac.vigor = hrac.vigor - nepritel.nstrength;
                std::cout << "Bohuzel si nesplnil zadany text nebo jsi moc pomaly... "<< std::endl;
                std::cout << "Tve zivoty: " << GREEN << hrac.vigor << RESET << std::endl;
                if (hrac.vigor <= 0){
                    std::cout << "Zemrel si..." << std::endl;
                    std::exit(0);
                }
        }
    } else if (odpovedutok == 'b'){
        leceni(hrac);
        }
    }        
}

void minibossfight(Miniboss &miniboss, Hrac &hrac){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 100);
    int pocetkol = 0;

    while(hrac.vigor > 0 && miniboss.mbvigor > 0) {
        pocetkol++;

        pauza("1");
        std::cout << std::endl << std::endl;
        std::cout << "*** MINIBOSS ***" << std::endl;
        std::cout << "=== Kolo " << pocetkol << " ===" << std::endl;
        std::cout << "Tvoje zivoty: " << hrac.vigor << "/" << hrac.maxvigor << std::endl;
        std::cout << "Nepritelovi zivoty: " << miniboss.mbvigor << std::endl;
        std::cout << std::endl;

        std::string zadanytext = randomtext();
        char odpovedutok;
        do {
            std::cout << "Chces utocit (a) nebo se pouzit healpotion (b)?: ";
            std::cin >> odpovedutok;
        } while (odpovedutok != 'a' && odpovedutok != 'b');

        if (odpovedutok == 'a'){
        std::cout << "Priprav se na utok..." << std::endl;
        pauza("1");
        std::cout << "Mate " << hrac.endurance << " sekund na napsani: " << zadanytext << std::endl;
        auto start = steady_clock::now();

        std::string vstupnitext;
        std::cin >> vstupnitext;

        auto end = steady_clock::now();
    
        auto trvani = duration_cast<seconds>(end - start).count();
        
        if (trvani <= hrac.endurance && vstupnitext == zadanytext) {
            if (miniboss.mbjmeno == "1"){
                miniboss.mbvigor = miniboss.mbvigor - hrac.strength;
                int gambautok = dist(gen);
                if (gambautok <= 20){
                    miniboss.mbvigor = miniboss.mbvigor - (hrac.strength + 10);
                }
                std::cout << "Vyborne zasahl si hit... " << std::endl << "Zivoty nepritele: " << RED << miniboss.mbvigor << RESET << std::endl;
                if(pocetkol % 4 == 0){
                    miniboss.mbstrength = miniboss.mbstrength + 10;
                    std::cout << "Pouzil specialni utok!!";
                    hrac.vigor = hrac.vigor - miniboss.mbstrength;
                    std::cout << RED << "Dostal si hit za: " << miniboss.mbstrength << RESET << std::endl;
                }
                

                if (miniboss.mbvigor <= 0){
                    std::cout << std::endl;
                    std::cout << BLUE << "=== VYHRAL SI SOUBOUJJ ===" << RESET << std::endl;
                    hrac.xp = hrac.xp + 60;
                    std::cout << "Ziskal si 60 XP!!" << std::endl;
                    levelup(hrac);
                    gamba(hrac);
                    break;
                }
            } else if(miniboss.mbjmeno == "2"){
                miniboss.mbvigor = miniboss.mbvigor - hrac.strength;
                int gambautok = dist(gen);
                if (gambautok <= 20){
                    miniboss.mbvigor = miniboss.mbvigor - (hrac.strength + 10);
                }
                std::cout << "\nVyborne zasahl si hit... " << std::endl << "Zivoty nepritele: " << miniboss.mbvigor << std::endl;
                if(pocetkol % 4 == 0){
                    miniboss.mbstrength = miniboss.mbstrength + 10;
                    std::cout << "Pouzil specialni utok!!";
                    hrac.vigor = hrac.vigor - miniboss.mbstrength;
                    std::cout << "Dostal si hit za: " << miniboss.mbstrength << std::endl;
                }
                

                if (miniboss.mbvigor <= 0){
                    std::cout << std::endl;
                    std::cout << BLUE << "=== VYHRAL SI SOUBOUJJ ===" << RESET << std::endl;
                    hrac.xp = hrac.xp + 60;
                    std::cout << "Ziskal si 60 XP!!" << std::endl;
                    levelup(hrac);
                    gamba(hrac);
                    break;
                }
            }
        } else {
                if (miniboss.mbjmeno == "1"){
                    hrac.vigor = hrac.vigor - miniboss.mbstrength;

                    std::cout << "Tve zivoty: " << hrac.vigor << std::endl;
                    if (hrac.vigor <= 0){
                        std::cout << "Zemrel si..." << std::endl;
                        std::exit(0);
                    }
                } else if (miniboss.mbjmeno == "2"){
                    hrac.vigor = hrac.vigor - miniboss.mbstrength;

                    std::cout << "Tve zivoty: " << hrac.vigor << std::endl;
                    if (hrac.vigor <= 0){
                        std::cout << "Zemrel si..." << std::endl;
                        std::exit(0);
                    }
                } 
            }
        } else if (odpovedutok == 'b'){
            leceni(hrac);
        }
    }
}

void bossfight(Boss &boss, Hrac &hrac){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 100);

    int pocetkol = 0;
    bool bossfaze2 = false;
    char odpovedboss;
    while (hrac.vigor > 0 && boss.bvigor > 0) {
        pocetkol++;
        std::string zadanytext = randomtext();

        pauza("1");
        std::cout << std::endl << std::endl;
        std::cout << "*** BOSS ***" << std::endl;
        std::cout << "=== Kolo " << pocetkol << " ===" << std::endl;
        std::cout << "Tvoje zivoty: " << hrac.vigor << "/" << hrac.maxvigor << std::endl;
        std::cout << "Thornhostovoti zivoty: " << boss.bvigor << std::endl;
        std::cout << std::endl;

        do {
            std::cout << "Chces utocit (a) nebo se pouzit healpotion (b)?: ";
            std::cin >> odpovedboss;
        } while (odpovedboss != 'a' && odpovedboss != 'b');

        if (odpovedboss == 'a') {
            std::cout << "Priprav se na utok..." << std::endl;
            pauza("1");
            std::cout << "Napis rychle: " << zadanytext << " za: " << hrac.endurance << " sekund" << std::endl;

        auto start = steady_clock::now();

        std::string vstupnitext;
        std::cin >> vstupnitext;

        auto end = steady_clock::now();

        auto trvani = duration_cast<seconds>(end - start).count();

        std::cout << std::endl;
        if (trvani <= hrac.endurance && zadanytext == vstupnitext){
            boss.bvigor = boss.bvigor - hrac.strength;
            int gambautok = dist(gen);
                if (gambautok <= 20){
                    boss.bvigor = boss.bvigor - (hrac.strength + 10);
                }
            std::cout << "\nZasahl jsi bosse za: " << hrac.strength << std::endl;

            int odrazeni = hrac.strength / 3;
            hrac.vigor = hrac.vigor - odrazeni;
            std::cout << "Thornhost odrazi: " << odrazeni << " poskozeni" << std::endl;

            if (pocetkol % 2 == 0){
                int trnyposkozeni = 5;
                hrac.vigor = hrac.vigor - trnyposkozeni;
                std::cout << "Thornost vystreluje trny! Ztracis: " << trnyposkozeni << " HP" << std::endl;
            }
            if (boss.bvigor < boss.bmaxvigor * 0.3 && !bossfaze2){
                bossfaze2 = true;
                std::cout << "THORNOST ZACINA VYBUSNOU FAZI !!!" << std::endl;
            }
            if (bossfaze2){
                hrac.vigor = hrac.vigor - 10;
                boss.bvigor = boss.bvigor -10;
                std::cout << "Trnovy vybuch!! Oba ztracite 10 HP!";
            }
        }
        else {
            hrac.vigor = hrac.vigor - boss.bstrength;
            std::cout << "Zasahl tee za: " << boss.bstrength << " zivotu" << std::endl;
        }
    } else if (odpovedboss == 'b'){
        leceni(hrac);
    }
        
        if (hrac.vigor <= 0){
            std::cout << "\nZemrel si...";
            std::exit(0);
        }
        if (boss.bvigor <= 0){
            std::cout << BLUE << "\n\nVITEZSTVIIII!!! (Dekuju ze si hral mou demo hru...)" << RESET;
            break;
        }
        cara(); //odelovac kol oliku
    }
}

void overeni(std::string &potvrzeni, std::string role, Hrac &h){
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
                    h.vigor = 16; 
                    h.maxvigor = 16;
                    h.role = role;
                    h.endurance = 6;
                    h.intelligence = 18;
                    h.strength = 15; 
                    h.healpotion = 1;
                    h.penize = 10;
                    h.xp = 0;
                    std::cout << std::endl;
                    std::cout << "  " << "Statistiky: " << std::endl;
                    std::cout << "             " << "Vigor: " << h.vigor << std::endl;
                    std::cout << "             " << "Endurance: " << h.endurance << std::endl;
                    std::cout << "             " << "Intelligence: " << h.intelligence << std::endl;
                    std::cout << "             " << "Strength: " << h.strength << std::endl;
                    std::cout << std::endl;
                } else if (role == "Havel"){
                    h.vigor  = 20;
                    h.maxvigor = 20;
                    h.endurance = 12;
                    h.intelligence = 5;
                    h.strength = 18;
                    h.healpotion = 1;
                    h.penize = 10;
                    h.xp = 0;
                    std::cout << std::endl;
                    std::cout << "  " << "Statistiky: " << std::endl;
                    std::cout << "             " << "Vigor: " << h.vigor << std::endl;
                    std::cout << "             " << "Endurance: " << h.endurance << std::endl;
                    std::cout << "             " << "Intelligence: " << h.intelligence << std::endl;
                    std::cout << "             " << "Strength: " << h.strength << std::endl;
                    std::cout << std::endl;
                } else if (role == "Raven"){
                    h.vigor = 18;
                    h.maxvigor = 18;
                    h.endurance = 14;
                    h.intelligence = 7;
                    h.strength = 16;
                    h.healpotion = 1;
                    h.penize = 10;
                    h.xp = 0;
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

Nepritel createNepritel (const std::string &njmeno){
    Nepritel n;
    n.njmeno = njmeno;
        if (njmeno == "1"){n.nvigor = 16; n.nstrength = 5;} else if (njmeno == "2"){n.nvigor = 15; n.nstrength = 3;} else if (njmeno == "3"){n.nvigor = 20; n.nstrength = 4;} else if (njmeno == "4"){n.nvigor = 18; n.nstrength = 5;} else if (njmeno == "5"){n.nvigor = 30; n.nstrength = 6;} else if (njmeno == "6"){n.nvigor = 25; n.nstrength = 8;} else if (njmeno == "7"){n.nvigor = 13; n.nstrength = 13;} else if (njmeno == "8"){n.nvigor = 23; n.nstrength = 2;} else if (njmeno == "9"){n.nvigor = 9; n.nstrength = 5;} else if (njmeno == "10"){n.nvigor = 29; n.nstrength = 13;} else if (njmeno == "11"){n.nvigor = 5; n.nstrength = 5;} else if (njmeno == "12"){n.nvigor = 17; n.nstrength = 8;} else if (njmeno == "13"){n.nvigor = 2; n.nstrength = 5;} else if (njmeno == "14"){n.nvigor = 14; n.nstrength = 6;} else if (njmeno == "15"){n.nvigor = 21; n.nstrength = 5;} else if (njmeno == "16"){n.nvigor = 10; n.nstrength = 5;}
        return n;
}

Miniboss createMiniboss (const std::string &mbjmeno){
    Miniboss mb;
    mb.mbjmeno = mbjmeno;
    if (mbjmeno == "1"){
    mb.mbvigor = 40;
    mb.mbstrength = 20;
    mb.mbspecials = 30;
    } else if (mbjmeno == "2"){
    mb.mbvigor = 60;
    mb.mbstrength = 19;
    mb.mbspecials = 36;
    }
    return mb;
}

Boss createBoss (const std::string &bjmeno){
    Boss b;
    b.bjmeno = "Thornhost";
    b.bvigor = 100;
    b.bspecials = -10;
    b.bstrength = 10;

    return b;
}

Hrac createHrac(const std::string &jmeno, const std::string &role){
    Hrac h;
    std::string potvrzeni;
    h.jmeno = jmeno;
        if (role == "N!x"){
            h.vigor = 16; 
            h.maxvigor = 16;
            h.role = role;
            h.endurance = 6;
            h.intelligence = 18;
            h.strength = 15; 
            h.healpotion = 1;
            h.penize = 10;
            h.xp = 0;
        } else if (role == "Havel"){
            h.vigor  = 20;
            h.maxvigor = 20;
            h.endurance = 12;
            h.intelligence = 5;
            h.strength = 18;
            h.healpotion = 1;
            h.penize = 10;
            h.xp = 0;
        } else if (role == "Raven"){
            h.vigor = 18;
            h.maxvigor = 18;
            h.endurance = 14;
            h.intelligence = 7;
            h.strength = 16;
            h.healpotion = 1;
            h.penize = 10;
            h.xp = 0;
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

void obchod(Hrac &hrac){
char volba;
    do {
        std::cout << "\n=== Obchod ===" << std::endl;
        std::cout << "Mas " << hrac.penize << " zlataku." << std::endl;
        std::cout << "1) Kup Jednoduchy mec (+3 sila) - 20 zlataku" << std::endl;
        std::cout << "2) Kup Kozeny stit (+10 max HP) - 25 zlataku" << std::endl;
        std::cout << "3) Zpet" << std::endl;
        std::cout << "Vyber moznost: ";
        std::cin >> volba;

        switch (volba) {
            case '1':
                if (hrac.penize >= 20) {
                    hrac.strength = hrac.strength + 3;
                    hrac.penize = hrac.penize - 20;
                    std::cout << "Kupils Jednoduchy mec! Tva sila je ted: " << hrac.strength << std::endl;
                } else {
                    std::cout << "Nemas dost peněz." << std::endl;
                }
                break;
            case '2':
                if (hrac.penize >= 25) {
                    hrac.maxvigor = hrac.maxvigor + 10;
                    hrac.vigor = hrac.vigor + 10;
                    hrac.penize = hrac.penize - 25;
                    std::cout << "Kupils Kozeny stit! Tve max HP je ted: " << hrac.maxvigor << std::endl;
                } else {
                    std::cout << "Nemas dost penez." << std::endl;
                }
                break;
            case '3':
                std::cout << "Odchazis z obchodu." << std::endl;
                break;
            default:
                std::cout << "Neplatna volba, zkus to znovu." << std::endl;
        }
    } while (volba != '3');
}

void mlekarna(Hrac &hrac) {
    char volba;
    do {
        std::cout << "\n--- Mlekarna ---" << std::endl;
        std::cout << "Mas " << hrac.penize << " zlataku." << std::endl;
        std::cout << "Heal potion (+20 HP) - 5 zlataku [H]" << std::endl;
        std::cout << "Zpet [Z]" << std::endl;
        std::cout << "Co chces koupit? ";
        std::cin >> volba;

        if (volba == 'h' || volba == 'H') {
            if (hrac.penize >= 5) {
                hrac.healpotion++;
                hrac.penize = hrac.penize - 5;
                std::cout << "Koupils sis heal potion. Mas jich ted: " << hrac.healpotion << std::endl;
            } else {
                std::cout << "Nemas dost penez." << std::endl;
            }
        } else if (volba == 'z' || volba == 'Z') {
            std::cout << "Odchazis z mlekarny." << std::endl;
            break;
        } else {
            std::cout << "Neplatna volba, zkus to znovu." << std::endl;
        }
    } while (true);
}

void mag(Hrac &hrac) {
    char volba;
    do {
        std::cout << "\n--- Mag ---" << std::endl;
        std::cout << "Mas " << hrac.xp << " XP." << std::endl;
        std::cout << "1) Vylepsit Vigor (+5 max HP) - 10 XP" << std::endl;
        std::cout << "2) Vylepsit Silu (+2 strength) - 15 XP" << std::endl;
        std::cout << "3) Vylepsit Vydrz (+1 sekunda endurance) - 10 XP" << std::endl;
        std::cout << "4) Zpet" << std::endl;
        std::cout << "Vyber moznost: ";
        std::cin >> volba;

        switch (volba) {
            case '1':
                if (hrac.xp >= 10) {
                    hrac.maxvigor = hrac.maxvigor + 5;
                    hrac.vigor = hrac.vigor + 5;
                    hrac.xp = hrac.xp - 10;
                    std::cout << "Vylepsil jsi vigor! Max HP: " << hrac.maxvigor << std::endl;
                } else {
                    std::cout << "Nemas dost XP." << std::endl;
                }
                break;
            case '2':
                if (hrac.xp >= 15) {
                    hrac.strength = hrac.strength + 2;
                    hrac.xp = hrac.xp - 15;
                    std::cout << "Vylepsil jsi silu! Strength: " << hrac.strength << std::endl;
                } else {
                    std::cout << "Nemas dost XP." << std::endl;
                }
                break;
            case '3':
                if (hrac.xp >= 10) {
                    hrac.endurance = hrac.endurance + 1;
                    hrac.xp = hrac.xp - 10;
                    std::cout << "Vylepsil jsi vytrvalost! Endurance: " << hrac.endurance << " sekund." << std::endl;
                } else {
                    std::cout << "Nemas dost XP." << std::endl;
                }
                break;
            case '4':
                std::cout << "Odchazis od maga." << std::endl;
                break;
            default:
                std::cout << "Neplatna volba, zkus to znovu." << std::endl;
        }
    } while (volba != '4');
}

Vesnice createVesnice(Vesnice &vesnice, Hrac &hrac){
    Vesnice v;
        char vyberobchodu;
        std::string odpovedmlekarna;
        std::string odpovedmag;
        char odpoved;
        std::cout << "\nOpravdu chces vstoupit? [a - ano, n - ne]: ";
        std::cin >> odpoved;
        if (odpoved == 'a'){

        do {
        std::cout << "Vyber si kam chces zajit: [obchod - o, mlekarna - m, mag - g, odejit - e] ";
        std::cin >> vyberobchodu;

        switch(vyberobchodu){
                case 'o':
                    obchod(hrac);
                    break;
                case 'm':
                    mlekarna(hrac);
                    break;
                case 'g':
                    mag(hrac);
                    break;
                case 'e':
                    std::cout << "Opoustis vesnici..." << std::endl;
                    break;
                default:
                std::cout << "Neplatna volba..." << std::endl;
                }
        } while (vyberobchodu != 'e'); 
        } else {
                    std::cout << "Dobre, tak jdes dal..." << std::endl;
                }
        return v;
}

void zacatek(std::string &jmeno, std::string &role){
    std::cout << "Vitej v me hre, dobrodruhu. Pred tebou se oteviraji dvere do sveta plneho nebezpeci, tajemstvi a dobrodruzstvi. Jako hrdina mas pred sebou spoustu vyzev." << std::endl << "Tvoje cesta zacina nyni, ale nez se vydas do boje, je treba pochopit, system utoku." << std::endl << "Boj bude probihat formou psani textu. Zadny obycejny boj s mecem nebo ciste random zaletisost to nebude." << std::endl << "Misto toho tedy budes muset rychle reagovat na vyzvy, ktere ti budou predkladany ve forme textu. Cely system bude zalezet na tom, jak rychle dokazes napsat odpoved." << std::endl << "Statistiky tve postavy ovlivni tvuj uspech v boji:" << std::endl;
    std::cout << std::endl;
    std::cout << "Vigor urcuje, jak dlouho vydrzis v boji." << std::endl;
    std::cout << "Endurance urcuje, casovy limit na psani odpovedi." << std::endl;
    //std::cout << "Intelligence ovlivnuje slozitost textu, ktery budes muset napsat." << std::endl;
    std::cout << "Strength urcuje, velikost textu." << std::endl;
        cara();
    std::cout << "\n \nV prubehu hry budes narazet na mista zvane vesnice," << std::endl;
    std::cout << "kde si budes moct vylepsovat statistiky, lecit se ci nakupovat itemy..." << std::endl;
        cara();
    std::cout << std::endl << std::endl;
    std::cout << "Jak se budes jmenovat?: ";
    std::cin >> jmeno;
    std::cout << "Vyber roli (N!x, Havel, Raven): ";
    std::cin >> role;
}

void hra(){
    std::string njmeno;
    int nstrength;
    std::string jmeno;
    std::string role;
    std::string potvrzeni;
    int vigor;

    zacatek(jmeno, role);
    Hrac hrac = createHrac(jmeno, role);
    overeni(potvrzeni, role, hrac);
    std::cout << "\nTva cesta zacina v klidne vesnici. Muzes se pripravit, mozna neco nakoupit a vylepsit statistiky na cestu za hlavnim bossem...\nMas zajem?";
    Vesnice vesnice = createVesnice(vesnice, hrac); // bro jakto ze to zavola vesnici??
    std::cout << "Vyrazis na cestu za hlavnim zaporakem... a to Thornhostem... tvuj cil je se k nemu dostat a porazit ho..." << std::endl;
    cara();
    pauza("3");
    std::cout << "\nTva prvni destiance je temny les." << std::endl;
    pauza("3");
    std::cout << "Jen tak prochazis lesem a uslysis susteni stromu a krovi..." << std::endl;
    pauza("3");
    std::cout << "Nahle se zpoza stromu vynoril vlk a zautocil na tebe!";
    Nepritel nepritel = createNepritel("1"); // zavolani daneho nepritele 1-16
    utok(nepritel, hrac);
    pauza("1");
    std::cout << "\nPro tve stesti byl temny les mensi cast tve cesty, nyni ale na druhou stranu,\npro tve nestesti prochazis skrz opustenou jeskyni ktera neni uplne opustena\na je zde spousta pasti na blbecky jako jsi ty..." << std::endl;
    pauza("3");
    std::cout << "Pri prochazeni slysis skripani kosti... zautocil na tebe kostlivec!";
    nepritel = createNepritel("2");
    utok(nepritel, hrac);
    pauza("1");
    std::cout << "\nV prubehu tveho boje si jeste naskocil na zivou past.. musis se s ni vyporadat!";
    nepritel = createNepritel("3");
    utok(nepritel, hrac);
    pauza("1");
    std::cout << "Po porazeni nepratel ti uz zbyva kratka cesta do konce jeskyne, ale vychod ti brani... zmutovany kostlivec!!";
    Miniboss miniboss = createMiniboss("1"); // zavolani daneho minibosse 1-2
    minibossfight(miniboss, hrac);
    pauza("1");
    std::cout << "\nVyhral si boj s tvym prvnim minibossem a zaroven si z jeskyne vyvazl zivy!!" << std::endl;
    pauza("3");
    std::cout << "Po jeskyni, si vyrazil na horskou cestu..." << std::endl;
    pauza("3");
    std::cout << "Kracis jen tak po ceste, dlouho se nic nedeje..." << std::endl;
    pauza("1");
    std::cout << "...";
    pauza ("1");
    std::cout << " ...." << std::endl;
    pauza("1");
    std::cout << "BUMMMM" << std::endl;
    pauza("1");
    std::cout << "PRASKK" << std::endl;
    pauza("1");
    std::cout << "Z nebe na tebe spadli dva banditi a chteji te zabit..." << std::endl;
    pauza("3");
    std::cout << "Mas ale stesti, ze jeden zakopl pri dopadu, tudiz je na nejakou dobu omracenyy..";
    nepritel = createNepritel("4");
    utok(nepritel, hrac);
    pauza("1");
    std::cout << "Druhy bandita uz se stihl probudit v prubehu tveho souboje s prvnim banditou.." << std::endl;
    pauza("3");
    std::cout << "Z toho jeho predesleho padu, se lekl a chce utect..." << std::endl;
    pauza("3");
    char rozhodnuti;
    std::cout << "Muzes si vybrat.. chces ho usetrit nebo zabit?: [u - usetrit, z - zabit]: ";
    std::cin >> rozhodnuti;
        if (rozhodnuti == 'u'){
            std::cout << "\nDobre tak jdes dal..." << std::endl;
        } else {
            Nepritel nepritel = createNepritel("5");
            utok(nepritel, hrac);
        }
    pauza("3");
    std::cout << "\nUz si pokoril horskou cestu..." << std::endl;
    pauza("3");
    std::cout << "Pro tve nestesi uz temer pred koncem tve cesty za Thornhostem, je tabor banditu..." << std::endl;
    pauza("3");
    std::cout << "Z dalky pozorujes ze je tam 5 nepratelu a jeden brutalne nasvalenej bandita..." << std::endl;
    pauza("3");
    std::cout << "Jses normalni clovek tudiz se rozhodnes ze nepujdes na vsechny naraz ale porazis je stealth metodou nebo se proplizis skrz." << std::endl;
    pauza("3");
    std::cout << "Jediny kolem ktereho se nemuzes proplizit je ten ultramegagiga nasvaleny typek, protoze chrani branu kterou musis projit.." << std::endl;
    pauza("3");
    bool vybrani[7] = {false};
    stanoviste:
    std::cout << "\n=== MOZNOSTI UTOKU ===" << std::endl << "1) Usmrakny bandita" << std::endl << "2) Na pohled z dalky moc poznat nejde takze gamba!" << std::endl << "3) Krava" << std::endl << "4) Bandita prolezly cervama" << std::endl << "5) Bandita" << std::endl << "6) NASVALENY TYPEKK" << std::endl << "Vyber: ";
    int vyberenemy;
    std::cin >> vyberenemy;
        if (vyberenemy < 1 || vyberenemy > 6) {
            std::cout << "Neplatne zadani..." << std::endl;
            goto stanoviste;
        }
        if (vybrani[vyberenemy]){
            std::cout << "Tuto moznost si uz zvolil, vyber jinou!" << std::endl;
            goto stanoviste;
        }
        vybrani[vyberenemy] = true;
    switch (vyberenemy){
        case 1: {
            nepritel = createNepritel("6");
            utok(nepritel, hrac);
            goto stanoviste;
        } case 2: {
            nepritel = createNepritel("7");
            utok(nepritel, hrac);
            goto stanoviste;
        } case 3: {
            nepritel = createNepritel("8");
            utok(nepritel, hrac);
            goto stanoviste;
        } case 4: {
            nepritel = createNepritel("9");
            utok(nepritel, hrac);
            goto stanoviste;
        } case 5: {
            nepritel = createNepritel("10");
            utok(nepritel, hrac);
            goto stanoviste;
        } case 6: {
            Miniboss miniboss = createMiniboss("2");
            minibossfight(miniboss, hrac);
            break;
        } default: {
            std::cout << "Neplatne zadani..." << std::endl;
            goto stanoviste;
        }
    }
    pauza("1");
    std::cout << "Dostal ses skrz jejich tabor... uz jses skoro nakonci, zaslouzis si odpocinek." << std::endl;
    pauza("3");
    char rozhodnuti1;
    std::cout << "Cestou za Thronhostem vidis vesnici, chces do nit zajit? (A/N): ";
    std::cin >> rozhodnuti1;
        if (rozhodnuti1 == 'A' || rozhodnuti1 == 'a'){
            std::cout << "Jdes tedy do vesnice..." << std::endl;
            vesnice = createVesnice(vesnice, hrac);
        } else {
            std::cout << "Dobre jdes tedy splnit svuj osud..." << std::endl;
        }
    pauza("1");
    std::cout << "\nK tomu, aby ses dostal k Thornhostovi se musis vloupat do hradu, ktery je videt z dalky." << std::endl;
    pauza("3");
    std::cout << "Muzes videt straze, jez hlidaji ten hrad..." << std::endl;
    pauza("3");
    std::cout << "Musis se s nimi vyporadat..." << std::endl;
    pauza("3");
    std::cout << "Na jednoho si nabehl a omracil, pricemz na tebe zautocil ten druhy...";
    nepritel = createNepritel("11");
    utok(nepritel, hrac);
    pauza("1");
    char rozhodnuti2;
    std::cout << "\nZabil si jednoho strazneho, a ten druhy je hodne poznamenany,\nmuzes ho usetrit anebo ho zabit... vyber si [U/Z]: ";
    std::cin >> rozhodnuti2;
        if (rozhodnuti2 == 'Z' || rozhodnuti2 == 'z'){
            nepritel = createNepritel("12");
            utok(nepritel, hrac);
        } else {
            std::cout << "Jses zlata duse... ale vymstilo se ti to..";
            nepritel = createNepritel("12");
            utok(nepritel, hrac);
        }
    pauza("1");
    std::cout << "Dokazal si to... uz ti nikdo nestoji v ceste, ted uz jdes na bosse. Hodne stesti!";
    Boss boss = createBoss("Thornhost");
    bossfight(boss, hrac); //TOHLE JE BOSFIGHT OLIKOSSS NARCOPSS
}

int main(){
    hra();
}