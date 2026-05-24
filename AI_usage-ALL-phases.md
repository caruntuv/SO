Raport privind utilizarea inteligentei artificiale

-AI ales

Pentru implementarea proiectului din Phase 1, Phase 2 si Phase 3 am utilizat ChatGPT PRO.


-Scopul utilizarii AI in Phase 1

In Phase 1 AI-ul a fost utilizat pentru implementarea functionalitatii de filtrare a rapoartelor si pentru explicatii legate de anumite concepte utilizate in prima faza.

Am folosit AI pentru functiile cerute in enunt:

parse_condition()
match_condition()

Pentru aceste functii am descris structura Report, care contine:

id
inspector
latitude
longitude
category
severity
timestamp
description

Am cerut AI-ului sa genereze o functie care imparte o conditie de forma:

field:operator:value

in cele trei parti: field, operator si value.

De asemenea am cerut o functie care verifica daca un raport respecta o conditie pentru campurile:

severity
category
inspector
timestamp

Codul generat a fost verificat si adaptat. Am avut grija ca severity si timestamp sa fie comparate numeric, iar category si inspector sa fie comparate ca string-uri.

Logica principala pentru comanda filter a fost integrata manual in city_manager. Programul deschide fisierul reports.dat, citeste rapoartele pe rand cu read(), parseaza fiecare conditie si afiseaza doar rapoartele care respecta toate conditiile.

AI-ul m-a ajutat si sa inteleg mai bine folosirea functiilor:

open()
read()
write()
lseek()
ftruncate()
stat()
lstat()
mkdir()
symlink()
unlink()
chmod()

Aceste functii au fost folosite pentru lucrul cu fisiere binare, directoare, permisiuni si symlink-uri.


-Scopul utilizarii AI in Phase 2

In Phase 2 am utilizat AI-ul deoarece au aparut concepte noi legate de procese si semnale, cu care nu lucrasem anterior.

Am folosit AI pentru a intelege:

fork()
exec()
wait()
kill()
sigaction()
open()
write()
unlink()

De asemenea am folosit AI pentru a intelege semnalele:

SIGUSR1
SIGINT

In aceasta faza am modificat city_manager pentru comanda remove_district, care sterge un district folosind un proces copil si comanda externa rm -rf.

AI-ul m-a ajutat sa inteleg cum se creeaza un proces copil cu fork(), cum se ruleaza o comanda externa cu exec() si cum procesul parinte asteapta terminarea copilului cu wait().

Am folosit AI si pentru monitor_reports. Monitorul creeaza fisierul .monitor_pid, salveaza PID-ul procesului, asteapta semnale si sterge fisierul cand se inchide.

La primirea semnalului SIGUSR1, monitorul afiseaza un mesaj ca a fost adaugat un raport nou.

La primirea semnalului SIGINT, monitorul afiseaza un mesaj de inchidere si se opreste.

Practic am invatat aceste concepte in timpul implementarii.


-Scopul utilizarii AI in Phase 3

In Phase 3 am utilizat AI-ul pentru partea de pipe-uri, redirectari si coordonarea mai multor procese.

Conform enuntului, a trebuit implementat programul city_hub, care porneste monitorul si calculeaza scorurile inspectorilor folosind procese separate.

Am folosit AI pentru a intelege:

pipe()
dup2()
fork()
exec()
read()
write()
wait()

AI-ul m-a ajutat sa inteleg cum poate city_hub sa porneasca un proces hub_mon, iar acesta sa porneasca monitor_reports intr-un alt proces copil.

Pentru comunicarea dintre hub_mon si monitor_reports am folosit pipe(). Output-ul monitorului este redirectionat cu dup2() catre pipe, iar hub_mon citeste mesajele si le afiseaza in terminal.

Am modificat monitor_reports astfel incat mesajele afisate sa aiba un format mai usor de interpretat:

INFO|Monitor started
EVENT|New report added
ERROR|Monitor already running
EXIT|Monitor shutting down

Acest format ajuta city_hub sa observe cand monitorul porneste, cand primeste un eveniment, cand exista deja un monitor pornit si cand monitorul se opreste.

Tot in Phase 3 am implementat comanda:

calculate_scores <list_of_districts>

Pentru aceasta comanda am folosit AI ca ajutor pentru a intelege cum se porneste cate un proces scorer pentru fiecare district.

Programul scorer citeste reports.dat pentru un district si calculeaza pentru fiecare inspector scorul total, adica suma nivelurilor de severitate ale rapoartelor facute de acel inspector.

city_hub creeaza cate un pipe pentru fiecare scorer, foloseste dup2() pentru a redirectiona output-ul scorerului catre pipe si apoi citeste rezultatele pentru a afisa un raport combinat.


-Debugging

In Phase 2 si Phase 3 am utilizat AI mai mult pentru debugging.

L-am folosit pentru:

-verificarea functionalitatii monitorului
-rezolvarea problemelor legate de transmiterea semnalelor
-verificarea comenzii remove_district
-testarea functionalitatilor implementate
-identificarea erorilor aparute in timpul rularii
-verificarea comunicarii prin pipe dintre city_hub si monitor_reports
-verificarea redirectarii cu dup2()
-verificarea comenzii calculate_scores
-verificarea programului scorer

AI-ul m-a ajutat sa identific mai rapid problemele si sa verific daca implementarea respecta cerintele proiectului.


-Ce a generat AI-ul si ce am modificat

AI-ul a fost folosit in special pentru exemple si explicatii.

Pentru Phase 1, AI-ul a generat idei pentru parse_condition() si match_condition(), dar codul a fost verificat si adaptat la structura Report din proiect.

Pentru Phase 2, AI-ul a explicat cum se folosesc fork(), exec(), wait(), sigaction() si kill(), iar implementarea a fost adaptata la city_manager si monitor_reports.

Pentru Phase 3, AI-ul a explicat cum se folosesc pipe() si dup2() pentru comunicarea intre procese. Codul a fost adaptat pentru city_hub, monitor_reports si scorer.

Am verificat manual codul si am testat comenzile principale pentru a ma asigura ca programele functioneaza impreuna.


-Observatii personale

Utilizarea AI-ului a facut implementarea mai rapida si mai usor de realizat.

In special in Phase 2 si Phase 3 a fost util pentru intelegerea conceptelor noi: procese, semnale, pipe-uri si redirectari.

AI-ul nu a inlocuit intelegerea proiectului, deoarece a fost necesar sa verific raspunsurile, sa adaptez codul la fisierele existente si sa testez functionalitatile manual.

Nu au existat probleme majore in utilizarea ChatGPT PRO.
