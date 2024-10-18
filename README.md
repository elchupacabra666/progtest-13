# Intervaly

**Hodnocení**: 5.0 bodů (MAXIMÁLNĚ 10.8), pokud v Progtestu vidíte 11.88, je to včetně včasného odevzdání, které se do těchto statistik neuvádí.

**Termín odevzdání**: 10.04.2023 11:59:59

---

## Zadání

Úkolem je realizovat třídy `CRange` a `CRangeList`, které budou reprezentovat celočíselné intervaly a jejich seznamy.

### CRange

- **Intervaly celých čísel**: Interval může obsahovat pouze jedno číslo, nebo více čísel. 
  - Jednoprvkové intervaly se zapisují jako jedno číslo (např. `42`).
  - Víceprvkové intervaly se zapisují v lomených závorkách (např. `<1..5>` obsahuje čísla 1, 2, 3, 4, 5).
- **Typ proměnných**: CRange ukládá meze intervalu jako `long long`, protože chceme pracovat s velkým rozsahem čísel a se zápornými hodnotami.
- **Konstruktor**: `CRange(lo, hi)`
  - Inicializuje instanci na interval v rozsahu `lo` až `hi`. 
  - Pokud podmínka `lo ≤ hi` není splněna, je vyhozena výjimka `std::logic_error`.
- **Rozhraní**: Další rozhraní odvoďte z ukázkového kódu. Můžete přidat další metody dle potřeby, ale dodržujte maximální velikost instance (max. 2x velikost `long long`).

### CRangeList

Třída `CRangeList` reprezentuje seznam intervalů, které musí být ukládány co nejkompaktněji.

- **Seznamy intervalů**: Sousedící nebo překrývající se intervaly sloučíme do jednoho delšího intervalu. Např.:
  - `<10..20>` a `<15..30>` se sloučí na `<10..30>`.
  - Intervaly `<10..20>` a `<21..30>` se sloučí, protože pokrývají celý interval `<10..30>`.
  - Intervaly `<10..19>` a `<21..30>` se už ale nesloučí, protože nepokrývají číslo `20`.

#### Rozhraní CRangeList:

- **Implicitní konstruktor**: Inicializuje prázdný seznam intervalů.
- **Kopírování a přesun**: Pokud je potřeba, implementujte destruktor, kopírovací konstruktor a operátor přiřazení (`op=`).
- **includes(long long) / includes(CRange)**: Zjišťuje, zda seznam intervalů obsahuje zadanou hodnotu nebo celý zadaný interval.
  - Pokud ano, vrací `true`, jinak `false`.
- **+= operátor**: Přidává další intervaly do seznamu, slučuje sousedící nebo překrývající se intervaly.
- **-= operátor**: Odebírá intervaly ze seznamu, implementuje množinový rozdíl, ukládá kompaktně.
- **Operátory `==` a `!=`**: Porovnávají obsah dvou instancí. Dvě instance jsou shodné, pokud mají identický seznam intervalů.
- **<< operátor**: Výstupní operátor, který zobrazí obsah seznamu ve složených závorkách. 
  - Jednotlivé intervaly jsou odděleny čárkou.
  - Jednoprvkové intervaly jsou zobrazené jako číslo, delší intervaly pak v lomených závorkách.
  - Intervaly musí být zobrazeny seřazené vzestupně.

### Bonusové testy

Úloha nabízí bonusový test s následujícími požadavky:

- **Bonus 1**: Implementace rozhraní pro snadnější práci se seznamem intervalů.
- **Bonus 2**: Rychlejší než lineární řešení pro operace `includes`.
- **Bonus 3**: Rychlejší než lineární řešení pro operace vkládání a mazání intervalů.

Pokud nechcete implementovat rozšířené rozhraní pro bonusový test, nechte direktivu preprocesoru `EXTENDED_SYNTAX` v komentáři.

---

## Nápověda

- **Operátor pro výstup**: Bez správně fungujícího operátoru bude Vaše řešení hodnoceno velmi nízko.
- **Optimalizace operátorů**: Operátory `+=` a `-=` musí správně fungovat i se seznamem intervalů na pravé straně.
- **Kontejnery**: Můžete použít `std::vector`, `std::list`, a `std::string`. Ostatní kontejnery z STL nejsou dostupné.
- **Mezní hodnoty**: V testu jsou zadávané intervaly s počátky a konci `LLONG_MIN` a `LLONG_MAX`.

---

## Ukázka použití

```cpp
CRange a(10, 20);
CRangeList l;
l += a;
l -= CRange(15, 18);
std::cout << l << std::endl;  // Výstup: {10..14, 19..20}
```

---

**Poznámka**: Odevzdávejte zdrojový soubor bez hlavičkových souborů a funkcí `main`. V případě potřeby je můžete vložit do bloku podmíněného překladu.
