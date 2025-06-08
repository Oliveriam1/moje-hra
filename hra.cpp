#include <iostream>
#include <chrono>
#include <thread>
#include <random>

using namespace std::chrono;
using namespace std::this_thread;
// Nezapomen poupravit statistiky u postav(vigor, ...)

void pauza(std::string typpauzy){
    if (typpauzy == "1"){
        sleep_for(seconds(2));
    }
    else if (typpauzy == "3"){
        sleep_for(seconds(5));
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
    int intelligence; // Urcuje slozitost textu
    int strength; // Urcuje poskozeni zakolik ubere
    int penize = 10;
    int xp = 1;
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

std::string randomtext(){
    std::string moznosti[6] = {
        "Skibdii boilet",
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

void utok(Nepritel &nepritel, Hrac &hrac){
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
            if (nepritel.njmeno == "1"){
                nepritel.nvigor = nepritel.nvigor - hrac.strength;
                std::cout << "Vyborne zasahl si hit... " << std::endl << "Zivoty nepritele: " << nepritel.nvigor << std::endl;
                if (nepritel.nvigor <= 0){
                    std::cout << "Vyhral si souboj...";
                    break;
                }
            } 
        } else {
                if (nepritel.njmeno == "1"){
                    hrac.vigor = hrac.vigor - nepritel.nstrength;

                    std::cout << "Tve zivoty: " << hrac.vigor << std::endl;
                    if (hrac.vigor <= 0){
                        std::cout << "Zemrel si..." << std::endl;
                        break;
                    }
                }
            }
        } else if (odpovedutok == 'b'){
            std::cout << "LEcenmiii" << std::endl;
        }
    }        
}

void bossfight(Boss &boss, Hrac &hrac){
    int pocetkol = 0;
    bool bossfaze2 = false;
    char odpovedboss;

    while (hrac.vigor > 0 && boss.bvigor > 0) {
        pocetkol++;
        std::string zadanytext = randomtext();

        pauza("1");
        std::cout << std::endl << std::endl;
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
            std::cout << "Zasahl jsi bosse za: " << hrac.strength << std::endl;

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
        std::cout << "vyhlili ses" << std::endl;
    }
        
//Olivere udelej nabidku pri fightech ze si muzes vybrat jestli chces zautocit nebo se vylecitt
        if (hrac.vigor <= 0){
            std::cout << "\nZemrel si";
            break;
        }
        if (boss.bvigor <= 0){
            std::cout << "VITEZSTVIIII!!!";
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
                    h.vigor = 7;
                    h.maxvigor = 7;
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
                    h.maxvigor = 15;
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
                    h.maxvigor = 10;
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

Nepritel createNepritel (const std::string &njmeno){
    Nepritel n;
    n.njmeno = njmeno;
        if (njmeno == "1"){ // PRIDAT JMENA
            n.nvigor = 10;
            n.nstrength = 5;
        } else if (njmeno == "2"){
            n.nvigor = 20;
        } else if (njmeno == "3"){
            n.nvigor = 20;
        }
        return n;
}

Miniboss createMiniboss (const std::string &mbjmeno){
    Miniboss mb;
    mb.mbjmeno = mbjmeno;

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
            h.vigor = 7;
            h.maxvigor = 7;
            h.role = role;
            h.endurance = 6;
            h.intelligence = 18;
            h.strength = 5;
        } else if (role == "Havel"){
            h.vigor  = 15;
            h.maxvigor = 15;
            h.endurance = 12;
            h.intelligence = 5;
            h.strength = 18;
        } else if (role == "Raven"){
            h.vigor = 10;
            h.maxvigor = 10;
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

Vesnice createVesnice(Vesnice &vesnice, Hrac &hrac){
    Vesnice v;
        char vyberobchodu;
        std::string odpovedmlekarna;
        std::string odpovedmag;

        std::cout << ""; // dopsat uvitani do vesnice
        std::cout << "Vyber si kam chces zajit: [obchod - o, mlekarna - m, mag - g] ";
        std::cin >> vyberobchodu;

        switch(vyberobchodu){
                case 'o':
                //udelat vic funkci obchodu, kde bude vzdycky jiny vyber veci
                break;
                case 'm':
                std::cout << "Muzete si koupit Heal potion...\n";
                std::cout << "Menu:" << std::endl;
                std::cout << "   Heal potion (+3) [Cena - 3] [H]" << std::endl;
                std::cout << "Mate " << hrac.penize << " zlataku..." << std::endl;
                std::cout << "Co to bude? ";
                std::cin >> odpovedmlekarna;

                    if (odpovedmlekarna == "H" || odpovedmlekarna == "h"){
                        if (hrac.penize >= 3) {
                            if (hrac.maxvigor > hrac.vigor){
                                hrac.vigor = hrac.vigor + 3;
                                hrac.penize = hrac.penize - 3;
                            }        
                        } else if (hrac.maxvigor = hrac.vigor){
                            hrac.vigor = hrac.maxvigor;
                        } else {
                            std::cout << "Mate blbe"; 
                        }
                        std::cout << "Vase zivoty po vyhealeni: " << hrac.vigor << std::endl;
                        std::cout << "Zbyvta ti " << hrac.penize << " zlataku." << std::endl;
                    }

                break;
                case 'g':
                std::cout << "Zde si muzete vylepsovat sve statistiky..." << std::endl;
                std::cout << "Menu:" << std::endl;
                std::cout << "   Vigor (+1) [Cena - 1xp] [V]" << std::endl;
                std::cout << "Co chcete vylepsit? ";
                std::cin >> odpovedmag;
                    if (odpovedmag == "V"){
                        if (hrac.xp >=1){
                            hrac.maxvigor++;
                            std::cout << "Vase max zdravi se zvyslo: " << hrac.maxvigor;//nastav hranici zivotu ze nemuse jit dal s healpotionama a na to by bylo prave to upgradovani... zvysovani max statistik
                        } else {
                            std::cout << "Jdi domu..." << std::endl;
                        }

                    }
                //Olivereeee dodelej pak vsechny ty statistiky a vic lidstejsi text plsky mlsky a urci cenuuuuu
                break;
        }
        return v;
}

void zacatek(std::string &jmeno, std::string &role){
    std::cout << "Vitej v me hre, dobrodruhu. Pred tebou se oteviraji dvere do sveta plneho nebezpeci, tajemstvi a dobrodruzstvi. Jako hrdina mas pred sebou spoustu vyzev." << std::endl << "Tvoje cesta zacina nyni, ale nez se vydas do boje, je treba pochopit, system utoku." << std::endl << "Boj bude probihat formou psani textu. Zadny obycejny boj s mecem nebo ciste random zaletisost to nebude." << std::endl << "Misto toho tedy budes muset rychle reagovat na vyzvy, ktere ti budou predkladany ve forme textu. Cely system bude zalezet na tom, jak rychle dokazes napsat odpoved." << std::endl << "Statistiky tve postavy ovlivni tvuj uspech v boji:" << std::endl;
    std::cout << std::endl;
    std::cout << "Vigor urcuje, jak dlouho vydrzis v boji." << std::endl;
    std::cout << "Endurance urcuje, casovy limit na psani odpovedi." << std::endl;
    std::cout << "Intelligence ovlivnuje slozitost textu, ktery budes muset napsat." << std::endl;
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

int main(){
    std::string njmeno;
    int nstrength;

    std::string jmeno;
    std::string role;
    std::string potvrzeni;
    int vigor;

    zacatek(jmeno, role);

    Hrac hrac = createHrac(jmeno, role);
    Boss boss = createBoss("Thornhost");
    Nepritel nepritel = createNepritel("1"); // zavolani daneho nepritele
    overeni(potvrzeni, role, hrac);

    //utok(nepritel, hrac);
    //std::cout << std::endl << "Zivoty postavy (" << hrac.jmeno << "): " << hrac.vigor << std::endl; //Oli to je treba na vypsani zivotu
    //Vesnice vesnice = createVesnice(vesnice, hrac);

    bossfight(boss, hrac); //TOHLE JE BOSFIGHT OLIKOSSS NARCOPSS
}

//pridej získávání XP za kill a i penize a potom to s temi potiony ze je budes moc nosti u sebee