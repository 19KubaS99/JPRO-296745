                                                         GRA W ŻYCIE
                                                         
Symulacja odbywa się zgodnie z zasadami Johna Conwaya:
- martwa komórka, która ma dokładnie 3 żywych sąsiadów, staje się żywa w następnej jednostce czasu (rodzi się)
- żywa komórka z 2 albo 3 żywymi sąsiadami pozostaje nadal żywa; przy innej liczbie sąsiadów umiera (z „samotności” albo „zatłoczenia”)

Intrukcja obługi:
1) Pobierz plik main.c oraz config.txt
2) Skompiluj plik main.c na maszynie linuxowej lub pod systemem windows (uwaga wymagany jest kompilator działający w standardzie C99!)
3) W pliku config.txt ustaw parametry symulacji:
-wybierz czy początkowe rozmieszczenie komórek ma być losowe czy zdefiniowane w polach na końcu pliku. Jeżeli rozmieszczenie ma być losowe 
wstaw literę 'y' przy przełączniku "random[y/n]:". Jeżeli ma być zdefiniowane przez użytkownika wstaw literę n a następnie wypełnij plasznę
zgodnie z zasadą 'X' - dla żywej komórki oraz '.' - dla martwej komórki. Program nie odczyta innego znaku, dlatego zwróć uwagę czy użyłeś
jedynie znaków 'X' lub '.'
- w parametrze "degree of compaction:" podaj wartość zagęszczenia żywych komórek (od 1 do 9) w przypadku gdy korzystasz z losowego ustawienia początkowego.
Nawet jeśli początkowe ustawienie jest zdefiniowane przez użytkownika parametr ten nigdy nie powinien zostać pusty.
- w parametrze "number of steps:" podaj ile kolejnych generacji komórek ma wykonać symulacja.
- w parametrze "step time:" podaj przez jaki okres czasu (w sekundach) ma być wyświetlana pojedyńcza generacja komórek. Zalecana wartość to 0.3
4) Uruchom skompilowany wcześniej program, po zakończeniu symulacji zostanie utworzony plik data.txt w którym znajdują się następujące dane:
- alive - reprezentuje ilość żywych komórek w danej generacji,
- dead - reprezentuje ilość martwych komórek w danej generacji,
- born - reprezentuje ilość nowo narodzonych komórek w danej generacji,
- deceased - reprezentuje ilość komórek, które zmarły w danej generacji.
Każdy wiersz to kolejna generacja komórek.

W repozytorium znajduje się także przykładowy plik example_config.txt wraz z omówieniem.


Po więcej informacji odsyłam do wpisu o grze na wikipedii: https://pl.wikipedia.org/wiki/Gra_w_%C5%BCycie


