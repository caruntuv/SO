Raport privind utilizarea inteligentei artificiale

-AI ales
Pentru implementarea functionalitatii de filtrare a rapoartelor am utilizat ChatGPT PRO.

-Scopul utilizarii AI
Conform cerintei din proiect, AI-ul a fost utilizat pentru implementarea functiilor:
parse_condition()
match_condition()

Acestea sunt folosite pentru interpretarea si evaluarea conditiilor introduse de utilizator in comanda filter.

-Prompt-uri utilizate
Am formulat cerinte de tipul:
„Genereaza o functie in C care parseaza un string de forma field:operator:value”
„Genereaza o functie care verifica daca un raport respecta o conditie pe baza campurilor sale”
Cod generat de AI

parse_condition()
Functia separa un string de forma:
severity:>=:2

in trei componente:
field = "severity"
operator = ">="
value = "2"

Implementarea foloseste functia strtok().

match_condition()
Functia verifica daca un obiect de tip Report respecta o conditie data.

identifica campul (severity, category, inspector, timestamp)
converteste valoarea la tipul necesar
aplica operatorul de comparatie

-Integrarea in aplicatie

Functiile au fost integrate in functia:
filter_reports()

Aceasta:
citeste fiecare raport din fisierul binar
aplica conditiile introduse de utilizator
afiseaza doar rapoartele care respecta toate conditiile

-Observatii personale

Utilizarea AI-ului a facut implementarea acestei parti mai rapida si mai usor de realizat.

Functiile generate au fost corecte si au oferit o baza buna de lucru. Integrarea lor in proiect nu a fost dificila, insa a fost necesara intelegerea modului in care functioneaza si adaptarea la structura aplicatiei(schimbari in main-ul aplicatiei).
