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
Jag har skrivit en egen I2C-driver. Genom att skicka bit för bit som styrs av SCL, exempel: SCL 1 betyder läs bit, SCL 0 betyder invänta SCL 1. Vid SCL 0 ändrar man/håller kvar HIGH eller LOW på SDL, om SDL exempelvis är HIGH och SCL går HIGH så sparar LCDn den biten i sitt minne.

När det gäller scrollande text så delar jag upp texten ifall den är längre än LCD-display med hjälp av null-terminators. Så t.ex om text > lcd-längd, gå tillbaka tills mellanslag hittat, sätt \0 istället för mellanslag, och sen repetera så många gånger det behövs.
Sedan vid utskrift så skannar jag bara efter \0 för att veta när man ska bryta och sedan skriva ut nästa stycke.

Tankar på förbättringar:
Jag har använt mig av magic numbers, tyvärr så det är något jag måste tänka mer på i framtiden, en annan sak är också att vissa variabelnamn var otydliga. Jag använde mig av alldeles för lite variabler/macros speciellt i I2C drivern (lcd-screen.h/c), där kunde jag t.ex ge alla LCD kommandon namn istället för att det ska vara magic numbers/ magic masks.

Jag skulle säkert faila väldigt hårt på ett MISRA test, så jag startar inte ens den! Skulle ta mig säkert en vecka att ha allt korrekt, MINST!
Men det är något jag vill bli bättre på snarast.
Om man kollar i ad-displayer.h så kan det tyckas konstigt att jag har en array[MACRO_MAX_SIZE + 2]   men det är av anledningen så att jag kan få plats med 2 null-terminators. Det skulle kunna vara väldigt förvirrande för en annan kodare, kanske det är något som är emot all praxis?

Joakim: Om du har frågor om min kod och det är något du inte förstår, vill kolla om jag förstår eller vill bara skrika vilken förjävlig kod! Tveka inte att kontakta mig så reder vi ut det!



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
