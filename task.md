# Ukol

- najit unikatni, dat uzivateli moznost rozhodnout o akci (tmp, smazat, ponechat)
- navolit adresare
  - navrh: yaml

## struktura YAMLu

- directories
  - list adresaru, ktere maji byt prohlizeny a kontrolovany
- action
  - rozhodnuti o uzivatelske akci
  - **4 stavy**
    1. **tmp** - presunout do uzivatelem definovaneho adresare
    2. **erase** - vymazat (musi schvalit uzivatel)
    3. **keep** - ponechat beze zmeny
    4. *(nice to have) **ignore** - ignorovat, potlacit barvu, ukazat samostatne a po zadani --ignored flagu*

* significant
  * pocet znaku, ktere jsou dulezite pro rozpoznani
* ignored
  * ignorovane file extensions
