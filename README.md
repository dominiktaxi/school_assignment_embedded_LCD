För att kompilera krävs att ESP-IDF är installerat.
För att bygga kommando: idf.py build
För att flasha        : idf.py flash
För monitor           : idf.py monitor
eller allt på en gång : idf.py build flash monitor

För att kunna simulera i wokwi: använd bin filen som genereras med idf.py build.


Applikationen genererar och visar reklamtext baserat på företagens betalningsnivå. Texten väljs enligt definierade randomiseringsregler.

Visningslägen:

Skrollande text
Blinkande text
Statisk text

Randomiseringsmetoder:

Slumpmässigt (Random)
Baserat på jämna/ojämna minuter

Om texten i statiskt eller blinkande läge överskrider LCD-skärmens visningsbredd delas den upp i segment. Dessa segment visas sekventiellt (första → … → sista) med automatisk växling.

Allt minne sker i stacken. De stora textvariablerna initialiseras och lever på stacken i .data segmentet.



Filer:
inlUppgift.c -> mainfilen, härifrån körs setup som också kör application.
setup.h/c -> Här sätts alla företagsnamn, hur mycket varje företag betalat, vilken reklamtext och hur reklamen ska visas, sedan startar loopen i setup_run.

application.h/c -> application styr tid, randomiserar företag och styr alla andra filer.

company-manager.h/c -> Ansvarar för urvalslogik av företag. 
Använder company-storage för data och implementerar viktad slump baserat på betalning samt valt visningsmönster.

company-storage.h/c -> Lagrar alla företag i en intern array. Ansvarar för kapacitet, dubblettkontroll och summering av total betalning.

ad-displayer.h/c -> Ansvarar för hur företagets namn och reklamtext visas på LCD-skärmen. Hanterar skrollande, blinkande och statisk text samt uppdelning av text som är för lång för skärmen.

lcd-screen.h/c -> Sköter kommunikationen med LCD-skärmen via I2C. Innehåller initiering av skärmen, rensning av displayen och utskrift av text.

error-handler.h/c -> Skriver ut felmeddelanden baserat på statuskoder för att underlätta felsökning.

status.h -> Innehåller projektets statuskoder, till exempel SUCCESS, FAILED, OUT_OF_SPACE och DUPLICATE.

macros.h -> Innehåller projektgemensamma konstanter som max antal företag, maxlängd på namn/reklamtext samt vilka GPIO-pinnar som används för LCD-kommunikation.

companies.h/c -> Innehåller datastrukturer för företag och reklamdata, samt enums som representerar hur reklamen ska visas och randomiseras
