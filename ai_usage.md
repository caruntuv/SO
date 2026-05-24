Raport privind utilizarea inteligentei artificiale - Phase 1

Pentru Phase 1 am utilizat ChatGPT PRO ca ajutor pentru functiile de filtrare:

- parse_condition()
- match_condition()

Prompturile principale au fost:

- Genereaza o functie in C care parseaza o conditie de forma field:operator:value.
- Genereaza o functie care verifica daca un raport respecta o conditie.

Structura explicata catre AI a fost Report, cu campurile id, inspector, latitude,
longitude, category, severity, timestamp si description.

Codul generat a fost verificat si adaptat astfel incat:

- severity si timestamp sunt comparate numeric
- category si inspector sunt comparate ca string-uri
- operatorii ==, !=, <, <=, > si >= sunt tratati in functie de tipul campului
- conditiile invalide sunt respinse

Logica principala a comenzii filter a fost integrata manual in city_manager:
fisierul reports.dat este deschis, rapoartele sunt citite pe rand cu read(), fiecare
conditie este parsata si raportul este afisat doar daca respecta toate conditiile.

Mai multe detalii despre folosirea AI in toate fazele sunt in:

- AI_usage-phases_1_and_2.md
- AI_usage-ALL-phases.md
